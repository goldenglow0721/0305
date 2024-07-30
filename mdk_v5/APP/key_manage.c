#include "key_manage.h"
#include "at32f403a_407_gpio.h"
#include "motor_manage.h"
#include "battery_manage.h"
#include "audio_manage.h"
#include "infusion.h"
#include "protocol.h"
#include "ui.h"
#include "FreeRTOS.h"
#include "task.h"

extern __IO  uint8_t   DeviceFlag;
extern TaskHandle_t lvgl_handler;
extern void app_jump_to_bootloader();
extern void app_clear_sys_status();
extern void lvgl_task_function(void *pvParameters);



void sendUpkeyDownMessageToLvgl(void)
{
	gt_event_send(gt_disp_get_scr(),MY_KEY_EVENT,"1");
}

void sendUpkeyLongDownMessageToLvgl(void)
{
	gt_event_send(gt_disp_get_scr(),MY_KEY_EVENT,"2");
}

void sendUpkeyUpMessageToLvgl(void)
{
	gt_event_send(gt_disp_get_scr(),MY_KEY_EVENT,"3");
}

void sendDownKeyDownMessageToLvgl(void)
{
	gt_event_send(gt_disp_get_scr(),MY_KEY_EVENT,"4");
}



extern __IO uint8_t   DeviceFlag;
bool PowerFlag;
void sendPowerKeyDownMessageToLvgl(void)
{
	if(DeviceFlag == DEVICE_STATUP)
	{
		gt_event_send(MainScreen,MY_EVENT_UPDATA,"999");		
	}
	else
	{
		#if 1
		/*system reset*/
//		if(PowerFlag == true)
//		{
//			taskENTER_CRITICAL();
//			/*create lvgl task*/
//			xTaskCreate(lvgl_task_function,"lvgl_task",1024,NULL,3,&lvgl_handler);
//			taskEXIT_CRITICAL();
//			vTaskStartScheduler(); 
//			gpio_bits_set(GPIOC,GPIO_PINS_13);	
//		}
//		else
//			NVIC_SystemReset();

//		gpio_bits_set(GPIOC,GPIO_PINS_13);
		
		#else
		crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		DeviceFlag = DEVICE_STATUP;
		gpio_bits_set(GPIOC,GPIO_PINS_13);
		delay_ms(10);
		vtaskmanage(2);
		#endif
	}
}

 
void sendPowerKeyLongDownMessageToLvgl(void)
{
	gt_event_send(gt_disp_get_scr(),MY_KEY_EVENT,"6");
}

