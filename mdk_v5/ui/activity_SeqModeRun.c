#include "ui.h"







/** SeqModeRun */
gt_obj_st * SeqModeRun = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * bar1 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * lab17 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab18 = NULL;
static gt_obj_st * lab19 = NULL;
static gt_obj_st * lab20 = NULL;
static gt_obj_st * lab21 = NULL;
static _gt_timer_st * timer_run_300msec;
static _gt_timer_st * run_progress;

static char buffer[50];

SeqMode_Run SeqMode_run;

extern int BlevelData[4];

uint32_t current;

static const char title[5][9][50]={
	"序列模式",
	"快进",
	"品牌",
	"累计量",
	"压力",
	"剩余时间",
	"暂停",
	"流速",
	"待入量",

	"Sequential Mode",
	"Bolus",
	"Brand",
	"Total Volume",
	"Pressure",
	"Remain Time",
	"Pause",
	"Rate",
	"VTBI",
	
	"El Modo Secuencial",
	"Bolo",
	"Marca",
	"Volumen total",
	"Presión",
	"Tiempo restante",
	"Pausa",
	"Tasa",
	"VTBI",

	"序列模式",
	"快進",
	"品牌",
	"累計量",
	"壓力",
	"剩餘時間",
	"暫停",
	"流速",
	"待入量",

	"Modo sequencial",
	"Bolus",
	"Marca",
	"Volume total",
	"Pressão",
	"Tempo restante",
	"Pausar",
	"Taxa",
	"VTBI"
		
};

static double sg_quanbegin=0.0; //记录刚开始的待入量
static double sg_cumlant=0.0;	//记录刚开始的累积量
double sg_seqmoderun_NowCumulant=0.0;//记录现在的累积量
static double CurrentnumVTBI=0.0;//记录当前正在运行的序列的代入量
static double sg_seqmoderun_SeqCumulant=0.0;//标志序列累积量

static int temp_timesecond=0,sequen_timesecond=0,surplus_timesecond=0;
static TIME sg_surplustime,SurplusTime_Temp;//记录剩余时间
static int tempseq_timesecond=0;//记录总时间
static unsigned int pressureAD = 0;
static unsigned int UltrasonicTimeMS; //计算当前速度下超声检查时间
static unsigned int AcBubTimeNumMs;   //在当前速度下累计气泡达到设置值需要的毫秒

static _Bool SetcumulantFlag=FALSE;  //在电池耗尽状态下保存当前累计量标志

static uint32_t sequentialnum;//序列

static double CurrentRate;//当前速度
static double CurrentVTBI;//当前总的待入量
static int num=11;

