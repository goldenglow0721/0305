#include "sleep_mode.h"
#include "at32f403a_407.h" 
#include "clock_manage.h"
#include "battery_manage.h"
#include "audio_manage.h"

void rtc_config(void)
{
  exint_init_type exint_init_struct;

  /* config the exint line of the rtc alarm */
  exint_init_struct.line_select   = EXINT_LINE_17;
  exint_init_struct.line_enable   = TRUE;
  exint_init_struct.line_mode     = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);

  /* enable the battery-powered domain write operations */
  pwc_battery_powered_domain_access(TRUE);

  /* reset battery-powered domain register */
  bpr_reset();

  /* enable the lick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);

  /* wait lick is ready */
  while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);

  /* select the rtc clock source */
  crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);

  /* enable rtc clock */
  crm_rtc_clock_enable(TRUE);

  /* wait for rtc registers update */
  rtc_wait_update_finish();

  /* set rtc divider: set rtc period to 1sec */
  rtc_divider_set(32767);

  /* wait for the register write to complete */
  rtc_wait_config_finish();

  /* enable alarm interrupt */
  rtc_interrupt_enable(RTC_TA_INT, TRUE);

  /* wait for the register write to complete */
  rtc_wait_config_finish();

  /* configure and enable rtc alarm interrupt */
  nvic_irq_enable(RTCAlarm_IRQn, 0, 0);
}


void go_to_sleep_mode(void)
{
	 /* enable pwc and bpr clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
	
  rtc_config();

}


void set_sysclk_low_power(void)
{
	
 /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

   /* wait till HICK is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) == RESET)
  {
  }

	//��pll��ֻ��4M
  /* config pll clock resource */
   crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_2, CRM_PLL_OUTPUT_RANGE_LE72MHZ);
   //4*2 = 8MHZ

 
  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 120 MHz */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 120 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}





/* ʡ��ģʽ */

void enable_pwc_clk(void)
{
	/* enable pwc clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
	
   //�Ӵ���״̬����
  if(pwc_flag_get(PWC_STANDBY_FLAG) != RESET)
  {
      /* wakeup from standby */     
      pwc_flag_clear(PWC_STANDBY_FLAG);
	  
	  NVIC_SystemReset();
  }
  
   //�����¼�
  if(pwc_flag_get(PWC_WAKEUP_FLAG) != RESET)
  {
      /* wakeup event occurs */
      pwc_flag_clear(PWC_WAKEUP_FLAG);
	  
      //NVIC_SystemReset();
  }
  
  /* enable wakeup pin ���û�������*/
   pwc_wakeup_pin_enable(PWC_WAKEUP_PIN_1, TRUE);

}

/* ����ģʽ��������ʼ�� */
void standby_mode_peripheral_deinit(void)
{
	//MOTOR-PW  PB9����
	
	//BAT-LOW   PC2����
	
	//UR3_TX   PD8  ����
	
	//UR3_RX   PD9  ����
	
	//HX712-DOUT  PB1  ����
	
	//HX712-SCK   PB0  ����
	
	//T-CS  PB7  �ߵ�ƽ
	
	//DCLK  PB3 ����
	
	//PC11/UART4_RX  ����
	
	//PC10/UART4_TX  ����
	
	//BTL_CTRL PA6  ���� 
	
	// PC8 PA15����
	
	//pb10 pb11����
	
	gpio_init_type  gpio_init_struct = {0}; 
	
	/*enable the gpio click*/ 	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE); 	
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE); 	
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE); 	
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE); 	
	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE); 	
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE); 	
	
	/* PC 1 2,10,11 ���� */ 	
	gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_2|GPIO_PINS_10|GPIO_PINS_11; 	
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT; 	 
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE; 	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;  
	gpio_init(GPIOC, &gpio_init_struct); 

//	/* PA6 ���� */ 	
//	gpio_init_struct.gpio_pins = GPIO_PINS_6;
//	gpio_init(GPIOA, &gpio_init_struct); 
	
	/* PB3  PB10 PB11 ���� */ 	 	
	gpio_init_struct.gpio_pins = GPIO_PINS_3|GPIO_PINS_10|GPIO_PINS_11; 
	gpio_init(GPIOB, &gpio_init_struct); 
	
	/* PD8 PD9  ���� */ 	
	gpio_init_struct.gpio_pins = GPIO_PINS_8|GPIO_PINS_9; 
	gpio_init(GPIOD, &gpio_init_struct); 
	
	//PB9 �͵�ƽ
	gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_1|GPIO_PINS_9;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT; 	
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL; 
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE; 
	gpio_init(GPIOB, &gpio_init_struct); 
	gpio_bits_set(GPIOB,GPIO_PINS_9);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_8|GPIO_PINS_13;  
	gpio_init(GPIOC, &gpio_init_struct); 
	gpio_bits_write(GPIOC,GPIO_PINS_13,0);
		
	gpio_init_struct.gpio_pins = GPIO_PINS_15;   
	gpio_init(GPIOA, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_15;   
 	gpio_init(GPIOB, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_7|GPIO_PINS_8|GPIO_PINS_9|GPIO_PINS_10;  
   	gpio_init(GPIOE, &gpio_init_struct);
	
	gpio_bits_write(GPIOB,GPIO_PINS_9,0);
	gpio_bits_write(GPIOB,GPIO_PINS_15,1);
	
	gpio_bits_write(GPIOE,GPIO_PINS_7,0);
	gpio_bits_write(GPIOE,GPIO_PINS_8,0);
	gpio_bits_write(GPIOE,GPIO_PINS_9,0);
	gpio_bits_write(GPIOE,GPIO_PINS_10,0);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_1|GPIO_PINS_14|GPIO_PINS_15;  
   	gpio_init(GPIOD, &gpio_init_struct);
	gpio_bits_write(GPIOD,GPIO_PINS_0,0);
 	gpio_bits_write(GPIOD,GPIO_PINS_1,0);	
	gpio_bits_write(GPIOD,GPIO_PINS_14,0);
	gpio_bits_write(GPIOD,GPIO_PINS_15,0);
	

//	gpio_bits_write(GPIOC,GPIO_PINS_8,0);
//	gpio_bits_write(GPIOA,GPIO_PINS_15,0);
	
	//PB7 �ߵ�ƽ
	gpio_init_struct.gpio_pins = GPIO_PINS_7;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT; 	
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL; 
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE; 
	gpio_init(GPIOB, &gpio_init_struct); 
	gpio_bits_set(GPIOB,GPIO_PINS_7);

	gpio_bits_write(GPIOB,GPIO_PINS_7,1);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_6;   
  	gpio_init(GPIOA, &gpio_init_struct);
	gpio_bits_write(GPIOA,GPIO_PINS_6,1);
	
	
}


void at32_button__init(void)
{
  gpio_init_type gpio_init_struct;

  /* enable the button clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure button pin as input with pull-up/pull-down */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_0;
  gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
  gpio_init(GPIOA, &gpio_init_struct);
}



void rtc_config_(void)
{
  /* enable the battery-powered domain write operations */
  pwc_battery_powered_domain_access(TRUE);

  /* reset battery-powered domain register */
  bpr_reset();

  /* enable the lick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);

  /* wait lick is ready */
  while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);

  /* select the rtc clock source */
  crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);

  /* enable rtc clock */
  crm_rtc_clock_enable(TRUE);

  /* wait for rtc registers update */
  rtc_wait_update_finish();

  /* set rtc divider: set rtc period to 1sec */
  rtc_divider_set(32767);

  /* wait for the register write to complete */
  rtc_wait_config_finish();
}


