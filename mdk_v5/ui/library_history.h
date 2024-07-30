#ifndef LIBRARY_HISTORY_H
#define LIBRARY_HISTORY_H


#include "ui.h"


#define History_MaxNumber 2500


extern char historyname1[30];
extern char historyname2[30];
extern char historyname3[30];
extern char historyname4[30];
extern char historyname5[30];
extern char historyname6[50];
extern char historyname7[50];
extern char historyname8[50];
extern char historyname9[50];
extern char historyname10[50];

extern char historytime1[50];
extern char historytime2[50];
extern char historytime3[50];
extern char historytime4[50];
extern char historytime5[50];

extern char historyData1[30];
extern char historyData2[30];
extern char historyData3[30];
extern char historyData4[30];
extern char historyData5[30];


typedef struct 
{

    char        ch_name1[50];                        
    char        en_name1[50];                       
    char        es_name1[50];
    char        ch2_name1[50];
    char        pu_name1[50];

    char        ch_name2[50];                        
    char        en_name2[50];                       
    char        es_name2[50];
    char        ch2_name2[50];
    char        pu_name2[50];

    char        Data[30];
    TIME        TIME_DATA;

}HistoryNodeMessage;



typedef struct history_node
{
    struct history_node* nextnode;
    HistoryNodeMessage message;
   
}HistoryNode_t;



typedef struct historyList{
    int node_number;                    
    HistoryNode_t * node;
}HistoryList;


typedef struct
{
	int EvType;  
	char*  EvChar;
}RecordEv;

