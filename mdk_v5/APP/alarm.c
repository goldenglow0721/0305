#include "alarm.h"

int ALARM_Message=0;
static _Bool LockTimeFlag=FALSE;    
static int  LockTimeSec=5*60;      
static _Bool LOCK_NewALARMFLAG=FALSE;        
static int DEPLETETime=180;       
 
_Bool NewAddAlarmFlag=FALSE;  
static _Bool DEPLETEFlag=FALSE;   
static unsigned int AllAlarmMark_H=0;
static unsigned int AllAlarmMark_Z=0;
static unsigned int AllAlarmMark_L=0;
static unsigned int AllAlarmMark_T=0;
int alarmflag;



static _Bool ASoundFlag=FALSE;    //报警警音标志 TRUE:静音 FALSE：报警响起
static int ASoundTime=120;       //120秒 静音2分时间
int neardone=0;
_Bool NewALARMFLAG=FALSE;   /*新报警标志*/

Alarm_Data alarm_data = {0};

AlarmMessage alarmMessage[ALARM_MAX+1]=
{
	/*高级报警*/
	ALARM_START,					"","","","","", 
	ALARM_UPPER_OCCLUSION,			"上阻塞","Upstream Occlusion","Oclusión Aguas Arriba","上阻塞","Oclusão a montante",
	ALARM_UNDERBLOCKING,			"下阻塞","Downstream Occlusion","Oclusión Aguas Abajo","下阻塞","Oclusão a jusante",
	ALARM_BATTERY_DEPLETE,			"电池耗尽","No Battery","Sin Batería","電池耗盡","Sem bateria",
	ALARM_FINISH_KVO, 			 	"KVO完成","KVO Finished","KVO Terminado","KVO完成","KVO finalizado",
	ALARM_HYPERACOUSTIC,	 	    "管路气泡","Air in Line","Burbuja En el Tubo","管路氣泡","Ar na linha",
	ALARM_SYSTEM_FAILURE,	 	    "系统故障","System Error","Error del Sistema","系統故障","Erro de sistema",
	ALARM_ABNORMAL_SWITCH, 	     	"切换异常","Abnormal switch","Interruptor Anormal","切換異常","Mudança anormal",
	ALARM_INFUSION_DRAIN,			"输液完成","VTBI Completed","VTBI Completado","輸液完成","VTBI completo",
	ALARM_INFUSION_OFF,			   	"输液管脱落","IV set or Knob is not Installed Well","El IV set o perilla no está bien instalada","輸液管脫落","Equipo ou botão não está bem instalado",         
	ALARM_CUMULANT_BUBBLE,   	 	"累积气泡过大","Exceed Accum. Bubbles","Exceder Burbujas Acumuladas","累積氣泡過大","Exceder Acum. Bolhas",
	ALARM_HIGH,	 		         	"","","","","",
	/*中级报警*/
	ALARM_DAJI_FINISH,              "待机时间结束","Standby Time Expired","Tiempo de Espera Expirado","待機時間結束","Tempo de espera expirado",
	ALARM_MID,  	            	"","","","","",
	/*低级报警*/
	ALARM_NO_OPERATION,			    "无操作","Reminder","Recordatorio","無操作","Lembrete",
	ALARM_BATTERY_LOW,			    "电池电量低","Low Battery","Batería Baja","電池電量低","Bateria fraca",
	ALARM_NO_BATTETY,				"未安装电池","No Battery Inserted","Sin Batería insertada","未安裝電池","Nenhuma bateria inserida",
	ALARM_NEAR_DONE,				"接近完成","Time Near End","Tiempo Casi Terminado","接近完成","Tempo próximo do fim",
	ALARM_NET_POWER_OFF,    		"网电源脱落","No AC Power","Sin Fuente de CA","網電源脫落","Sem alimentação eletrica",
	ALARM_LOW,		                "","","","","",
	/*over*/

	ALARM_MAX,						"","","","",""  
};

int NowAlarmMessage[ALARM_MAX+1];
//获取现在的报警信息内容
void GetNowAlarmMessage(unsigned int* Glevel)
{
	static int i=1;
	int MAX=ALARM_MAX;
	
	if(i>=ALARM_MAX)
	{
		i=1;
	}
	for(i;i<ALARM_MAX;i++)
	{                  
		if(NowAlarmMessage[i]!=0)
		{
			MAX=NowAlarmMessage[i];     //有报警信息则保存并退出
			*Glevel = MAX;
			i++;
			break;
		}
	  	//防止当没有报警信息时一直播报之前的报警
	  	*Glevel = MAX;				
	}	
}

