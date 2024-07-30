#include "ui.h"


/** SystemDataSetting */
gt_obj_st * SystemDataSetting = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * inputNum1 = NULL;
static gt_obj_st * inputNum2 = NULL;
static gt_obj_st * inputNum3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * rect10 = NULL;


static TIME TIME_DATA;
static const char title[5][1][50]={
	"系统日期",

	"System Date",

	"Fecha",

	"系統日期",

	"Data do sistema"
		
};


//back
static void img1_0_cb(gt_event_st * e) {
	
	gt_disp_stack_go_back(1);
}

//ok
static void btn1_0_cb(gt_event_st * e) {
	calendar.year = TIME_DATA.year;
	calendar.mon = TIME_DATA.mon;
	calendar.day = TIME_DATA.day;
	gt_event_send(SystemDataTimeSetting,MY_EVENT_UPDATA,"2");

	gt_disp_stack_go_back(1);
}

//修改年
static void rect2_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,"年");
	keyboardi.data = &TIME_DATA.year; 
	keyboardi.id=15;
	limit.toplimit = 2055;
	limit.lowerlimit = 2010;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}
//修改月
static void rect3_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,"月");
	keyboardi.data = &TIME_DATA.mon; 
	keyboardi.id=16;
	limit.toplimit = 12;
	limit.lowerlimit = 1;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}
//修改日
static void rect4_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,"日");
	keyboardi.data = &TIME_DATA.day; 
	keyboardi.id=17;
	limit.toplimit = 31;
	limit.lowerlimit = 1;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void rect5_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum1);
}

static void rect6_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum1);
}

static void rect7_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum2);
}

static void rect8_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum2);
}

static void rect9_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum3);
}

static void rect10_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum3);
}

static void EventUpdata(gt_event_st * e)
{
	
	if(atoi(e->param) == 15)  //修改完年出来的
	{
		gt_input_number_set_value(inputNum1, TIME_DATA.year);
	}
	if(atoi(e->param) == 16)  //修改完月出来的
	{
		gt_input_number_set_value(inputNum2, TIME_DATA.mon);
	}
	if(atoi(e->param) == 17)  //修改完日出来的
	{
		gt_input_number_set_value(inputNum3, TIME_DATA.day);
	}

}

