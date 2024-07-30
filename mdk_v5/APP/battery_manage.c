#include "battery_manage.h"
#include "at32f403a_407.h"
#include "at32f403a_407_board.h"
#include "audio_manage.h"
#include "clock_manage.h"

extern __IO uint8_t   DeviceFlag;
extern void system_clock_config(enum CLOCK_WHICH clock_which);


#define PRE_ADC_SPMPLE_NUM 4  //压力滑动滤波样本

__IO uint16_t adc1_ordinary_valuetab[1] = {0};
__IO uint16_t vmor_flag_index = 0;

uint32_t BatteryStatusCount_PD=0; 

static uint8_t BATTERY_FLAG_STATE=1;  //增加一个标志量用来判断电池脱落还是断电后刚上电瞬间的状态
static exint_init_type exint_init_struct; 
_Bool BatterState = false;


/* pc0 */
void gpio_bat_control(bool flag)
{
	gpio_init_type  gpio_init_struct = {0};
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	gpio_init_struct.gpio_pins = GPIO_PINS_0;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);
	if(flag)
	gpio_bits_write(GPIOC,GPIO_PINS_0,TRUE);	
	else
	gpio_bits_write(GPIOC,GPIO_PINS_0,FALSE);		
}

void BUZZER_control(bool flag)
{
	gpio_init_type  gpio_init_struct = {0};
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	gpio_init_struct.gpio_pins = GPIO_PINS_15;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOB, &gpio_init_struct);
	if(flag)
	gpio_bits_write(GPIOB,GPIO_PINS_15,TRUE);	
	else
	gpio_bits_write(GPIOB,GPIO_PINS_15,FALSE);		
}


void gpio_bat_init(uint8_t val)  
{
	  gpio_init_type  gpio_init_struct = {0};
	  dma_init_type dma_init_struct;
	  adc_base_config_type adc_base_struct;
	  
	  
	  /*enable the gpio click*/
	    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);	
	  
	  if(val==1){
		  
		gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_2;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;	
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOC, &gpio_init_struct);
		  	  
	  }else if(val == 2){
		
		/*PC0 BAT-GPIO */
//		gpio_init_struct.gpio_pins = GPIO_PINS_0;
//		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//		gpio_init(GPIOC, &gpio_init_struct);
////	gpio_bits_set(GPIOC,GPIO_PINS_0);
//      gpio_bits_write(GPIOC,GPIO_PINS_0,TRUE);

		/*PC13 PWR-EN */
		pwc_battery_powered_domain_access(TRUE);
		bpr_tamper_pin_enable(FALSE);
		bpr_interrupt_enable(FALSE);
		pwc_battery_powered_domain_access(FALSE);
		
		gpio_init_struct.gpio_pins = GPIO_PINS_13;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOC, &gpio_init_struct);
		gpio_bits_set(GPIOC,GPIO_PINS_13);

		#if 1
		gpio_init_struct.gpio_pins = GPIO_PINS_3;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOE, &gpio_init_struct);
		#endif

		gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOE, GPIO_PINS_SOURCE3); //status
		exint_default_para_init(&exint_init_struct);
		exint_init_struct.line_enable = TRUE;
		exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
		exint_init_struct.line_select = EXINT_LINE_3;
		exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
		exint_init(&exint_init_struct);
		nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
		nvic_irq_enable(EXINT3_IRQn, 0, 0);


		/*PC1 DC-PWR input  �ж���������Դ*/
		gpio_init_struct.gpio_pins = GPIO_PINS_1;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOC, &gpio_init_struct);
		
		/*BAT voltage monitor config*/
		/*PC2 17 ADC1_IN12*/
		crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		gpio_default_para_init(&gpio_init_struct);
		gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
		gpio_init_struct.gpio_pins = GPIO_PINS_2;
		gpio_init(GPIOC, &gpio_init_struct);

		/*DMA config*/
		crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
		nvic_irq_enable(DMA1_Channel1_IRQn, 0, 0);
		dma_reset(DMA1_CHANNEL1);
		dma_default_para_init(&dma_init_struct);
		dma_init_struct.buffer_size = 5;
		dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
		dma_init_struct.memory_base_addr = (uint32_t)adc1_ordinary_valuetab;
		dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
		dma_init_struct.memory_inc_enable = FALSE;
		dma_init_struct.peripheral_base_addr = (uint32_t)&(ADC1->odt);
		dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
		dma_init_struct.peripheral_inc_enable = FALSE;
		dma_init_struct.priority = DMA_PRIORITY_HIGH;
		dma_init_struct.loop_mode_enable = FALSE;
		dma_init(DMA1_CHANNEL1, &dma_init_struct);
		dma_interrupt_enable(DMA1_CHANNEL1, DMA_FDT_INT, TRUE);
		dma_channel_enable(DMA1_CHANNEL1, TRUE);

		/*ADC config*/
		crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
		crm_adc_clock_div_set(CRM_ADC_DIV_6);
		/* select combine mode */
		adc_combine_mode_select(ADC_INDEPENDENT_MODE); 
		adc_base_default_para_init(&adc_base_struct);
		adc_base_struct.sequence_mode = TRUE;
		adc_base_struct.repeat_mode = TRUE;
		adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
		adc_base_struct.ordinary_channel_length = 1;
		adc_base_config(ADC1, &adc_base_struct);
		adc_ordinary_channel_set(ADC1, ADC_CHANNEL_12, 1, ADC_SAMPLETIME_239_5);
		adc_ordinary_conversion_trigger_set(ADC1, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);
		adc_dma_mode_enable(ADC1, TRUE);
		adc_enable(ADC1, TRUE);
		adc_calibration_init(ADC1);
		while(adc_calibration_init_status_get(ADC1));
		adc_calibration_start(ADC1);
		while(adc_calibration_status_get(ADC1));

		adc_ordinary_software_trigger_enable(ADC1,TRUE);
		
   }

}

