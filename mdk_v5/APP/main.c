/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *       tmr1 2 6用于超声
  * 	  tmr12 用于pwm输出beep
  * 	  tmr3 用于电机
  *       tmr5用于ui  tmr13用于lcd背光亮度调节
  * 
  * 	  usart1用于串口打印  
  * 	  usart4用于与HC89F0421A沟通光耦信息
  * 	  usart6用于控制电机
  * 
  * 
  * 	  exint_line0 PA0 用于电源键产生外部中断  exint_line3 PE3 用来检测电池status 
  * 	  exint_line14 PB14 用于控制超声
													
  *
  **************************************************************************
  */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "at32f403a_407.h" 
#include "at32f403a_407_board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "define.h"
#include "clock_manage.h"
#include "timer_manage.h"
#include "init_manage.h"
#include "audio_manage.h"
#include "motor_manage.h"
#include "key_manage.h"
#include "battery_manage.h"
#include "bsp_lcd_xmc.h"
#include "HX711.h"
#include "bsp_qspi_flash.h"
#include "gt.h"
#include "ui.h"
#include "touch.h"
#include "vp_button.h"
#include "alarm.h"
#include "gpio_manage.h"

#include "my_flash.h"
#include "sleep_mode.h"
#include "voltage_detection.h"
#include "battery_manage.h"
#include "bsp_usb.h"


extern __IO uint16_t adc1_ordinary_valuetab[1]; 
extern __IO uint16_t vmor_flag_index;  //voltage monitor flag

TaskHandle_t hardware_handler;
TaskHandle_t lvgl_handler;
TaskHandle_t fast_handler;
    
/*hardware task*/
void hardware_task_function(void *pvParameters);
/*lvgl task*/
void lvgl_task_function(void *pvParameters);
/*fast task*/
void fast_task_function(void *pvParameters);


Button_t *UpButton;
Button_t *DownButton;
Button_t *PowerButton;


static _Bool poweron=true;

tp_dev_t *tp_dev;



__IO uint8_t   DeviceFlag=DEVICE_STATUP; 
__IO uint32_t  MotorRunFlag=MOTOR_STOP;
__IO uint32_t  ModeDeviceFlag=syringe; 
__IO uint32_t  WakeupTime=50;
static bool PowerFlag = false;


uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
	uint32_t ReadAddr;
	ReadAddr = *(data_write + 1) << 16;					//�߰�λ��ַ
	ReadAddr += *(data_write + 2) << 8;				//�а�λ��ַ
	ReadAddr += *(data_write + 3);						//�Ͱ�λ��ַ		
	spiflash_read(data_read, ReadAddr , len_read );
    return 1;
}


void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color)
{
		gt_size_t x=area->x,y=area->y;
		uint16_t w = area->w,h = area->h;
		uint32_t i = 0 , len = w*h;

		bsp_lcd_set_block(LCD_XMC_OFFSET_X + x, LCD_XMC_OFFSET_Y + y, LCD_XMC_OFFSET_X + x + w - 1, LCD_XMC_OFFSET_Y + y + h - 1);

		for(i = 0 ; i < len ; ++i)
		{
			bsp_lcd_write_2_data(color->full);
			color++;
		}

}

void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
	// GT_LOGD(GT_LOG_TAG_TP , "point in: x: %d , y: %d , state = %d\r\n", data->point.x , data->point.y , data->state);
#if 1
    if(!tp_dev->read_point()){
		data->state = GT_INDEV_STATE_RELEASED;
        data->point.x = tp_dev->point.x;
        data->point.y = tp_dev->point.y;
		return;
	}
#endif
    data->point.x = tp_dev->point.x;
	data->point.y = tp_dev->point.y;
	data->state = tp_dev->point.status == TP_STATE_RELEASED ? GT_INDEV_STATE_RELEASED : GT_INDEV_STATE_PRESSED;

	// GT_LOGD(GT_LOG_TAG_TP , "point: x: %d , y: %d , state = %d\r\n", data->point.x , data->point.y , data->state);
}

void read_cb_btn(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
    uint8_t status = 0;
	//status = KEY_Scan(1);
	if (status) {
		data->btn_id = status;
		data->state = GT_INDEV_STATE_PRESSED;
	}
	else {
		data->state = GT_INDEV_STATE_RELEASED;
	}
}




