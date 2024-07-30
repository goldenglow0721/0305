#include "ui.h"

//注:   注意是否需要传参数来确认是哪个界面过来的(8888 or 6686)





/** PressureCalibrate2 */
gt_obj_st * PressureCalibrate2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * rect16 = NULL;
static gt_obj_st * lab17 = NULL;
static gt_obj_st * rect17 = NULL;
static gt_obj_st * lab18 = NULL;
static gt_obj_st * rect18 = NULL;
static gt_obj_st * lab19 = NULL;
static gt_obj_st * rect19 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * rect11 = NULL;
static gt_obj_st * rect12 = NULL;
static gt_obj_st * rect13 = NULL;
static gt_obj_st * rect14 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect15 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * lab20 = NULL;
static _gt_timer_st * timer_main_ThirmSec = NULL;


static int sg_AD0_temp;
static int sg_AD40_temp;
static int sg_AD70_temp;
static int sg_AD120_temp;
static double sg_P40_temp;
static double sg_P70_temp;
static double sg_P120_temp;


static const char title[5][5][50]={
	"压力校准",
	"返回",
	"确认",
	"运行",
	"暂停",

	"Pressure Calibration",
	"",
	"",
	"",
	"",

	"Calibración de Presión",
	"",
	"",
	"",
	"",

	"壓力校準",
	"",
	"",
	"",
	"",

	"Pressão de calibração",
	"",
	"",
	"",
	""
		
};



static void Timer_ThirmSec(gt_event_st * e){
	//300ms的定时器
	char buffer[50];
	sprintf(buffer,"%d",sensorpack.DownPressure);
	gt_label_set_text(lab20,buffer);
}


static void back(gt_event_st * e) {

	TMC2226_MotorStop();
	
	if(my_judge_obj_exists(GT_SCR_ID_54))
	{
		gt_disp_stack_go_back(3);
	}
	else
	{
		gt_disp_stack_go_back(2);
	}

}

static void Confirm(gt_event_st * e) {
	
	//还要判断这几个值是否都在合理的范围内
	infusion_data.Pressure_AD0 = sg_AD0_temp;
	infusion_data.Pressure_AD40 = sg_AD40_temp;
	infusion_data.Pressure_AD70 = sg_AD70_temp;
	infusion_data.Pressure_AD120 = sg_AD120_temp;
	infusion_data.Pressure_value40 = sg_P40_temp;
	infusion_data.Pressure_value70 = sg_P70_temp;
	infusion_data.Pressure_value120 = sg_P120_temp;

	writeInfusionTubeListToFlash();
	//修改的数据写入flash
	TMC2226_MotorStop();

	if(my_judge_obj_exists(GT_SCR_ID_54))
	{
		gt_disp_stack_go_back(3);
	}
	else
	{
		gt_disp_stack_go_back(2);
	}
}

static void Run(gt_event_st * e) {
	//电机转动
	TMC2226_MotorRun(1,0,561);
}

static void Pause(gt_event_st * e) {
	//电机停
	TMC2226_MotorStop();
}


