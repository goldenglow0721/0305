#include "ui.h"
#include "up.h"

/** SpeedAndTimeModeRun */
gt_obj_st * SpeedAndTimeModeRun = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
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
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * bar1 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * lab17 = NULL;
static gt_obj_st * lab18 = NULL;
static gt_obj_st * lab19 = NULL;
static gt_obj_st * lab20 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static _gt_timer_st * timer_run_300msec;
static _gt_timer_st * run_progress;


extern int BlevelData[4];

#define sg_debug 1


SpeedAndTimeRun speed_time_run;



static const char title[5][9][50]={
	"速度模式",
	"快进",
	"流速",
	"品牌",
	"累计量",
	"压力",
	"剩余时间",
	"暂停",
	"待入量",

	"Rate Mode",
	"Bolus",
	"Rate",
	"Brand",
	"Total Volume",
	"Pressure",
	"Remain Time",
	"Pause",
	"VTBI",

	"Modo de Velocidad",
	"Bolo",
	"Tasa",
	"Marca",
	"Volumen total",
	"Presión",
	"Tiempo restante",
	"Pausa",
	"VTBI",
	
	"速度模式",
	"快進",
	"流速",
	"品牌",
	"累計量",
	"壓力",
	"剩餘時間",
	"暫停",
	"待入量",
	
	"Modo taxa",
	"Bolus",
	"Taxa",
	"Marca",
	"Volume total",
	"Pressão",
	"Tempo restante"
	"Pausar",
	"VTBI"
	
};


static double sg_quanbegin; //记录刚开始的待入量
static double sg_cumlant;	//记录刚开始的累积量
static TIME sg_surplustime;
double sg_speedandtimemoderun_NowCumulant;
static unsigned int pressureAD = 0;
static unsigned int UltrasonicTimeMS; //计算当前速度下超声检查时间
static unsigned int AcBubTimeNumMs;   //在当前速度下累计气泡达到设置值需要的毫秒


static _Bool SetcumulantFlag=FALSE;  //在电池耗尽状态下保存当前累计量标志
static int num=10;


