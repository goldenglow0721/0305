#include "ui.h"

static const char title[5][3][50]={
	"压力校准",
	"校准",
	"请将泵与压力表连接好！",

	"Pressure Calibration",
	"",
	"",

	"Calibración de Presión",
	"",
	"",

	"壓力校準",
	"",
	"",

	"Pressão de calibração",
	"",
	""
		
};
/** PressureCalibrate1 */
gt_obj_st * PressureCalibrate1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab8 = NULL;

static void back(gt_event_st * e) {
	
	gt_disp_stack_go_back(2);
}

static void Confirm(gt_event_st * e) {
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_55, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_PressureCalibrate1(void)
{
	PressureCalibrate1 =  gt_obj_create(NULL);
	my_set_obj_title(PressureCalibrate1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PressureCalibrate1, gt_color_hex(0x000000));
	 


	/** img1 */
	img1 = gt_img_create(PressureCalibrate1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn1 */
	btn1 = gt_btn_create(PressureCalibrate1);
	gt_obj_set_pos(btn1, 367, 274);
	gt_obj_set_size(btn1, 88, 46);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][1]);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(PressureCalibrate1);
	gt_obj_set_pos(lab8, 86, 140);
	gt_obj_set_size(lab8, 321, 38);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, title[SystemSetting.langue][2]);


	return PressureCalibrate1;
}