void CutSpeed(void)
{
	#if 0
	if((sg_seqmoderun_NowCumulant <= (*SeqMode_run.quantity1))&&(*SeqMode_run.speed1) != 0){
		SeqMode_run.speed = &SequenMode.S1Rate;current = 1;}
	else if(((*SeqMode_run.quantity1) <= sg_seqmoderun_NowCumulant <= ((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)))&&(*SeqMode_run.speed2) != 0){
		SeqMode_run.speed = &SequenMode.S2Rate;current = 2;}
	else if((((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)) <= sg_seqmoderun_NowCumulant <= ((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)+(*SeqMode_run.quantity3)))&&(*SeqMode_run.speed3) != 0){
		SeqMode_run.speed = &SequenMode.S3Rate;current = 3;}
	else if((((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)+(*SeqMode_run.quantity3)) <= sg_seqmoderun_NowCumulant <= ((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)+(*SeqMode_run.quantity3)+(*SeqMode_run.quantity4)))&&(*SeqMode_run.speed4) != 0){
		SeqMode_run.speed = &SequenMode.S4Rate;current = 4;}
	else if((((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)+(*SeqMode_run.quantity3)+(*SeqMode_run.quantity4)) <= sg_seqmoderun_NowCumulant == ((*SeqMode_run.quantity1)+(*SeqMode_run.quantity2)+(*SeqMode_run.quantity3)+(*SeqMode_run.quantity4)+(*SeqMode_run.quantity5)))&&(*SeqMode_run.speed5) != 0){
		SeqMode_run.speed = &SequenMode.S5Rate;current = 5;}
	#endif
	
	
	
	SeqMode_run.speed1 = &CurrentRate;
	if(*SeqMode_run.quantity1 <= 0.0) //当前序列代入量结束,开始下一个序列
	{

		SequenMode.S2VTBI = *SeqMode_run.quantity2;
		SeqMode_run.quantity1 = &SequenMode.S2VTBI;
		SequenMode.S3VTBI = *SeqMode_run.quantity3;
		SeqMode_run.quantity2 = &SequenMode.S3VTBI;
		SequenMode.S4VTBI = *SeqMode_run.quantity4;	
		SeqMode_run.quantity3 = &SequenMode.S4VTBI;
		SequenMode.S5VTBI = *SeqMode_run.quantity5;
		SeqMode_run.quantity4 = &SequenMode.S5VTBI;
		SeqMode_run.quantity5 = NULL;
		
		SequenMode.S2Rate = *SeqMode_run.speed2;
		SeqMode_run.speed1 = &SequenMode.S2Rate;
		SequenMode.S3Rate = *SeqMode_run.speed3;
		SeqMode_run.speed2 = &SequenMode.S3Rate;
		SequenMode.S4Rate = *SeqMode_run.speed4;
		SeqMode_run.speed3 = &SequenMode.S4Rate;
		SequenMode.S5Rate = *SeqMode_run.speed5;
		SeqMode_run.speed4 = &SequenMode.S5Rate;
		SeqMode_run.speed5 = NULL;
		
		SequenMode.S2_Time.hour = SeqMode_run.time2->hour;
		SeqMode_run.time1->hour = SeqMode_run.time2->hour;
		SequenMode.S3_Time.hour = SeqMode_run.time3->hour;
		SeqMode_run.time2->hour = SeqMode_run.time3->hour;
		SequenMode.S4_Time.hour = SeqMode_run.time4->hour;
		SeqMode_run.time3->hour = SeqMode_run.time4->hour;
		SequenMode.S5_Time.hour = SeqMode_run.time5->hour;
		SeqMode_run.time4->hour = SeqMode_run.time5->hour;
		
		SeqMode_run.time5->hour = 0;
		
		SequenMode.S2_Time.min = SeqMode_run.time2->min;
		SeqMode_run.time1->min = SeqMode_run.time2->min;
		SequenMode.S3_Time.min = SeqMode_run.time3->min;
		SeqMode_run.time2->min = SeqMode_run.time3->min;
		SequenMode.S4_Time.min = SeqMode_run.time4->min;
		SeqMode_run.time3->min = SeqMode_run.time4->min;
		SequenMode.S5_Time.min = SeqMode_run.time5->min;
		SeqMode_run.time4->min = SeqMode_run.time5->min;
		
		SeqMode_run.time5->min = 0;
		
		SequenMode.S2_Time.sec = SeqMode_run.time2->sec;
		SeqMode_run.time1->sec = SeqMode_run.time2->sec;
		SequenMode.S3_Time.sec = SeqMode_run.time3->sec;
		SeqMode_run.time2->sec = SeqMode_run.time3->sec;
		SequenMode.S4_Time.sec = SeqMode_run.time4->sec;
		SeqMode_run.time3->sec = SeqMode_run.time4->sec;
		SequenMode.S5_Time.sec = SeqMode_run.time5->sec;
		SeqMode_run.time4->sec = SeqMode_run.time5->sec;
		
		SeqMode_run.time5->sec = 0;
		

		CurrentRate = *SeqMode_run.speed1;
		SeqMode_run.speed1 = &CurrentRate;
		CurrentnumVTBI = *SeqMode_run.quantity1;

		sg_seqmoderun_SeqCumulant = sg_seqmoderun_SeqCumulant + sg_seqmoderun_NowCumulant;
		sequentialnum++;

		if(sequentialnum >= *SeqMode_run.value)
			sequentialnum = *SeqMode_run.value;
		gt_event_send(SeqModeRun,MY_MOTOR_RUN,NULL);
	}
	
	*SeqMode_run.quantity = sg_quanbegin - sg_seqmoderun_NowCumulant;
	if(*SeqMode_run.quantity <= 0.0)
	{
		*SeqMode_run.quantity = 0.0;
		sg_seqmoderun_NowCumulant = *SeqMode_run.quantity;
	}

}

/** enter bolus */
static void bolus(gt_event_st * e) {
	if(GetLockFlag()){return ;}else{SetAutoLockTime(ParamSetting.LockTime);}
	if(GetNowAlarmLeve12()==H_ALARM){return ;}
	if(*SeqMode_run.speed >= SystemMaintain.MaxSpeed){return ;}
	

	//在快进时还要保存运行模式下的初始预置量

	#if 01
	lab11 = NULL;
	lab20 = NULL;
	lab16 = NULL;
	lab13 = NULL;
	lab17 = NULL;
	lab4 = NULL;
	//进度条停
	DEL_TIMER_VAL(run_progress);
	DEL_TIMER_VAL(timer_run_300msec);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_94, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
	#else
	lab11 = NULL;
	lab20 = NULL;
	lab16 = NULL;
	lab13 = NULL;
	lab17 = NULL;
	lab4 = NULL;
	//进度条停
	DEL_TIMER_VAL(run_progress);
	DEL_TIMER_VAL(timer_run_300msec);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_94, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	#endif

}

//drug
static void drugChoice(gt_event_st * e) {
	if(GetLockFlag()){return ;}else{SetAutoLockTime(ParamSetting.LockTime);}
	if(GetNowAlarmLeve12()==H_ALARM){return ;}

	gt_disp_stack_load_scr_anim(GT_SCR_ID_16, GT_SCR_ANIM_TYPE_NONE, 500, 0,false);
	
}

