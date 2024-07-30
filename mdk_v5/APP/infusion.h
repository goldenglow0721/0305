#ifndef _INFUSION_H
#define _INFUSION_H


#include "at32f403a_407.h"
#include "define.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "at32f403a_407_board.h"
#include "gt_hal_disp.h"
#include "protocol.h"
#include "audio_manage.h"


#define BrandNameMaxSize 50
#define DrugNameMaxSize 50
#define HistoryNameMaxSize 50

#define CHANGE_Speed               0x01    /*速度*/
#define CHANGE_DRIP               0x11    /*滴数*/
#define CHANGE_QUAN               0x22    /*预置量*/
#define CHANGE_TIME               0x33    /*时间*/


#define CHANGE_WEIGHT             0x44    /*体重*/
#define CHANGE_Medicine           0x55    /*药量*/
#define CHANGE_Liquid             0x66    /*液量*/
#define CHANGE_DOS                0x77    /*剂量速度*/
#define CHANGE_DOSUNIT            0x88    /*剂量单位*/ 
#define CHANGE_MedicineUNIT       0x99    /*药量单位*/ 
#define CHANGE_QUANTITY           0xAA    /*预置量*/



#define   CYLINDER_ML    (100/infusion_data.Calibdata1)
#define   CYLINDER_HIGH_ML    (100/infusion_data.Calibdata2)
#define   CYLINDER_MAXHIGH_ML    (100/(infusion_data.Calibdata2+0.35))

#define   BUBBLE_uL(speed)     (speed/3600)  //当前速度下，每ms气泡体积（uL） 
#define   BUBBLE_timeuL(speed)  (speed/12)  //单位检测时间下气泡体积（单位是微升）
#define   REQUIRED_TIMES(speed,uL)   (uL/(BUBBLE_timeuL(speed))) 
#define   CAL_SPEED_ACC_BUB_TIME_MS_NUM(speed,AcBuspeed)     (AcBuspeed*1000/BUBBLE_timeuL(speed))


typedef struct
{

	unsigned int Pressure_newAD0,Pressure_newAD40,Pressure_newAD70,Pressure_newAD120;
	double k;
	double Pressure_valuenow;				//当前压力值
	unsigned int Pressure_AD0temp;
	unsigned int Knob_Flag;
	unsigned int AD0num;
}Press_Data;
extern Press_Data press_Data;


/*精度校准*/
typedef struct
{
	double Calibdata1;
	double Calibdata2;
	
	int Pressure_AD0;
	int Pressure_AD40;
	int Pressure_AD70;
	int Pressure_AD120;
	double Pressure_value40;
	double Pressure_value70;
	double Pressure_value120;

}Infusion_Data;
extern Infusion_Data infusion_data;


/*add or reduce*/
typedef enum
{
	add,
	reduce
}AddOrRdc;




/*Dose Uint*/
typedef enum   
{
	D_ug_kg_min=0,	    
	D_ug_kg_h,      
	D_ng_kg_min,  	
	D_ng_kg_h,	
	D_mg_kg_min,       
	D_mg_kg_h, 
	D_g_kg_min,       
	D_g_kg_h,    	          	
	D_UintMAX      
}DoseUint;             

/*Medicine Uint*/
typedef enum   
{
	M_ug=0,	  
	M_mg,	
	M_g,   
	M_ng,  		        	                        	          
	M_UintMAX      
}MedicineUint;       


/*pressure unit */
typedef enum
{
	P_mmHg = 0,
	P_KPa,
	P_bar,	
	P_psi
}Pressure_Uint;           
 
//��Ҫ200ms����һ�ε�����
typedef struct
{
	uint32_t UpPressure;  					//上压力
	uint32_t DownPressure;					//下压力
	uint32_t Motor_NowAngleNumber;  		//电机当前的角度值
	uint32_t NowPhoto;  					// 
	uint32_t LeftknobStatus;				//左旋钮状态
	uint32_t RightKnobStatus;				//右旋钮状态
	NoBubble_State BubbleStatus;          	//气泡状态
	uint8_t  batterystatus;					//电池状态
	int		 voltagevalue;					//电压值
	uint32_t Speed;							//转速
	int electricity;						//电流
}SensorPack;
extern SensorPack sensorpack;


typedef struct 
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}TIME;


