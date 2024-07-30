#include "at32f403a_407_gpio.h"
#include "at32f403a_407_board.h"
#include "gpio_manage.h"

#include "alarm.h"


extern __IO uint8_t   DeviceFlag;


void led_gpio_init(void)
{
		gpio_init_type  gpio_init_struct = {0};
		/*enable the gpio click*/
		crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		/*gpio configuration*/
		gpio_init_struct.gpio_pins = GPIO_PINS_1;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		/*ARM-MCU-RLED*/
		gpio_init(GPIOA, &gpio_init_struct);
		gpio_bits_set(GPIOA,GPIO_PINS_1); 
		
		/*ARM-MCU-YLED*/
		gpio_init_struct.gpio_pins = GPIO_PINS_2;
		gpio_init(GPIOA, &gpio_init_struct);
		
		/*M4-RLED*/
		gpio_init_struct.gpio_pins = GPIO_PINS_3;
		gpio_init(GPIOA, &gpio_init_struct);
		
		/*BAT_LED*/
		gpio_init_struct.gpio_pins = GPIO_PINS_8;
		gpio_init(GPIOC, &gpio_init_struct);
		gpio_bits_set(GPIOC,GPIO_PINS_8); 
		
		/*AC_LED*/
		gpio_init_struct.gpio_pins = GPIO_PINS_15;
		gpio_init(GPIOA, &gpio_init_struct);
		gpio_pin_remap_config(SWJTAG_MUX_010, TRUE);
		gpio_bits_set(GPIOA,GPIO_PINS_15);
}


void key_gpio_init(void)
{
 gpio_init_type  gpio_init_struct = {0};
 
  /* enable the gpio clock */
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  // PB10 DOWN KEY
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOB, &gpio_init_struct);
	

	//PB11 UP KEY
  gpio_init_struct.gpio_pins = GPIO_PINS_11;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOB, &gpio_init_struct);

	//PA0 PWR KEY
  gpio_init_struct.gpio_pins = GPIO_PINS_0;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
//  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
//  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOA, &gpio_init_struct);
}

/**
  * @brief  powerkey
  * @param  none
  * @retval none
  */
void EXINT0_IRQHandler(void)     
{
	if((EXINT->intsts & EXINT_LINE_0) != RESET)   
	{
		EXINT->intsts = EXINT_LINE_0;
		
	}
}

/**
  * @brief  configure button exint(power PA0)
  * @param  none
  * @retval none
  */
void power_button_exint_init(void)
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOA, GPIO_PINS_SOURCE0);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_0;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);

  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT0_IRQn, 0, 0);
}



void led_control(int level)
{
    static int ledtime=0;
    extern _Bool LedDetection;
    switch(level)
    {
        if(DeviceFlag == DEVICE_STOP){break;}
        case 0:
        if(LedDetection = false)
        {
          led_off(ARM_RLED);
          led_off(ARM_YLED);
        }
          break;
        case H_ALARM: 
          led_turn(ARM_RLED);
          led_off(ARM_YLED);
          break;
        case M_ALARM:
          ledtime += 100;
          if(ledtime >= 400)
          {
            ledtime = 0;
            led_off(ARM_RLED);
            led_turn(ARM_YLED);
          }
          break;
        case L_ALARM:
          led_off(ARM_RLED);
          led_on(ARM_YLED);
          break;
        case T_ALARM:
          led_off(ARM_RLED);
          led_on(ARM_YLED);
          break;
        default:

          break;
    }

}




void gpio_switch_init()
{
  gpio_init_type  gpio_init_struct = {0};
 
  /* enable the gpio clock */
  crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);

  // PD10 switch 
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOD, &gpio_init_struct);

}




