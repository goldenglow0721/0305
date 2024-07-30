#include "ui.h"
#include "headbar_view.h"

/** Maintenance1 */
gt_obj_st * Maintenance1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect6 = NULL;


static const char title[5][5][50]={
	"系统维护",
	"最大速度",
	"精度校准",
	"压力校准",
	"主菜单",

	"Maintenance",
	"Max Rate",
	"IV Set Calibration",
	"Pressure Calibration",
	"Main Menu",
	
	"Mantenimiento",
	"Tasa máxima",
	"Calibración de IV Conjunto",
	"Calibración de Presión",
	"Menú Principal",
	
	"系統維護",
	"最大速度",
	"精度校準",
	"壓力校準",
	"主菜單",
	
	"Manutenção",
	"Taxa máxima",
	"Calibração de equipo",
	"Pressão de calibração",
	"Menu principal"
};


static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][4]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void ChangeMaxSpeed(gt_event_st * e) {

	keyboardf.data = &SystemMaintain.MaxSpeed;
	strcpy(keyboardf.title,title[SystemSetting.langue][0]);
	limit.toplimit = 2000.0;
	limit.lowerlimit = 0.01;
	keyboardf.id=19;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}



static void AccuracyCalibrate(gt_event_st * e) {

	brandchoice2_from = 1;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_88, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}



static void PressureCalibrate(gt_event_st * e) {

	brandchoice2_from = 2;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_88, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}



static void up(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_45, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}

static void down(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_42, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 19)  //修改完最大速度出来的
	{
		
		
		sprintf(buffer,"%.2f",SystemMaintain.MaxSpeed);
		gt_label_set_text(lab3, buffer);
		not_first_start_write_history_info(EA_Amend,Ev_MaxSpeed,buffer);
		WriteSystemMaintainMessageToFlash();
	}
}


gt_obj_st * gt_init_Maintenance1_1(void)
{
	char buffer[50];
	Maintenance1 =  gt_obj_create(NULL);
	my_set_obj_title(Maintenance1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(Maintenance1, gt_color_hex(0x000000));
	gt_obj_add_event_cb(Maintenance1,EventUpdata,MY_EVENT_UPDATA,NULL);
	 

	


	/** lab2 */
	lab2 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab2, 75, 68);
	gt_obj_set_size(lab2, 115, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);
	


	/** lab3 */
	lab3 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab3, 200, 68);
	gt_obj_set_size(lab3, 110, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",SystemMaintain.MaxSpeed);
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	lab4 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab4, 75, 150);
	gt_obj_set_size(lab4, 325, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);


	/** lab5 */
	lab5 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab5, 75, 233);
	gt_obj_set_size(lab5, 325, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** img1 */
	img1 = gt_img_create(Maintenance1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect2 */
	rect2 = gt_rect_create(Maintenance1);
	gt_obj_set_pos(rect2, 75, 68);
	gt_obj_set_size(rect2, 125, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, ChangeMaxSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect3 */
	rect3 = gt_rect_create(Maintenance1);
	gt_obj_set_pos(rect3, 200, 68);
	gt_obj_set_size(rect3, 120, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, ChangeMaxSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(Maintenance1);
	gt_obj_set_pos(rect4, 75, 150);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, AccuracyCalibrate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	rect5 = gt_rect_create(Maintenance1);
	gt_obj_set_pos(rect5, 75, 233);
	gt_obj_set_size(rect5, 325, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, PressureCalibrate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** svg1 */
	svg1 = gt_img_create(Maintenance1);
	gt_obj_set_pos(svg1, 416, 74);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(Maintenance1);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab8, 406, 157);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "1/5");


	/** lab7 */
	lab7 = gt_label_create(Maintenance1);
	gt_obj_set_pos(lab7, 320, 68);
	gt_obj_set_size(lab7, 80, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "ml/h");


	/** rect6 */
	rect6 = gt_rect_create(Maintenance1);
	gt_obj_set_pos(rect6, 320, 68);
	gt_obj_set_size(rect6, 80, 60);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, ChangeMaxSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return Maintenance1;
}