typedef struct
{	
	double speed; 
	double quantity; 
	TIME   time;
}Speed_ModeType;
typedef union             
{
    uint16_t BUF[sizeof(Speed_ModeType)];        
    Speed_ModeType SpeedMode;  
}Speed_Mode;
//extern Speed_Mode SpeedMode;


typedef struct
{
	double speed; 
	double quantity; 
	TIME   time;
}Time_ModeType;
typedef union             
{
    uint16_t BUF[sizeof(Time_ModeType)];        
    Time_ModeType TimeMode;  
}Time_Mode;
//extern Time_Mode TimeMode;


typedef struct
{	
	double Body;                    //体重    
    double Medicine;                //药量          
    MedicineUint Med_Uint;            
    double Liquid;   			    //液量 		
    double DoseSpeed;      		    //剂量速度
    DoseUint DS_Uint;               
    double W_Quantity;				//代入量       
    double Speed;				    //流速             
	unsigned int W_Quantity_0;
}Weight_ModeType;
typedef union             
{
    uint16_t BUF[sizeof(Weight_ModeType)];        
    Weight_ModeType WeightMode;  
}Weight_Mode;
//extern Weight_Mode WeightMode;

typedef struct
{
		double Rate,S1Rate,S2Rate,S3Rate,S4Rate,S5Rate;      
		double VTBI,S1VTBI,S2VTBI,S3VTBI,S4VTBI,S5VTBI;     
		TIME Time,S1_Time,S2_Time,S3_Time,S4_Time,S5_Time;
		double SequenVTBI;  
		TIME Sequen_Time;
		uint_fast32_t time_Second;
}Sequen_ModeType;
//extern Sequen_Mode SequenMode;
typedef union             
{
    uint16_t BUF[sizeof(Sequen_ModeType)];
    Sequen_ModeType SequenMode;
}Sequen_Mode;
//extern Sequen_Mode SequenMode;

typedef struct
{
		int drip;                                //滴数
		_Bool state;  //�ζ�ģʽ����
		unsigned int dripmaxvalue;
		double quantity;
		int drips;									//滴系数
		TIME  time;
		double speed;
}Drip_ModeType;
//extern Drip_Mode DripMode;
typedef union             
{
    uint16_t BUF[sizeof(Drip_ModeType)];        
    Drip_ModeType DripMode;  
}Drip_Mode;
//extern Drip_Mode DripMode;


typedef struct
{
    double speed; 
	double quantity; 
	TIME  time;
}Bolus_Mode;  
extern Bolus_Mode BolusMode;  


typedef struct
{
	double *                speed;
	double * 				quantity;
	TIME   *				time;
}BolusModeRun;
extern BolusModeRun Bolus_ModeRun;

typedef struct
{
	double *                speed;
	double * 				quantity;
	TIME   *				time;
}SeqBolusModeRun;
extern SeqBolusModeRun SeqBolus_ModeRun;

typedef struct
{
    double speed; 
}Exhaust_Mode;
extern Exhaust_Mode exhaustMode;






typedef struct
{
	/*��һҳ*/
	char        			NowBrandName[BrandNameMaxSize];   //���ڵ���Һ������
	char        			NowDrugName[DrugNameMaxSize];
	char        			NowHistoryName[HistoryNameMaxSize];
	int 					BlockLevel;   										//�����ȼ�
	Pressure_Uint 			PressUint;
	/*�ڶ�ҳ*/
	double 					KVOSpeed;
	uint16_t 				BubbleSize;
	double 					AccumBubbleSize;
	/*����ҳ*/
	_Bool  					LockState;               								/*Auto lock  */
	int   					LockTime; 			   											/*min*/	
	_Bool  					NoOperationState;   	   								/*no-operation  */
	int   					NoOperationTime;    	   								/*min*/	
	_Bool  					NearDoneState;           								/*Near Done State */
	int   					NearDoneTime; 	     									/*min*/	

	int 					brandnumber;
	int						drugnumber;
	int						historynumber;
	TIME					Standbytime;
	int                     history_full_flag;
}Param_SettingType;


typedef union             
{
    uint16_t BUF[sizeof(Param_SettingType)];        
    Param_SettingType ParamSetting;  
}Param_Setting;
//extern Param_Setting *ParamSetting;

typedef enum
{
	timeformat_12,
	timeformat_24
}TimeFormat;

typedef enum
{
	yyyymmdd=0,     
	mmddyyyy,      
	ddmmyyyy 
}DateFormat;