static void ad0(gt_event_st * e) {
	strcpy(keyboardi.title,"AD0");
	keyboardi.data = &sg_AD0_temp;
	limit.lowerlimit=16000;
	limit.toplimit=20000;
	keyboardi.id=6;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ad40(gt_event_st * e) {
	strcpy(keyboardi.title,"AD40");
	keyboardi.data = &sg_AD40_temp;
	limit.lowerlimit=16000;
	limit.toplimit=21000;
	keyboardi.id=7;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void P40(gt_event_st * e) {

	strcpy(keyboardf.title,"P40");
	keyboardf.data = &sg_P40_temp;
	limit.lowerlimit=30.00;
	limit.toplimit=50.00;
	keyboardf.id=13;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ad70(gt_event_st * e) {
	strcpy(keyboardi.title,"AD70");
	keyboardi.data = &sg_AD70_temp;
	limit.lowerlimit=16000;
	limit.toplimit=22000;
	keyboardi.id=8;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void P70(gt_event_st * e) {
	strcpy(keyboardf.title,"P70");
	keyboardf.data = &sg_P70_temp;
	limit.lowerlimit=60.00;
	limit.toplimit=80.00;
	keyboardf.id=14;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void AD120(gt_event_st * e) {
	strcpy(keyboardi.title,"AD120");
	keyboardi.data = &sg_AD120_temp;
	limit.lowerlimit=16000;
	limit.toplimit=23000;
	keyboardi.id=9;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void P120(gt_event_st * e) {
	strcpy(keyboardf.title,"P120");
	keyboardf.data = &sg_P120_temp;
	limit.lowerlimit=110.00;
	limit.toplimit=130.00;
	keyboardf.id=15;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	if(atoi(e->param) == 13)  //修改完P40出来的
	{
		sprintf(buffer,"%.1f",sg_P40_temp);
		gt_label_set_text(lab11, buffer);
	}
	if(atoi(e->param) == 14)  //修改完P70出来的
	{
		sprintf(buffer,"%.1f",sg_P70_temp);
		gt_label_set_text(lab13, buffer);
	}
	if(atoi(e->param) == 15)  //修改完P120出来的
	{
		sprintf(buffer,"%.1f",sg_P120_temp);
		gt_label_set_text(lab15, buffer);
	}
	if(atoi(e->param) == 6)  //修改完AD0出来的
	{
		sprintf(buffer,"%d",sg_AD0_temp);
		gt_label_set_text(lab9, buffer);
	}
	if(atoi(e->param) == 7)  //修改完AD40出来的
	{
		sprintf(buffer,"%d",sg_AD40_temp);
		gt_label_set_text(lab10, buffer);
	}
	if(atoi(e->param) == 8)  //修改完AD70出来的
	{
		sprintf(buffer,"%d",sg_AD70_temp);
		gt_label_set_text(lab12, buffer);
	}
	if(atoi(e->param) == 9)  //修改完AD120出来的
	{
		sprintf(buffer,"%d",sg_AD120_temp);
		gt_label_set_text(lab14, buffer);
	}
}





gt_obj_st * gt_init_PressureCalibrate2(void)
{
	char buffer[50];
 
	
	PressureCalibrate2 =  gt_obj_create(NULL);
	my_set_obj_title(PressureCalibrate2,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PressureCalibrate2, gt_color_hex(0x000000));
	gt_obj_add_event_cb(PressureCalibrate2,EventUpdata,MY_EVENT_UPDATA,NULL);
	 
	/** lab16 */
	lab16 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab16, 20, 270);
	gt_obj_set_size(lab16, 90, 50);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 24);
	gt_label_set_font_family_cn(lab16, 20);
	gt_label_set_font_family_en(lab16, 33);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab16, title[SystemSetting.langue][1]);			//	返回


	/** rect16 */
	rect16 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect16, 20, 270);
	gt_obj_set_size(rect16, 90, 50);
	gt_obj_set_opa(rect16, GT_OPA_54);
	gt_rect_set_radius(rect16, 0);
	gt_rect_set_bg_color(rect16, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect16, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect16, 1);
	gt_rect_set_border(rect16, 0);
	gt_obj_add_event_cb(rect16, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab17 */
	lab17 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab17, 140, 270);
	gt_obj_set_size(lab17, 90, 50);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 24);
	gt_label_set_font_family_cn(lab17, 20);
	gt_label_set_font_family_en(lab17, 33);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab17, title[SystemSetting.langue][2]);			//确认


	/** rect17 */
	rect17 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect17, 140, 270);
	gt_obj_set_size(rect17, 90, 50);
	gt_obj_set_opa(rect17, GT_OPA_50);
	gt_rect_set_radius(rect17, 0);
	gt_rect_set_bg_color(rect17, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect17, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect17, 1);
	gt_rect_set_border(rect17, 0);
	gt_obj_add_event_cb(rect17, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab18 */
	lab18 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab18, 260, 270);
	gt_obj_set_size(lab18, 90, 50);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 24);
	gt_label_set_font_family_cn(lab18, 20);
	gt_label_set_font_family_en(lab18, 33);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab18,title[SystemSetting.langue][3]);			//运行


	/** rect18 */
	rect18 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect18, 260, 270);
	gt_obj_set_size(rect18, 90, 50);
	gt_obj_set_opa(rect18, GT_OPA_50);
	gt_rect_set_radius(rect18, 0);
	gt_rect_set_bg_color(rect18, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect18, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect18, 1);
	gt_rect_set_border(rect18, 0);
	gt_obj_add_event_cb(rect18, Run, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab19 */
	lab19 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab19, 380, 270);
	gt_obj_set_size(lab19, 90, 50);
	gt_label_set_font_color(lab19, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab19, 24);
	gt_label_set_font_family_cn(lab19, 20);
	gt_label_set_font_family_en(lab19, 33);
	gt_label_set_font_family_fl(lab19, 50);
	gt_label_set_font_align(lab19, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab19,title[SystemSetting.langue][4]);			//暂停


	/** rect19 */
	rect19 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect19, 380, 269);
	gt_obj_set_size(rect19, 90, 50);
	gt_obj_set_opa(rect19, GT_OPA_50);
	gt_rect_set_radius(rect19, 0);
	gt_rect_set_bg_color(rect19, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect19, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect19, 1);
	gt_rect_set_border(rect19, 0);
	gt_obj_add_event_cb(rect19, Pause, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab9 */
	lab9 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab9, 64, 69);
	gt_obj_set_size(lab9, 75, 33);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",infusion_data.Pressure_AD0);
	gt_label_set_text(lab9, buffer);


	/** lab10 */
	lab10 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab10, 66, 138);
	gt_obj_set_size(lab10, 75, 32);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",infusion_data.Pressure_AD40 );
	gt_label_set_text(lab10, buffer);


	/** lab11 */
	lab11 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab11, 65, 203);
	gt_obj_set_size(lab11, 75, 33);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.1f",infusion_data.Pressure_value40);
	gt_label_set_text(lab11, buffer);


	/** lab12 */
	lab12 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab12, 222, 136);
	gt_obj_set_size(lab12, 75, 32);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",infusion_data.Pressure_AD70);
	gt_label_set_text(lab12, buffer);


	/** lab13 */
	lab13 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab13, 221, 203);
	gt_obj_set_size(lab13, 75, 31);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.1f",infusion_data.Pressure_value70);
	gt_label_set_text(lab13, buffer);


	/** lab14 */
	lab14 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab14, 396, 136);
	gt_obj_set_size(lab14, 75, 31);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_cn(lab14, 20);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",infusion_data.Pressure_AD120);
	gt_label_set_text(lab14, buffer);


	/** lab15 */
	lab15 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab15, 395, 200);
	gt_obj_set_size(lab15, 75, 33);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 24);
	gt_label_set_font_family_cn(lab15, 20);
	gt_label_set_font_family_en(lab15, 33);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.1f",infusion_data.Pressure_value120);
	gt_label_set_text(lab15, buffer);


	/** rect9 */
	rect9 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect9, 65, 69);
	gt_obj_set_size(rect9, 75, 35);
	gt_obj_set_opa(rect9, GT_OPA_41);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);
	gt_obj_add_event_cb(rect9, ad0, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect10 */
	rect10 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect10, 65, 136);
	gt_obj_set_size(rect10, 75, 35);
	gt_obj_set_opa(rect10, GT_OPA_41);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect10, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 0);
	gt_obj_add_event_cb(rect10, ad40, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect11 */
	rect11 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect11, 64, 203);
	gt_obj_set_size(rect11, 75, 35);
	gt_obj_set_opa(rect11, GT_OPA_41);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect11, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 0);
	gt_obj_add_event_cb(rect11, P40, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect12 */
	rect12 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect12, 221, 135);
	gt_obj_set_size(rect12, 75, 35);
	gt_obj_set_opa(rect12, GT_OPA_41);
	gt_rect_set_radius(rect12, 0);
	gt_rect_set_bg_color(rect12, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect12, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect12, 1);
	gt_rect_set_border(rect12, 0);
	gt_obj_add_event_cb(rect12, ad70, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect13 */
	rect13 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect13, 221, 200);
	gt_obj_set_size(rect13, 75, 35);
	gt_obj_set_opa(rect13, GT_OPA_41);
	gt_rect_set_radius(rect13, 0);
	gt_rect_set_bg_color(rect13, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect13, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect13, 1);
	gt_rect_set_border(rect13, 0);
	gt_obj_add_event_cb(rect13, P70, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect14 */
	rect14 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect14, 395, 135);
	gt_obj_set_size(rect14, 75, 35);
	gt_obj_set_opa(rect14, GT_OPA_41);
	gt_rect_set_radius(rect14, 0);
	gt_rect_set_bg_color(rect14, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect14, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect14, 1);
	gt_rect_set_border(rect14, 0);
	gt_obj_add_event_cb(rect14, AD120, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab2, 1, 70);
	gt_obj_set_size(lab2, 64, 34);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "AD0");


	/** rect2 */
	rect2 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect2, 1, 69);
	gt_obj_set_size(rect2, 64, 35);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, ad0, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab3 */
	lab3 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab3, 0, 136);
	gt_obj_set_size(lab3, 63, 34);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "AD40");


	/** rect3 */
	rect3 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect3, 1, 136);
	gt_obj_set_size(rect3, 64, 35);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, ad40, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab4 */
	lab4 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab4, 0, 204);
	gt_obj_set_size(lab4, 63, 34);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "P40");


	/** rect4 */
	rect4 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect4, 0, 203);
	gt_obj_set_size(rect4, 64, 35);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, P40, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	lab5 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab5, 157, 136);
	gt_obj_set_size(lab5, 64, 34);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "AD70");


	/** rect5 */
	rect5 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect5, 157, 135);
	gt_obj_set_size(rect5, 64, 35);
	gt_obj_set_opa(rect5, GT_OPA_50);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, ad70, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab6 */
	lab6 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab6, 158, 203);
	gt_obj_set_size(lab6, 62, 32);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "P70");


	/** rect6 */
	rect6 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect6, 157, 201);
	gt_obj_set_size(rect6, 64, 35);
	gt_obj_set_opa(rect6, GT_OPA_50);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, P70, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect15 */
	rect15 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect15, 395, 200);
	gt_obj_set_size(rect15, 75, 35);
	gt_obj_set_opa(rect15, GT_OPA_41);
	gt_rect_set_radius(rect15, 0);
	gt_rect_set_bg_color(rect15, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect15, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect15, 1);
	gt_rect_set_border(rect15, 0);
	gt_obj_add_event_cb(rect15, P120, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	lab7 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab7, 315, 136);
	gt_obj_set_size(lab7, 80, 34);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "AD120");


	/** rect7 */
	rect7 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect7, 315, 135);
	gt_obj_set_size(rect7, 80, 35);
	gt_obj_set_opa(rect7, GT_OPA_50);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, AD120, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab8, 316, 201);
	gt_obj_set_size(lab8, 77, 34);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "P120");


	/** rect8 */
	rect8 = gt_rect_create(PressureCalibrate2);
	gt_obj_set_pos(rect8, 315, 200);
	gt_obj_set_size(rect8, 80, 35);
	gt_obj_set_opa(rect8, GT_OPA_50);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8, P120, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab20 */
	lab20 = gt_label_create(PressureCalibrate2);
	gt_obj_set_pos(lab20, 250, 70);
	gt_obj_set_size(lab20, 100, 35);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 24);
	gt_label_set_font_family_cn(lab20, 20);
	gt_label_set_font_family_en(lab20, 33);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab20, "16356");

	timer_main_ThirmSec =  _gt_timer_create(Timer_ThirmSec,300,NULL);

	return PressureCalibrate2;
}