static void bolus(gt_event_st * e) 
{
	if(GetLockFlag()){return ;}else{SetAutoLockTime(ParamSetting.LockTime);}
	if(GetNowAlarmLeve12()==H_ALARM){return ;}
	if(*speed_time_run.speed >= SystemMaintain.MaxSpeed){return ;}

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
	gt_disp_stack_load_scr_anim(GT_SCR_ID_92, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
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
	gt_disp_stack_load_scr_anim(GT_SCR_ID_92, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	#endif
	
}

//change speed
static void ChangeSpeed(gt_event_st * e) {
	if(GetLockFlag()){return ;}else{SetAutoLockTime(ParamSetting.LockTime);}
	if(GetNowAlarmLeve12()==H_ALARM){return ;}
	strcpy(keyboardf.title,title[SystemSetting.langue][2]);
	keyboardf.id = 20;
	keyboardf.data = speed_time_run.speed;
	limit.toplimit=SystemMaintain.MaxSpeed;
	limit.lowerlimit = 0.01;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

//pause
static void back(gt_event_st * e) {
	char buffer[30];
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
	SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
	TMC2226_MotorStop();

	lab11 = NULL;
	lab20 = NULL;

	//进度条停
	DEL_TIMER_VAL(run_progress);
	DEL_TIMER_VAL(timer_run_300msec);
	sprintf(buffer,"%.2fml",GetNowcumulant());
	not_first_start_write_history_info(EA_stop,Ev_GetVolume,buffer);
	if(my_judge_obj_exists(GT_SCR_ID_6))
		WriteSpeedModeMessageToFlash();
	else
		WriteTimeModeMessageToFlash();
	gt_disp_stack_go_back(1); 
}


//drug
static void drugChoice(gt_event_st * e) {

	if(GetLockFlag()){return ;}else{SetAutoLockTime(ParamSetting.LockTime);}
	if(GetNowAlarmLeve12()==H_ALARM){return ;}

	gt_disp_stack_load_scr_anim(GT_SCR_ID_16, GT_SCR_ANIM_TYPE_NONE, 500, 0,false);
	
}

//lock
static void svg1_0_cb(gt_event_st * e) {

	if((InfusionNow.glevel!=H_ALARM))
	{
		gt_obj_set_visible(svg1,GT_INVISIBLE);
		gt_obj_set_visible(svg2,GT_VISIBLE);
		//UpdateWindow (GetDlgItem(hWnd,15), TRUE);
		Lock();   /*上锁*/
	}
	
}

//unlock
static void svg2_0_cb(gt_event_st * e) {
	gt_obj_set_visible(svg1,GT_VISIBLE);
	gt_obj_set_visible(svg2,GT_INVISIBLE);
	if(GetLockFlag()) 
	{	  
		UnLock(ParamSetting.LockTime); /*解锁*/
	}

}

//300ms的消息
static void Timer_300mSecond(struct _gt_timer_s *timer){
	char buffer[50];
	if(MotorControl.status != MOTOR_BACK)
	{
		sg_speedandtimemoderun_NowCumulant = CalCumulant(MotorControl.anglesum,*speed_time_run.speed);
		//printf("num = %f\n",MotorControl.anglesum);
		if(sg_speedandtimemoderun_NowCumulant <= 0.0)
		{
			sg_speedandtimemoderun_NowCumulant = 0.0;
		}
		
		if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_10) == RESET)
			back(NULL);

		if(*speed_time_run.quantity != 0)
		{
			*speed_time_run.quantity = sg_quanbegin - sg_speedandtimemoderun_NowCumulant;
			sprintf(buffer,"%.2f",(float)*speed_time_run.quantity);
			gt_label_set_text(lab11, buffer);

			sprintf(buffer,"%.2f",(float)(sg_cumlant+sg_speedandtimemoderun_NowCumulant)); 
			gt_label_set_text(lab20,buffer);

			//输液完成
			if((*speed_time_run.quantity)<=0.0)
			{
				*speed_time_run.quantity = 0.0;
				sg_speedandtimemoderun_NowCumulant = sg_quanbegin;

				if(SystemMaintain.KVOState)
				{
					SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
					sprintf(buffer,"%.2f",GetNowcumulant()); 
					gt_label_set_text(lab20,buffer);

					sprintf(buffer,"%.2f",(float)*speed_time_run.quantity);
					gt_label_set_text(lab11,buffer);
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
					DEL_TIMER_VAL(timer_run_300msec);//300ms定时器停
					gt_disp_stack_load_scr(GT_SCR_ID_90);

				}
				else
				{
					if(MotorControl.status == MOTOR_RUN)
					{
						TMC2226_MotorStop();
						
						sprintf(buffer,"%.2f",(float)(GetNowcumulant()+sg_speedandtimemoderun_NowCumulant)); 
						gt_label_set_text(lab20,buffer);

						sprintf(buffer,"%.2f",(float)*speed_time_run.quantity);
						gt_label_set_text(lab11,buffer);
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
	//printf("%d",pressureAD);
	#if VET_USE
	if(JudgedInfusionDownBlock_AD(pressureAD))
	{	 
		
		/*判断下阻塞时Anti-Bolus功能*/
		if(MotorControl.status==MOTOR_RUN)
		{
			TMC2226_MotorStop();

			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			//_gt_timer_del(run_progress);
			AddAlarm(ALARM_UNDERBLOCKING);
		}
		
	}
	#else
	if(JudgedInfusionDownBlock_AD(pressureAD))
	{	 
		if(SystemMaintain.AntiState && MotorControl.status == MOTOR_RUN)
		{
			//电机反转
			TMC2226_MotorRun(0,0,50);
			/*设置运行条停止*/
			//if(pressureAD)
			delay_ms(300);
			TMC2226_MotorStop();
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

	#if 0
	//上超声
	if(JudgeINjection(sensorpack.BubbleStatus,UltrasonicTimeMS))
	{
		
		
		if(MotorControl.status ==MOTOR_RUN)
		{
				
			TMC2226_MotorStop();
			/*设置运行条停止*/
			DEL_TIMER_VAL(run_progress);
			//_gt_timer_del(run_progress);
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
			//_gt_timer_del(run_progress);
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
	#endif

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

//1s的消息
static void Timer_OneSecond(gt_event_st * e){
	char buffer[50];
	
	//计算剩余时间
	if(*speed_time_run.quantity != 0 )
	{
		sg_surplustime = CalSurplusTime(*speed_time_run.quantity,*speed_time_run.speed);
		sprintf(buffer,"%d:%d:%d",sg_surplustime.hour,sg_surplustime.min,sg_surplustime.sec);
		gt_label_set_text(lab16,buffer);

		if(JudgedYesNoAlarm(ALARM_INFUSION_DRAIN) == false)
		{
			/*接近完成*/
			if(JudgedinfusionNeaeTimeAlarm(&sg_surplustime))
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
			{
				AddAlarm(ALARM_UPPER_OCCLUSION);
			}
		}
	}
	#endif
	//下阻塞自动释放功能
	#if VET_USE
	if(JudgedYesNoAlarm(ALARM_UNDERBLOCKING))	
	{
		if(JudgedDownBlockRelease_AD(ParamSetting.BlockLevel,sensorpack.DownPressure))
		{
			SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
			ClearAlarm(ALARM_UNDERBLOCKING);
			gt_event_send(SpeedAndTimeModeRun,MY_MOTOR_RUN,NULL);
		}
	}
	#endif

	#if 0
	//判断输液器脱落
	if(!sensorpack.RightKnobStatus || JudgedInfusionTubeFallOff_P(sensorpack.DownPressure)) 
	{
		
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			DEL_TIMER_VAL(run_progress);
			// _gt_timer_del(run_progress);
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
	{
		//黄色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfdfd00));
	}
	else if((Pressuredata*100)/Pressuredata_max >= 100)
	{
		//红色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfe1b01));
	}
	else
	{
		//绿色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	}
	sprintf(temp2,"%.1f",(float)Pressuredata);
	gt_label_set_text(lab13,temp2);

}


static void run_progress_func(struct _gt_timer_s *timer){
	
	if(num -- <= 0)
		num = 10;
	gt_obj_set_pos(img2, 8+20*num, 280);
}


static void MotorRun(gt_event_st * e){
	double tempdata;
	//发送motorclear消息
	MotorControl.anglesum = 0;
	
	sg_quanbegin = *speed_time_run.quantity;
	sg_cumlant   = GetNowcumulant();

	//计算超声检查时间
	UltrasonicTimeMS=(unsigned int)(REQUIRED_TIMES(*speed_time_run.speed,ParamSetting.BubbleSize)/2);  
	if(UltrasonicTimeMS<=1)
	{
		UltrasonicTimeMS=1;
	}
	//计算累计气泡量在当前速度下速度的时间毫秒
	AcBubTimeNumMs=(unsigned int)CAL_SPEED_ACC_BUB_TIME_MS_NUM(*speed_time_run.speed,ParamSetting.AccumBubbleSize);
	
	SetNerDoneFlag(0);
	//计算速度
	tempdata =CalSpeed(*speed_time_run.speed); 
	TMC2226_MotorRun(1,0,tempdata);
	//设置运行条运行速度
	DEL_TIMER_VAL(run_progress);
	run_progress = _gt_timer_create(run_progress_func,SetProgressRunSpeed(*speed_time_run.speed),NULL);
	if(atoi(e->param) == 666) //从排气运行出来
		gt_label_set_text(lab17, InfusionNow.drugname);
	
}



static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 20)  //修改完速度出来的
	{
		
		UpdateSpeedModeTheDisplay(CHANGE_Speed,speed_time_run.speed,speed_time_run.quantity,speed_time_run.time);
		//更新速度显示
		sprintf(buffer,"%.2f",(float)*speed_time_run.speed);
		gt_label_set_text(lab4, buffer);

		//更新时间显示
		if(speed_time_run.time->hour>99)
		{
			speed_time_run.time->hour=100;
			speed_time_run.time->min=0;
			speed_time_run.time->sec=0;			
			sprintf(buffer,">%d:%d:%d", 99, 59, 59);
		}
		sprintf(buffer,"%d:%d:%d",speed_time_run.time->hour, speed_time_run.time->min,speed_time_run.time->sec);
		gt_label_set_text(lab16, buffer);
		//写历史记录
		sprintf(buffer,"%.2fml/h",(float)*speed_time_run.speed);
		not_first_start_write_history_info(EA_Amend,Ev_SetSpeed,buffer);

		SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
		gt_event_send(SpeedAndTimeModeRun,MY_MOTOR_RUN,NULL);
	}
	else if(atoi(e->param) == 666) //从药物库出来
		gt_label_set_text(lab17, InfusionNow.drugname);
	if(my_judge_obj_exists(GT_SCR_ID_6))
		WriteSpeedModeMessageToFlash();
	else
		WriteTimeModeMessageToFlash();
}


gt_obj_st * gt_init_SpeedAndTimeModeRun(void)
{
	char buffer[50];
	/*创建自动锁时间*/
	SetAutoLockTime(ParamSetting.LockTime);
	//写历史记录
	sprintf(buffer,"%.2fml/h,%.2fml.  %s",(float)*speed_time_run.speed,(float)*speed_time_run.quantity,InfusionNow.drugname);
	not_first_start_write_history_info(EA_start,Ev_StarInjection,buffer);

	pressureAD = 0;
	
	SpeedAndTimeModeRun =  gt_obj_create(NULL);
	my_set_obj_title(SpeedAndTimeModeRun,speed_time_run.title);
	gt_screen_set_bgcolor(SpeedAndTimeModeRun, gt_color_hex(0x000000));

	gt_obj_add_event_cb(SpeedAndTimeModeRun, EventUpdata,MY_EVENT_UPDATA, NULL);
	gt_obj_add_event_cb(SpeedAndTimeModeRun, MotorRun,MY_MOTOR_RUN, NULL);
	gt_obj_add_event_cb(SpeedAndTimeModeRun, Timer_OneSecond,MY_ONE_SECONDS_TIME, NULL);

	

	/** btn1 */
	btn1 = gt_btn_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(btn1, 0, 170);
	gt_obj_set_size(btn1, 105, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][1]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, bolus, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab2, 0, 50);
	gt_obj_set_size(lab2, 75, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 20);
	gt_label_set_font_family_cn(lab2, 10);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][2]);//流速


	/** lab3 */
	lab3 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab3, 170, 58);
	gt_obj_set_size(lab3, 70, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 30);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab3, "mL/h");


	/** lab4 */
	lab4 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab4, 0, 85);
	gt_obj_set_size(lab4, 240, 80);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",(float)*speed_time_run.speed);
	gt_label_set_text(lab4, buffer);


	/** lab5 */
	lab5 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab5, 254, 50);
	gt_obj_set_size(lab5, 75, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 20);
	gt_label_set_font_family_cn(lab5, 10);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);//品牌


	/** lab6 */
	lab6 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab6, 254, 135);
	gt_obj_set_size(lab6, 130, 25);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 20);
	gt_label_set_font_family_cn(lab6, 10);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][4]);//累积量


	/** lab7 */
	lab7 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab7, 254, 230);
	gt_obj_set_size(lab7, 85, 25);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 20);
	gt_label_set_font_family_cn(lab7, 10);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, title[SystemSetting.langue][5]);//压力

	/** lab8 */
	lab8 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab8, 418, 85);
	gt_obj_set_size(lab8, 60, 25);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 30);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab8, "mL");


	/** lab9 */
	lab9 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab9, 380, 230);
	gt_obj_set_size(lab9, 100, 25);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 30);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab9, GetPressUintString(ParamSetting.PressUint));


	/** lab10 */
	lab10 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab10, 330, 50);
	gt_obj_set_size(lab10, 150, 35);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 20);
	gt_label_set_font_family_cn(lab10, 10);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab10, InfusionNow.tubename);


	/** 待入量 */
	lab11 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab11, 410, 112);
	gt_obj_set_size(lab11, 70, 25);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 30);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_RIGHT_MID);
	sprintf(buffer,"%.2f",(float)*speed_time_run.quantity);
	gt_label_set_text(lab11, buffer);


	/** img1 */
	img1 = gt_img_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(img1, 254, 252);
	gt_obj_set_size(img1, 20, 30);
	gt_img_set_src(img1, "f:img_20x30_46_keyboard_shift.png");


	/** rect3 */
	rect3 = gt_rect_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(rect3, 0, 85);
	gt_obj_set_size(rect3, 240, 80);
	gt_obj_set_opa(rect3, GT_OPA_35);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, ChangeSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab12 */
	lab12 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab12, 275, 259);
	gt_obj_set_size(lab12, 50, 30);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 30);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_LEFT_MID);
	sprintf(buffer,"%.1f",(float)PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	gt_label_set_text(lab12, buffer);


	/** lab13 */
	lab13 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab13, 417, 259);
	gt_obj_set_size(lab13, 60, 30);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_en(lab13, 30);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab13, "0");


	/** bar1 */
	bar1 = gt_progress_bar_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(bar1, 254, 290);
	gt_obj_set_size(bar1, 220, 23);
	gt_progress_bar_set_start_end(bar1, 0, 100);
	gt_progress_bar_set_pos(bar1, 50);
	gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	gt_progress_bar_set_color_ina(bar1, gt_color_hex(0xebeef5));
	gt_progress_bar_set_dir(bar1, GT_BAR_DIR_HOR_R2L);


	/** lab14 */
	lab14 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab14, 254, 185);
	gt_obj_set_size(lab14, 130, 25);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 20); 
	gt_label_set_font_family_cn(lab14, 10);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab14, title[SystemSetting.langue][6]);//剩余时间

 
	/** lab15 */
	lab15 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab15, 378, 185);
	gt_obj_set_size(lab15, 100, 25);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 24);
	gt_label_set_font_family_en(lab15, 30);
	gt_label_set_font_family_cn(lab15, 20);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab15, "h:m:s");


	/** lab16 */
	lab16 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab16, 354, 212);
	gt_obj_set_size(lab16, 124, 23);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 24);
	gt_label_set_font_family_en(lab16, 30);
	gt_label_set_font_family_cn(lab16, 20);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_RIGHT_MID);
	sprintf(buffer,"%d:%d:%d",speed_time_run.time->hour, speed_time_run.time->min,speed_time_run.time->sec);
	gt_label_set_text(lab16, buffer);

	/** btn2 */
	btn2 = gt_btn_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(btn2, 135, 170);
	gt_obj_set_size(btn2, 105, 40);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_family_en(btn2, 33);
	gt_btn_set_font_family_fl(btn2, 50);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][7]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn2,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2,4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	#if (VET_USE || !CH_USE) //兽用或者国外使用
	/** 药物名 */
	lab17 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab17, 138, 224);
	gt_obj_set_size(lab17, 100, 44);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 20);
	gt_label_set_font_family_cn(lab17, 10);
	gt_label_set_font_family_en(lab17, 33);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_CENTER_MID);
	if(InfusionNow.drugname == NULL)
		gt_label_set_text(lab17, "未选药");
	else
		gt_label_set_text(lab17, InfusionNow.drugname);

	/** rect7 */
	rect7 = gt_rect_create(SpeedAndTimeModeRun);
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
	svg1 = gt_img_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(svg1, 7, 213);
	gt_obj_set_size(svg1, 48, 48);
	gt_img_set_src(svg1, "f:img_48x48_electronic_locks_open_51_28.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** svg2 */
	svg2 = gt_img_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(svg2, 7, 212);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_48x48_electronic_locks_close_51_29.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	gt_obj_set_visible(svg2,GT_INVISIBLE);


	/** rect4 */
	rect4 = gt_rect_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(rect4, 250, 50);
	gt_obj_set_size(rect4, 230, 270);
	gt_obj_set_opa(rect4, GT_OPA_35);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	my_rect_set_feedback(rect4,false);



	/** rect5 */
	rect5 = gt_rect_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(rect5, 245, 50);
	gt_obj_set_size(rect5, 3, 270);
	gt_obj_set_opa(rect5, GT_OPA_25);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	my_rect_set_feedback(rect5,false);



	/** lab18 */
	lab18 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab18, 254, 84);
	gt_obj_set_size(lab18, 130, 25);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 20);
	gt_label_set_font_family_cn(lab18, 10);
	gt_label_set_font_family_en(lab18, 33);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab18, title[SystemSetting.langue][8]);//待入量


	/** lab19 */
	lab19 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab19, 419, 135);
	gt_obj_set_size(lab19, 60, 24);
	gt_label_set_font_color(lab19, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab19, 24);
	gt_label_set_font_family_en(lab19, 30);
	gt_label_set_font_family_cn(lab19, 20);
	gt_label_set_font_family_fl(lab19, 50);
	gt_label_set_font_align(lab19, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab19, "mL");


	/** 累积量 */
	lab20 = gt_label_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(lab20, 410, 163);
	gt_obj_set_size(lab20, 70, 25);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 24);
	gt_label_set_font_family_en(lab20, 30);
	gt_label_set_font_family_cn(lab20, 20);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_RIGHT_MID);
	sprintf(buffer,"%.2f",GetNowcumulant());
	gt_label_set_text(lab20, buffer);

	
	/** img3 */
	img3 = gt_img_create(SpeedAndTimeModeRun);
	gt_obj_set_pos(img3, 10, 280);
	gt_obj_set_size(img3, 214, 30);
	gt_img_set_src(img3, "f:img_214x30_Runstrip.png");

	/** img2 */
	img2 = gt_img_create(SpeedAndTimeModeRun);
//	gt_obj_set_pos(img2, 208, 280);
	gt_obj_set_pos(img2, 8+20*num, 280);
	gt_obj_set_size(img2, 19, 30);
	gt_img_set_src(img2,"f:img_19x30_Run.png");

	
	//create timer
	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	gt_event_send(SpeedAndTimeModeRun,MY_MOTOR_RUN,NULL);

	return SpeedAndTimeModeRun;
}

