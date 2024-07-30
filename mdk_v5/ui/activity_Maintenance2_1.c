#include "ui.h"
#include "headbar_view.h"

/** Maintenance2 */
gt_obj_st * Maintenance2 = NULL;
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


//按键反馈没做、文本没改、回调函数没做


static const char title[5][6][50]={
	"系统维护",
	"最大速度",
	"精度校准",
	"压力校准",
	"系统自检",
	"主菜单",

	"Maintenance",
	"Max Rate",
	"IV Set Calibration",
	"Pressure Calibration",
	"System Check",
	"Main Menu",
	
	"Mantenimiento",
	"Tasa máxima",
	"Calibración de IV Conjunto",
	"Calibración de Presión",
	"Autochequeo",
	"Menú Principal",

	
	"系統維護",
	"最大速度",
	"精度校準",
	"壓力校準",
	"系統自檢",
	"主菜單",
	
	"Manutenção",
	"Taxa máxima",
	"Calibração de equipo",
	"Pressão de calibração",
	"Autoverificação",
	"Menu principal"
};

//back
static void back(gt_event_st * e) {
	
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][5]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

#if 0
static void ChangeMaxRate(gt_event_st * e) {

	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &SystemMaintain.MaxSpeed;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}
#endif
static void AccuracyCalibrate(gt_event_st * e) {


	brandchoice2_from = 3;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_88, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}


static void PressureCalibrate(gt_event_st * e) {
	
	brandchoice2_from = 4;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_88, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);


}

static void SystemCheck(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_60, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}


static void up(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_47, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void down(gt_event_st * e) {


	gt_disp_stack_load_scr_anim(GT_SCR_ID_47, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


gt_obj_st * gt_init_Maintenance2_1(void)
{
	char buffer[50];
	Maintenance2 =  gt_obj_create(NULL);
	my_set_obj_title(Maintenance2,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(Maintenance2, gt_color_hex(0x000000));
	 
	

	/** lab4 */
	lab4 = gt_label_create(Maintenance2);
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
	lab5 = gt_label_create(Maintenance2);
	gt_obj_set_pos(lab5, 75, 232);
	gt_obj_set_size(lab5, 325, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** img1 */
	img1 = gt_img_create(Maintenance2);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** rect4 */
	rect4 = gt_rect_create(Maintenance2);
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
	rect5 = gt_rect_create(Maintenance2);
	gt_obj_set_pos(rect5, 75, 232);
	gt_obj_set_size(rect5, 325, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, PressureCalibrate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	

	/** rect6 */
	rect6 = gt_rect_create(Maintenance2);
	gt_obj_set_pos(rect6, 75, 68);
	gt_obj_set_size(rect6, 325, 60);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0x778899));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);
	gt_obj_add_event_cb(rect6, SystemCheck, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	
	/** lab7 */
	lab7 = gt_label_create(Maintenance2);
	gt_obj_set_pos(lab7, 75, 68);
	gt_obj_set_size(lab7, 325, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, title[SystemSetting.langue][4]);
	gt_obj_add_event_cb(lab7, SystemCheck, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** svg1 */
	svg1 = gt_img_create(Maintenance2);
	gt_obj_set_pos(svg1, 416, 74);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(Maintenance2);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(Maintenance2);
	gt_obj_set_pos(lab8, 406, 157);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "1/2");





	return Maintenance2;
}