void BatteryManagement_PD(void)  //关机时候电池检测
{
		static uint32_t Scount_PD=0;
		uint8_t BatteryFlag=0;
		
		if(DC_PWR)  	//DC-PWR
		{
			led_on(AC_LED);
		}
		else
		{
			led_off(AC_LED);
		}
		
		if(DC_PWR && BatteryStatusCount_PD==Scount_PD && BatteryStatus) //充满
		{
			BATTERY_FLAG_STATE=1;
			led_on(BAT_LED);
			BatteryFlag=1;			
		}
		else if(DC_PWR && BatteryStatusCount_PD==Scount_PD && !BatteryStatus) //充电
		{
			BATTERY_FLAG_STATE=1;
			led_on(BAT_LED);
			BatteryFlag=2;
		}
		else if(BATTERY_FLAG_STATE && DC_PWR && BatteryStatusCount_PD != Scount_PD) //脱落
		{
			BATTERY_FLAG_STATE = 1;
			led_off(BAT_LED);
			BatteryFlag=3;
			
		}
		else if(!DC_PWR && BatteryStatusCount_PD==Scount_PD && BatteryStatus) //放电
		{
			BATTERY_FLAG_STATE=0;

			if(DeviceFlag == DEVICE_STATUP) 
				led_turn(BAT_LED);
			else
				led_off(BAT_LED);
				
        	BatteryFlag=4;
		}
		else
		{
			BatteryFlag=0;
		}
		
		sensorpack.batterystatus=BatteryFlag;
		
    	Scount_PD=BatteryStatusCount_PD;  		
}
/*
***************************************************************************
* Function: // BatteryManagement
* Description: 
* Called By: // TMR1_IRQHandler 
* Input: // none
* Return: // none
* Others: // 
*  // 
* //
***************************************************************************
*/
void BatteryManagement(void)  
{ 
    uint8_t BatteryFlag=0;
	uint8_t CellDetection=0;			//区分电池充满与脱落状态
    if(DC_PWR)
      led_on(AC_LED);  
    else
      led_off(AC_LED);   
	if(BatteryStatus)
		CellDetection = 1;
	else
		CellDetection = 0;

    if((DC_PWR)&&( battery_status.StatusFlag == 0)&&(BatteryStatus))        //充满 
    {
        BATTERY_FLAG_STATE=0;
		BatterState = true;
        led_on(BAT_LED);   
        BatteryFlag=1;
    }
    else if((DC_PWR)&&(battery_status.StatusFlag == 0)&&(!BatteryStatus))  //充电 
    {
        BATTERY_FLAG_STATE=1;
        led_on(BAT_LED);
        BatteryFlag=2;
    }
    else if((DC_PWR)&&(battery_status.StatusFlag == 1)&&(BATTERY_FLAG_STATE))//脱落 
    {
		BATTERY_FLAG_STATE=1;
		led_off(BAT_LED);
		BatteryFlag=3;
    }    
    else if((!DC_PWR)&&( battery_status.StatusFlag == 0)&&(BatteryStatus))  //放电  
    {
        BATTERY_FLAG_STATE=0;
        if(DeviceFlag == DEVICE_STATUP) 
          led_turn(BAT_LED);
        else
          led_off(BAT_LED);
        BatteryFlag=4;
    }
    else
    {
		BATTERY_FLAG_STATE=1;
      	BatteryFlag=0;
    }
    sensorpack.batterystatus=BatteryFlag;           
		
}




