/*
***************************************************************************
* Copyright: 2019 by SZKMED
* File name: HX711.c
* Description: HX711????,???????AD?
* Author: nick
* Version: ??
* Date: ????
* History: 
* 1?20200916 ??????????????,????128???64?
* 2?20200917 ??Chose_HX711_CH??,???????HX711??????
* 3?20200917  ??Read_HX712_A Read_HX712_B ??
* 4?20200917 ??Chose_HX712_CH ????A??64???
****************************************************************************
*/
#include "HX711.h"
#include "define.h"


#define PRE_ADC_SPMPLE_NUM 4  //????????

void gpio_HX711_init()
{
		/* enable the gpio clock */
		gpio_init_type  gpio_init_struct = {0};
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		/*ѹ��������*/
		//HX712_CLK PB0
		gpio_init_struct.gpio_pins = GPIO_PINS_0;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
		gpio_init(GPIOB, &gpio_init_struct);
		gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE);
		
		//HX712_DOUT PB1
		gpio_init_struct.gpio_pins = GPIO_PINS_1;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOB, &gpio_init_struct);		
		
}


/*
***************************************************************************
* Function: // Read_HX712_A
* Description: // ��ȡ��Һ����ѹ��ADֵ
* Called By: // SendSensorPackData
* Input: // none
* Return: // ����ֵ���Ϊ0����ͨ���л�ʧ�� 1�����л��ɹ�
* Others:  ��
***************************************************************************
*/
uint32_t Read_HX712_A()   
{ 
    static uint32_t oldCount_A = 0; 
    uint32_t Num = 0; 
    uint32_t Count_A = 0; 
    int8_t i= 0; 
    
	gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE); 
	
	delay_us(1);
    
    Count_A = 0;    
    Num = 0; 
  
    while(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1) 
    {
		Num++;
     	delay_us(100);
     	if(Num>600)
        {
        return oldCount_A;
        }
    }
    delay_us(1); //����t1
    for(i=0;i<24;i++) 
    {   
		gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE);
    delay_us(1);
    Count_A=Count_A<<1;    
		gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE);
    if(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1) 
			Count_A++;  
    delay_us(1); 
    } 
	gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE);
    delay_us(1);
	Count_A = Count_A^0x800000; 
    oldCount_A=Count_A;
	gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE);
	delay_us(1); 
	gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE);
    delay_us(1);
	gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE);
	
    return Count_A;
}


/*
***************************************************************************
* Function: // Read_HX712_B
* Description: // ��ȡ��Һ����ѹ��ADֵ
* Called By: // SendSensorPackData
* Input: // none
* Return: // ����ֵ���Ϊ0����ͨ���л�ʧ�� 1�����л��ɹ�
* Others:  
***************************************************************************
*/

#if 0
/*��ȡBͨ������*/
uint32_t Read_HX712_B()   
{ 
   static uint32_t oldCount_B=0; 
   uint32_t Num =0; 
   uint32_t Count_B =0; 
   int8_t i= 0; 
  
   gpio_bits_write(GPIOB,GPIO_PINS_0,0);
   delay_us(5);   //��һ�ν���vTaskDelay(200)���ٽ�������ӿ�����
   Count_B = 0;    

  while(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1)
  {
     Num++;
     //delay_us(8);
     delay_us(100);
     if(Num>600)
     {
        return oldCount_B;
     }
  }
  delay_us(5);
  for(i=0;i<24;i++) 
  {   
    gpio_bits_write(GPIOB,GPIO_PINS_0,1);  
    delay_us(5); 
    Count_B=Count_B<<1;    
    gpio_bits_write(GPIOB,GPIO_PINS_0,0); 
    if(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1)
			Count_B++;  
    delay_us(5); 
  }  
  gpio_bits_write(GPIOB,GPIO_PINS_0,1); 
  delay_us(5); 
  gpio_bits_write(GPIOB,GPIO_PINS_0,0); 
  delay_us(5);
  Count_B ^= 0x800000; 
  oldCount_B=Count_B;
  return Count_B;
}
#else
uint32_t Read_HX712_B()   
{ 
    static uint32_t oldCount_B=0; 
    uint32_t Num =0; 
    uint32_t Count_B =0; 
    int8_t i= 0; 
    
    gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE);
    vTaskDelay(200);
    //delay_us(5);   //��һ�ν���vTaskDelay(200)���ٽ�������ӿ�����
    Count_B = 0;   
    Num = 0;  
	//delay_ms(1);
    while(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1)
    {
        Num++;
        //delay_us(8);
        delay_us(100);
        if(Num>600)
        {                                                                                                                                                                                                                                                                                                                                                 
        return oldCount_B;
        }
    }
    //delay_us(1);
    for(i=0;i<24;i++) 
    {   
        gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE);  
        delay_us(1); 
        Count_B=Count_B<<1;    
        gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE); 
        if(gpio_input_data_bit_read(GPIOB,GPIO_PINS_1)==1)
            Count_B++;  
        delay_us(1); 
    }  
    gpio_bits_write(GPIOB,GPIO_PINS_0,TRUE); 
    delay_us(1); 
    gpio_bits_write(GPIOB,GPIO_PINS_0,FALSE); 
    delay_us(1);
    Count_B = Count_B^0x800000; 
    oldCount_B=Count_B;
    return Count_B;
}
#endif
/*
***************************************************************************
* Function: // pressure_get_average
* Description: // ��ADCƽ��ѹ��ֵ
* Called By: // process_adc_val
* Input: // val ADC����  num��������
* Return: // ����ADCƽ��ֵ
* Others:  //
*****/
 static unsigned int pressure_get_average(unsigned int *val, unsigned int num)
{
    unsigned int total;
    unsigned int i;

    if (num <= 0)
    {
        return 0;
    }
    total = 0;
    for (i = 0; i < num; i++)
    {
        total += val[i];
    }
    return total / num; //????
}