static void btn2_0_cb(gt_event_st * e) {
	double qua;
	if(GetLockFlag()){ return; }else{SetAutoLockTime(ParamSetting.LockTime);}

	ClearAlarm(ALARM_INFUSION_DRAIN);
	ClearAlarm(ALARM_HYPERACOUSTIC);
	ClearAlarm(ALARM_CUMULANT_BUBBLE);
	ClearAlarm(ALARM_UPPER_OCCLUSION);
	ClearAlarm(ALARM_UNDERBLOCKING);
	ClearAlarm(ALARM_SYSTEM_FAILURE);
	ClearAlarm(ALARM_INFUSION_OFF);
	ClearAlarm(ALARM_NEAR_DONE); 
	SetNerDoneFlag(0);
	SetNowcumulant(sg_seqmoderun_NowCumulant);
	TMC2226_MotorStop();
	qua = sg_quanbegin - sg_seqmoderun_NowCumulant;
	SeqMode_run.quantity = &qua;

	SequenMode.S1Rate = *SeqMode_run.speed1;
	SequenMode.S1VTBI = *SeqMode_run.quantity1;
	SequenMode.S1_Time.hour = sg_surplustime.hour;
	SequenMode.S1_Time.min = sg_surplustime.min;
	SequenMode.S1_Time.sec = sg_surplustime.sec;
	
	SequenMode.S2Rate = *SeqMode_run.speed2;
	SequenMode.S2VTBI = *SeqMode_run.quantity2;

	
	SequenMode.S3Rate = *SeqMode_run.speed3;
	SequenMode.S3VTBI = *SeqMode_run.quantity3;


	SequenMode.S4Rate = *SeqMode_run.speed4;
	SequenMode.S4VTBI = *SeqMode_run.quantity4;

	SequenMode.S5Rate = *SeqMode_run.speed5;
	SequenMode.S5VTBI = *SeqMode_run.quantity5;

	lab11 = NULL;
	lab19 = NULL;


	//进度条停
	DEL_TIMER_VAL(run_progress);
	DEL_TIMER_VAL(timer_run_300msec);
	sprintf(buffer,"%.2fml",GetNowcumulant());
	not_first_start_write_history_info(EA_stop,Ev_GetVolume,buffer);

	WriteSeqModeMessageToFlash();
	gt_disp_stack_load_scr_anim(GT_SCR_ID_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg1_0_cb(gt_event_st * e) {
	if((InfusionNow.glevel!=H_ALARM))
	{
		gt_obj_set_visible(svg1,GT_INVISIBLE);
		gt_obj_set_visible(svg2,GT_VISIBLE);
		//UpdateWindow (GetDlgItem(hWnd,15), TRUE);
		Lock();   /*上锁*/
	}
}

static void svg2_0_cb(gt_event_st * e) {

	gt_obj_set_visible(svg1,GT_VISIBLE);
	gt_obj_set_visible(svg2,GT_INVISIBLE);
	if(GetLockFlag())   
		UnLock(ParamSetting.LockTime); /*解锁*/
}

//1s的消息
static void Timer_OneSecond(gt_event_st * e){
	char buffer[50];
	//计算剩余时间
	CutSpeed();
	if(*SeqMode_run.quantity != 0 )
	{
		
		sg_surplustime = CalSurplusTime(*SeqMode_run.quantity1,*SeqMode_run.speed1);//计算当前序列剩余的时间
		SeqMode_run.time1->hour = sg_surplustime.hour;
		SeqMode_run.time1->min = sg_surplustime.min;
		SeqMode_run.time1->sec = sg_surplustime.sec;
		surplus_timesecond = sg_surplustime.hour*3600+sg_surplustime.min*60+sg_surplustime.sec;//记录当前序列剩余的时间
		
		sequen_timesecond = (SeqMode_run.time2->hour+SeqMode_run.time3->hour+SeqMode_run.time4->hour+SeqMode_run.time5->hour)*3600+(SeqMode_run.time2->min+SeqMode_run.time3->min+SeqMode_run.time4->min+SeqMode_run.time5->min)*60+SeqMode_run.time2->sec+SeqMode_run.time3->sec+SeqMode_run.time4->sec+SeqMode_run.time5->sec;//计算尚未进行的序列运行时间
		temp_timesecond = sequen_timesecond + surplus_timesecond;
		
		if(temp_timesecond<=0)
			temp_timesecond = 0;
		SurplusTime_Temp.hour = temp_timesecond/3600;
		SurplusTime_Temp.min = (temp_timesecond/60)%60;
		SurplusTime_Temp.sec = temp_timesecond%60;
		SeqMode_run.time = &SurplusTime_Temp;//记录剩余时间
		sprintf(buffer,"%d:%d:%d",SurplusTime_Temp.hour,SurplusTime_Temp.min,SurplusTime_Temp.sec);
		gt_label_set_text(lab16,buffer);

		if(JudgedYesNoAlarm(ALARM_INFUSION_DRAIN) == false)
		{
			/*接近完成*/
			if(JudgedinfusionNeaeTimeAlarm(&SurplusTime_Temp))
			{
				if(GetNerDoneFlag() == 0)
				{
					AddAlarm(ALARM_NEAR_DONE);
					SetNerDoneFlag(0xFF);
				}
			}
			else
			{
				ClearAlarm(ALARM_NEAR_DONE); 
				SetNerDoneFlag(0);
			}
		}
	}
	//自动锁倒计时、上锁
	if(LockTimeCountDown(ParamSetting.LockState,ParamSetting.LockTime)==0)
	{
		if((!GetLockFlag())&&(InfusionNow.glevel!=H_ALARM))
		{  
			gt_obj_set_visible(svg1,GT_INVISIBLE);
			gt_obj_set_visible(svg2,GT_VISIBLE);

			//ShowWindow(GetDlgItem(hWnd,15),SW_SHOW);
			//UpdateWindow(GetDlgItem(hWnd,15), TRUE);
			Lock();
		} 
	}
	//解锁
	if(GetLockFlag()&&(GetLockNewAFlag()))
	{	  
		gt_obj_set_visible(svg1,GT_VISIBLE);
		gt_obj_set_visible(svg2,GT_INVISIBLE);

		//UpdateWindow(GetDlgItem(hWnd,14), TRUE);
		UnLock(ParamSetting.LockTime); /*解锁*/
	}

	#if VP30
	//上阻塞
	if(JudgedInfusionUpBlock(sensorpack.UpPressure))
	{	 
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			if((!JudgedYesNoAlarm(ALARM_INFUSION_OFF)) && (!JudgedYesNoAlarm(ALARM_HYPERACOUSTIC)) && (!JudgedYesNoAlarm(ALARM_CUMULANT_BUBBLE))&& (!JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE)))
				AddAlarm(ALARM_UPPER_OCCLUSION);
		}

	}
	#endif
	//下阻塞自动释放功能
	#if VET_USE
	if(JudgedYesNoAlarm(ALARM_UNDERBLOCKING))	
	{
		if(JudgedDownBlockRelease_AD(ParamSetting.BlockLevel,sensorpack.DownPressure))
		{
			SetNowcumulant(sg_seqmoderun_NowCumulant);
			ClearAlarm(ALARM_UNDERBLOCKING);
			gt_event_send(SpeedAndTimeModeRun,MY_MOTOR_RUN,NULL);
		}
	}
	#endif

	#if sg_debug
	//判断输液器脱落
	if(!sensorpack.RightKnobStatus || JudgedInfusionTubeFallOff_P(sensorpack.DownPressure)) 
	{
		
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			DEL_TIMER_VAL(run_progress);
		}
		AddAlarm(ALARM_INFUSION_OFF);
	}
	#endif

	//压力数据变化
	double Pressuredata,Pressuredata_max;
	char temp2[50];
	Pressuredata=PressureConversion(press_Data.Pressure_valuenow,P_mmHg,ParamSetting.PressUint);
	Pressuredata_max=PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint);
	gt_progress_bar_set_pos(bar1, (Pressuredata*100)/Pressuredata_max);
	if((Pressuredata*100)/Pressuredata_max > 50 && (Pressuredata*100)/Pressuredata_max < 100)
		//黄色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfdfd00));
	else if((Pressuredata*100)/Pressuredata_max >= 100)
		//红色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfe1b01));
	else
		//绿色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	sprintf(temp2,"%.1f",(float)Pressuredata);
	gt_label_set_text(lab13,temp2);
	sprintf(buffer,"%.2f",(float)CurrentRate);
	gt_label_set_text(lab4, buffer);
	sprintf(buffer,"%d/%d",sequentialnum,*SeqMode_run.value);
	gt_label_set_text(lab2, buffer);

}

