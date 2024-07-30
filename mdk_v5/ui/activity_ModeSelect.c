#include "ui.h"
#include "headbar_view.h"

/** ModeSelect */
gt_obj_st * ModeSelect = NULL;
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
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * btn5 = NULL;
static gt_obj_st * btn6 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect7 = NULL;

static const char title[5][8][50]={
	"模式选择",
	"速度模式",
	"时间模式",
	"体重模式",
	"序列模式",
	"滴定模式",
	"药物库",
	"主菜单",

	"Select Mode",
	"Rate Mode",
	"Time Mode",
	"BW Mode",
	"Sequential Mode",
	"Drip Mode",
	"Drug Library ",
	"Main Menu",


	"Seleccione el Modo",
	"Modo de Velocidad",
	"Modo de Tiempo",
	"Modo de PC",
	"El Modo Secuencial",
	"Patrón de titulación",
	"Biblioteca de Drogas",
	"Menú Principal",

	"模式選擇",
	"速度模式",
	"時間模式",
	"體重模式",
	"序列模式",
	"滴定模式",
	"藥物庫",
	"主菜單",

	"Selecionar modo",
	"Modo taxa",
	"Modo Tempo",
	"Modo peso corporal",
	"Modo sequencial",
	"Modo de titulação",
	"Biblioteca de drogas",
	"Menu principal"

};









/** SpeedMode_RectEvent */
static void EnterSpeedMode(gt_event_st * e) {
	not_first_start_write_history_info(EA_Into,Ev_EntSpeed,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_6);

}

/** TimeMode_RectEvent */
static void EnterTimeMode(gt_event_st * e) {
	
	not_first_start_write_history_info(EA_Into,Ev_EntTime,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_7);
}

/** BWMode_RectEvent */
static void EnterBWMode(gt_event_st * e) {
	not_first_start_write_history_info(EA_Into,Ev_EntWeight,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_8);
}

/** SequentialMode_RectEvent */
static void EnterSquenceMode(gt_event_st * e) {
	not_first_start_write_history_info(EA_Into,Ev_EntSequential,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_9);
	
}

/** Drip_RectEvent */
static void EnterDripMode(gt_event_st * e) {
	not_first_start_write_history_info(EA_Into,Ev_EntDrip,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_10);
	
}

/** DrugLibrary_RectEvent */
static void EnterDrugLibrary(gt_event_st * e) {
	not_first_start_write_history_info(EA_Into,Ev_EntDruglib,NULL);
	gt_disp_stack_load_scr(GT_SCR_ID_16);
}

