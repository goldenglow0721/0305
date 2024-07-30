#ifndef _ALARM_H_
#define _ALARM_H_

#include "infusion.h"


extern int alarmflag;



#define N0_ALARM      0
#define H_ALARM       1
#define M_ALARM       2
#define L_ALARM       3
#define T_ALARM       4




enum{
	/*低级报警*/	
	  ALARM_START,					
	  ALARM_UPPER_OCCLUSION,			//	上阻塞
	  ALARM_UNDERBLOCKING,				 // 	下阻塞
	  ALARM_BATTERY_DEPLETE,			//		电池耗尽				        
	  ALARM_FINISH_KVO, 			 		//KVO完成
	  ALARM_HYPERACOUSTIC,	 	    // 		管路气泡
	  ALARM_SYSTEM_FAILURE,	 	  //		系统故障
	  ALARM_ABNORMAL_SWITCH, 				//切换异常
	  ALARM_INFUSION_DRAIN,			 	////	输液完成
	  ALARM_INFUSION_OFF,					//输液管脱落
	  ALARM_CUMULANT_BUBBLE,   	 	  //	累计气泡过大
	  ALARM_HIGH,	 		         	//
	  /*中级报警*/		
	  ALARM_DAJI_FINISH,               //待机时间结束	   
	  ALARM_MID,  	            	   
	  /*低级报警*/
	  ALARM_NO_OPERATION,			   		//无操作
	  ALARM_BATTERY_LOW,			  	//////	电池电量低
	  ALARM_NO_BATTETY,				   		////未安装电池
	  ALARM_NEAR_DONE,				 		//	接近完成
	  ALARM_NET_POWER_OFF,    		 	////	网电源脱落
	  ALARM_LOW,		              //
	  /*over*/    	    
	  ALARM_MAX,						 
};

typedef struct
{

	unsigned int Runtime;
}Alarm_Data;
extern Alarm_Data alarm_data;



typedef struct
{
	int 				AlarmType;
	char 				AlarmChar[langue_max][50];
}AlarmMessage;
extern AlarmMessage alarmMessage[ALARM_MAX+1];
extern int NowAlarmMessage[ALARM_MAX+1];




void NowAlarmMessageinit(void);
_Bool JudgedYesNoAlarm(int Message);
_Bool addAlarmFlag(int Message);
_Bool ClearAlarmFlag(int Message);
void AddNewSoundAFlag(void);
void AddLockNewAFlag(void);
_Bool GetNewAddAlarmFlag(void);
void SetNewAddAlarmFlag(_Bool Flag);

int GetAlarmLevel(int MeNum);
int GetNowAlarmLeve1l(unsigned int* Glevel);
int GetNowAlarmLevel(unsigned int* Glevel);
int GetCurrentAlarm(int AlarmLevel);
void AddAlarm(int Message);
void ClearAlarm(int Message);
void GetNowAlarmMessage(unsigned int* Glevel);

int DEPLETETimeCountDown(void);
_Bool GetDEPLETEFlag(void);
void SetDEPLETEFlag(_Bool ASFlag);



extern int ALARM_Message;
extern AlarmMessage alarmMessage[ALARM_MAX+1];
extern int NowAlarmMessage[ALARM_MAX+1];
extern int alarmflag;



/*Alarm sound on and off */
_Bool AlarmSoundSwitch(unsigned int SAlevel,_Bool ABATDE);       
_Bool GetAlarmSoundFlag(void);
void SetAlarmSoundFlag(_Bool ASFlag);

/*Alarm sound subtract*/
int AlarmSoundTimeCountDown(void);
_Bool GetNewSoundAFlag(void);
void SetNewSoundAFlag(_Bool NSFlag);
void AddNewSoundAFlag(void);

int GetNerDoneFlag(void);
void SetNerDoneFlag(int ndone);
void ClearAllAlarm(void);


#define  NOPRERTO_TIME  15   // 15S
int SetNoOperTimeLoadBack(int sec);
/*倒计数*/
int NoOperTimeCountDown(void);
int SetNoOperFunctionTimeAlarm(int min);
int NoOperFunctionTimeCountDown(_Bool noOperBool);
int GetNoOperFunctionTime(void);
void addAlarm(int Message);


void CleargHintAlarm(void);
void ClearLowAlarm(void);
void ClearHighAlarm();
void ClearMidAlarm();
int UnLock(int LockTime);
int Lock();
void SetLockNewAFlag(_Bool LAFlag);
_Bool GetLockNewAFlag();
_Bool GetLockFlag();
int SetAutoLockTime(int Min);



#endif

