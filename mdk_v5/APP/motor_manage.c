#include <math.h>
#include "motor_manage.h"
#include "timer_manage.h"
#include "protocol.h"
#include "FreeRTOS.h"
#include "task.h"



extern uint32_t MotorRunFlag; 
Motor_Control MotorControl;
static uint32_t Calib_Num;

/*
***************************************************************************
* Function: // motor_gpio_init
* Description: //配置相关的GPIO
* Called By: // 
* Input: // 
* Return: //
* Others: //注意M4-MT-IN  MT-ENB需要拉为高电平
*/
void motor_gpio_init(void)
{
		gpio_init_type  gpio_init_struct = {0};
		/*gpio config*/
		/*CLK CONFIG*/
		crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
		

		/*PB9 96 motor-pw 连接MP3435(升压转换器) 低电压输入，高电压输出*/
		gpio_init_struct.gpio_pins = GPIO_PINS_9;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOB, &gpio_init_struct);
		gpio_bits_set(GPIOB,GPIO_PINS_9); //给其赋高电平，使能mp3435

		/*MT-ENB 97 PE0*/
		gpio_init_struct.gpio_pins = GPIO_PINS_0;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOE, &gpio_init_struct);
		gpio_bits_set(GPIOE,GPIO_PINS_0);

		/*M4-MT-INT 64 PC7*/
		gpio_init_struct.gpio_pins = GPIO_PINS_7;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOC, &gpio_init_struct);
		MT_ENN_H;

		/*STEP 32 PA7*/
		gpio_init_struct.gpio_pins = GPIO_PINS_7;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOA, &gpio_init_struct);
		gpio_bits_reset(GPIOA,GPIO_PINS_7);
				
		/*DIR 98 PE1*/
		gpio_init_struct.gpio_pins = GPIO_PINS_1;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOE, &gpio_init_struct);
		gpio_bits_reset(GPIOE,GPIO_PINS_1);

		/*URTX 63 */
		gpio_init_struct.gpio_pins = GPIO_PINS_6;
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
		gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOC, &gpio_init_struct);		
		
		/*MT-STDY 95 PB8*/
		gpio_init_struct.gpio_pins = GPIO_PINS_8;
		gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOB, &gpio_init_struct);
		gpio_bits_reset(GPIOB,GPIO_PINS_8);		
}

/*
***************************************************************************
* Function: // stepmotor_default_para_init
* Description: //电机相关结构体参数初始化
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void stepmotor_default_para_init(Motor_Control *motor_control_srtuct)
{
	motor_control_srtuct->subdivide = 0;
	motor_control_srtuct->speed = 0;	
	motor_control_srtuct->force = 0;
	motor_control_srtuct->s_count = 0;
	motor_control_srtuct->anglesum = 0.0;
	motor_control_srtuct->angle_1s = 0.0;
	motor_control_srtuct->status = MOTOR_STOP;
}
/*
***************************************************************************
* Function: // motor_usart_init
* Description: //配置与tmc2226通讯的usart
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void motor_usart_init(void)
{
  /* enable the uart and gpio clock */
  crm_periph_clock_enable(CRM_USART6_PERIPH_CLOCK, TRUE);
  /* configure uart param */
  usart_init(USART6,115200,USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_parity_selection_config(USART6, USART_PARITY_NONE);
  usart_transmitter_enable(USART6, TRUE);
  //usart_single_line_halfduplex_select(USART6, TRUE);
  usart_enable(USART6, TRUE);   
}


/*
***************************************************************************
* Function: // motor_tmr_init
* Description: //配置控制电机step的定时器
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void motor_tmr_init(void)  
{
  	crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
	tmr_base_init(TMR3,119,119);  
	tmr_cnt_dir_set(TMR3,TMR_COUNT_UP);
	tmr_interrupt_enable(TMR3, TMR_OVF_INT, TRUE);
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR3_GLOBAL_IRQn, 0, 0);
	tmr_period_buffer_enable(TMR3, TRUE);
	tmr_counter_enable(TMR3, FALSE);	
}

/*
***************************************************************************
* Function: // UART_writeInt
* Description: //写tmc2226寄存器
* Called By: // 
* Input: // slave： Slave address  address：Register address  value：Register Data
* Return: //
* Others: // 写串口时必须等待TDBE
*/
void UART_writeInt(uint8_t slave, uint8_t address, uint32_t value)
{
	uint8_t writeData[8];

	writeData[0] = 0x05;                         // Sync byte
	writeData[1] = slave;                        // Slave address
	writeData[2] = address | TMC_WRITE_BIT;      // Register address with write bit set
	writeData[3] = ( value >> 24 );       // Register Data
	writeData[4] = ( value >> 16 );       // Register Data
	writeData[5] = ( value >> 8  );       // Register Data
	writeData[6] = ( value & 0xFF );       // Register Data
	writeData[7] = tmc_CRC8(writeData, 7, 1);    // Cyclic redundancy check

	for(uint32_t i = 0; i < ARRAY_SIZE(writeData); i++)
  {
		while(usart_flag_get(USART6, USART_TDBE_FLAG) == RESET);
		usart_data_transmit(USART6,writeData[i]);	
  }
      

}