typedef struct
{
	TIME 									timeanddata;
	TimeFormat 						timeformat;
	DateFormat						dateformat;
}SysTimeAndData;

typedef struct
{
	_Bool							nightmodeflag;
	TIME							begintime;
	TIME							overtime;
	int								volume;
	int								light;
}Night_Mode;

typedef enum
{
	Chinese,
	English,
	Spanish,
	Chinese2,
	Portuguese,
	langue_max,
}Langue;


typedef struct
{
	char							software[20]; 				
	char 							SerialNumber[20]; 				
	char							MaterialNumber[20];  			
}VersionMesg;


typedef struct
{
	/*第一页*/
	short int						Volume;
	uint8_t							Light;
	int								BedNumber;
	/*第二页*/	
	SysTimeAndData					TimeAndData;
	Langue							langue;
	Night_Mode						NightMode;
	/*第三页*/
	VersionMesg						Version;
}System_SettingType;

typedef union             
{
    uint16_t BUF[sizeof(System_SettingType)];
    System_SettingType SystemSetting;  
}System_Setting;
//extern System_Setting SystemSetting;


typedef struct
{
	double 							MaxSpeed;			//最大速度
	_Bool 							AntiState;			//Anti开关状态
	_Bool							KVOState;			//KVO开关状态
	_Bool							Alarm;				//报警状态
	unsigned int 					AD0_Notube;			//AD0通道数值
	unsigned int 					ADU_Notube;			//ADU通道数值
}System_MaintainType;
typedef union             
{
    uint16_t BUF[sizeof(System_MaintainType)];        
    System_MaintainType SystemMaintain;  
}System_Maintain;
//extern System_Maintain *SystemMaintain;




typedef struct
{
	int   		   			glevel;  				/*报警等级*/
	unsigned int   			alarmmsg; 				/*报警内容*/
	int 					ReminderFlag;			/*无操作报警flag*/ 
	char					drugname[30];
	char 					tubename[30];
}Infusion_Now;
extern Infusion_Now InfusionNow;









typedef struct
{
	char*					title;
	double *                speed;
	double * 				quantity;
	TIME   *				time;
	gt_scr_init_func_cb_t   init_func_cb; //需要返回的地方

}SpeedAndTimeRun;

typedef struct
{
    double Nowcumulant;
}Cumulant_Mode;
extern Cumulant_Mode cumulantMode; 

typedef struct
{
	unsigned int  airbubble_num;
	unsigned int  airbubble_time;
}AirBubble_Data;
extern AirBubble_Data airbubble_Data;

typedef struct
{
	char*					title;
	int *					drip;
	double *                speed;
	double * 				quantity;
	TIME   *				time;
	gt_scr_init_func_cb_t   init_func_cb; //需要返回的地方

}DripMode_Run;
 
typedef struct
{
	char*					title;
	double *                speed;
	double *				Body;
	double * 				quantity;
	double *				DoseSpeed;
	TIME   *				time;
	gt_scr_init_func_cb_t   init_func_cb; //需要返回的地方

}WeightMode_Run;
 
typedef struct
{
	char*					title;
	double 					*speed1,*speed2,*speed3,*speed4,*speed5;
	double  				*quantity1,*quantity2,*quantity3,*quantity4,*quantity5;
	TIME   					*time1,*time2,*time3,*time4,*time5;
	TIME *					time;//总的时间
	double *				speed;//当前的运行速度
	double *				quantity;//总代入量
	uint32_t * 				Seqnum;//当前的序列
	gt_scr_init_func_cb_t   init_func_cb; //需要返回的地方
	uint32_t *				value;//总有效序列

}SeqMode_Run;




extern System_Setting SystemSettingconfig;
#define SystemSetting SystemSettingconfig.SystemSetting 
extern Param_Setting ParamSettingconfig;
extern System_Maintain SystemMaintainconfig;
#define ParamSetting ParamSettingconfig.ParamSetting
#define SystemMaintain SystemMaintainconfig.SystemMaintain
extern Speed_Mode SpeedModeconfig;
extern Time_Mode TimeModeconfig;
extern Weight_Mode WeightModeconfig;
extern Sequen_Mode SequenModeconfig;
extern Drip_Mode DripModeconfig;
#define SpeedMode SpeedModeconfig.SpeedMode
#define	TimeMode TimeModeconfig.TimeMode
#define	WeightMode WeightModeconfig.WeightMode
#define	SequenMode SequenModeconfig.SequenMode
#define	DripMode DripModeconfig.DripMode