void Enter_PowerDown(void)
{
	gpio_init_type  gpio_init_struct = {0};
		
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
		
	/*����IO*/
	//led
	led_off(ARM_RLED);
	led_off(ARM_YLED);
	led_off(M4_RLED);
		
	//�رն�ʱ��
	TMR1->ctrl1_bit.tmren &= 0; //�رն�ʱ��1
	TMR2->ctrl1_bit.tmren &= 0; //�رն�ʱ��2
	TMR3->ctrl1_bit.tmren &= 0; //�رն�ʱ��3	 
	TMR4->ctrl1_bit.tmren &= 0; //�رն�ʱ��4
		
	gpio_default_para_init(&gpio_init_struct);
	//����������ͣ
		
	//����Щ���������Ÿ����ó�������
	gpio_init_struct.gpio_pull=GPIO_PULL_NONE;
		
	
	gpio_init_struct.gpio_pins=GPIO_PINS_10 | GPIO_PINS_11 |GPIO_PINS_1;
	gpio_init(GPIOB, &gpio_init_struct);
	
	
	gpio_init_struct.gpio_pins=GPIO_PINS_0 |GPIO_PINS_5;
	gpio_init(GPIOA, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins=GPIO_PINS_5;
	gpio_init(GPIOD, &gpio_init_struct);
	
	
	//��Ƶ��ͣ
	//WT588F_Send_Data(0xFE);
	//�����������ģʽ
	gpio_bits_set(GPIOB,GPIO_PINS_8); //����stdby������͹���״̬
	//lcd�ر�
	
	DeviceFlag=DEVICE_STOP;
	
	//ѹ��
	gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE); //���ߺ�ά��60us,hx711������ϵ�״̬
	
	

	#if 0  
	crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
	
	//���˯��ģʽ
	/* congfig the voltage regulator mode */
	pwc_voltage_regulate_set(PWC_REGULATOR_LOW_POWER);

	/* enter deep sleep mode */
	pwc_deep_sleep_mode_enter(PWC_DEEP_SLEEP_ENTER_WFI);
	
	//����ģʽ
	//pwc_wakeup_pin_enable(PWC_WAKEUP_PIN_1, TRUE);
	if(DC_PWR == RESET) //���û������Դ���룬��������ģʽ
		pwc_standby_mode_enter();
	
	#endif
}



void PowerDownFunction(void)
{
	crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
	
	if(DC_PWR == RESET) //���û������Դ���룬��������ģʽ
	pwc_standby_mode_enter();
	
}
static int getAverage(int *val, int num)
{
    int total;
    int i;

    if (num <= 0)
    {
        return 0;
    }
    total = 0;
    for (i = 0; i < num; i++)
    {
        total += val[i];
    }
    return total / num; //取平均值
}


