#include "ui.h"
#include "headbar_view.h"
/** screen_Maintenance_Normal_Five */
gt_obj_st * screen_Maintenance_Normal_Five = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * cbox1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;

static const char title[5][7][50]={
    "系统维护",
	"系统时间与日期",
	"设置",
	"系统语言",
	"中文简体",
	"恢复厂家设置",
	"主菜单",
	
    "Maintenance",
	"Date And Time",
	"Setting",
	"Language",
	"English",
	"Restore Factory Default",
	"Main Menu",

    "Mantenimiento",
	"",
	"",
	"",
	"Restaurar la Fábrica Predeterminada",
	"",
	"Menú Principal",
	

    "系統維護",
	"",
	"",
	"",
	"恢復廠家設置",
	"",
	"主菜單",

    "Manutenção",
	"",
	"",
	"",
	"Restaurar padrão de fábrica",
	"",
	"Menu principal"

};



static void DateAndTime(gt_event_st * e) {
	
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][6]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_59, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void language(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_58, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void img1_0_cb(gt_event_st * e) {
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_44, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_41, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void rect2_0_cb(gt_event_st * e) {
	
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_57, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
	
}


//static void ChangeAlarm(gt_event_st * e) {

//	if(SystemMaintain.Alarm)
//		SystemMaintain.Alarm = 0;
//	else
//		SystemMaintain.Alarm = 1;

//}



gt_obj_st * gt_init_Maintenance1_5(void)
{
	screen_Maintenance_Normal_Five =  gt_obj_create(NULL);
	my_set_obj_title(screen_Maintenance_Normal_Five,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(screen_Maintenance_Normal_Five, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(svg1, 416, 75);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	
	lab1 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab1, 406, 156);
	gt_obj_set_size(lab1, 69, 45);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "5/5");

	//system time and data
	lab2 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab2, 75,232);
	gt_obj_set_size(lab2, 200, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);

	//system language
	lab3 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab3, 75, 150);
	gt_obj_set_size(lab3, 200, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][3]);


	
	lab4 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab4, 275, 232);
	gt_obj_set_size(lab4, 125, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);

		
	lab5 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab5, 275, 150);
	gt_obj_set_size(lab5, 125, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][4]);

	lab6 = gt_label_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(lab6, 75, 66);
	gt_obj_set_size(lab6, 325, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][5]);
	gt_obj_add_event_cb(lab6, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	


	rect1 = gt_rect_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(rect1, 75, 66);
	gt_obj_set_size(rect1, 325, 60);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x778899));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 4);
	gt_obj_add_event_cb(rect1, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect2 */
	rect2 = gt_rect_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(rect2, 75, 232);
	gt_obj_set_size(rect2, 200, 60);
	gt_obj_set_opa(rect2, GT_OPA_53);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, DateAndTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect3 */
	rect3 = gt_rect_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(rect3, 275, 232);
	gt_obj_set_size(rect3, 125, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, DateAndTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect4 */
	rect4 = gt_rect_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(rect4, 75, 150);
	gt_obj_set_size(rect4, 200, 60);
	gt_obj_set_opa(rect4, GT_OPA_53);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, language, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect5 */
	rect5 = gt_rect_create(screen_Maintenance_Normal_Five);
	gt_obj_set_pos(rect5, 275, 150);
	gt_obj_set_size(rect5, 125, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, language, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	

	return screen_Maintenance_Normal_Five;
}