void ReadSystemSettingMessageFromFlash(void);
void WriteSystemSettingMessageToFlash(void);
void ReadParamSettingMessageFromFlash(void);
void WriteParamSettingMessageToFlash(void);
void ReadSystemMaintainMessageFromFlash(void); 
void WriteSystemMaintainMessageToFlash(void);

int readInfusionTubeListFromFlash(void); 
void writeInfusionTubeListToFlash(void);
void writeAddInfusionTubeListToFlash(void);
int readDrugListFromFlash(void); 
void WriteDrugListToFlash(void);
void WriteAddDrugListToFlash(void);
void readHistoryListFromFlash(void);


void WriteSpeedModeMessageToFlash(void);
void ReadSpeedModeMessageFromFlash(void);
void WriteTimeModeMessageToFlash(void);
void ReadTimeModeMessageFromFlash(void);
void WriteWeightModeMessageToFlash(void); 
void ReadWeightModeMessageFromFlash(void);
void WriteSeqModeMessageToFlash(void);
void ReadSeqModeMessageFromFlash(void);
void WriteDripModeMessageToFlash(void);
void ReadDripModeMessageFromFlash(void);

double MedicineUintComeToConversion(MedicineUint SourceUint,double SourceData,MedicineUint ToUint);
double DOSEUintComeToConversion(DoseUint SourceUint,double SourceData,DoseUint ToUint);
void UpdateSpeedModeTheDisplay(int id,double* FlowRate ,double* Quantity, TIME* Time);
void UpdateTimeModeTheDisplay(int id,double* FlowRate ,double* Quantity, TIME* Time);
void UpdateDripModeTheDisplay(int id,int* Drip ,double* Quantity, TIME* Time);
void UpdateWeightModeTheDisplay(int id);

int getAverage(int *val, int num);

float GetNowcumulant(void);
void SetNowcumulant(double nowanglenumber);
void ClearNowcumulant(void);










/*������װ*/
int ObDefValue(void);
void ChangeScreenBlk(AddOrRdc cmd);
char* GetPressUintString(Pressure_Uint Press_Uint);
double PressureConversion(double NowPressure,Pressure_Uint FromPressUint,Pressure_Uint ToPressUint);
void calpressureADandValue(int blocklevel);
void SoundManage(_Bool SoundOnAndOffFlag,unsigned int glevel);
int GetNowAlarmLeve12(void);
double CalSpeed(double speed);
char* GetMedicineUintString(MedicineUint MUint);
char* GetDoseUintString(DoseUint DUint);
TIME CalSurplusTime(double PresetValue,double Speed);
TIME DripCalSurplusTime(double PresetValue,int Drip);
_Bool JudgedinfusionNeaeTimeAlarm(TIME* ResidueTime);
_Bool JudgedInfusionTubeFallOff_P(  unsigned int NowPrVal);
_Bool TubeFallTimeCountDown(_Bool StartFlag);
double CalCumulant(double NowAngleNumber,double speed);

_Bool JudgeINjection(unsigned int Photo,double UTimeMS);
_Bool CalAccumulativeBubble(unsigned int Photo,double AcBubTimeNumMs);
_Bool JudgedDownBlockRelease_AD(int blocklevel,unsigned int  NowPrVal);
int getParamsettingBlockLevel();
_Bool JudgedInfusionDownBlock_AD(  unsigned int NowPrVal);

_Bool DownBlockTimeCountDown(_Bool StartFlag);

void JudgeInstallTube();



uint32_t SetProgressRunSpeed(double speed);
void vtaskmanage(uint8_t id);

void BattetyStatusAlarm(unsigned char AFlag);


_Bool JudgedInfusionUpBlock(  unsigned int NowPre3AD);
int LockTimeCountDown(_Bool DevBool,_Bool LockTime);
_Bool UpBlockTimeCountDown(_Bool StartFlag);
void BattetyLowAndDepleteAlarm(unsigned char NowBatt);

void flash_read(uint32_t read_addr, uint16_t *p_buffer, uint16_t num_read);
void detection_motor_start_point_and_update_pressure(void);
void infusion_apparatus_detection(void);

#endif