/** 返回 */
static void back(gt_event_st * e) {

	my_set_obj_title(ModeSelect,title[SystemSetting.langue][7]);

	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void KEY_EVENT(gt_event_st * e) {
	if(atoi(e->param) == 1) //up down
	{
		led_turn(ARM_YLED);
	}
	else if(atoi(e->param) == 2) //up longdown
	{
		BeepStart();
	}
	else if(atoi(e->param) == 3) //up up
	{
		BeepStop();
	}
	else if(atoi(e->param) == 4) //down down
	{
		led_turn(ARM_RLED);
	}
	else if(atoi(e->param) == 5) //power longdown
	{	
		led_turn(ARM_RLED);
	}
	else if(atoi(e->param) == 6) //power longdown
	{
		BeepStart();
	}
}


gt_obj_st * gt_init_ModeSelect(void)
{
	ModeSelect =  gt_obj_create(NULL);
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][0]);
	
	gt_screen_set_bgcolor(ModeSelect, gt_color_hex(0x000000));
	gt_obj_add_event_cb(ModeSelect,KEY_EVENT,MY_KEY_EVENT,NULL);
	#if 0 
	/** lab1 */
	lab1 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab1, 80, 65);
	gt_obj_set_size(lab1, 160, 65);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, title[SystemSetting.langue][1]);					//速度模式
	gt_obj_add_event_cb(lab1, EnterSpeedMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab2, 260, 65);
	gt_obj_set_size(lab2, 160, 65);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2,title[SystemSetting.langue][2]);						//时间模式
	gt_obj_add_event_cb(lab2, EnterTimeMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab3 */
	lab3 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab3, 80, 145);
	gt_obj_set_size(lab3, 160, 65);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][3]);					//体重模式
	gt_obj_add_event_cb(lab3, EnterBWMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab4 */
	lab4 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab4, 260, 145);
	gt_obj_set_size(lab4, 160, 65);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][4]);					//序列模式
	gt_obj_add_event_cb(lab4, EnterSquenceMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	lab5 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab5, 80, 225);
	gt_obj_set_size(lab5, 160, 65);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][5]);					//滴定模式
	gt_obj_add_event_cb(lab5, EnterDripMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab6 */
	lab6 = gt_label_create(ModeSelect);
	gt_obj_set_pos(lab6, 260, 225);
	gt_obj_set_size(lab6, 160, 65);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][6]);					//药物库
	gt_obj_add_event_cb(lab6, EnterDrugLibrary, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** rect1 */
	/** 速度模式rect */
	rect1 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect1, 80, 65);
	gt_obj_set_size(rect1, 160, 65);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 5);
	gt_obj_add_event_cb(rect1, EnterSpeedMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect2 */
	/** 时间模式rect */
	rect2 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect2, 260, 65);
	gt_obj_set_size(rect2, 160, 65);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 5);
	gt_obj_add_event_cb(rect2, EnterTimeMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	/** 体重模式rect */
	rect3 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect3, 80, 145);
	gt_obj_set_size(rect3, 160, 65);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 5);
	gt_obj_add_event_cb(rect3, EnterBWMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	/** 序列模式rect */
	rect4 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect4, 260, 145);
	gt_obj_set_size(rect4, 160, 65);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 5);
	gt_obj_add_event_cb(rect4, EnterSquenceMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	/** 滴速rect */
	rect5 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect5, 80, 225);
	gt_obj_set_size(rect5, 160, 65);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 5);
	gt_obj_add_event_cb(rect5, EnterDripMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect6 */
	/** 药物库-rect */
	rect6 = gt_rect_create(ModeSelect);
	gt_obj_set_pos(rect6, 260, 225);
	gt_obj_set_size(rect6, 160, 65);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 5);
	gt_obj_add_event_cb(rect6, EnterDrugLibrary, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	
	#endif

	/** btn1 */
	btn1 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn1, 80, 65);
	gt_obj_set_size(btn1, 160, 65);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][1]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1,4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, EnterSpeedMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn2 */
	btn2 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn2, 260, 65);
	gt_obj_set_size(btn2, 160, 65);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_family_en(btn2, 33);
	gt_btn_set_font_family_fl(btn2, 50);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn2,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2,4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, EnterTimeMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn3 */
	btn3 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn3, 80, 145);
	gt_obj_set_size(btn3, 160, 65);
	gt_btn_set_font_color(btn3, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn3, 24);
	gt_btn_set_font_family_cn(btn3, 20);
	gt_btn_set_font_family_en(btn3, 33);
	gt_btn_set_font_family_fl(btn3, 50);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn3, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn3,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn3,4);
	gt_btn_set_radius(btn3, 4);
	gt_obj_add_event_cb(btn3, EnterBWMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn4 */
	btn4 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn4, 260, 145);
	gt_obj_set_size(btn4, 160, 65);
	gt_btn_set_font_color(btn4, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn4, 24);
	gt_btn_set_font_family_cn(btn4, 20);
	gt_btn_set_font_family_en(btn4, 33);
	gt_btn_set_font_family_fl(btn4, 50);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn4, title[SystemSetting.langue][4]);
	gt_btn_set_color_background(btn4, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn4,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn4,4);
	gt_btn_set_radius(btn4, 4);
	gt_obj_add_event_cb(btn4, EnterSquenceMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn5 */
	btn5 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn5, 80, 225);
	gt_obj_set_size(btn5, 160, 65);
	gt_btn_set_font_color(btn5, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn5, 24);
	gt_btn_set_font_family_cn(btn5, 20);
	gt_btn_set_font_family_en(btn5, 33);
	gt_btn_set_font_family_fl(btn5, 50);
	gt_btn_set_font_align(btn5, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn5, title[SystemSetting.langue][5]);
	gt_btn_set_color_background(btn5, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn5, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn5,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn5,4);
	gt_btn_set_radius(btn5, 4);
	gt_obj_add_event_cb(btn5, EnterDripMode, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn6 */
	btn6 = gt_btn_create(ModeSelect);
	gt_obj_set_pos(btn6, 260, 225);
	gt_obj_set_size(btn6, 160, 65);
	gt_btn_set_font_color(btn6, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn6, 24);
	gt_btn_set_font_family_cn(btn6, 20);
	gt_btn_set_font_family_en(btn6, 33);
	gt_btn_set_font_family_fl(btn6, 50);
	gt_btn_set_font_align(btn6, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn6, title[SystemSetting.langue][6]);
	gt_btn_set_color_background(btn6, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn6, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn6,gt_color_hex(0x778899));
	gt_btn_set_border_width(btn6,4);
	gt_btn_set_radius(btn6, 4);
	gt_obj_add_event_cb(btn6, EnterDrugLibrary, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** img1 */
	/** ReturnIcon */
	img1 = gt_img_create(ModeSelect);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




	return ModeSelect;
}