static void run_progress_func(struct _gt_timer_s *timer){
	if(num -- <= 0)
		num = 10;
	gt_obj_set_pos(img2, 8+20*num, 280);

}

static void MotorRun(gt_event_st * e){
	
	//发送motorclear消息
	
	MotorControl.anglesum = 0;
	double tempdata;
	CutSpeed();
	
	sg_cumlant = GetNowcumulant();
	//计算超声检查时间
	UltrasonicTimeMS=(unsigned int)(REQUIRED_TIMES(*SeqMode_run.speed1,ParamSetting.BubbleSize)/2);  
	if(UltrasonicTimeMS<=1)
	{
		UltrasonicTimeMS=1;
	}
	//计算累计气泡量在当前速度下速度的时间毫秒
	AcBubTimeNumMs=(unsigned int)CAL_SPEED_ACC_BUB_TIME_MS_NUM(*SeqMode_run.speed1,ParamSetting.AccumBubbleSize);
	
	SetNerDoneFlag(0);
	//计算速度
	tempdata =CalSpeed(*SeqMode_run.speed1); 
	TMC2226_MotorRun(1,0,tempdata);
	//设置运行条运行速度
	DEL_TIMER_VAL(run_progress);
	run_progress = _gt_timer_create(run_progress_func,SetProgressRunSpeed(*SeqMode_run.speed1),NULL);
	
}

