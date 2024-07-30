#include "ui.h"
#include "headbar_view.h"

/** SystemSetting2 */
gt_obj_st * SystemSetting2 = NULL;

static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;


static const char title[5][7][50]={
	"系统设定",
	"历史记录",
	"版本信息",
	"查看",
	"夜间模式",
	"设置",
	"主菜单",

	"System",
	"History Record",
	"Version",
	"Checking",
	"Night Mode",
	"Setting",
	"Main Menu",

	"Sistema",
	"Registro de Historia",
	"Versión",
	"Revisión",
	"Modo Nocturno",
	"Config.",
	"Menú Principal",

	"系統設定",
	"歷史記錄",
	"版本資訊",
	"查看",
	"夜間模式",
	"設置",
	"主菜單",

	"Sistema",
	"Registro Histórico",
	"Versão",
	"Verif.",
	"Modo noturno",
	"Config.",
	"Menu principal"

};

static void back(gt_event_st * e) {
	 my_set_obj_title(ModeSelect,title[SystemSetting.langue][6]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void UpPage(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void DownPage(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


static void ViewHistory(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_32, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void ViewVersion(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_33, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void nightmode(gt_event_st * e) {
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_34, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


gt_obj_st * gt_init_SystemSetting2(void)
{
	SystemSetting2 =  gt_obj_create(NULL);
	my_set_obj_title(SystemSetting2,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemSetting2, gt_color_hex(0x000000));
	 

	/** lab2 */
	lab2 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab2, 75, 65);
	gt_obj_set_size(lab2, 200, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2,title[SystemSetting.langue][1]);


	/** img1 */
	img1 = gt_img_create(SystemSetting2);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(SystemSetting2);
	gt_obj_set_pos(svg1, 413, 73);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(SystemSetting2);
	gt_obj_set_pos(svg2, 413, 210);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, DownPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab8, 407, 147);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "2/2");


	/** lab3 */
	lab3 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab3, 75, 145);
	gt_obj_set_size(lab3, 200, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][2]);


	/** rect2 */
	rect2 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 200, 60);
	gt_obj_set_opa(rect2, GT_OPA_53);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,ViewHistory,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab5 */
	lab5 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab5, 275, 65);
	gt_obj_set_size(lab5, 125, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** rect3 */
	rect3 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect3, 275, 65);
	gt_obj_set_size(rect3, 125, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 5);
	gt_obj_add_event_cb(rect3,ViewHistory,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect4 */
	rect4 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect4, 75, 145);
	gt_obj_set_size(rect4, 200, 60);
	gt_obj_set_opa(rect4, GT_OPA_53);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4,ViewVersion,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab6 */
	lab6 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab6, 275, 145);
	gt_obj_set_size(lab6, 125, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][3]);


	/** rect5 */
	rect5 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect5, 275, 145);
	gt_obj_set_size(rect5, 125, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5,ViewVersion,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab4 */
	lab4 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab4, 75, 225);
	gt_obj_set_size(lab4, 200, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][4]);

		/** rect6 */
	rect6 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect6, 75, 225);
	gt_obj_set_size(rect6, 200, 60);
	gt_obj_set_opa(rect6, GT_OPA_51);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, nightmode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** lab7 */
	lab7 = gt_label_create(SystemSetting2);
	gt_obj_set_pos(lab7, 275, 225);
	gt_obj_set_size(lab7, 125, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, title[SystemSetting.langue][5]);


	/** rect7 */
	rect7 = gt_rect_create(SystemSetting2);
	gt_obj_set_pos(rect7, 275, 225);
	gt_obj_set_size(rect7, 125, 60);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, nightmode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	return SystemSetting2;
}

