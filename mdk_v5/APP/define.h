#ifndef _DEFINE_H_
#define _DEFINE_H_


#include "at32f403a_407.h"



#define TMC_WRITE_BIT 0x80


#define audio 0


#define PWM_LCD_DEBUG 1


#define History 0
#define debug 0
#define lowpower 0  //低功耗测试

#define VET_USE 0  //是否兽用
#define CH_USE 1
#define VP30 1


#define wait 0

typedef enum
{
    infusion,
    syringe
}DeviceType;


typedef struct  
{
    uint32_t  	StatusFlagCount;      //记录STATUS低电平频率
    uint32_t    StatusFlag;
}Battery_Status;

extern Battery_Status battery_status;

#define  DEVICE_STATUP          0X11    
#define  DEVICE_STOP		    0x22	

#define DIR_R	    0  
#define DIR_L	    1  

#define yue         0


#define PRESSUREUNIT00 "mmHg"
#define PRESSUREUNIT01 "kPa"
#define PRESSUREUNIT02 "bar"
#define PRESSUREUNIT03 "psi"

#define DateFormat01 "yyyy-mm-dd"
#define DateFormat02 "mm-dd-yyyy"
#define DateFormat03 "dd-mm-yyyy"
#define TimeFormat01 "24 H"
#define TimeFormat02 "12 H"

#define MEDICINEUNIT00 "ug"
#define MEDICINEUNIT01 "mg"
#define MEDICINEUNIT02 "g"
#define MEDICINEUNIT03 "ng"

#define DOSESPEEDUNIT00 "ug/kg/min"
#define DOSESPEEDUNIT01 "ug/kg/h"
#define DOSESPEEDUNIT02 "ng/kg/min"
#define DOSESPEEDUNIT03 "ng/kg/h"
#define DOSESPEEDUNIT04 "mg/kg/min"
#define DOSESPEEDUNIT05 "mg/kg/h"
#define DOSESPEEDUNIT06 "g/kg/min"
#define DOSESPEEDUNIT07 "g/kg/h"


#define BrandCome1  1   //8888的精度校准
#define BrandCome2  2   //8888的压力校准
#define BrandCome3  3   //6686的精度校准
#define BrandCome4  4   //6686的压力校准


//#define SystemSetting_Flash_ADDRESS_START 				(0x08070000)
//#define ParamSetting_Flash_ADDRESS_START				    (SystemSetting_Flash_ADDRESS_START + sizeof(System_Setting))
//#define SystemMaintain_Flash_Address_Start				(ParamSetting_Flash_ADDRESS_START+sizeof(Param_Setting)) 
//#define FirstComeFlagAddress                              (SystemMaintain_Flash_Address_Start+sizeof(System_Maintain))

//#define SpeedMode_Flash_Address_Start                   	(FirstComeFlagAddress + sizeof(uint16_t))
//#define TimeMode_Flash_Address_Start                    	(SpeedMode_Flash_Address_Start + sizeof(Speed_Mode))
//#define WeightMode_Flash_Address_Start                  	(TimeMode_Flash_Address_Start + sizeof(Time_Mode))
//#define SeqMode_Flash_Address_Start                    	(WeightMode_Flash_Address_Start + sizeof(Weight_Mode))
//#define DripMode_Flash_Address_Start                   	(SeqMode_Flash_Address_Start + sizeof(Sequen_Mode))

//#define InfusionTube_Flash_ADDRESS_Start                	(DripMode_Flash_Address_Start+sizeof(Drip_Mode))
//#define DrugTube_Flash_ADDRESS_Start                    	(InfusionTube_Flash_ADDRESS_Start+InfusionTube_MaxNumber*sizeof(InfusionNode_t))
	
//#define next_flash_address_start                       	(DrugTube_Flash_ADDRESS_Start+DrugTube_MaxNumber*sizeof(DrugNode_t))
//#define History_Flash_ADDRESS_Start                     	 0x700000            

//#define SystemSetting_Flash_ADDRESS_START 			    0x08080000
//#define ParamSetting_Flash_ADDRESS_START				    0x08080800
//#define SystemMaintain_Flash_Address_Start                0x08082000    
//#define FirstComeFlagAddress                              0x08083000
//#define SpeedMode_Flash_Address_Start                     0x08084000
//#define TimeMode_Flash_Address_Start                      0x08085000
//#define WeightMode_Flash_Address_Start                    0x08086000
//#define SeqMode_Flash_Address_Start                       0x08087000
//#define DripMode_Flash_Address_Start                      0x08088000
//#define InfusionTube_Flash_ADDRESS_Start                  0x08090000
//#define DrugTube_Flash_ADDRESS_Start                      0x080A0000