enum{
    /****************动作***********************************************/
    EA_Starting=0,	   /*开机*/
    EA_Shutdown,	   /*关机*/
    EA_Await,	  	   /*待机*/	 
    EA_Alarm, 	       /*报警*/
    EA_CleAlarm,	   /*消警*/
    EA_CleCumulant,   /*清零*/	 
    EA_Amend, 	       /*修改*/
    EA_start,		   /*启动*/
    EA_stop,		   /*暂停*/
    EA_Set,		   /*设置*/
    EA_Adjust,		   /*校准*/	 
    EA_Into,		   /*进入*/
    EA_Delete,			/*删除*/
    EA_Add,			/*添加*/
    /****************描述***********************************************/
    Ev_Startup,                   /*开机*/
    Ev_EntMODE,	     		      /*进入模式选择*/
    Ev_EntSpeed,	     		  /*进入速度模式*/
    Ev_EntTime, 	     		  /*进入时间模式*/
    Ev_EntWeight,	       		  /*进入体重模式*/
    Ev_EntSequential,			 /*进入序列模式*/
    Ev_EntDrip,				      /*进入滴定模式*/
    Ev_EntDruglib,                /*进入药品库*/
    Ev_General,                   /*进入输注设定*/
    Ev_SystemSetting,             /*进入系统设定*/
    Ev_Maintenance1,              /*进入系统维护8888*/
    Ev_Maintenance2,              /*进入系统维护6686*/
    Ev_EntBolus,	       		  /*进入快进菜单*/	 
    Ev_EntExhaust,	       		  /*进入排气菜单*/	 	 
    Ev_SetSpeed,	     		  /*速度为:*/
    Ev_SetTime,	     		  /*时间为:*/
    Ev_SetLiquid,	    		  /*液量为:*/
    Ev_SetWeight,	        	  /*设置为:*/
    Ev_SetWeightUint,	          /*体重单位:*/
    Ev_SetMeDose,	     		  /*药量为:*/
    Ev_SetDose,	     		  /*剂量*/
    Ev_SetQuantity,	     	  /*待入量*/	
    Ev_GetVolume,	     	  	  /*获得累计量*/	
    Ev_SetDripswitch,	     	  /*滴数为*/	
    Ev_SetKVO,	     	  		  /*KVO:*/	  
    Ev_SetBubbleSize,	     	  /*气泡大小:*/	   
    Ev_AccumBubble,	     	  /*累计气泡:*/	   
    Ev_EnterKVO,				  /*进入KVO*/	 
    Ev_ConfirmBrand,	     	  /*品牌确认*/	   	 
    Ev_SetMedicineUint,	   	  /*药量单位:*/	 
    Ev_SetDoseSpeed,	     	  /*剂量速度:*/	 
    Ev_SetDoseUnit,	     	  /*剂量单位:*/
    Ev_SetPressUnit,	     	  /*压力单位:*/  
    Ev_Setlightsize,	     	  /*亮度:*/  	 
    Ev_SetLockTime,	     	  /*自动锁为:*/
    Ev_SetNoOperationTime, 	  /*无操作为:*/  
    Ev_SetNearDoneTime, 	      /*设置接近完成:*/  	 
    Ev_BedNum,  	              /*床号*/
    Ev_StarInjection,	 	      /*开始输液*/
    Ev_FinishInjection, 		  /*输液完成*/
    Ev_StopInjection,	 		  /*停止输液*/
    Ev_KeySound,	 		 	  /*按键声音*/     
    Ev_AlarmSound,	 		 	  /*报警声音*/     	 
    Ev_CloseAlarmS,     		  /*清除所有报警*/
    Ev_langue, 				  /*设置语言*/
    Ev_SoundSize, 				  /*设置音量:*/
    Ev_NightMode, 				  /*夜间模式*/
    Ev_ClearAccVolu,	 		  /*累积量清零*/
    Ev_AntiBolus,	 			  /*Anti-Bolus*/          	 
    Ev_CorrectSucceed,	 		  /*校准成功*/
    Ev_CorrectFail,     		  /*校准失败*/
    Ev_ChangeSysTime,	 		  /*系统时间*/
    Ev_Shutdown,				  /*关机操作*/
    Ev_InfusionAdjust,			  /*精度校准*/	 
    Ev_PressureAdjust, 		  /*压力校准*/	 
    Ev_RecoverSet,				  /*恢复出厂设置*/
    Ev_MaxSpeed,			      /*最大速度*/	
    Ev_NetworkDown,			  /*网电掉电报警*/	
    Ev_BolusSpeed,		          /*快进速度*/
    Ev_BolusQuantity,			  /*快进预置量*/		
    Ev_BolusTime, 		 		  /*快进时间*/		 
    Ev_ExhaustSpeed, 		 	  /*排气速度*/		 	 
    Ev_SpeedERRALARM,			  /*速度错误报警*/	
    Ev_CleSpeedEALARM,			  /*清除速度错误报警*/
    Ev_ELELowALARM,			  /*电量低报警*/	 
    Ev_CleELELowALARM,			  /*清除电量低报警*/
    Ev_ChokeALARM,				  /*阻塞*/
    Ev_CleChokeALARM,			  /*清除阻塞报警*/
    Ev_CleOverALARM,			  /*清除完成报警*/
    Ev_EnterBlous,				  /*进入快进*/
    Ev_AutoBlous,				 /*自动快进*/
    Ev_ExitBlous,				  /*结束快进*/
    Ev_EnterExhaust,			  /*进入排气*/
    Ev_ExitExhaust,			  /*结束排气*/
    Ev_ConfirmDrug,			  /*药物确认*/
    Ev_Tube,					/*输液器品牌*/	
    Ev_PressureRating,			 /*阻塞等级为：*/
    Ev_Drip,                     /*滴系数：*/
    Ev_MAX,				    
};

/************************function*************************/
void initHistoryList();

void destroyHistoryList(void);

_Bool addHistoryNode(HistoryNode_t* newnode,_Bool flag);

_Bool AddHistoryNode(HistoryNode_t* newnode,_Bool flag);

int getNowHistoryListNum(void);

void fineHistoryNode_five_ById(int id);

void createHistoryLib(void);

HistoryNode_t* getThefirstHistoryNode(void);

HistoryNode_t* fineHistoryNodeByPosit(int id);

void not_first_start_write_history_info(int MoTion,int Describe,char* Data);

void Historynodelangue(char* Historytime,char* Historyname_O,char* Historyname_T,char* historyData,HistoryNode_t* node);

#endif