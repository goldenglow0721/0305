#include "ui.h"


/** PurgeRun */
gt_obj_st * PurgeRun = NULL;
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
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * bar1 = NULL;
static gt_obj_st * rect6 = NULL;
static _gt_timer_st * run_progress;

extern int BlevelData[4];
static int num=10;


static const char title[5][7][50]={
	"排气",
	"停止",
	"排气速度",
	"排气量",
	"品牌",
	"累计量",
	"压力",

	"Purge",
	"Stop",
	"Purge Rate",
	"Purge Volume",
	"Brand",
	"Total Volume",
	"Pressure",

	"Purga",
	"Parar",
	"Tasa de Purga",
	"Volumen de Purga",
	"Marca",
	"Volumen total",
	"Presión",
	
	"排氣",
	"停止",
	"排氣速度",
	"排氣量",
	"品牌",
	"累計量",
	"壓力",

	"Purga",
	"Parar",
	"Taxa de Purga",
	"Volume de purga",
	"Marca",
	"Volume total",
	"Pressão"

};


static void Stop(gt_event_st * e) {
	

	ClearAlarm(ALARM_INFUSION_OFF);
	DEL_TIMER_VAL(run_progress);
	run_progress = NULL;
	TMC2226_MotorStop();
	lab12 = NULL;
	lab16 = NULL;
	lab13 = NULL;
	lab7 = NULL;
	lab4 = NULL;
		DEL_TIMER_VAL(run_progress);
	gt_disp_stack_go_back(2);

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
	

	//计算速度
	tempdata =CalSpeed(exhaustMode.speed); 
	TMC2226_MotorRun(1,0,tempdata);
	//设置运行条运行速度
	DEL_TIMER_VAL(run_progress);
	run_progress = _gt_timer_create(run_progress_func,SetProgressRunSpeed(exhaustMode.speed),NULL);
	
}

static void Timer_OneSecond(gt_event_st * e){
	char buffer[50];

	//判断输液器脱落
	if(!sensorpack.RightKnobStatus || JudgedInfusionTubeFallOff_P(sensorpack.DownPressure)) 
	{
		
		if(MotorControl.status == MOTOR_RUN)
		{
			TMC2226_MotorStop();
			DEL_TIMER_VAL(run_progress);
			run_progress = NULL;
		}
		AddAlarm(ALARM_INFUSION_OFF);
		TMC2226_MotorStop();
	}


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
	sprintf(temp2,"%.1f",Pressuredata);
	gt_label_set_text(lab16,temp2);


}