/*
***************************************************************************
* Function: // UART_readInt
* Description: //读tmc2226寄存器
* Called By: // 
* Input: // slave： Slave address  address：Register address  value：保存读到的值
* Return: //
* Others: // 
*/
void UART_readInt(uint8_t slave, uint8_t address, uint32_t *value)
{
	uint8_t readData[8], dataRequest[4];
	uint32_t timeout;

	dataRequest[0] = 0x05;                        // Sync byte
	dataRequest[1] = slave;                       // Slave address
	dataRequest[2] = address;                     // Register address
	dataRequest[3] = tmc_CRC8(dataRequest, 3, 1); // Cyclic redundancy check

	for(uint32_t i = 0; i < ARRAY_SIZE(readData); i++)
	{
		 usart_data_transmit(USART6,readData[i]);
	}
}

/*
***************************************************************************
* Function: // motor_init
* Description: //电机相关初始化
* Called By: // 
* Input: // 
* Return: //
* Others: // 配置TMC2226寄存器后需等待至少200ms再释放ENN引脚
*/
void motor_init(void)
{
	stepmotor_default_para_init(&MotorControl);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	motor_gpio_init();
	motor_usart_init();
	motor_tmr_init();
	
	tmc_fillCRC8Table(0x07, true, 1); 
  	UART_writeInt(0,TMC2226_GCONF,0x000000C5);//配置General Registers 
 	UART_writeInt(0,TMC2226_IHOLD_IRUN,0x00071703);
 	UART_writeInt(0,TMC2226_TPOWERDOWN,0x00000014);//0x00000014
  	UART_writeInt(0,TMC2226_CHOPCONF,0x20000053);//0x10000053		
	delay_ms(200);
	MT_ENN_L;
}

/*
***************************************************************************
* Function: // TMC2226_speed2subdivide
* Description: //根据转速计算对应的细分数
* Called By: // MotorRun
* Input: // Speed 电机转速  subdivide_num细分数
* Return: // 细分寄存器值
* Others: // 
*/
uint32_t TMC2226_speed2subdivide(uint32_t Speed,uint16_t *subdivide_num)
{
	#if 1
    if(Speed<=100) // 100r/h
    {
				*subdivide_num = 256;
        return INITIAL_MICROSTEP_256;
    }
    else if(Speed<=500) //500r/h
    {
				*subdivide_num = 128;
        return INITIAL_MICROSTEP_128;
    }
    else if(Speed<=1000) //1000r/h
    {
				*subdivide_num = 32;
        return INITIAL_MICROSTEP_32;
    }  
    else if(Speed<=2000) //2000r/h
    {
				*subdivide_num = 16;
        return INITIAL_MICROSTEP_16;
			
    }
    else if(Speed<=16000) //16000r/h
    {
				*subdivide_num = 8;
        return INITIAL_MICROSTEP_8;
    }  
    else if(Speed<=22000)
    {
				*subdivide_num = 1;
        return INITIAL_MICROSTEPPING;
    }
    else if(Speed>22000)
    {
				*subdivide_num = 1;
        return INITIAL_MICROSTEPPING;
    }
    else 
    {
				*subdivide_num = 16;
        return INITIAL_MICROSTEP_16;
    } 	
	#else
		*subdivide_num = 8;
        return INITIAL_MICROSTEP_8;


	#endif
	
}
/*
***************************************************************************
* Function: // TMC2226_set_subdivide
* Description: //设置指定的细分
* Called By: // MotorRun
* Input: // subdivide 细分寄存器值  subdivide_num细分数
* Return: // 电机分频系数
* Others: // 
*/
uint16_t TMC2226_set_subdivide(uint32_t subdivide , uint16_t subdivide_num)
{
    static uint32_t cmd = 0;
    
    cmd = (0x20000053 | (subdivide << 24));
    UART_writeInt(0,TMC2226_CHOPCONF,cmd);
    return subdivide_num;
}