#define SystemSetting_Flash_ADDRESS_START 			      0x08070000
#define ParamSetting_Flash_ADDRESS_START				  0x08070800
#define SystemMaintain_Flash_Address_Start                0x08071000    
#define FirstComeFlagAddress                              0x08071800
#define SpeedMode_Flash_Address_Start                     0x08072000
#define TimeMode_Flash_Address_Start                      0x08072800
#define WeightMode_Flash_Address_Start                    0x08073000
#define SeqMode_Flash_Address_Start                       0x08073800
#define DripMode_Flash_Address_Start                      0x08074000
#define InfusionTube_Flash_ADDRESS_Start                  0x08074800
#define DrugTube_Flash_ADDRESS_Start                      0x08077000

#define History_Flash_ADDRESS_Start                       0x00700000 
#define History_max_num                                         1700

/* 使用此处的地址会造成不可访问卡死 */
//#define History_Flash_ADDRESS_Start                       0x6E0000 
//#define History_max_num                                       2000



#if 0
//---------------------------------------------motro????-------------------------------------------
#define    MOTO_RUN_CLOCK       0xCC         //???
#define    MOTO_RUN_ANTIC       0xDD         //???
//------------------------------------------------dev--------------------------------------------------
#define    CENTRE_DEV           0x00         
#define    SYRINGE_DEV          0xAA
#define    INFUSION_DEV         0xBB
//------------------------------------------------ID---------------------------------------------------
#define    HEAD     		 0x02
#define    TAIL     		 0x03
#define    KEYID     		 0x05
#define    ACKID     		 0x06
#define    TIMERID   		 0x07  
#define    SENSORID  		 0x08 
#define    MOTORID   		 0x09
#define    GETTIMEID 		 0x10
#define    BEEPID 		 0x11
#define    LEDID    		 0x12
#define    PWNID    		 0x13
#define    OPENRUNID             0x14 /*2021/7/9 ??????????????*/
#define    GETVERSIONID          0x15

//-----------------------------------------------ACKCMD------------------------------------------------
#define    ACK_CMD_RLED_OPEN 		   0x20
#define    ACK_CMD_YLED_OPEN 		   0x21
#define    ACK_CMD_BEEP_OPEN 		   0x22
#define    ACK_CMD_CLOSE 		   0x23
#define    ACK_CMD_PWN_CLOSE 		   0x24

//------------------------------------------------CMD--------------------------------------------------
#define  MOTOR_RUN              0x41   	/*?0x41:�������   */ 
#define  MOTOR_STOP	        0x42	/*?0x42:ֹͣ���   */
#define  MOTOR_BACK	        0x43	/*?0x43:��ת���   */
#define  MOTOR_FORCE            0x45    /*?0x45:��������   */
#define  MOTOR_CLEAR            0x46    /*?0x46:����ۻ���*/
#define  MOTOR_BOLUS_1         	0x47    /*0x47:���ģʽ   1*/
#define  MOTOR_BOLUS_2         	0x48    /*0x48:���ģʽ   2*/
#define  MOTOR_GOLD_ALARM	0x49	/*?0x49:����ݱ���*/
#define  MOTOR_CALIBRATE        0x50  	/*0x50:У׼*/
#define  MOTOR_KVO              0x51 	/*0x51:KVO*/
#define  MOTOR_EXHAUST          0x52    /*0x52:����*/
#define  MOTOR_TESTRUN          0x53    /*0x53:����ģʽ*/
#define  MOTOR_TESTBACK         0x54    /*0x54:����ģʽ,��ת*/
#define  MOTOR_OPENRUN          0x55    /*0x55:����������״̬�����ת*/
#define  MOTOR_PRESSURE         0x56    /*0x56:ѹ��У׼*/
#define  MOTOR_STOPSTATE        0x57    /*0x57:ֹͣ�����־*/
#define  MOTOR_AUTOSYRINGE_BACK      0x58    /*0x58:ֹͣ�����־*/
#define  MOTOR_AUTOSYRINGE_RUN      0x59    /*0x58:ֹͣ�����־*/


