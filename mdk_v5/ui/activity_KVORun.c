#include "ui.h"
#include "up.h"


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
	"VTBI",
};

/** KVORun */
gt_obj_st * KVORun = NULL;
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

static unsigned int UltrasonicTimeMS; //计算当前速度下超声检查时间
static unsigned int AcBubTimeNumMs;   //在当前速度下累计气泡达到设置值需要的毫秒
static unsigned int pressureAD = 0;
static double sg_NowCumulant=0.0;
static double sg_cumlant;	//记录刚开始的累积量


static int TimeNearSec=30*60; //30分钟后电机停止工作，发生KVO完成报警

static void run_progress_func(struct _gt_timer_s *timer){
	static int num=11;
	if(num -- < 0)
	{
		num = 10;
	}
	gt_obj_set_pos(img2, 9+20*num, 280);

}

//drug
static void drugChoice(gt_event_st * e) {

	#if 0
	gt_obj_st * target_scr = gt_init_drugChoice();
	gt_disp_set_backoff_scr(target_scr, gt_init_SpeedAndTimeModeRun, 500, 0,SpeedAndTimeModeRun);
	
	#endif
}

static void MotorRun(gt_event_st * e){
	double tempdata;
	//发送motorclear消息
	MotorControl.anglesum = 0;
	
	sg_cumlant  = GetNowcumulant();

	//计算超声检查时间
	UltrasonicTimeMS=(unsigned int)(REQUIRED_TIMES(ParamSetting.KVOSpeed,ParamSetting.BubbleSize)/2);  
	if(UltrasonicTimeMS<=1)
	{
		UltrasonicTimeMS=1;
	}
	//计算累计气泡量在当前速度下速度的时间毫秒
	AcBubTimeNumMs=(unsigned int)CAL_SPEED_ACC_BUB_TIME_MS_NUM(ParamSetting.KVOSpeed,ParamSetting.AccumBubbleSize);
	
	SetNerDoneFlag(0);
	//计算速度
	tempdata =CalSpeed(ParamSetting.KVOSpeed); 
	TMC2226_MotorRun(1,0,tempdata);
	//设置运行条运行速度
	DEL_TIMER_VAL(run_progress);
	run_progress = _gt_timer_create(run_progress_func,SetProgressRunSpeed(ParamSetting.KVOSpeed),NULL);
	
}


//1s的消息
static void Timer_OneSecond(gt_event_st * e){
    TimeNearSec = TimeNearSec-1;
    if(TimeNearSec <= 0)
    {
        TimeNearSec = 0;
    }

    #if VP30
    /*上阻塞*/
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
    /*判断输液器是否脱落*/
	if(!sensorpack.RightKnobStatus || JudgedInfusionTubeFallOff_P(sensorpack.DownPressure)) 
	{
		
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			DEL_TIMER_VAL(run_progress);
		}
		AddAlarm(ALARM_INFUSION_OFF);
	}	
    /*压力*/
	double Pressuredata,Pressuredata_max;
	char temp2[50];
	Pressuredata=PressureConversion(press_Data.Pressure_valuenow,P_mmHg,ParamSetting.PressUint);
	Pressuredata_max=PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint);
	gt_progress_bar_set_pos(bar1, (Pressuredata*100)/Pressuredata_max);
	if( (Pressuredata*100)/Pressuredata_max > 50)
	{
		//黄色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfdfd00));
	}
	else if((Pressuredata*100)/Pressuredata_max > 100)
	{
		//红色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0xfe1b01));
	}
	else
	{
		//绿色
		gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	}
	sprintf(temp2,"%.1f",Pressuredata);
	gt_label_set_text(lab13,temp2);

}




static void back(gt_event_st * e){

	ClearHighAlarm();
	ClearAlarm(ALARM_FINISH_KVO); 
	ClearAlarm(ALARM_INFUSION_DRAIN);
	ClearAlarm(ALARM_HYPERACOUSTIC);
	ClearAlarm(ALARM_CUMULANT_BUBBLE);
	ClearAlarm(ALARM_UPPER_OCCLUSION);
	ClearAlarm(ALARM_UNDERBLOCKING);
	ClearAlarm(ALARM_SYSTEM_FAILURE);
	ClearAlarm(ALARM_INFUSION_OFF);
	SetNowcumulant(sg_NowCumulant); 
	TMC2226_MotorStop();

	lab13 = NULL;
	lab20 = NULL;
	img1  = NULL;

	DEL_TIMER_VAL(run_progress);
	DEL_TIMER_VAL(timer_run_300msec);
    gt_disp_stack_go_back(2);


}

