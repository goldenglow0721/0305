#include "ui.h"


/** WeightMode */
gt_obj_st * UiWeightMode = NULL;
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
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * svg1 = NULL;
static _gt_timer_st * timer_run_300msec;


extern WeightMode_Run WeightMode_run;

static const char title[5][5][50]={
	"体重模式",
	"药量",
	"液量",
	"运行",
	"排气",

	"BW Mode",
	"Drug amt.",
	"Volume",
	"Start",
	"Purge1",

	"Modo de PC",
	"Dosificación de Drogas",
	"Volumen",
	"Inicio",
	"Purga",

	"體重模式",
	"藥量",
	"液量",
	"運行",
	"排氣",
	
	"Modo peso corporal",
	"Valor da droga",
	"Volume",
	"Inicio",
	"Purga"
};



static void img1_0_cb(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	lab5 = NULL;
	lab10 = NULL;
	lab7 = NULL;
	img1 = NULL;
	DEL_TIMER_VAL(timer_run_300msec);
	gt_disp_stack_go_back(1);
}

static void ChangeBody(gt_event_st * e) {
	strcpy(keyboardf.title,title[SystemSetting.langue][0]);
	keyboardf.data = &WeightMode.Body;
	keyboardf.id=5;
	limit.toplimit = 300.0;
	limit.lowerlimit = 0.01;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ChangeMedicine(gt_event_st * e) {
	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &WeightMode.Medicine;
	keyboardf.id=6;
	limit.toplimit = 999.9;
	limit.lowerlimit = 0.01;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ChangeLiquid(gt_event_st * e) {
	strcpy(keyboardf.title,title[SystemSetting.langue][2]);
	keyboardf.data = &WeightMode.Liquid;
	keyboardf.id=7;
	limit.toplimit = 9999.9;
	limit.lowerlimit = 0.01;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void Run(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);


	if(WeightMode.Body == 0){
		dialog1_create("请输入体重!");
		return;
	}
	else if(WeightMode.Medicine == 0){
		dialog1_create("请输入药量!");
		return;
	}
	else if(WeightMode.Liquid==0){
		dialog1_create("请输入液量");
		return;
	}
	else if(WeightMode.DoseSpeed==0){
		dialog1_create("请输入剂量速度");
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
	WeightMode_run.title = (char*)&title[SystemSetting.langue][0];
	WeightMode_run.Body = &WeightMode.Body;
	WeightMode_run.DoseSpeed = &WeightMode.DoseSpeed;
	WeightMode_run.quantity = &WeightMode.W_Quantity;
	WeightMode_run.speed 	= &WeightMode.Speed;
	WeightMode_run.init_func_cb = gt_init_WeightMode;
	press_Data.Pressure_newAD0 = sensorpack.DownPressure;
	WriteWeightModeMessageToFlash();
	gt_disp_stack_load_scr_anim(GT_SCR_ID_97, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

//Purge1
static void Purge1(gt_event_st * e) {	
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_85, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);	
}

static void btn3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_91, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void Next(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_17, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void Timer_300mSecond(gt_event_st* e){
	if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_11) == RESET)
	{
		Run(NULL);
		DEL_TIMER_VAL(timer_run_300msec);
	}
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 5)  //修改完体重出来的
	{
		UpdateWeightModeTheDisplay(CHANGE_WEIGHT);
		//更新体重显示
		sprintf(buffer,"%.2f",(float)WeightMode.Body);
		gt_label_set_text(lab5,buffer);
	}
	if(atoi(e->param) == 6)  //修改完药量出来的
	{
		UpdateWeightModeTheDisplay(CHANGE_Medicine);
		//更新药量
		sprintf(buffer,"%.2f",(float)WeightMode.Medicine);
		gt_label_set_text(lab7, buffer);

	}
	if(atoi(e->param) == 7)  //修改完液量出来的
	{
		UpdateWeightModeTheDisplay(CHANGE_Liquid);
		//更新液量
		sprintf(buffer,"%.2f",(float)WeightMode.Liquid);
		gt_label_set_text(lab10, buffer);
	}
}




gt_obj_st * gt_init_WeightMode(void)
{
	char buffer[50];
	UiWeightMode =  gt_obj_create(NULL);
	my_set_obj_title(UiWeightMode,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(UiWeightMode, gt_color_hex(0x000000));
	gt_obj_add_event_cb(UiWeightMode,EventUpdata,MY_EVENT_UPDATA,NULL);
	 


	/** img1 */
	img1 = gt_img_create(UiWeightMode);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(UiWeightMode);
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
	lab3 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab3, 170, 70);
	gt_obj_set_size(lab3, 140, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][1]);


	/** lab4 */
	lab4 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab4, 325, 70);
	gt_obj_set_size(lab4, 140, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);


	/** rect2 */
	rect2 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect2, 15, 70);
	gt_obj_set_size(rect2, 140, 50);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, ChangeBody, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	rect3 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect3, 170, 70);
	gt_obj_set_size(rect3, 140, 50);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, ChangeMedicine, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect4, 325, 70);
	gt_obj_set_size(rect4, 140, 50);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, ChangeLiquid, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	lab5 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab5, 15, 130);
	gt_obj_set_size(lab5, 140, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	if(WeightMode.Body)
		sprintf(buffer,"%.2f",(float)WeightMode.Body);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab5,buffer);


	/** lab6 */
	lab6 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab6, 15, 180);
	gt_obj_set_size(lab6, 140, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "kg");


	/** rect5 */
	rect5 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect5, 15, 120);
	gt_obj_set_size(rect5, 140, 120);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, ChangeBody, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	lab7 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab7, 170, 130);
	gt_obj_set_size(lab7, 140, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	if(WeightMode.Medicine)
		sprintf(buffer,"%.2f",(float)WeightMode.Medicine);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab7, buffer);


	/** rect6 */
	rect6 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect6, 170, 120);
	gt_obj_set_size(rect6, 140, 120);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, ChangeMedicine, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab10 */
	lab10 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab10, 325, 140);
	gt_obj_set_size(lab10, 140, 50);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	if(WeightMode.Liquid)
		sprintf(buffer,"%.2f",(float)WeightMode.Liquid);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab10, buffer);


	/** lab11 */
	lab11 = gt_label_create(UiWeightMode);
	gt_obj_set_pos(lab11, 325, 180);
	gt_obj_set_size(lab11, 140, 50);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "mL");


	/** rect7 */
	rect7 = gt_rect_create(UiWeightMode);
	gt_obj_set_pos(rect7, 325, 120);
	gt_obj_set_size(rect7, 140, 120);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, ChangeLiquid, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	

	/** btn1 */
	btn1 = gt_btn_create(UiWeightMode);
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
	btn2 = gt_btn_create(UiWeightMode);
	gt_obj_set_pos(btn2, 110, 250);
	gt_obj_set_size(btn2, 110, 55);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_family_en(btn2, 33);
	gt_btn_set_font_family_fl(btn2, 50);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][4]);
	gt_btn_set_color_border(btn2, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2, 4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, Purge1, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn3 */
	btn3 = gt_btn_create(UiWeightMode);
	gt_obj_set_pos(btn3, 195, 185);
	gt_obj_set_size(btn3, 95, 41);
	gt_btn_set_font_color(btn3, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn3, 24);
	gt_btn_set_font_family_en(btn3, 33);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, GetMedicineUintString(WeightMode.Med_Uint));
	gt_btn_set_color_border(btn3, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn3, 4);
	gt_btn_set_radius(btn3, 4);
	gt_obj_add_event_cb(btn3, btn3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(UiWeightMode);
	gt_obj_set_pos(svg1, 410, 245);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg1, Next, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	return UiWeightMode;
}