void rtc_alarm_config(uint8_t alarm_time)
{
  /* clear second flag */
  rtc_flag_clear(RTC_TS_FLAG);

  /* wait for the second flag to be set */
  while(rtc_flag_get(RTC_TS_FLAG) == RESET);

  /* config the wakeup time */
  rtc_alarm_set(rtc_counter_get() + alarm_time);

  /* wait for the register write to complete */
  rtc_wait_config_finish();
}


//DC
#define DC_Detection 		gpio_input_data_bit_read(GPIOC,GPIO_PINS_1)         
//AC
#define AC_Detection		gpio_input_data_bit_read(GPIOC,GPIO_PINS_2)          

#define BatteryStatus_Detection       gpio_input_data_bit_read(GPIOE,GPIO_PINS_3)

//BAT-LED      PC8     
//AC-LED       PA15    
//M4-RLED      PA3    
//ARM-MCU-YLED PA2

void io_deinit(void)
{
 	gpio_init_type  gpio_init_struct = {0};
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_15;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_8;
	gpio_init(GPIOC, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_2|GPIO_PINS_3;
	gpio_init(GPIOA, &gpio_init_struct);
	
//	gpio_init_struct.gpio_pins = GPIO_PINS_15;
//	gpio_init(GPIOB, &gpio_init_struct);
		
	gpio_bits_write(GPIOA,GPIO_PINS_15,TRUE);	
	gpio_bits_write(GPIOC,GPIO_PINS_8,false);

	gpio_bits_write(GPIOA,GPIO_PINS_2,false);	
	gpio_bits_write(GPIOC,GPIO_PINS_3,false);
	
//	gpio_bits_write(GPIOB,GPIO_PINS_15,false);	
}


//设置 PE3 输入上拉
void status_io(void)
{
	gpio_init_type  gpio_init_struct = {0};
	
	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOE, &gpio_init_struct);
}



/* 
  使用状态脚检测 
  
  DC_Detection为低电平时候


*/


/* pc2浮空输入 */
void bat_low_Floated_input(void)
{
	


}


void  rtc_weak_up_process(void)
{
    gpio_bat_control(true);   //此处打开会增加功耗，不打开无法检测电池是否脱落
	gpio_bat_init(1);
//	io_deinit();
//	BUZZER_control(false);
	for(int i = 0; i<=220; i++);
		
	if(DC_Detection || AC_Detection )
	 {	
	     gpio_bat_control(false);		
	 }
	else{ 	
         gpio_bat_control(false);		
         beep_init(2);		
		 BeepStart();  		
    }
}

extern void weak_up(void);


void key_weak_up_process(void)
{
	 weak_up();       	
}


extern void key_gpio_init(void);


void low_power_consumption(void)
{	
	system_clock_config(USE_1MHZ); 
	
	key_gpio_init();
	
	/* config priority group */
//    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	
    /* enable pwc clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
	//RTC
	crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
		
    pwc_wakeup_pin_enable(PWC_WAKEUP_PIN_1, TRUE);
	
	 if(pwc_flag_get(PWC_STANDBY_FLAG) != RESET)
   {
    /* wakeup from standby */    
	   //rtc
	    if( SET == rtc_flag_get(RTC_TA_FLAG))
	  {		  	         	  
		  rtc_weak_up_process();
		  
	  }else{
	  	  
		  key_weak_up_process();	    
	  }	  	  
     pwc_flag_clear(PWC_STANDBY_FLAG);
   }

   if(pwc_flag_get(PWC_WAKEUP_FLAG) != RESET)
   {
     /* wakeup event occurs */	 
     pwc_flag_clear(PWC_WAKEUP_FLAG);	
   }
   
//   gpio_bat_control(false);
   
   rtc_config_();
   
   rtc_alarm_config(6);

    /* enter standby mode */
   pwc_standby_mode_enter();
}



