#include "ui.h"


/** TimeMode */
gt_obj_st * UiTimeMode = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static _gt_timer_st * timer_run_300msec;


extern SpeedAndTimeRun speed_time_run;

static const char title[5][6][50]={
	"时间",
	"待入量",
	"流速",
	"运行",
	"排气",
	"时间模式",

	
	"Time",
	"VTBI",
	"Rate",
	"Start",
	"purge",
	"Time Mode",

	"Tiempo",
	"VTBI",
	"Tasa",
	"Inicio",
	"Purga",
	"Modo de Tiempo",

	"時間",
	"待入量",
	"流速",
	"運行",
	"排氣",
	"時間模式",

	"Tempo",
	"VTBI",
	"Taxa",
	"Inicio",
	"Purga",
	"Modo Tempo"	
};




static void img1_0_cb(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);


	gt_disp_stack_go_back(1);
}



static void ChangeTime(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);

	strcpy(keyboardt.title,title[SystemSetting.langue][0]);
	keyboardt.time = &TimeMode.time; 
	gt_disp_stack_load_scr_anim(GT_SCR_ID_82, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}

static void ChangeQuantity(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);

	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &TimeMode.quantity; 
	limit.toplimit = 9999.9;
	limit.lowerlimit = 0.01;
	keyboardf.id=2;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void Run(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);

	if(!TimeMode.time.hour && !TimeMode.time.min && !TimeMode.time.sec){
		dialog1_create("请输入时间!");
		return;
	}
	else if(TimeMode.quantity==0){
		dialog1_create("请输入代入量");
		return;
	}
	else if(sensorpack.BubbleStatus == Bubble_TRUE)
	{
		dialog1_create("右边管路有气泡");
		return;
	}
	else
	{
		;
	}
	

	strcpy(speed_time_run.title,title[SystemSetting.langue][5]);
	speed_time_run.quantity = &TimeMode.quantity;
	speed_time_run.speed 	= &TimeMode.speed;
	speed_time_run.time		= &TimeMode.time;
	speed_time_run.init_func_cb = gt_init_TimeMode;

	press_Data.Pressure_newAD0 = sensorpack.DownPressure;
	WriteTimeModeMessageToFlash();

	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_96, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void purge(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_85, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void Timer_300mSecond(gt_event_st* e){
	if(at32_up_button_state() == RESET)
	{
		Run(NULL);
		DEL_TIMER_VAL(timer_run_300msec);
	}
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 1)  //修改完时间出来的
	{
		
		UpdateTimeModeTheDisplay(CHANGE_TIME,&TimeMode.speed,&TimeMode.quantity,&TimeMode.time);
		//更新时间显示
		sprintf(buffer,"%d:%d:%d",TimeMode.time.hour,TimeMode.time.min,TimeMode.time.sec);
		gt_label_set_text(lab10, buffer);
		//更新速度
		if(TimeMode.speed!=0.0)
		{
			sprintf(buffer,"%.2f",(float)TimeMode.speed);
			TimeMode.speed= atof(buffer);
		}
		else
		{
			sprintf(buffer,"%s","--");
		}	
		gt_label_set_text(lab5, buffer);
	}
	if(atoi(e->param) == 2)  //修改完待入量出来的
	{
		UpdateTimeModeTheDisplay(CHANGE_QUAN,&TimeMode.speed,&TimeMode.quantity,&TimeMode.time);
		//更新待入量
		sprintf(buffer,"%.2f",(float)TimeMode.quantity);
		gt_label_set_text(lab7, buffer);
		//更新速度
		if(TimeMode.speed != 0.0)
		{
			sprintf(buffer,"%.2f",(float)TimeMode.speed);
			TimeMode.speed= atof(buffer);
		}
		else
		{
			sprintf(buffer,"%s","--");
		}	
		gt_label_set_text(lab5, buffer);
	}
}

static void one_sec_timer(gt_event_st * e)
{
	if(MotorControl.status != MOTOR_STOP)
	{
		TMC2226_MotorStop();
	}
	/*无操作功能*/
	if(sensorpack.RightKnobStatus)
	{
		if(MotorControl.status == MOTOR_STOP)
		{			 
			if(NoOperFunctionTimeCountDown(ParamSetting.NoOperationState))
			{
				ClearAlarm(ALARM_NO_OPERATION);  
				
			}
			else
			{
				if(InfusionNow.ReminderFlag == 1)
				{
					AddAlarm(ALARM_NO_OPERATION);	 
				}
			}
		}
	}
	else
	{
		ClearAlarm(ALARM_NO_OPERATION); 		   
	}
}

