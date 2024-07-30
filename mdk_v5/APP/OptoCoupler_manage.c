#include "OptoCoupler_manage.h"
#include "at32f403a_407_board.h"




void OptoCoupler_init()
{
    gpio_init_type  gpio_init_struct={0};

    /* enable the usart2 and gpio clock */ 
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    //78 UART4_TX PC10
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);
    //79 UART4_RX PC11
    gpio_init_struct.gpio_pins = GPIO_PINS_11;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);

    /* configure usart2 param */
    usart_init(UART4,115200,USART_DATA_8BITS,USART_STOP_1_BIT);
    //发送使能
    usart_transmitter_enable(UART4, TRUE);
    //接收使能
    usart_receiver_enable(UART4, TRUE);
    usart_enable(UART4,TRUE);

    //usart_data_transmit(UART4,0x55);
}



void uart_receive_data_process(void (*fun1_callback)(void) , void (*fun2_callback)(void))
{ 
   while(usart_flag_get(UART4, USART_RDBF_FLAG) == RESET);
	
   if(usart_data_receive(UART4) == 0xAA)
   {
      //未检测到光耦
	  fun1_callback();
	   
   }else if(usart_data_receive(UART4) == 0x55)
   {
      //检测到光耦
	  fun2_callback(); 
   }
}