void exint_line1_config(void)
{
	exint_init_type exint_init_struct;

	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

	gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE1);		//网电源触发

	//gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE2);		//电池电源触发

	exint_default_para_init(&exint_init_struct);
	exint_init_struct.line_enable = TRUE;
	exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
	exint_init_struct.line_select = EXINT_LINE_1; 							//设置选择外部中断线1
	exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE; 			   //触发条件为下降沿和上升沿

	exint_init(&exint_init_struct);

	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(EXINT1_IRQn, 1, 0);
}



void weak_up(void)
{
		if(PowerFlag != true)
		PowerFlag = true;
	
	/* config vector table offset */
	nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x00000);
	
	system_clock_config(USE_240MHZ);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	
	__enable_irq();
		
//    usb_msc_cdc_config();  /* USB配置 */
		
	sys_init();

	Button_Process();
		
	taskENTER_CRITICAL();
	
	/*create task for hardware*/
	xTaskCreate(hardware_task_function,"hardware_task",512,NULL,2,&hardware_handler);

	xTaskCreate(lvgl_task_function,"lvgl_task",2048,NULL,4,&lvgl_handler);
	
	/*create fast task*/
	xTaskCreate(fast_task_function,"fast_task",512,NULL,3,&fast_handler);

	/* exit critical */
	taskEXIT_CRITICAL();

	//TMC2226_MotorRun(INFUSION_DEV,1,1,100);
	NowAlarmMessageinit();
	
	/* start  scheduler */
	vTaskStartScheduler(); 
}





/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void) 
{	
    //开机就进入低功耗，按键唤醒开机，RTC唤醒检测电源
    low_power_consumption();																																																																																											 		
}
	



/*hradware task function*/
void hardware_task_function(void *pvParameters)
{
	extern int GlevelOld;

	while(1)
	{	

		#if 0
		UBaseType_t freestack;
		freestack=uxTaskGetStackHighWaterMark(lvgl_handler);
		printf("task = %d\n",freestack);
		#endif

		//switch detect
		sensorpack.RightKnobStatus = !gpio_input_data_bit_read(GPIOD,GPIO_PINS_10);

		#if debug
		printf("switch = %d\n",sensorpack.RightKnobStatus);
		#endif

		//�ɼ�ѹ��ֵ
		sensorpack.DownPressure = Read_HX712_A()>>9;
		sensorpack.UpPressure = Read_HX712_B()>>9;

		#if debug
		printf("downpressure=%d\n",sensorpack.DownPressure);
		#endif
		
		//电池电量检测
		while(vmor_flag_index == 0);
		
//		if(BatteryStatus)
//			sensorpack.voltagevalue = 0;
//		else
			sensorpack.voltagevalue = getVoltageADCValue();
		#if 0
		WT588F_Send_Data(0x04);
		delay_ms(300);
		#endif
		
		//灯光报警检测
		//if(InfusionNow.alarmmsg != ALARM_MAX)
			led_control(GetNowAlarmLeve1l(&InfusionNow.glevel));
	

		vTaskDelay(1000);    
	}
}

extern uint8_t detection_motor_start_point_flag;

                                                                                                                                              
/*lvgl task function*/
void lvgl_task_function(void *pvParameters)
{
	pwc_voltage_regulate_set(PWC_REGULATOR_LOW_POWER);
	spiflash_init();
	bsp_lcd_xmc_init();
	tp_dev = touch_init();
	delay_ms(10);
	while(GT_Font_Init() == 0);
	gt_init();
	gt_ui_init();
	tmr5_init();
		
	/* 
	  usb msc与文件系统存在冲突 
	
	   测试：
	  1.usb虚拟u盘地址 与 文件系统地址 使用相同地址：0x08080000   只有第一次可以启动成功 系统复位不可用
	  2.usb虚拟u盘地址包括 文件系统地址  usb msc add:0x0807A000   disk fatfs address:0x08080000  系统复位不可用
	  3.文件系统地址包括USB虚拟u盘地址   usb msc add:0x08080000   disk fatfs address:0x0807A000  系统复位不可用
	
	 */
//	
//	my_test_fatfs("0:");   /* 内部flash */  
//	usb_msc_cdc_config();  /* USB配置 */	

	while(1)
	{
		gt_task_handler();
		
		/* 输液器是否脱落检测 */
		infusion_apparatus_detection();
		
		/* 输液器脱落处理 检测电机是否到达起始点 */
	    detection_motor_start_point_and_update_pressure();
		
//		usb_config_process();
				
		vTaskDelay(1);
	}
		
}