static void Timer_300mSecond(gt_event_st* e){
	char buffer[50];
	/*更新累计量*/
	if(MotorControl.status != MOTOR_BACK)
	{
		if(GetNowAlarmLeve12() != H_ALARM)
		{
			sg_NowCumulant=CalCumulant(MotorControl.anglesum,ParamSetting.KVOSpeed);
			sprintf(buffer,"%.2f",sg_cumlant+sg_NowCumulant); 
			gt_label_set_text(lab20,buffer);	
		}
	}
	/*kvo完成报警*/
	if(TimeNearSec==0)
	{
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();	 
			DEL_TIMER_VAL(run_progress);
			AddAlarm(ALARM_FINISH_KVO); 
		}	
		
	}

	/*下阻塞*/
	if((ParamSetting.KVOSpeed)>=1.0)
	{
		pressureAD = sensorpack.DownPressure -5;
	}
	else
	{
		pressureAD = sensorpack.DownPressure ;
	}
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

	/*上超声*/
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

	/*电池耗尽*/
	if(JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE))
	{
		DEL_TIMER_VAL(run_progress);
	}


}



gt_obj_st * gt_init_KVORun(void)
{

    char buffer[50];
	/*创建自动锁时间*/
	//SetAutoLockTime(ParamSetting.LockTime);
	//写历史记录
	not_first_start_write_history_info(EA_Into,Ev_EnterKVO,NULL);
	pressureAD = 0;
	
	KVORun =  gt_obj_create(NULL);
	my_set_obj_title(KVORun,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(KVORun, gt_color_hex(0x000000));

	gt_obj_add_event_cb(KVORun, MotorRun,MY_MOTOR_RUN, NULL);
	gt_obj_add_event_cb(KVORun, Timer_OneSecond,MY_ONE_SECONDS_TIME, NULL);



	/** lab2 */
	lab2 = gt_label_create(KVORun);
	gt_obj_set_pos(lab2, 0, 50);
	gt_obj_set_size(lab2, 75, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 20);
	gt_label_set_font_family_cn(lab2, 10);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][2]);


	/** lab3 */
	lab3 = gt_label_create(KVORun);
	gt_obj_set_pos(lab3, 170, 50);
	gt_obj_set_size(lab3, 70, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab3, "mL/h");


	/** lab4 */
	lab4 = gt_label_create(KVORun);
	gt_obj_set_pos(lab4, 0, 85);
	gt_obj_set_size(lab4, 240, 80);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",ParamSetting.KVOSpeed);
	gt_label_set_text(lab4, buffer);


	/** lab5 */
	lab5 = gt_label_create(KVORun);
	gt_obj_set_pos(lab5, 252, 50);
	gt_obj_set_size(lab5, 75, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 20);
	gt_label_set_font_family_cn(lab5, 10);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** lab6 */
	lab6 = gt_label_create(KVORun);
	gt_obj_set_pos(lab6, 252, 135);
	gt_obj_set_size(lab6, 130, 25);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 20);
	gt_label_set_font_family_cn(lab6, 10);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][4]);


	/** lab7 */
	lab7 = gt_label_create(KVORun);
	gt_obj_set_pos(lab7, 252, 230);
	gt_obj_set_size(lab7, 85, 25);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 20);
	gt_label_set_font_family_cn(lab7, 10);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, title[SystemSetting.langue][5]);


	/** lab8 */
	lab8 = gt_label_create(KVORun);
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
	lab9 = gt_label_create(KVORun);
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
	lab10 = gt_label_create(KVORun);
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
	lab11 = gt_label_create(KVORun);
	gt_obj_set_pos(lab11, 410, 112);
	gt_obj_set_size(lab11, 70, 25);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 30);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab11, "--");


	/** img1 */
	img1 = gt_img_create(KVORun);
	gt_obj_set_pos(img1, 252, 257);
	gt_obj_set_size(img1, 20, 30);
	gt_img_set_src(img1, "f:img_20x30_46_keyboard_shift.png");


	/** rect3 */
	rect3 = gt_rect_create(KVORun);
	gt_obj_set_pos(rect3, 0, 85);
	gt_obj_set_size(rect3, 240, 80);
	gt_obj_set_opa(rect3, GT_OPA_35);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	my_rect_set_feedback(rect3,false);


	/** lab12 */
	lab12 = gt_label_create(KVORun);
	gt_obj_set_pos(lab12, 275, 257);
	gt_obj_set_size(lab12, 50, 30);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 30);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_LEFT_MID);
	sprintf(buffer,"%.1f",PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	gt_label_set_text(lab12, buffer);


	/** lab13 */
	lab13 = gt_label_create(KVORun);
	gt_obj_set_pos(lab13, 417, 257);
	gt_obj_set_size(lab13, 60, 30);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_en(lab13, 30);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab13, "0");


	/** bar1 */
	bar1 = gt_progress_bar_create(KVORun);
	gt_obj_set_pos(bar1, 252, 290);
	gt_obj_set_size(bar1, 225, 23);
	gt_progress_bar_set_start_end(bar1, 0, 100);
	gt_progress_bar_set_pos(bar1, 50);
	gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	gt_progress_bar_set_color_ina(bar1, gt_color_hex(0xebeef5));
	gt_progress_bar_set_dir(bar1, GT_BAR_DIR_HOR_R2L);


	/** lab14 */
	lab14 = gt_label_create(KVORun);
	gt_obj_set_pos(lab14, 252, 185);
	gt_obj_set_size(lab14, 130, 25);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 20); 
	gt_label_set_font_family_cn(lab14, 10);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab14, title[SystemSetting.langue][6]);

 
	/** lab15 */
	lab15 = gt_label_create(KVORun);
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
	lab16 = gt_label_create(KVORun);
	gt_obj_set_pos(lab16, 354, 212);
	gt_obj_set_size(lab16, 124, 23);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 24);
	gt_label_set_font_family_en(lab16, 30);
	gt_label_set_font_family_cn(lab16, 20);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab16, "--:--:--");

	/** btn2 */
	btn2 = gt_btn_create(KVORun);
	gt_obj_set_pos(btn2, 135, 170);
	gt_obj_set_size(btn2, 105, 40);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][7]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn2,gt_color_hex(0xffffff));
	gt_btn_set_border_width(btn2,1);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

    #if (VET_USE || !CH_USE) //兽用或者国外使用
	/** 药物名 */
	lab17 = gt_label_create(KVORun);
	gt_obj_set_pos(lab17, 143, 235);
	gt_obj_set_size(lab17, 95, 25);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 20);
	gt_label_set_font_family_cn(lab17, 10);
	gt_label_set_font_family_en(lab17, 30);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_CENTER_MID);
	if(InfusionNow.drugname == NULL)
		gt_label_set_text(lab17, "未选药");
	else
		gt_label_set_text(lab17, InfusionNow.drugname);

	/** rect7 */
	rect7 = gt_rect_create(KVORun);
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


	/** rect4 */
	rect4 = gt_rect_create(KVORun);
	gt_obj_set_pos(rect4, 250, 50);
	gt_obj_set_size(rect4, 230, 270);
	gt_obj_set_opa(rect4, GT_OPA_35);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	my_rect_set_feedback(rect4,false);



	/** rect5 */
	rect5 = gt_rect_create(KVORun);
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
	lab18 = gt_label_create(KVORun);
	gt_obj_set_pos(lab18, 252, 84);
	gt_obj_set_size(lab18, 130, 25);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 20);
	gt_label_set_font_family_cn(lab18, 10);
	gt_label_set_font_family_en(lab18, 33);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab18, title[SystemSetting.langue][8]);


	/** lab19 */
	lab19 = gt_label_create(KVORun);
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
	lab20 = gt_label_create(KVORun);
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

	

	/** img12 */
	img3 = gt_img_create(KVORun);
	gt_obj_set_pos(img3, 10, 280);
	gt_obj_set_size(img3, 214, 30);
	gt_img_set_src(img3, "f:img_214x30_Runstrip.png");

	/** img10 */
	img2 = gt_img_create(KVORun);
	gt_obj_set_pos(img2, 209, 280);
	gt_obj_set_size(img2, 19, 30);
	gt_img_set_src(img2, "f:img_19x30_RunBright.png");


	//create timer
	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	gt_event_send(KVORun,MY_MOTOR_RUN,NULL);


    return KVORun;
}