//300ms的消息
static void Timer_300mSecond(struct _gt_timer_s *timer){
	char buffer[50];
	CutSpeed();
	sg_cumlant = GetNowcumulant();
	if(MotorControl.status != MOTOR_BACK)
	{
	
		sg_seqmoderun_NowCumulant = CalCumulant(MotorControl.anglesum,*SeqMode_run.speed1);
		//printf("num = %f\n",MotorControl.anglesum);
		if(sg_seqmoderun_NowCumulant <= 0.0)
			sg_seqmoderun_NowCumulant = 0.0;

		if(*SeqMode_run.quantity != 0)
		{
			sg_seqmoderun_SeqCumulant = sg_seqmoderun_NowCumulant;
//			if()
//				sg_seqmoderun_SeqCumulant = 0.0;
			*SeqMode_run.quantity1 = CurrentnumVTBI - sg_seqmoderun_SeqCumulant;//到下一个序列会出现问题  需要另一个累积量做标志位每到一个新的序列都应让标志累积量置零
			
			sprintf(buffer,"%.2f",(float)*SeqMode_run.quantity);
			gt_label_set_text(lab19, buffer);

			sprintf(buffer,"%.2f",(float)(sg_cumlant+sg_seqmoderun_NowCumulant)); 
			gt_label_set_text(lab11,buffer);
			if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_10) == RESET)
				btn2_0_cb(NULL);

			//输液完成1
			
			if((*SeqMode_run.quantity) <= 0.0)
			{
				(*SeqMode_run.quantity1) = (*SeqMode_run.quantity2) = (*SeqMode_run.quantity3) = (*SeqMode_run.quantity4) = (*SeqMode_run.quantity5) = 0.0;
				SeqMode_run.time1->hour = SeqMode_run.time2->hour = SeqMode_run.time3->hour = SeqMode_run.time4->hour = SeqMode_run.time5->hour = 0;
				SeqMode_run.time1->min = SeqMode_run.time2->min = SeqMode_run.time3->min = SeqMode_run.time4->min = SeqMode_run.time5->min = 0;
				SeqMode_run.time1->sec = SeqMode_run.time2->sec = SeqMode_run.time3->sec = SeqMode_run.time4->sec = SeqMode_run.time5->sec = 0;
				SeqMode_run.time->hour = 0;SeqMode_run.time->min = 0;SeqMode_run.time->sec = 0;
				*SeqMode_run.quantity = 0.0;

				sg_seqmoderun_NowCumulant = sg_quanbegin;

				if(SystemMaintain.KVOState)
				{
					SetNowcumulant(sg_seqmoderun_NowCumulant);
					sprintf(buffer,"%.2f",GetNowcumulant()); 
					gt_label_set_text(lab11,buffer);

					sprintf(buffer,"%.2f",(float)*SeqMode_run.quantity);
					gt_label_set_text(lab19,buffer);
					if(JudgedYesNoAlarm(ALARM_NEAR_DONE))
					{ 
						ClearAlarm(ALARM_NEAR_DONE); 
						SetNerDoneFlag(0);
					}
					/*输液完成报警*/
					AddAlarm(ALARM_INFUSION_DRAIN);
					UnLock(ParamSetting.LockTime); /*解锁*/
					//进入kVO模式
						TMC2226_MotorStop(); //电机停
						DEL_TIMER_VAL(run_progress);//运行条停
						DEL_TIMER_VAL(timer_run_300msec); //300ms定时器停
						gt_disp_stack_load_scr(GT_SCR_ID_90);

				}
				else
				{
					if(MotorControl.status == MOTOR_RUN)
					{
						TMC2226_MotorStop();
						
						sprintf(buffer,"%.2f",(float)(GetNowcumulant()+sg_seqmoderun_NowCumulant)); 
						gt_label_set_text(lab11,buffer);

						sprintf(buffer,"%.2f",(float)*SeqMode_run.quantity);
						gt_label_set_text(lab19,buffer);
						/*设置运行条停止*/
						DEL_TIMER_VAL(run_progress);
					}	
					if(JudgedYesNoAlarm(ALARM_NEAR_DONE))
					{ 
						ClearAlarm(ALARM_NEAR_DONE); 
							SetNerDoneFlag(0);
					}
					/*输液完成报警*/
					AddAlarm(ALARM_INFUSION_DRAIN);
				}
			}
		}

	}