/*
***************************************************************************
* Function: // TMC2226_speed2force
* Description: //根据转速计算对应的电机电流
* Called By: // MotorRun
* Input: // Speed 电机转速  
* Return: // 电机电流档位
* Others: // 
*/
uint32_t TMC2226_speed2force(uint32_t Speed)
{
		uint32_t force_num = 0;
	
    if(Speed<=100) // 100r/h
    {
				force_num = 16;
        return force_num;
    }
    else if(Speed<=500) //500r/h
    {
				force_num = 17;
        return force_num;
    }
    else if(Speed<=1000) //1000r/h
    {
				force_num = 18;
        return force_num;
    }  
    else if(Speed<=2000) //2000r/h
    {
				force_num = 19;
        return force_num;
			
    }
    else if(Speed<=16000) //16000r/h
    {
				force_num = 20;
        return force_num;
    }  
    else if(Speed<=22000)
    {
				force_num = 21;
        return force_num;
    }
    else if(Speed>22000)
    {
				force_num = 22;
        return force_num;
    }
    else 
    {
				force_num = 13;
        return force_num;
    } 	
	
}

/*
***************************************************************************
* Function: // TMC2226_set_force
* Description: //根据电机转速设置电机驱动电流
* Called By: // 
* Input: // force 目标电流*8 （目标电流范围为0~31）
* Return: // none
* Others: // 
***************************************************************************
*/
void TMC2226_set_force(uint32_t force)
{
    uint32_t cmd = 0;
       
    cmd = 0x00070001 | (force<<8);  //IHOLD=3,IHOLDDELAY=7
    MotorControl.force = force;
    UART_writeInt(0,TMC2226_IHOLD_IRUN,cmd);	
}


/*
***************************************************************************
* Function: // TMC2226_MotorRun
* Description: //电机运行控制函数
* Called By: // UnMotor
* Input: //   Dir电机运行方向 Cmd当前运行模式 Speed电机转速(转/h)
* Return: //  none
* Others: //  主要功能 设置分频系数，电流等级、电机运行放向，速度所对应的定时器参数
***************************************************************************
*/
void TMC2226_MotorRun(uint8_t Dir,uint8_t Cmd,uint32_t Speed)
{
    static uint32_t time_s = 0, tmr_pr, tmr_div;

    uint16_t Subdivide = 0;  
		
	MotorControl.s_count = 0;
	if(Dir == DIR_R)
	{
		DIR_RUN;
	}
	else
	{
		DIR_BACK;
	}
	TMC2226_set_force(TMC2226_speed2force(Speed));
	vTaskDelay(10);		
	Subdivide = TMC2226_set_subdivide(TMC2226_speed2subdivide(Speed, &(MotorControl.subdivide)), MotorControl.subdivide);
	
	MotorControl.angle_1s = 1.8/(float)(Subdivide);
	vTaskDelay(10);
	time_s = (uint32_t) ((Speed*Subdivide)/18);
	Freq_to_Pr_Div(time_s, &tmr_pr , &tmr_div);
	tmr_base_init(TMR3,tmr_pr,tmr_div);  
	tmr_counter_enable(TMR3, TRUE);
	
	MotorControl.status = MOTOR_RUN;
}

/*
***************************************************************************
* Function: // Freq_to_Pr_Div
* Description: //通过电机频率计算分频系数和周期
* Called By: // TMC2226_MotorRun
* Input: //  none
* Return: //  none
* Others: //  
***************************************************************************
*/
static void Freq_to_Pr_Div(uint32_t Freq, uint32_t *tmr_pr, uint32_t *tmr_div)
{
	uint32_t u32Clk;
	crm_clocks_freq_type crm_clocks_freq_struct = {0};	
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	u32Clk = crm_clocks_freq_struct.apb2_freq * 2;
	if(u32Clk >= 0x2000000)
	{
		*tmr_div = 3;
		u32Clk >>= 2;
	}
	else  if(u32Clk >= 0x1000000)
	{
		*tmr_div = 2;
		u32Clk >>= 1;
	}
	*tmr_pr = (u32Clk / Freq) - 1;
}