/*fast task function*/
void fast_task_function(void *pvParameters)
{
	//upkey init
	UpButton = (Button_t *)malloc(sizeof(Button_t));
	Button_Create("up",UpButton,(void *)at32_up_button_state,0);
	Button_Attach(UpButton,BUTTON_DOWM,(void *)sendUpkeyDownMessageToLvgl);
	Button_Attach(UpButton,BUTTON_LONG,(void *)sendUpkeyLongDownMessageToLvgl);
	Button_Attach(UpButton,BUTTON_UP,(void *)sendUpkeyUpMessageToLvgl);
	
	DownButton = (Button_t *)malloc(sizeof(Button_t));
	Button_Create("down",DownButton,(void *)at32_down_button_state,0);
	Button_Attach(DownButton,BUTTON_DOWM,(void *)sendDownKeyDownMessageToLvgl);
	
	PowerButton = (Button_t *)malloc(sizeof(Button_t));
	Button_Create("power",PowerButton,(void *)at32_power_button_state,1); 
	Button_Attach(PowerButton,BUTTON_DOWM,(void *)sendPowerKeyDownMessageToLvgl);
	Button_Attach(PowerButton,BUTTON_LONG,(void *)sendPowerKeyLongDownMessageToLvgl);


	while(1)
	{	
		Button_Process();
		#if 0
		if(PowerFlag == false)
		{
			//if(DeviceFlag == DEVICE_STATUP)
			//if(PowerButton->Button_Last_Level == PowerButton->Button_Trigger_Level)
			//if(PowerButton->Button_State == PowerButton->Button_Last_State == BUTTON_DOWM)
			//{
			//	NVIC_SystemReset();	
			//	PowerFlag = true;
			//}
			PowerFlag = true;
			vtaskmanage(1);	
		}
		
		if(PowerButton->Button_State == BUTTON_DOWM||PowerButton->Button_Last_State == BUTTON_DOWM)
		{
			PowerFlag = true;
			NVIC_SystemReset();
		}
		#endif
		vTaskDelay(30);
	}
}


extern struct infusionList* infusionlist;
extern struct drugList* druglist;

//保存输液器品牌到flash
void save_infusion_and_drug_to_flash(void)
{ 	
	printf("start save infusion and drug to flash\r\n");
	ParamSetting.drugnumber = druglist->node_number;
	ParamSetting.brandnumber = infusionlist->node_number;
	printf("drugnumber=%d,brandnumber=%d \r\n",ParamSetting.drugnumber,ParamSetting.brandnumber);
    WriteParamSettingMessageToFlash();
	writeInfusionTubeListToFlash();	
    WriteDrugListToFlash();
	printf("save infusion and drug to flash success…… \r\n");
}


//进入低功耗
void vtaskmanage(uint8_t id)
{
   if(id == 1)
  {  
	save_infusion_and_drug_to_flash();
	  
    tmr_counter_enable(TMR13, FALSE); 
	  
	system_clock_config(USE_1MHZ);
	
	key_gpio_init();
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);	
//    /* enable pwc clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
	//备份区域时钟RTC
	crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
//	
//	//唤醒引脚
    pwc_wakeup_pin_enable(PWC_WAKEUP_PIN_1, TRUE);
	
    rtc_config_();
   
    rtc_alarm_config(2);
			
    pwc_standby_mode_enter();		
   }   
}
	

void EXINT1_IRQHandler(void)
{
	flag_status PowerSupply;
	flag_status Cell;
	if((EXINT->intsts & EXINT_LINE_1) != RESET)
	{
		PowerSupply = gpio_input_data_bit_read(GPIOC,GPIO_PINS_1);
		Cell = gpio_input_data_bit_read(GPIOC,GPIO_PINS_2);
		if(PowerSupply || Cell)
			vtaskmanage(1);				//关机
		else
			
		EXINT->intsts = EXINT_LINE_1;
    }
}