void NowAlarmMessageinit()
{
	int i=0;
	for(i=0;i<=ALARM_MAX;i++){
		NowAlarmMessage[1]=0;
	}
}

_Bool JudgedYesNoAlarm(int Message)
{
	if(Message<ALARM_HIGH) 		//11
	{
		if(AllAlarmMark_H &(1<<Message))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if(Message<ALARM_MID) //28
	{
		if(AllAlarmMark_Z &(1<<(Message-ALARM_HIGH)))
		{ 
			return TRUE;
		}
		else
		{
			return FALSE;
		}		
	}
	else if(Message<ALARM_LOW)
	{
		if(AllAlarmMark_L &(1<<(Message-ALARM_MID)))
		{ 
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if(Message<ALARM_MAX)
	{
		if(AllAlarmMark_T &(1<<(Message-ALARM_LOW)))
		{ 
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}







_Bool ClearAlarmFlag(int Message)
{
	#if wait
	KillTimer(hwnd_my,_SoundAlarmHigh_);
	KillTimer(hwnd_my,_SoundAlarmLow_);
	KillTimer(hwnd_my,_SoundAlarmmid_);	
	#endif
	
	if(Message<ALARM_HIGH)
	{
		AllAlarmMark_H &= (~(1<<Message));              
	}
	else if(Message<ALARM_MID)
	{
		AllAlarmMark_Z &= (~(1<<(Message-ALARM_HIGH))); 
	}
	else if(Message<ALARM_LOW)
	{
		AllAlarmMark_L &= (~(1<<(Message-ALARM_MID)));  
	}
	else if(Message<ALARM_MAX)
	{
		AllAlarmMark_T &= (~(1<<(Message-ALARM_LOW)));   
	}
	else{
		;
	}
}




_Bool addAlarmFlag(int Message)
{
	
	alarmflag=0;
	if(Message<ALARM_HIGH)
	{
		AllAlarmMark_H |= (1<<Message);					
		AddNewSoundAFlag();  
		AddLockNewAFlag();  
	}
	else if(Message<ALARM_MID)
	{
		AllAlarmMark_Z |= (1<<(Message-ALARM_HIGH));  
		AddNewSoundAFlag(); 
		AddLockNewAFlag();
	}
	else if(Message<ALARM_LOW)
	{
		AddNewSoundAFlag();

		AllAlarmMark_L |= (1<<(Message-ALARM_MID)); 	
	}
	else if(Message<ALARM_MAX)
	{
		AllAlarmMark_T |= (1<<(Message-ALARM_LOW)); 	
	}	
}



void AddNewSoundAFlag()
{
	#if wait
	system("echo 0 > /sys/class/gpio/gpio140/value");
	//TRUE:闈欓煶鏃舵坊鍔犳柊鎶�??︽爣�??
	#endif
	
	if(ASoundFlag)
	{
		NewALARMFLAG=TRUE;
	}
}




void AddLockNewAFlag()
{
	if(LockTimeFlag)
	{
		LOCK_NewALARMFLAG=TRUE;    
	}
	
}

void SetNewAddAlarmFlag(_Bool Flag)
{
	NewAddAlarmFlag=Flag;
}

/*Get a new alarm Flag*/
_Bool GetNewAddAlarmFlag()
{
	return NewAddAlarmFlag;
}



int GetAlarmLevel(int MeNum)
{
	int level=0;
	if(MeNum==ALARM_START)
	{
		level=N0_ALARM;
	}
	else if(MeNum<ALARM_HIGH)
	{
		level=H_ALARM;
	}
	else if(MeNum<ALARM_MID) 
	{
		level=M_ALARM;
	}
	else if(MeNum<ALARM_LOW)
	{
		level=L_ALARM;
	}
	else if(MeNum<ALARM_MAX)
	{
		level=T_ALARM;
	}
	else  
	{
		level=N0_ALARM; 
	}
	return level;
}





int GetNowAlarmLevel(unsigned int* Glevel)
{
	int i=1;
	int MAX=ALARM_MAX;
	for(i=1;i<ALARM_MAX;i++)
	{
		if(NowAlarmMessage[i]!=0)
		{
			if(MAX>NowAlarmMessage[i])
			{
				MAX=NowAlarmMessage[i];     
			}
		}
	}
	*Glevel= GetAlarmLevel(MAX);
	return *Glevel;
}




//获得当前的报警信息
int GetCurrentAlarm(int AlarmLevel)
{
	static int NowNum=1;
	int i=0;

	if(AlarmLevel==N0_ALARM)
	{
		return 0;
	}
	
	for(i=NowNum;i<=ALARM_MAX;i++)
	{
		NowNum=i+1;	
		
		if((NowAlarmMessage[i]<ALARM_MAX)&&(NowAlarmMessage[i]>ALARM_START))
		{
			return NowAlarmMessage[i];  
		}
		else if(i<ALARM_MAX)
		{
			continue;
		}
		else if(i>=ALARM_MAX)
		{
			i=0;
			continue;
		}
		if(AlarmLevel==N0_ALARM)
		{	
			return 0;
		}
	}
	return 0;	
}

//电池耗尽关机倒计时
int DEPLETETimeCountDown()
{
	if(DEPLETEFlag)
	{		
		DEPLETETime--;
		if(DEPLETETime<=0)
		{ 
			DEPLETETime=0; 
		}
	}
	else
	{
		DEPLETETime=180;  //3*60;
	}
	return DEPLETETime;
}

_Bool GetDEPLETEFlag()
{
	return DEPLETEFlag;
}

void SetDEPLETEFlag(_Bool ASFlag)
{
	DEPLETEFlag=ASFlag;
}

//获取报警中的最高等级
int GetNowAlarmLeve1l(unsigned int* Glevel)
{
	int i=1;
	int MAX=ALARM_MAX;
	for(i=1;i<ALARM_MAX;i++)
	{
		if(NowAlarmMessage[i]!=0)
		{
			if(MAX>NowAlarmMessage[i])
			{
				MAX=NowAlarmMessage[i];     //取非0的最小值就是最高级报警
			}
		}
	}
	*Glevel= GetAlarmLevel(MAX);
	return *Glevel;
}



//添加报警信息
void AddAlarm(int Message)
{

	int i=1;
	if(JudgedYesNoAlarm(Message))       //判断有无当前报警存在
	{
	    return;
	}
	else
	{
		addAlarmFlag(Message);

		#if History
		Write_Record_Events(Message,EA_Alarm,alarmMessage[Message].AlarmChar); 
		#endif

		for(i=1;i<ALARM_MAX;i++)
		{
			if(NowAlarmMessage[i]==0)
			{
				NowAlarmMessage[i]=Message;
				ALARM_Message=GetCurrentAlarm(GetNowAlarmLeve1l(&InfusionNow.glevel));	//文字报警信息 
				return ;
			}
		}
	}	
}

//清除报警信息
void ClearAlarm(int Message)
{
	int i=1;
	if(JudgedYesNoAlarm(Message))    //有
	{
	   ClearAlarmFlag(Message);

	   #if History
	   Write_Record_Events(Message,EA_CleAlarm,alarmMessage[Message].AlarmChar);
	   #endif 

	}
	else
	{
	   return;
	}
	
	for(i=1;i<ALARM_MAX;i++)
	{
		if(NowAlarmMessage[i]==Message)
		{
			NowAlarmMessage[i]=0;
			//printf("find this alarm;\n");
			return ;
		}
	}
}






_Bool GetAlarmSoundFlag()
{
	return ASoundFlag;
}

void SetAlarmSoundFlag(_Bool ASFlag)
{
	ASoundFlag=ASFlag;
}


/*Alarm sound CountDown*/
int AlarmSoundTimeCountDown()
{
	if(ASoundFlag)
	{		
		ASoundTime--;
		if(ASoundTime<=0)
		{ 
			ASoundTime=0; 
		}
	}
	else
	{
		ASoundTime=116;  //2*60;
	}
	return ASoundTime;
}




_Bool AlarmSoundSwitch(unsigned int SAlevel,_Bool ABATDE)       
{
	int flag=0;
	if(ASoundFlag) //如果报警静音，报警再次响起
	{
		#if wait
		system("echo 0 > /sys/class/gpio/gpio140/value");
		#endif
		ASoundFlag=FALSE;
		flag=1;
		alarm_data.Runtime = 0;
	}
	else
	{
		if((SAlevel==H_ALARM) || (SAlevel==M_ALARM) || (SAlevel==L_ALARM) )
		{
			if(!ABATDE) //如果存在报警，报警且不为电池耗尽
			{
				#if wait
				system("echo 1 > /sys/class/gpio/gpio140/value");
				#endif
				ASoundFlag=TRUE; //报警静音标志置1
				SetNewSoundAFlag(FALSE); //消除新报警标志
				flag=2;
			}
			else
			{
				flag=4;
			}
		}
		/*else if(SAlevel==L_ALARM)
		{
			ASoundFlag=TRUE; //报警静音标志置1
			SetNewSoundAFlag(FALSE); //消除新报警标志
			flag=5;
		}*/
		else
		{
			flag=3;
		}
	}
	return flag;
}

_Bool GetNewSoundAFlag()
{
	return NewALARMFLAG;
}

void SetNewSoundAFlag(_Bool NSFlag)
{
	NewALARMFLAG=NSFlag;
}



int GetNerDoneFlag()
{
	return neardone;
}

void SetNerDoneFlag(int ndone)
{
	neardone=ndone;
}


void ClearAllAlarm()
{
	int i=1;
	AllAlarmMark_H=0;
	AllAlarmMark_Z=0;
	AllAlarmMark_L=0;
	AllAlarmMark_T=0;
	
	for(i=1;i<ALARM_MAX;i++)
	{
		NowAlarmMessage[i]=0;
	}
}




/********************************无操作返回功能**************************************/
int noOperTime= 15;
/*
	选择【自动锁键时间】：
	关、1～5min。
	设置具体时间后，运行过程中，若在设定的锁键时间内无操作、无高级报警，按键板自动锁定。设置为【关】则表示关闭自动加锁功能。
*/
int SetNoOperTimeLoadBack(int sec)
{
	noOperTime=sec;
	return noOperTime;
}


/*倒计数*/
int NoOperTimeCountDown()
{
	if(noOperTime>0){
		noOperTime -=1;
	}else{
		noOperTime =0;
	}
	return noOperTime;              
}


/********************************无操作功能***************************************/
/*
	说明：选择【无操作时间】：关、1～5min。设置具体时间后，安装好输液器，在设定
	时间内没有对泵进行任何操作（包含对按键、推拉盒、拉柄的操作），触发【无
	操作】报警，提示用户进行下一步操作。设置为【关】则表示关闭该功能。
*/


int noOperFunctionTime=5*60;  //5min


/*设置无操作报警  */ 
/*分钟*/
int SetNoOperFunctionTimeAlarm(int min)
{
	noOperFunctionTime=min*60;
	return noOperFunctionTime;	
}


/*无操作功能倒计数*/
int NoOperFunctionTimeCountDown(_Bool noOperBool)
{
	if(noOperBool)
	{
		if(noOperFunctionTime>0){
			noOperFunctionTime--;
		}else{
			noOperFunctionTime=0;
		}
	}else{
		noOperFunctionTime=5*60;
	}
//	printf("noOperFunctionTime =%d \n",noOperFunctionTime);
	return noOperFunctionTime; 
}
/*判断时间是否为0 */
int GetNoOperFunctionTime()
{
	return noOperFunctionTime;
}



void CleargHintAlarm()
{
	int Meg=0;
	for(Meg=ALARM_LOW+1;Meg<ALARM_MAX;Meg++)
	{
		ClearAlarm(Meg);
	}
}
void ClearLowAlarm()
{
	int Meg=0;
	for(Meg=ALARM_MID+1;Meg<ALARM_LOW;Meg++){
		ClearAlarm(Meg);
	}
}

void ClearHighAlarm()
{
	int Meg=0;
	for(Meg=ALARM_START+1;Meg<ALARM_HIGH;Meg++){
		ClearAlarm(Meg);
	}
}

void ClearMidAlarm()
{
	int Meg=0;
	for(Meg=ALARM_HIGH+1;Meg<ALARM_MID;Meg++){
		ClearAlarm(Meg);
	}
}




/*加锁*/
int Lock()
{
	LockTimeFlag=TRUE;
	SetLockNewAFlag(FALSE);
}

/*解锁*/
int UnLock(int LockTime)
{
   LockTimeFlag=FALSE;
   LockTimeSec=LockTime*60;
}

void SetLockNewAFlag(_Bool LAFlag)
{
	LOCK_NewALARMFLAG=LAFlag;
}

_Bool GetLockFlag()
{
	return LockTimeFlag;
}

_Bool GetLockNewAFlag()
{
	return LOCK_NewALARMFLAG;
}

/*设置自动锁倒计时时间分钟*/
int SetAutoLockTime(int Min)
{
	LockTimeSec=Min*60;
}






















