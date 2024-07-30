#include "HX711.h"
#include "UltraSonic.h"
#include "battery_manage.h"
#include "motor_manage.h"
#include "audio_manage.h"
#include "init_manage.h"
#include "gpio_manage.h"
#include "clock_manage.h"
#include "timer_manage.h"
#include "OptoCoupler_manage.h"
#include "rtc.h"
#include "voltage_detection.h"
#include "bsp_usb.h"



Battery_Status battery_status = 
{
  0,
  0
};



void sys_init(void)
{
	delay_init();
	led_gpio_init();
	key_gpio_init();
	power_button_exint_init();
	gpio_HX711_init();
	uart_print_init(115200);
	uart4_config(9600);
	gpio_switch_init();
	gpio_bat_control(true);
	gpio_bat_init(2);
	audio_gpio_init();
	tmr4_init();
//	OptoCoupler_init();
	motor_init();
	beep_init(1);
	ultrasonic_init();
	usb_hardware_connect_init();
	
		
	
	/* 电压检测 */
//	chip_voltage_detection();
//  chip_voltage_detection_dma_config();
	
//	exint_line1_config();
//  exint_line2_config();
	
//	vtaskmanage(1);
	{
		calendar_type time_struct;
		/* config calendar */
		time_struct.year  = 2024;
		time_struct.mon = 1;
		time_struct.day  = 1;
		time_struct.hour  = 12;
		time_struct.min   = 30;
		time_struct.sec   = 0;
		
		rtc_init(&time_struct);
	}
	
}




