//ADC滑动滤波4个
 int process_adc_A_val(int val)
{
    static unsigned int cur_adc_sample_num=0;
    static unsigned int adc_A_val[PRE_ADC_SPMPLE_NUM] = { 0 };
    unsigned int tmp_data = 0;
    int i = 0;
    
    if (cur_adc_sample_num < PRE_ADC_SPMPLE_NUM)  //采样四次 滑动滤波法
    {
        adc_A_val[cur_adc_sample_num++] = val;
    }
    else
    {
        for (i = 0; i < PRE_ADC_SPMPLE_NUM - 1; i++)
        {
            adc_A_val[i] = adc_A_val[i + 1];
        }
        adc_A_val[PRE_ADC_SPMPLE_NUM - 1] = val;
    }

    tmp_data = getAverage(adc_A_val, cur_adc_sample_num);
    return tmp_data;

}

/*
	functionname:   getVoltageADCValue
	describe:       采用滑动滤波方式获取电池电压AD值
	Param1:			Null
	Param2:			Null
	return: 		1-100内的数字,加个百分号即可表示电量百分比
	author:			dong
*/
int getVoltageADCValue()
{
	int temp; 
    int Voltage;
	int BatAD;
    temp = adc_ordinary_conversion_data_get(ADC1);  //读出来的ad值  2771.6-3600为百分之0到百分之100 	9V - 11.68V
	printf("temp = %d",temp);
    temp = process_adc_A_val(temp);     //滑动滤波求平均值
	BatAD = temp;
	printf("BatAD = %d",BatAD);
    if(temp < 2772)
        temp = 2772;
    if(temp > 3600)
        temp=3600;
    Voltage = (temp-2772.0)*100/(3600.0-2772.0);
	printf("Voltage = %d",Voltage);
	return Voltage;
}



/*DMA interrupt for voltage monitor*/
void DMA1_Channel1_IRQHandler(void)
{
	if(dma_flag_get(DMA1_FDT1_FLAG) != RESET)
	{
		dma_flag_clear(DMA1_FDT1_FLAG);
		vmor_flag_index = 1;
	}
}


//用于开机时电池管理，主要用来修改battery_status.StatusFlag的值
void TMR4_GLOBAL_IRQHandler(void)
{
	static uint32_t t_count1=0;
	
	if(tmr_flag_get(TMR4, TMR_OVF_FLAG) != RESET)
	{
		if(DeviceFlag == DEVICE_STATUP)
		{      
			if(++t_count1 > 5) //每5s
			{
				t_count1 = 0;

				if(sensorpack.voltagevalue)
				{
					battery_status.StatusFlagCount = 0;
					battery_status.StatusFlag = 0;
				}
				else{
					battery_status.StatusFlagCount = 0;
				 	battery_status.StatusFlag = 1;
				}
				// if((battery_status.StatusFlagCount >= 1)&&(battery_status.StatusFlagCount <= 3))
				// {
				// 	battery_status.StatusFlagCount = 0;
				//  	battery_status.StatusFlag = 1;
				//  }
				//  else
				// {
				// 	battery_status.StatusFlagCount = 0;
				// 	battery_status.StatusFlag = 0;
				// }
			}
		}
		tmr_flag_clear(TMR4, TMR_OVF_FLAG);
	}
}



void EXINT3_IRQHandler(void)
{
	if(exint_flag_get(EXINT_LINE_3) != RESET)
	{
		exint_flag_clear(EXINT_LINE_3);
		if(DeviceFlag == DEVICE_STATUP)
		{
			battery_status.StatusFlagCount++;
			if( battery_status.StatusFlagCount >= 0x40000000)
			{
				battery_status.StatusFlagCount = 0;
			}          
		}
		else if(DeviceFlag == DEVICE_STOP)
		{
			if(DC_PWR) //如果插了网电源
			{
				BatteryStatusCount_PD++;
				if(BatteryStatusCount_PD >= 0x40000000)
				{
					BatteryStatusCount_PD = 0;
				}
			}
		}
	}
}



























