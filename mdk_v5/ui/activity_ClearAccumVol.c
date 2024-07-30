#include "ui.h"
#include "headbar_view.h"

static const char title[5][4][50]={
	"清除累计量",
	"累计量",
	"清除当前累计量",
	"主菜单",

	"Total Volume",
	"Total Volume",
	"Cleaning",
	"Main Menu",

	"Volumen Total",
	"Volumen total",
	"Limpieza",
	"Menú Principal",

	"清除累計量",
	"累計量",
	"清除當前累計量",
	"主菜單",

	"Volume Total",
	"Volume total",
	"Limpeza",
	"Menu principal"
		
};



/** ClearAccumVol */
gt_obj_st * ClearAccumVol = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;

static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][3]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void btn1_0_cb(gt_event_st * e) {
	char buffer[30];

	ClearNowcumulant();
	sprintf(buffer,"%.2f",GetNowcumulant());
	gt_label_set_text(lab3, buffer);
}

gt_obj_st * gt_init_ClearAccumVol(void)
{
	ClearAccumVol =  gt_obj_create(NULL);
	my_set_obj_title(ClearAccumVol,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(ClearAccumVol, gt_color_hex(0x000000));


	char buffer[50];

	/** img1 */
	img1 = gt_img_create(ClearAccumVol);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(ClearAccumVol);
	gt_obj_set_pos(lab2, 85, 137);
	gt_obj_set_size(lab2, 160, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** rect2 */
	rect2 = gt_rect_create(ClearAccumVol);
	gt_obj_set_pos(rect2, 10, 137);
	gt_obj_set_size(rect2, 460, 60);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);


	/** btn1 */
	btn1 = gt_btn_create(ClearAccumVol);
	gt_obj_set_pos(btn1, 256, 280);
	gt_obj_set_size(btn1, 224, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab3 */
	lab3 = gt_label_create(ClearAccumVol);
	gt_obj_set_pos(lab3, 275, 137);
	gt_obj_set_size(lab3, 130, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",GetNowcumulant());
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	lab4 = gt_label_create(ClearAccumVol);
	gt_obj_set_pos(lab4, 245, 137);
	gt_obj_set_size(lab4, 30, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, ":");


	return ClearAccumVol;
}