gt_obj_st * gt_init_SystemDataSetting(void)
{
	SystemDataSetting =  gt_obj_create(NULL);
	my_set_obj_title(SystemDataSetting,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemDataSetting, gt_color_hex(0x000000));
	 
	gt_obj_add_event_cb(SystemDataSetting,EventUpdata,MY_EVENT_UPDATA,NULL);

	/** img1 */
	img1 = gt_img_create(SystemDataSetting);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);





	/** btn1 */
	btn1 = gt_btn_create(SystemDataSetting);
	gt_obj_set_pos(btn1, 376, 263);
	gt_obj_set_size(btn1, 100, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0xffffff));
	gt_btn_set_border_width(btn1, 1);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




	/** lab2 */
	lab2 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab2, 161, 140);
	gt_obj_set_size(lab2, 35, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "年");


	/** lab3 */
	lab3 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab3, 280, 140);
	gt_obj_set_size(lab3, 35, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "月");


	/** lab4 */
	lab4 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab4, 402, 140);
	gt_obj_set_size(lab4, 35, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "日");


	/** inputNum1 */
	inputNum1 = gt_input_number_create(SystemDataSetting);
	gt_obj_set_pos(inputNum1, 85, 140);
	gt_obj_set_size(inputNum1, 80, 35);
	gt_input_number_set_font_color(inputNum1, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum1, 24);
	gt_input_number_set_font_family_en(inputNum1, 33);
	gt_input_number_set_font_align(inputNum1, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum1, calendar.year);
	gt_input_number_set_step(inputNum1, 1);
	gt_input_number_set_min(inputNum1, 2010);
	gt_input_number_set_max(inputNum1, 2055);
	gt_input_number_set_fill_zero_front(inputNum1, false);
	gt_input_number_set_display_integer_length(inputNum1, 2);
	gt_input_number_set_display_decimal_length(inputNum1, 0);


	/** inputNum2 */
	inputNum2 = gt_input_number_create(SystemDataSetting);
	gt_obj_set_pos(inputNum2, 211, 140);
	gt_obj_set_size(inputNum2, 60, 35);
	gt_input_number_set_font_color(inputNum2, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum2, 24);
	gt_input_number_set_font_family_en(inputNum2, 33);
	gt_input_number_set_font_align(inputNum2, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum2, calendar.mon);
	gt_input_number_set_step(inputNum2, 1);
	gt_input_number_set_min(inputNum2, 1);
	gt_input_number_set_max(inputNum2, 12);
	gt_input_number_set_fill_zero_front(inputNum2, false);
	gt_input_number_set_display_integer_length(inputNum2, 2);
	gt_input_number_set_display_decimal_length(inputNum2, 0);


	/** inputNum3 */
	inputNum3 = gt_input_number_create(SystemDataSetting);
	gt_obj_set_pos(inputNum3, 334, 140);
	gt_obj_set_size(inputNum3, 60, 35);
	gt_input_number_set_font_color(inputNum3, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum3, 24);
	gt_input_number_set_font_family_en(inputNum3, 33);
	gt_input_number_set_font_align(inputNum3, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum3, calendar.day);
	gt_input_number_set_step(inputNum3, 1);
	gt_input_number_set_min(inputNum3, 1);
	gt_input_number_set_max(inputNum3, 31);
	gt_input_number_set_fill_zero_front(inputNum3, false);
	gt_input_number_set_display_integer_length(inputNum3, 2);
	gt_input_number_set_display_decimal_length(inputNum3, 0);


	/** rect2 */
	rect2 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect2, 96, 121);
	gt_obj_set_size(rect2, 60, 75);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	rect3 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect3, 216, 120);
	gt_obj_set_size(rect3, 60, 75);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, rect3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect4, 339, 120);
	gt_obj_set_size(rect4, 60, 75);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	lab5 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab5, 104, 84);
	gt_obj_set_size(lab5, 45, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "+");






	/** rect5 */
	rect5 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect5, 96, 86);
	gt_obj_set_size(rect5, 60, 35);
	gt_obj_set_opa(rect5, GT_OPA_55);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab6 */
	lab6 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab6, 103, 194);
	gt_obj_set_size(lab6, 45, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "-");


	/** rect6 */
	rect6 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect6, 96, 196);
	gt_obj_set_size(rect6, 60, 35);
	gt_obj_set_opa(rect6, GT_OPA_55);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, rect6_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	lab7 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab7, 224, 84);
	gt_obj_set_size(lab7, 45, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "+");


	/** lab8 */
	lab8 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab8, 224, 194);
	gt_obj_set_size(lab8, 45, 35);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "-");


	/** rect7 */
	rect7 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect7, 216, 85);
	gt_obj_set_size(rect7, 60, 35);
	gt_obj_set_opa(rect7, GT_OPA_55);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, rect7_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect8 */
	rect8 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect8, 216, 195);
	gt_obj_set_size(rect8, 60, 35);
	gt_obj_set_opa(rect8, GT_OPA_55);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8, rect8_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab9 */
	lab9 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab9, 347, 84);
	gt_obj_set_size(lab9, 45, 35);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "+");


	/** rect9 */
	rect9 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect9, 339, 85);
	gt_obj_set_size(rect9, 60, 35);
	gt_obj_set_opa(rect9, GT_OPA_55);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect9, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);
	gt_obj_add_event_cb(rect9, rect9_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab10 */
	lab10 = gt_label_create(SystemDataSetting);
	gt_obj_set_pos(lab10, 347, 194);
	gt_obj_set_size(lab10, 45, 35);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "-");


	/** rect10 */
	rect10 = gt_rect_create(SystemDataSetting);
	gt_obj_set_pos(rect10, 339, 195);
	gt_obj_set_size(rect10, 60, 35);
	gt_obj_set_opa(rect10, GT_OPA_55);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 0);
	gt_obj_add_event_cb(rect10, rect10_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return SystemDataSetting;
}

