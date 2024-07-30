#include "bsp_usb.h"
#include "usbd_core.h"
#include "cdc_msc_class.h"
#include "cdc_msc_desc.h"
#include "usbd_int.h"
#include <stdio.h> 
#include <stdarg.h>
#include "fatfs_history.h"

usbd_core_type usb_core_dev;
uint8_t usb_buffer[256];

/**
  * @brief  usb 48M clock select
  * @param  clk_s:USB_CLK_HICK, USB_CLK_HEXT
  * @retval none
  */
void usb_clock48m_select(usb_clk48_s clk_s)
{
  if(clk_s == USB_CLK_HICK)
  {
    crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

    /* enable the acc calibration ready interrupt */
    crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

    /* update the c1\c2\c3 value */
    acc_write_c1(7980);
    acc_write_c2(8000);
    acc_write_c3(8020);

    /* open acc calibration */
    acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
  }
  else
  {
    switch(system_core_clock)
    {
      /* 48MHz */
      case 48000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1);
        break;

      /* 72MHz */
      case 72000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1_5);
        break;

      /* 96MHz */
      case 96000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2);
        break;

      /* 120MHz */
      case 120000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2_5);
        break;

      /* 144MHz */
      case 144000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3);
        break;

      /* 168MHz */
      case 168000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3_5);
        break;

      /* 192MHz */
      case 192000000:
        crm_usb_clock_div_set(CRM_USB_DIV_4);
        break;

      default:
        break;

    }
  }
}


void usb_msc_cdc_config(void)
{
  /* select usb 48m clcok source */
  usb_clock48m_select(USB_CLK_HICK);

  /* enable usb clock */
  crm_periph_clock_enable(CRM_USB_PERIPH_CLOCK, TRUE);

  /* enable usb interrupt */
  nvic_irq_enable(USBFS_L_CAN1_RX0_IRQn, 0, 0);

  /* usb core init */
  usbd_core_init(&usb_core_dev, USB, &cdc_msc_class_handler, &cdc_msc_desc_handler, 0);

  /* enable usb pull-up */
  usbd_connect(&usb_core_dev);
}


void usb_cdc_test(void)
{	
	static uint16_t data_len;  
	static uint32_t timeout;  
	static uint8_t send_zero_packet = 0;
	
    /* get usb vcp receive data */
    data_len = usb_vcp_get_rxdata(&usb_core_dev, usb_buffer);

    if(data_len > 0 || send_zero_packet == 1)
    {
      /* bulk transfer is complete when the endpoint does one of the following
         1 has transferred exactly the amount of data expected
         2 transfers a packet with a payload size less than wMaxPacketSize or transfers a zero-length packet
      */
      if(data_len > 0)
        send_zero_packet = 1;

      if(data_len == 0)
        send_zero_packet = 0;

      timeout = 5000000;
      do
      {
        /* send data to host */
        if(usb_vcp_send_data(&usb_core_dev, usb_buffer, data_len) == SUCCESS)
        {
          break;
        }
      }while(timeout --);
    }
}


void usb_cbc_send_data_test(void)
{
  uint8_t buff[20] = "usb cdc test\r\n";
  usb_vcp_send_data(&usb_core_dev, buff, sizeof(buff));
}


void usb_dis_connect(void)
{
  usbd_disconnect(&usb_core_dev);
}
	

void USBFS_L_CAN1_RX0_IRQHandler(void)
{
  usbd_irq_handler(&usb_core_dev);
}

#define USB_PRINT_BUFFER_SIZE 256

void usb_print(const char *format, ...)
{
    char buffer[USB_PRINT_BUFFER_SIZE];
    va_list args;
    int length;

    // 格式化字符串
    va_start(args, format);
    length = vsnprintf(buffer, USB_PRINT_BUFFER_SIZE, format, args);
    va_end(args);

    // 确保字符串不会超出缓冲区
    if (length > USB_PRINT_BUFFER_SIZE - 1) {
        length = USB_PRINT_BUFFER_SIZE - 1;
    }

     // 通过 USB CDC 发送数据
	 usb_vcp_send_data(&usb_core_dev, (uint8_t *)buffer, length);
}


void usb_hardware_connect_init(void)
{
	gpio_init_type  gpio_init_struct = {0};
 
    /* enable the gpio clock */
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	  
	gpio_init_struct.gpio_pins = GPIO_PINS_14;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
}

typedef enum usb_hard_connect_state{
	usb_hard_connect,
	usb_hard_disconnect
}usb_hard_connect_state;


usb_hard_connect_state read_usb_state(void)
{
   if(gpio_input_data_bit_read(GPIOA,GPIO_PINS_14))
   {
     return usb_hard_connect;
	   
   }else{
	   
     return usb_hard_disconnect;
   }
}

static uint8_t usb_states_flag;

void usb_config_process(void)
{
	static uint32_t count;
	
	
	if( usb_hard_connect == read_usb_state())
	{	
       if(usb_states_flag == 0)
	   {
         write_history_to_fatfs(); //写历史记录至文件系统 					   
	     usb_msc_cdc_config();	        
		 usb_states_flag = 1;
	   }
      	   
	}else{
		if(usb_states_flag ==1)
		{
		  usb_dis_connect();
		  usb_states_flag =0;	
		}	  
	}
}