/********************************报警判断**************************************/
#if sg_debug
	/*测试临时关闭，正式使用需要打开！！！！！！！！！！！！！！！！！！！*/

	//下阻塞
	if(*speed_time_run.speed >=1000.0)
	{
		pressureAD = sensorpack.DownPressure + 50;
	}
	else if((*speed_time_run.speed)>=800.0)
	{
		pressureAD = sensorpack.DownPressure + 30;
	}
	else if((*speed_time_run.speed)>=500.0)
	{
		pressureAD = sensorpack.DownPressure + 20;
	}
	else if((*speed_time_run.speed)>=300.0)
	{
		pressureAD = sensorpack.DownPressure + 10;
	}
	else if((*speed_time_run.speed)>=50.0)
	{
		pressureAD = sensorpack.DownPressure + 8;
	}	
	else if((*speed_time_run.speed)>=25.0)
	{
		pressureAD = sensorpack.DownPressure;
	}	
	else if((*speed_time_run.speed)>=1.0)
	{
		pressureAD = sensorpack.DownPressure -5;
	}
	else
	{
		pressureAD = sensorpack.DownPressure ;
	}
	#if VET_USE
	if(JudgedInfusionDownBlock_AD(pressureAD))
	{	 
		
		/*判断下阻塞时Anti-Bolus功能*/
		if(MotorControl.status==MOTOR_RUN)
		{
			TMC2226_MotorStop();

			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			AddAlarm(ALARM_UNDERBLOCKING);
		}
		
	}
	#else
	if(JudgedInfusionDownBlock_AD(pressureAD))
	{	 
		if(SystemMaintain.AntiState && MotorControl.status == MOTOR_RUN)
		{
			//点击反转
			TMC2226_MotorRun(0,0,50);
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
		}
		else
		{
			TMC2226_MotorStop(); 
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
		}
		AddAlarm(ALARM_UNDERBLOCKING);
	}
	#endif


	//上超声
	if(JudgeINjection(sensorpack.BubbleStatus,UltrasonicTimeMS))
	{
		
		
		if(MotorControl.status ==MOTOR_RUN)
		{
				
			TMC2226_MotorStop();
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			if((JudgedYesNoAlarm(ALARM_INFUSION_OFF) == FALSE) && (JudgedYesNoAlarm(ALARM_UNDERBLOCKING) == FALSE) )
			{
				AddAlarm(ALARM_HYPERACOUSTIC);
			}
		}
	}
	airbubble_Data.airbubble_time++;
	if(airbubble_Data.airbubble_time > 3600)
	{
		airbubble_Data.airbubble_time = 0;
		airbubble_Data.airbubble_num = 0;
	}
	/*计算累计气泡量*/
	if(CalAccumulativeBubble(sensorpack.BubbleStatus,AcBubTimeNumMs))
	{
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();	 
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			if((JudgedYesNoAlarm(ALARM_INFUSION_OFF) == FALSE) && (JudgedYesNoAlarm(ALARM_UNDERBLOCKING) == FALSE) )
			{
				AddAlarm(ALARM_CUMULANT_BUBBLE);
			}
		}
	}
	if(JudgedYesNoAlarm(ALARM_HYPERACOUSTIC) || JudgedYesNoAlarm(ALARM_CUMULANT_BUBBLE) || JudgedYesNoAlarm(ALARM_UPPER_OCCLUSION) || JudgedYesNoAlarm(ALARM_INFUSION_OFF) || JudgedYesNoAlarm(ALARM_UNDERBLOCKING))
	{
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
		}
	}

	//电池耗尽
	if(JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE))
	{
		if(SetcumulantFlag == false)
		{
			SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
			SetcumulantFlag=TRUE;
		}
		DEL_TIMER_VAL(run_progress);
	}

#endif
}