gt_obj_st * gt_init_TimeMode(void)
{
	char buffer[50];
	UiTimeMode =  gt_obj_create(NULL);
	my_set_obj_title(UiTimeMode,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(UiTimeMode, gt_color_hex(0x000000));
	gt_obj_add_event_cb(UiTimeMode,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_obj_add_event_cb(UiSpeedMode,one_sec_timer,MY_ONE_SECONDS_TIME,NULL);


	/** img1 */
	img1 = gt_img_create(UiTimeMode);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);





	/** lab2 */
	lab2 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab2, 15, 70);
	gt_obj_set_size(lab2, 140, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][0]);


	/** lab3 */
	lab3 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab3, 170, 70);
	gt_obj_set_size(lab3, 150, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][1]);


	/** lab4 */
	lab4 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab4, 325, 70);
	gt_obj_set_size(lab4, 150, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);


	/** rect2 */
	rect2 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect2, 15, 70);
	gt_obj_set_size(rect2, 140, 50);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	rect3 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect3, 170, 70);
	gt_obj_set_size(rect3, 140, 50);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	



	/** lab6 */
	lab6 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab6,325,180);
	gt_obj_set_size(lab6, 140, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "mL/h");


	/** rect5 */
	rect5 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect5, 15, 120);
	gt_obj_set_size(rect5, 140, 120);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** lab7 */
	lab7 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab7, 170, 130);
	gt_obj_set_size(lab7, 140, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	if(TimeMode.quantity)
		sprintf(buffer,"%.2f",(float)TimeMode.quantity);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab7, buffer);


	/** lab8 */
	lab8 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab8, 170, 180);
	gt_obj_set_size(lab8, 140, 50);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "mL/h");


	/** rect6 */
	rect6 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect6, 170, 120);
	gt_obj_set_size(rect6, 140, 120);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab10 */
	lab10 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab10,15, 130);
	gt_obj_set_size(lab10, 140, 50);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	if(TimeMode.quantity)
		sprintf(buffer,"%d:%d:%d",TimeMode.time.hour,TimeMode.time.min,TimeMode.time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab10, buffer);
	gt_obj_add_event_cb(lab10, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** lab11 */
	lab11 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab11, 15, 180);
	gt_obj_set_size(lab11, 140, 50);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "h:m:s");
	gt_obj_add_event_cb(lab11, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect7 */
	rect7 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect7, 325, 120);
	gt_obj_set_size(rect7, 140, 120);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	my_rect_set_feedback(rect7,false);



	/** rect4 */
	rect4 = gt_rect_create(UiTimeMode);
	gt_obj_set_pos(rect4, 325, 70);
	gt_obj_set_size(rect4, 140, 50);
	gt_obj_set_opa(rect4, GT_OPA_55);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	my_rect_set_feedback(rect4,false);



	/** lab5 */
	lab5 = gt_label_create(UiTimeMode);
	gt_obj_set_pos(lab5, 325,130);
	gt_obj_set_size(lab5, 140, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	if(TimeMode.speed!=0.0)
	{
		sprintf(buffer,"%.2f",(float)TimeMode.speed);
	}
	else
	{
		sprintf(buffer,"%s","--");
	}	
	gt_label_set_text(lab5, buffer);


	/** btn1 */
	btn1 = gt_btn_create(UiTimeMode);
	gt_obj_set_pos(btn1, 270, 250);
	gt_obj_set_size(btn1, 110, 55);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn1, gt_color_hex(0x00ff40));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x228B22));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Run, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn2 */
	btn2 = gt_btn_create(UiTimeMode);
	gt_obj_set_pos(btn2, 110, 249);
	gt_obj_set_size(btn2, 110, 55);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_family_en(btn2, 33);
	gt_btn_set_font_family_fl(btn2, 50);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][4]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn2, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2, 4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, purge, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	return UiTimeMode;
}