//-------------------------------FLAG------------------------------------------
#define  DEVICE_STATUP          0X11    /*?0x11: ??  */
#define  DEVICE_STOP		0x22	/*?0x22: ??  */

// STEP MOTOR



#define MT_EN  	    PD12
//#define DIR 		PE1
#define STEP		PD14

#define SG_T		PC5
#define DIR_R	    0  //???
#define DIR_L	    1  //???
#define STEP_ms	    1     
//#define STEP_NUM 200  

//#define PWR-EN 		PE5      //peng add 

#endif

#define DC_PWR 							gpio_input_data_bit_read(GPIOC,GPIO_PINS_1)         //网电源检测
#define BatteryStatus  			        gpio_input_data_bit_read(GPIOE,GPIO_PINS_3)         //充电检测


#if wait
typedef struct   //����ʱ��ع�����
{
    uint32_t  	StatusFlagCount;      
    uint32_t    StatusFlag;
}Battery_Status;
extern Battery_Status battery_status;

#endif



/*****************************logo**********************************************/
#define fydb            0        //仅能有一个为1
#define yiye            0
#define zhongke         1
#define zhongxing_en    0
#define ansha           0

#if 0

/*
PHOTO3,PHOTO4   	???
PHOTO7,PHOTO8


PHOTO9,PHOTO10		????	
PHOTO11,PHOTO12	
*/

/*PHOTO*/
#define  PHOTO1  PB15            /*??*/
#define  PHOTO3  PA0             /*????????*/
#define  PHOTO4  PA1             /*????????*/
#define  PHOTO5  PE14            /*???????,??*/         
#define  PHOTO6  PE15            /*??????,??*/         
#define  PHOTO7  PD3             /*??*/
#define  PHOTO8  PD4             /*??*/
#define  PHOTO9  PE7              /*??????????????*/
#define  PHOTO10 PE8              /*??????????????*/
#define  PHOTO11 PE10            /*???*/
#define  PHOTO12 PE9             /*???*/

/*HALL*/
#define  HALLFIXL  PB13        //  ????
#define  HALLFIXR  PB12        //  ???
#define  HALLDOOR  PC1         //   ????


#define  PHOTO1_MOVE         (1<<1)        /*??????*/
#define  PHOTO3_MOVE         (1<<3)        /*????????*/
#define  PHOTO4_MOVE         (1<<4)        /*????????*/
#define  PHOTO5_MOVE         (1<<5)        /*???????,??*/
#define  PHOTO6_MOVE         (1<<6)        /*??????,??*/
#define  PHOTO7_MOVE         (1<<7)        /*??*/
#define  PHOTO8_MOVE         (1<<8)        /*??*/
#define  PHOTO9_MOVE         (1<<9)        /*??????????????*/
#define  PHOTO10_MOVE        (1<<10)       /*??????????????*/
#define  PHOTO11_MOVE        (1<<11)       /*???*/
#define  PHOTO12_MOVE        (1<<12)       /*???*/
#define  HALLFIXL_MOVE       (1<<13)       /*???????*/
#define  HALLFIXR_MOVE       (1<<14)       /*???*/
#define  HALLDOOR_MOVE       (1<<15)       /*???*/
#define  TUBE_MOVE           (1<<16)       /*????,???*/
#define  INJECTION_MOVE      (1<<17)       /*????,???*/


/*Tube  Injection */
#define  TUBE         PA6    /*??????*/
#define  INJECTION    PD2 


/*HX711*/
#define HX711_DOUT    PD5
#define HX711_SCK     PC7 



/*HX713*/
#define HX713_DOUT    PA4  //????
#define HX713_SCK     PA5  //????


/*key*/
#define COL0			PE1
#define COL1			PE2
#define COL2			PE3
#define COL3			PE4

#define RAW0			PC8
#define RAW1			PC9
#define RAW2			PC10

#define ARM_MCU_YLED    PE0
#define ARM_MCU_RLED	PC13

#define RLED			PB9
#define GLED			PB10
#define TESTLED			PD11
#define _5V_DET			PB14
#define DC_PWR			PE12
#define STATUS_B		PB6



#define H_ALARM       1
#define M_ALARM       2
#define L_ALARM       3
#define T_ALARM       4

#define MOTOR_LINE       1

#define VERSION "V01.01.00.01"
#endif


#define MOTOR_LINE       1

#define VERSION "V01.01.00.01"


#endif