/*
***************************************************************************
* Function: // TMC2226_MotorStop
* Description: //电机停转函数
* Called By: // UnMotor
* Input: //  none
* Return: //  none
* Others: //  将电机驱动电流降低后，关闭定时器
***************************************************************************
*/
void TMC2226_MotorStop(void)
{    
    // uint32_t cmd = 0;
  
    // MotorControl.force  = 1;
	// MotorControl.s_count = 0;
    // cmd = 0x00010100;
    // UART_writeInt(0,TMC2226_IHOLD_IRUN,cmd);   
    // tmr_counter_enable(TMR3, FALSE);
	// MotorControl.status = MOTOR_STOP;
	motor_init();
}

/***********************************************************/
/*精度校准相关*/

/*
***************************************************************************
* Function: // MotorCALIBRRun
* Description: //精度校准
* Called By: // 
* Input: //  calib_num ： 1 精度校准第一次 calib_num ： 2 精度校准第二次
* Return: // none
* Others: // 
***************************************************************************
*/
void MotorCALIBRRun(uint32_t calib_num)
{
    uint32_t cmd = 0;
	uint32_t tmr_pr, tmr_div; 
	
    /*设置电机微步分频系数*/
	TMC2226_set_subdivide(INITIAL_MICROSTEP_32, 32);
	TMC2226_set_force(24);
	DIR_BACK;
	MotorRunFlag = MOTOR_CALI;
	set_calib_num(calib_num);
    if(calib_num == 1)
    {
     	Freq_to_Pr_Div(1778, &tmr_pr , &tmr_div);  //6min 转 100r
    }
    else if(calib_num == 2)
    {
		Freq_to_Pr_Div(5333, &tmr_pr , &tmr_div); //2min 转 100r
	}
	tmr_base_init(TMR3,tmr_pr,tmr_div);  
	tmr_counter_enable(TMR3, TRUE); 
}

/*
***************************************************************************
* Function: // set_calib_num
* Description: //设置当前精度校准的次数
* Called By: // 
* Input: //  calib_num 精度校准次数，1 精度校准第一次 calib_num ： 2 精度校准第二次
* Return: //  none
* Others: 
***************************************************************************
*/
void set_calib_num(uint32_t calib_num)
{
	Calib_Num = calib_num;
}
/*
***************************************************************************
* Function: // get_calib_num
* Description: //获取当前精度校准的次数
* Called By: // 
* Input: //  none
* Return: //   精度校准次数，1 精度校准第一次   2 精度校准第二次
* Others: 
***************************************************************************
*/
uint32_t get_calib_num(void)
{
	return Calib_Num;
}

/*
***************************************************************************
* Function: // calculate_motor_prestep_angle
* Description: //计算当前细分下每走一步是多少角度
* Called By: // 
* Input: //  none
* Return: // 每走一步的角度
* Others: 
***************************************************************************
*/
float calculate_motor_prestep_angle(uint32_t subdivide)
{
	float prestep_angle = 0;
	prestep_angle = 1.8 / (float)subdivide;
	return prestep_angle;
}




/*
***************************************************************************
* Function: // TMR3_GLOBAL_IRQHandler
* Description: //电机运行定时器中断
* Called By: // 
* Input: //  none
* Return: //   精度校准次数，1 精度校准第一次   2 精度校准第二次
* Others: 
***************************************************************************
*/
void TMR3_GLOBAL_IRQHandler(void)
{
	static int num=0;
	if(tmr_flag_get(TMR3, TMR_OVF_FLAG) != RESET)
	{
		MotorControl.s_count++;
		GPIOA->odt ^= GPIO_PINS_7;  
		if(MotorRunFlag == MOTOR_CALI)
		{
			if(Calib_Num == 1)
			{
				if(MotorControl.s_count >= 640000)
				{	
					TMC2226_MotorStop();
				}
			}
			else if(Calib_Num == 2)
			{
				if(MotorControl.s_count >= 640000)
				{
					TMC2226_MotorStop();
				}				
			}
		}
		else if(MotorRunFlag==MOTOR_OPENRUN)
		{
			
		}
		else if(MotorRunFlag==MOTOR_BACK)
		{
		}
		else
		{
			if(num++ > 1)
			{
				MotorControl.anglesum	+= MotorControl.angle_1s;
				num = 0;
			}
			else
			{

			}
			 
		}
		tmr_flag_clear(TMR3, TMR_OVF_FLAG);
	}
}