gt_obj_st * gt_init_PurgeRun(void)
{
	char buffer[50];
	PurgeRun =  gt_obj_create(NULL);
	my_set_obj_title(PurgeRun,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PurgeRun, gt_color_hex(0x000000));
	 

	gt_obj_add_event_cb(PurgeRun, Timer_OneSecond,MY_ONE_SECONDS_TIME, NULL);
	gt_obj_add_event_cb(PurgeRun, MotorRun,MY_MOTOR_RUN, NULL);
	not_first_start_write_history_info(EA_start,Ev_EnterExhaust,NULL);
	
	
	/** btn1 */
	btn1 = gt_btn_create(PurgeRun);
	gt_obj_set_pos(btn1, 135, 210);
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
	gt_obj_add_event_cb(btn1, Stop, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab2, 3, 55);
	gt_obj_set_size(lab2, 170, 40);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][2]);


	/** lab3 */
	lab3 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab3, 178, 55);
	gt_obj_set_size(lab3, 60, 40);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab3, "mL/h");


	/** 排气速度 */
	lab4 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab4, 83, 89);
	gt_obj_set_size(lab4, 100, 34);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",exhaustMode.speed);
	gt_label_set_text(lab4, buffer);


	/** lab5 */
	lab5 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab5, 3, 125);
	gt_obj_set_size(lab5, 170, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** lab6 */
	lab6 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab6, 178, 125);
	gt_obj_set_size(lab6, 60, 40);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab6, "mL/h");


	/** 排气量 */
	lab7 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab7, 79, 157);
	gt_obj_set_size(lab7, 101, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "0.0");


	/** lab8 */
	lab8 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab8, 248, 55);
	gt_obj_set_size(lab8, 80, 40);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab8, title[SystemSetting.langue][4]);


	/** lab9 */
	lab9 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab9, 248, 125);
	gt_obj_set_size(lab9, 160, 40);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab9, title[SystemSetting.langue][5]);


	/** lab10 */
	lab10 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab10, 248, 210);
	gt_obj_set_size(lab10, 140, 40);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab10, title[SystemSetting.langue][6]);


	/** lab11 */
	lab11 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab11, 386, 125);
	gt_obj_set_size(lab11, 94, 40);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab11, "mL");


	/** lab12 */
	lab12 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab12, 380, 210);
	gt_obj_set_size(lab12, 100, 40);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab12, GetPressUintString(ParamSetting.PressUint));


	/** lab13 */
	lab13 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab13, 385, 55);
	gt_obj_set_size(lab13, 95, 40);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab13, InfusionNow.tubename);


	/** lab14 */
	lab14 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab14, 375, 165);
	gt_obj_set_size(lab14, 105, 36);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_cn(lab14, 20);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab14, "0.00");


	/** img1 */
	img1 = gt_img_create(PurgeRun);
	gt_obj_set_pos(img1, 248, 253);
	gt_obj_set_size(img1, 20, 30);
	gt_img_set_src(img1, "f:img_20x30_46_keyboard_shift.png");


	/** rect2 */
	rect2 = gt_rect_create(PurgeRun);
	gt_obj_set_pos(rect2, 245, 55);
	gt_obj_set_size(rect2, 235, 263);
	gt_obj_set_opa(rect2, GT_OPA_35);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	my_rect_set_feedback(rect2,false);


	/** rect3 */
	rect3 = gt_rect_create(PurgeRun);
	gt_obj_set_pos(rect3, 0, 55);
	gt_obj_set_size(rect3, 240, 150);
	gt_obj_set_opa(rect3, GT_OPA_35);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	my_rect_set_feedback(rect3,false);



	/** lab15 */
	lab15 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab15, 267, 256);
	gt_obj_set_size(lab15, 80, 24);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 24);
	gt_label_set_font_family_en(lab15, 33);
	gt_label_set_font_family_cn(lab15, 20);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_LEFT);
	sprintf(buffer,"%.1f",PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	gt_label_set_text(lab15, buffer);


	/** 压力值 */
	lab16 = gt_label_create(PurgeRun);
	gt_obj_set_pos(lab16, 405, 256);
	gt_obj_set_size(lab16, 80, 30);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 24);
	gt_label_set_font_family_en(lab16, 33);
	gt_label_set_font_family_cn(lab16, 20);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab16, "0");


	/** bar1 */
	bar1 = gt_progress_bar_create(PurgeRun);
	gt_obj_set_pos(bar1, 248, 288);
	gt_obj_set_size(bar1, 229, 30);
	gt_progress_bar_set_start_end(bar1, 0, 100);
	gt_progress_bar_set_pos(bar1, 50);
	gt_progress_bar_set_color_act(bar1, gt_color_hex(0x00ff00));
	gt_progress_bar_set_color_ina(bar1, gt_color_hex(0xebeef5));
	gt_progress_bar_set_dir(bar1, GT_BAR_DIR_HOR_R2L);
	




	/** img12 */
	img3 = gt_img_create(PurgeRun);
	gt_obj_set_pos(img3, 10, 280);
	gt_obj_set_size(img3, 214, 30);
	gt_img_set_src(img3, "f:img_214x30_Runstrip.png");

	/** img10 */
	img2 = gt_img_create(PurgeRun);
	gt_obj_set_pos(img2, 8+20*num, 280);
	gt_obj_set_size(img2, 19, 30);
	gt_img_set_src(img2, "f:img_19x30_Run.png");


	gt_event_send(PurgeRun,MY_MOTOR_RUN,NULL);

	return PurgeRun;
}

