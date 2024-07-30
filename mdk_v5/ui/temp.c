#include "ui.h"
#include "up.h"
#include "headbar_view.h"

/** ModeSelect_cp */
gt_obj_st * ModeSelect_cp = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect7 = NULL;

/** SpeedMode_RectEvent */
static void rect1_0_cb(gt_event_st * e) {
	if(JudgedYesNoAlarm(ALARM_HYPERACOUSTIC))
	{
		ClearAlarm(ALARM_HYPERACOUSTIC);
	}
	else
	{
		AddAlarm(ALARM_HYPERACOUSTIC);
		printf("add\n");
	}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}

/** TimeMode_RectEvent */
static void rect2_0_cb(gt_event_st * e) {
	if(JudgedYesNoAlarm(ALARM_INFUSION_OFF))
	{
		ClearAlarm(ALARM_INFUSION_OFF);
	}
	else
	{
		AddAlarm(ALARM_INFUSION_OFF);
		printf("add\n");
	}
}

/** BWMode_RectEvent */
static void rect3_0_cb(gt_event_st                                                                                                                                                                                                                                                                                                                                                               * e) {
	if(JudgedYesNoAlarm(ALARM_FINISH_KVO))
	{
		ClearAlarm(ALARM_FINISH_KVO);
	}
	else
	{
		AddAlarm(ALARM_FINISH_KVO);
		printf("add\n");
	}
}

/** SequentialMode_RectEvent */
static void rect4_0_cb(gt_event_st * e) {
	if(JudgedYesNoAlarm(ALARM_NO_BATTETY))
	{
		ClearAlarm(ALARM_NO_BATTETY);
	}
	else
	{
		AddAlarm(ALARM_NO_BATTETY);
		printf("add\n");
	}
}

/** Drip_RectEvent */
static void rect5_0_cb(gt_event_st * e) {
	if(JudgedYesNoAlarm(ALARM_NET_POWER_OFF))
	{
		ClearAlarm(ALARM_NET_POWER_OFF);
	}
	else
	{
		AddAlarm(ALARM_NET_POWER_OFF);
		printf("add\n");
	}
}

/** DrugLibrary_RectEvent */
static void rect6_0_cb(gt_event_st * e) {
	if(JudgedYesNoAlarm(ALARM_NET_POWER_OFF))
	{
		ClearAlarm(ALARM_NET_POWER_OFF);
	}
	else
	{
		AddAlarm(ALARM_NET_POWER_OFF);
		printf("add\n");
	}
}

/** 返回 */
static void img1_0_cb(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_ModeSelect_cp(void)
{
	ModeSelect_cp =  gt_obj_create(NULL);
	//my_set_obj_title(ModeSelect_cp,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(ModeSelect_cp, gt_color_hex(0x000000));



	/** lab1 */
	lab1 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab1, 100, 57);
	gt_obj_set_size(lab1, 100, 35);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "速度模式");


	/** lab2 */
	lab2 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab2, 280, 57);
	gt_obj_set_size(lab2, 100, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "时间模式");


	/** lab3 */
	lab3 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab3, 100, 136);
	gt_obj_set_size(lab3, 100, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "体重模式");


	/** lab4 */
	lab4 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab4, 280, 136);
	gt_obj_set_size(lab4, 100, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "序列模式");


	/** lab5 */
	lab5 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab5, 100, 218);
	gt_obj_set_size(lab5, 100, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	(lab5, 5);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "滴数设置");


	/** lab6 */
	lab6 = gt_label_create(ModeSelect_cp);
	gt_obj_set_pos(lab6, 280, 218);
	gt_obj_set_size(lab6, 100, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	(lab6, 5);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "药物库");


	/** rect1 */
	/** 速度模式rect */
	rect1 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect1, 92, 50);
	gt_obj_set_size(rect1, 120, 50);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);
	gt_obj_add_event_cb(rect1, rect1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** rect2 */
	/** 时间模式rect */
	rect2 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect2, 270, 50);
	gt_obj_set_size(rect2, 120, 50);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, rect2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** rect3 */
	/** 体重模式rect */
	rect3 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect3, 92, 128);
	gt_obj_set_size(rect3, 120, 50);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, rect3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** rect4 */
	/** 序列模式rect */
	rect4 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect4, 270, 128);
	gt_obj_set_size(rect4, 120, 50);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, rect4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** rect5 */
	/** 滴速rect */
	rect5 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect5, 92, 211);
	gt_obj_set_size(rect5, 120, 50);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, rect5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** rect6 */
	/** 药物库-rect */
	rect6 = gt_rect_create(ModeSelect_cp);
	gt_obj_set_pos(rect6, 271, 211);
	gt_obj_set_size(rect6, 120, 50);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, rect6_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** img1 */
	/** ReturnIcon */
	img1 = gt_img_create(ModeSelect_cp);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_60x60_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return ModeSelect_cp;
}