gt_obj_st * gt_init_SeqModeRun(void)
{
	char buffer[50];
	/*创建自动锁时间*/
	SetAutoLockTime(ParamSetting.LockTime);
	sequentialnum=1;

	CurrentnumVTBI = *SeqMode_run.quantity1;
	
	CurrentRate = *SeqMode_run.speed1;
	sg_quanbegin = *SeqMode_run.quantity;
//	tempseq_timesecond = SeqMode_run.time->hour*3600+SeqMode_run.time->min*60+SeqMode_run.time->sec;//总的时间
	//写历史记录
	switch(*SeqMode_run.value)
	{
		case 5:
			sprintf(buffer,"S5: %.2fml/h,%.2fml.",(float)*SeqMode_run.speed5,(float)*SeqMode_run.quantity5);
			not_first_start_write_history_info(Ev_StarInjection,EA_start,buffer);
		case 4:
			sprintf(buffer,"S4: %.2fml/h,%.2fml.",(float)*SeqMode_run.speed4,(float)*SeqMode_run.quantity4);
			not_first_start_write_history_info(Ev_StarInjection,EA_start,buffer);
		case 3:
			sprintf(buffer,"S3: %.2fml/h,%.2fml.",(float)*SeqMode_run.speed3,(float)*SeqMode_run.quantity3);
			not_first_start_write_history_info(Ev_StarInjection,EA_start,buffer);
		case 2:
			sprintf(buffer,"S2: %.2fml/h,%.2fml.",(float)*SeqMode_run.speed2,(float)*SeqMode_run.quantity2);
			not_first_start_write_history_info(Ev_StarInjection,EA_start,buffer);

			sprintf(buffer,"S1: %.2fml/h,%.2fml.  %s",(float)*SeqMode_run.speed1,(float)*SeqMode_run.quantity1,InfusionNow.drugname);
			not_first_start_write_history_info(Ev_StarInjection,EA_start,buffer);
			break;
		default:
			break;
	}	

	pressureAD = 0;

	SeqModeRun =  gt_obj_create(NULL);	
	my_set_obj_title(SeqModeRun,SeqMode_run.title);
	gt_screen_set_bgcolor(SeqModeRun, gt_color_hex(0x000000));
	
	gt_obj_add_event_cb(SeqModeRun, MotorRun,MY_MOTOR_RUN, NULL);
	gt_obj_add_event_cb(SeqModeRun, Timer_OneSecond,MY_ONE_SECONDS_TIME, NULL);

	
	/** btn1 */
	btn1 = gt_btn_create(SeqModeRun);
	gt_obj_set_pos(btn1, 0, 172);
	gt_obj_set_size(btn1, 105, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1,20);
	gt_btn_set_font_family_en(btn1,33);
	gt_btn_set_font_family_fl(btn1,50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][1]);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, bolus, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab2, 0, 53);
	gt_obj_set_size(lab2, 60, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	sprintf(buffer,"%d/%d",sequentialnum,*SeqMode_run.value);
	gt_label_set_text(lab2, buffer);
	

	/** lab3 */
	lab3 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab3, 146, 53);
	gt_obj_set_size(lab3, 93, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab3, "mL/h");
	

	/** lab4 */
	lab4 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab4, 0, 111);
	gt_obj_set_size(lab4, 240, 34);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",(float)*SeqMode_run.speed1);
	gt_label_set_text(lab4, buffer);
	

	/** lab5 */
	lab5 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab5, 252, 53);
	gt_obj_set_size(lab5, 70, 25);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 20);
	gt_label_set_font_family_cn(lab5, 10);
	gt_label_set_font_family_en(lab5, 30);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_text(lab5, title[SystemSetting.langue][2]);//品牌
	

	/** lab6 */
	lab6 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab6, 252, 132);
	gt_obj_set_size(lab6, 100, 26);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 20);
	gt_label_set_font_family_cn(lab6, 10);
	gt_label_set_font_family_en(lab6, 30);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT);
	gt_label_set_text(lab6, title[SystemSetting.langue][3]);//累积量
	
	/** lab7 */
	lab7 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab7, 252, 220);
	gt_obj_set_size(lab7, 63, 25);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 20);
	gt_label_set_font_family_cn(lab7, 10);
	gt_label_set_font_family_en(lab7, 30);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT);
	gt_label_set_text(lab7, title[SystemSetting.langue][4]);//压力
	

	/** lab8 */
	lab8 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab8, 418, 132);
	gt_obj_set_size(lab8, 60, 25);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 16);
	gt_label_set_font_family_en(lab8, 30);
	gt_label_set_font_family_cn(lab8, 9);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_RIGHT);
	gt_label_set_text(lab8, "mL");
	

	/** lab9 */
	lab9 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab9, 380, 218);
	gt_obj_set_size(lab9, 100, 25);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 16);
	gt_label_set_font_family_en(lab9, 30);
	gt_label_set_font_family_cn(lab9, 9);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_RIGHT);
	gt_label_set_text(lab9,  GetPressUintString(ParamSetting.PressUint));
	

	/** lab10 */
	lab10 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab10, 417, 53);
	gt_obj_set_size(lab10, 60, 25);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 16);
	gt_label_set_font_family_cn(lab10, 9);
	gt_label_set_font_family_en(lab10, 30);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_RIGHT);
	gt_label_set_text(lab10,InfusionNow.tubename);
	
	
	/** lab11 */
	lab11 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab11, 410, 154);
	gt_obj_set_size(lab11, 70, 25);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 16);
	gt_label_set_font_family_en(lab11, 30);
	gt_label_set_font_family_cn(lab11, 9);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_RIGHT);
	sprintf(buffer,"%.2f",GetNowcumulant());
	gt_label_set_text(lab11, buffer);
	

	/** img1 */
	img1 = gt_img_create(SeqModeRun);
	gt_obj_set_pos(img1, 252, 249);
	gt_obj_set_size(img1, 20, 30);
	gt_img_set_src(img1, "f:img_20x30_46_keyboard_shift.png");

	
	/** rect2 */
	rect2 = gt_rect_create(SeqModeRun);
	gt_obj_set_pos(rect2, 250, 50);
	gt_obj_set_size(rect2, 230, 270);
	gt_obj_set_opa(rect2, GT_OPA_35);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	my_rect_set_feedback(rect2,false);

	/** rect3 */
	rect3 = gt_rect_create(SeqModeRun);
	gt_obj_set_pos(rect3, 0, 88);
	gt_obj_set_size(rect3, 240, 75);
	gt_obj_set_opa(rect3, GT_OPA_35);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	my_rect_set_feedback(rect3,false);



	/** lab12 */
	lab12 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab12, 275, 259);
	gt_obj_set_size(lab12, 50, 30);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 16);
	gt_label_set_font_family_en(lab12, 30);
	gt_label_set_font_family_cn(lab12, 9);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_LEFT);
	sprintf(buffer,"%.1f",(float)PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	gt_label_set_text(lab12, buffer);
	

	/** lab13 */
	lab13 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab13, 417, 259);
	gt_obj_set_size(lab13, 60, 30);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 16);
	gt_label_set_font_family_en(lab13, 30);
	gt_label_set_font_family_cn(lab13, 9);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_RIGHT);
	gt_label_set_text(lab13, "0");
	

	/** bar1 */
	bar1 = gt_progress_bar_create(SeqModeRun);
	gt_obj_set_pos(bar1, 252, 290);
	gt_obj_set_size(bar1, 225, 20);
	gt_progress_bar_set_start_end(bar1, 0, 100);
	gt_progress_bar_set_pos(bar1, 50);
	gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	gt_progress_bar_set_color_ina(bar1, gt_color_hex(0xebeef5));
	gt_progress_bar_set_dir(bar1, GT_BAR_DIR_HOR_R2L);


	/** lab14 */
	lab14 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab14, 252, 175);
	gt_obj_set_size(lab14, 85, 25);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 20);
	gt_label_set_font_family_cn(lab14, 10);
	gt_label_set_font_family_en(lab14, 30);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_LEFT);
	gt_label_set_text(lab14, title[SystemSetting.langue][5]);//剩余时间

	

	/** lab15 */
	lab15 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab15, 378, 175);
	gt_obj_set_size(lab15, 100, 25);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 16);
	gt_label_set_font_family_cn(lab15, 9);
	gt_label_set_font_family_en(lab15, 30);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_RIGHT);
	gt_label_set_text(lab15, "h:m:s");

	

	/** lab16 */
	lab16 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab16, 354, 196);
	gt_obj_set_size(lab16, 124, 24);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 16);
	gt_label_set_font_family_cn(lab16, 9);
	gt_label_set_font_family_en(lab16, 30);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_RIGHT);
	sprintf(buffer,"%02d:%02d:%02d",SeqMode_run.time->hour,SeqMode_run.time->min,SeqMode_run.time->sec);
	gt_label_set_text(lab16,buffer);
	
	/** rect6 */
	rect6 = gt_rect_create(SeqModeRun);
	gt_obj_set_pos(rect6, 245, 50);
	gt_obj_set_size(rect6, 3, 270);
	gt_obj_set_opa(rect6, GT_OPA_35);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	my_rect_set_feedback(rect6,false);

	/** btn2 */
	btn2 = gt_btn_create(SeqModeRun);
	gt_obj_set_pos(btn2, 132, 171);
	gt_obj_set_size(btn2, 105, 40);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_family_en(btn2,33);
	gt_btn_set_font_family_fl(btn2,50);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][6]);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, btn2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	#if (VET_USE || !CH_USE) //兽用或者国外使用
	/** lab17 */
	lab17 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab17, 143, 235);
	gt_obj_set_size(lab17, 95, 25);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 16);
	gt_label_set_font_family_cn(lab17, 9);
	gt_label_set_font_family_en(lab17, 30);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_CENTER_MID);
	if(InfusionNow.drugname == NULL)
		gt_label_set_text(lab17, "未选药");
	else
		gt_label_set_text(lab17, InfusionNow.drugname);
	

	/** rect7 */
	rect7 = gt_rect_create(SeqModeRun);
	gt_obj_set_pos(rect7, 138, 224);
	gt_obj_set_size(rect7, 100, 44);
	gt_obj_set_opa(rect7, GT_OPA_39);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, drugChoice, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	#endif

	/** svg1 */
	svg1 = gt_img_create(SeqModeRun);
	gt_obj_set_pos(svg1, 0, 229);
	gt_obj_set_size(svg1, 48, 48);
	gt_img_set_src(svg1, "f:img_48x48_electronic_locks_open_51_28.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** svg2 */
	svg2 = gt_img_create(SeqModeRun);
	gt_obj_set_pos(svg2, 53, 228);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_48x48_electronic_locks_close_51_29.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	gt_obj_set_visible(svg2,GT_INVISIBLE);

	/** lab18 */
	lab18 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab18, 39, 53);
	gt_obj_set_size(lab18, 80, 35);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 20);
	gt_label_set_font_family_cn(lab18, 10);
	gt_label_set_font_family_en(lab18, 33);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_LEFT);
	gt_label_set_text(lab18, title[SystemSetting.langue][7]);//流速

	/** 待入量 */
	lab19 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab19, 423, 106);
	gt_obj_set_size(lab19, 55, 35);
	gt_label_set_font_color(lab19, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab19, 24);
	gt_label_set_font_family_en(lab19, 30);
	gt_label_set_font_family_cn(lab19, 20);
	gt_label_set_font_family_fl(lab19, 50);
	gt_label_set_font_align(lab19, GT_ALIGN_RIGHT_MID);
	sprintf(buffer,"%.2f",(float)*SeqMode_run.quantity);
	gt_label_set_text(lab19, buffer);

	/** lab20 */
	lab20 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab20, 252, 80);
	gt_obj_set_size(lab20, 100, 35);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 20);
	gt_label_set_font_family_cn(lab20, 10);
	gt_label_set_font_family_en(lab20, 33);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab20, title[SystemSetting.langue][8]);//待入量

	

	/** lab21 */
	lab21 = gt_label_create(SeqModeRun);
	gt_obj_set_pos(lab21, 423, 80);
	gt_obj_set_size(lab21, 55, 24);
	gt_label_set_font_color(lab21, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab21, 24);
	gt_label_set_font_family_en(lab21, 30);
	gt_label_set_font_family_cn(lab21, 20);
	gt_label_set_font_family_fl(lab21, 50);
	gt_label_set_font_align(lab21, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab21, "mL");

	/** img3 */
	img3 = gt_img_create(SeqModeRun);
	gt_obj_set_pos(img3, 10, 280);
	gt_obj_set_size(img3, 214, 30);
	gt_img_set_src(img3, "f:img_214x30_Runstrip.png");

	/** img2 */
	img2 = gt_img_create(SeqModeRun);
	gt_obj_set_pos(img2, 8+20*num, 280);
	gt_obj_set_size(img2, 19, 30);
	gt_img_set_src(img2, "f:img_19x30_Run.png");
	
	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	gt_event_send(SeqModeRun,MY_MOTOR_RUN,NULL);

	return SeqModeRun;
}

