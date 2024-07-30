


#include "audio_manage.h"
#include "at32f403a_407_board.h"
#include "timer_manage.h"


void audio_gpio_init()
{
	gpio_init_type  gpio_init_struct={0};
	// iomux_type *iomuxtype;
	/*enable the gpio click*/
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK,TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE);
		
	/*PA5 30 audio-pw*/
	gpio_init_struct.gpio_pins = GPIO_PINS_5;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
	
	/*PD8 55 */
	gpio_init_struct.gpio_pins = GPIO_PINS_8;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOD, &gpio_init_struct);

	gpio_bits_write(GPIOA,GPIO_PINS_5,TRUE);
	
}

/*
power_state : 

1: USE_240MHZ
2: USE_1MHZ

*/

void beep_init(uint8_t power_state)
{
	//54 PB15 TMR12_CH2 pwm���
	gpio_init_type  gpio_init_struct={0};
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE);
	crm_periph_clock_enable(CRM_TMR12_PERIPH_CLOCK,TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK,TRUE);

	gpio_init_struct.gpio_pins = GPIO_PINS_15;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_PULL_UP;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOB, &gpio_init_struct);
	
	if(power_state==1)
	{
	  tmr12_init(USE_240MHZ);		
	}else if(power_state ==2)
	{
	 tmr12_init(USE_1MHZ);	
	}

	
}

void BeepStart(void)
{
	tmr_counter_enable(TMR12, TRUE);
}

void BeepWork(void)
{
	static uint8_t pwm_on=1; 
	if(pwm_on==1) 
	{
		tmr_counter_enable(TMR12, TRUE); 
		pwm_on=0;
	}
	else 
	{
		tmr_counter_enable(TMR12, FALSE);
		pwm_on=1;
	}
}

void BeepStop(void)
{
	tmr_counter_enable(TMR12, FALSE);	
}

#if 0
void WT588F_Send_doubledata(unsigned int USER_DATA)
{
	unsigned char i, num_temp;
	unsigned char B_DATA;
	unsigned int ddata_temp, pdata_temp;
	ddata_temp = USER_DATA;
	pdata_temp = ddata_temp & 0X00FF; //移位前准�?
	pdata_temp <<= 8; //低字节移位到高字�?
	ddata_temp >>= 8; //高字节移位到低字�?
	ddata_temp |= pdata_temp; //移位后重新合�?
	num_temp = 16;
	
	gpio_bits_reset(GPIOD, GPIO_PINS_8);
	//one_line_DATA = 0; //拉低数据�?
	delay_ms(5); //延时5MS
	B_DATA = ddata_temp & 0X0001;
	for(i = 0; i < num_temp; i++)
	{
		if(i == 8)
		{
			gpio_bits_set(GPIOD, GPIO_PINS_8);
			//one_line_DATA = 1;
			delay_ms(2); //延时2MS
			gpio_bits_reset(GPIOD, GPIO_PINS_8);
			//one_line_DATA = 0;
			delay_ms(5); //延时5MS
		}
		gpio_bits_set(GPIOD, GPIO_PINS_8);
		//one_line_DATA = 1; //拉高数据传输�?,准�?�传输数�?
		if(B_DATA == 0)
		{
			/*表示逻辑电平0*/
			delay_us(200); // 延时200us
			gpio_bits_reset(GPIOD, GPIO_PINS_8);
			//one_line_DATA = 0;
			delay_us(600); // 延时600us
		}
		else
		{
			/*表示逻辑电平1*/
			delay_us(600); // 延时600us
			gpio_bits_reset(GPIOD, GPIO_PINS_8);
			//one_line_DATA = 0;
			delay_us(200); // 延时200us
		}
		ddata_temp = ddata_temp >> 1;
		B_DATA = ddata_temp & 0x0001;
	}
	gpio_bits_set(GPIOD, GPIO_PINS_8);
	//one_line_DATA = 1;
}
#endif


void WT588F_Send_Data(unsigned char DDATA)
{
	unsigned char S_DATA, j;
	unsigned char B_DATA;
	S_DATA = DDATA;
	gpio_bits_reset(GPIOD, GPIO_PINS_8);
	delay_ms(5); //延时5ms
	B_DATA = S_DATA & 0X01;
	for(j = 0; j < 8; j++)
	{
		if(B_DATA == 1)
		{
			gpio_bits_set(GPIOD, GPIO_PINS_8);
			delay_us(600); //延时600us
			gpio_bits_reset(GPIOD, GPIO_PINS_8);
			delay_us(200); //延时200us
		}
		else
		{
			gpio_bits_set(GPIOD, GPIO_PINS_8);
			delay_us(200); //延时200us
			gpio_bits_reset(GPIOD, GPIO_PINS_8);
			delay_us(600); //延时600us
		}
		S_DATA = S_DATA >> 1;
		B_DATA = S_DATA & 0X01;
	}
	gpio_bits_set(GPIOD, GPIO_PINS_8);
	delay_ms(3);
}





















