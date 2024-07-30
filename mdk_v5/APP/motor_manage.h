#ifndef _MOTOR_MANAGE_H_
#define _MOTOR_MANAGE_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "define.h"
#include "at32f403a_407.h"
#include "at32f403a_407_board.h"
#include "TMC2226_Register.h"
#include "crc.h"

#define Motor_Debug 0
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))          
#define CRC_TABLE_COUNT 2

#define DIR_RUN gpio_bits_set(GPIOE,GPIO_PINS_1);
#define DIR_BACK gpio_bits_reset(GPIOE,GPIO_PINS_1);

#define MT_ENN_H gpio_bits_set(GPIOC,GPIO_PINS_7);
#define MT_ENN_L gpio_bits_reset(GPIOC,GPIO_PINS_7);



typedef enum
{
    MOTOR_STOP,			//电机停止
    MOTOR_RUN,			//电机运行
    MOTOR_BACK,			//电机反转
	MOTOR_CALI,
	MOTOR_OPENRUN,
}Motor_Status;

typedef struct 
{
		uint16_t  					subdivide;      // 细分
		uint16_t            speed;  				//速度
		uint32_t  					force;       		//力矩
		uint32_t  					s_count;				//电机步数
		volatile float 			angle_1s;       //电机每走一步的角度
		volatile double 		anglesum;       //Angle角度和 sum 
		DeviceType          device; 				//设备类型
		//_Bool             dir;    				//方向
		Motor_Status        status; 				//当前电机状态
}Motor_Control;
extern Motor_Control MotorControl;


void motor_init(void);
void motor_usart_init(void);
void motor_gpio_init(void);
void motor_tmr_init(void);
void UART_writeInt(uint8_t slave, uint8_t address, uint32_t value);
uint32_t TMC2226_speed2force(uint32_t Speed);
void TMC2226_set_force(uint32_t force);
uint32_t TMC2226_speed2subdivide(uint32_t Speed,uint16_t *subdivide_num);
uint16_t TMC2226_set_subdivide(uint32_t subdivide , uint16_t subdivide_num);
void TMC2226_MotorRun(uint8_t Dir,uint8_t Cmd,uint32_t Speed);
void TMC2226_MotorRun_TEMP(void);
void TMC2226_MotorStop(void);
void MotorCALIBRRun(uint32_t calib_num);
static void Freq_to_Pr_Div(uint32_t Freq, uint32_t *tmr_pr, uint32_t *tmr_div);
void set_calib_num(uint32_t calib_num);
uint32_t get_calib_num(void);
float calculate_motor_prestep_angle(uint32_t subdivide);
void stepmotor_default_para_init(Motor_Control *motor_control_srtuct);






















#endif
