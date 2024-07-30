#include "ui.h"


static const char title[5][6][50]={
	"夜间模式",
	"开始时间",
	"结束时间",
	"音量",
	"亮度",
	"  开关",


	"Night Mode",
	"",
	"",
	"",
	"",
	"",

	"Modo Nocturno",
	"",
	"",
	"",
	"",
	"",

	"夜間模式",
	"",
	"",
	"",
	"",
	"",

	"Modo noturno",
	"",
	"",
	"",
	"",
	""
		
};







/** NightSetting */
gt_obj_st * NightSetting = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * cbox1 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * rect11 = NULL;
static gt_obj_st * rect12 = NULL;
static gt_obj_st * btn1 = NULL;

static TIME sg_begintime;
static TIME sg_endtime;

static void back(gt_event_st * e) {
	//系统设定page2
	gt_disp_stack_load_scr_anim(GT_SCR_ID_31, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void Start_Time(gt_event_st * e) {

	strcpy(keyboardt.title,"开始时间");
	keyboardt.time = &sg_begintime; 
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_82, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}


static void End_Time(gt_event_st * e) {
	
	strcpy(keyboardt.title,"结束时间");
	keyboardt.time = &sg_endtime; 

	gt_disp_stack_load_scr_anim(GT_SCR_ID_82, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


static void Confirm(gt_event_st * e) {
	SystemSetting.NightMode.begintime = sg_begintime;
	SystemSetting.NightMode.overtime = sg_endtime;
	
	WriteSystemSettingMessageToFlash();
	//系统设定page2
	gt_disp_stack_load_scr_anim(GT_SCR_ID_31, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


static void openflag(gt_event_st * e) {

	if(SystemSetting.NightMode.nightmodeflag == true)
		SystemSetting.NightMode.nightmodeflag = false;
	else
		SystemSetting.NightMode.nightmodeflag = true;
	
}

gt_obj_st * gt_init_NightSetting(void)
{
	char buff[50];
	NightSetting =  gt_obj_create(NULL);
	my_set_obj_title(NightSetting,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(NightSetting, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(NightSetting);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab2, 55, 115);
	gt_obj_set_size(lab2, 130, 40);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab3, 185, 115);
	gt_obj_set_size(lab3, 120, 40);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%02d:%02d:%02d",sg_begintime.hour,sg_begintime.min,sg_begintime.sec);
	gt_label_set_text(lab3, buff);


	/** lab4 */
	lab4 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab4, 305, 115);
	gt_obj_set_size(lab4, 100, 40);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "h:m:s");


	/** lab5 */
	lab5 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab5, 55, 170);
	gt_obj_set_size(lab5, 130, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5,title[SystemSetting.langue][2]);


	/** lab6 */
	lab6 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab6, 185, 170);
	gt_obj_set_size(lab6, 120, 40);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%02d:%02d:%02d",sg_endtime.hour,sg_endtime.min,sg_endtime.sec);
	gt_label_set_text(lab6, buff);


	/** lab7 */
	lab7 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab7, 305, 170);
	gt_obj_set_size(lab7, 100, 40);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "h:m:s");


	/** lab8 */
	lab8 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab8, 55, 225);
	gt_obj_set_size(lab8, 100, 40);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, title[SystemSetting.langue][3]);


	/** lab9 */
	lab9 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab9, 155, 225);
	gt_obj_set_size(lab9, 60, 40);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",SystemSetting.Volume);
	gt_label_set_text(lab9,buff);


	/** lab10 */
	lab10 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab10, 215, 225);
	gt_obj_set_size(lab10, 100, 40);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, title[SystemSetting.langue][4]);


	/** lab11 */
	lab11 = gt_label_create(NightSetting);
	gt_obj_set_pos(lab11, 315, 225);
	gt_obj_set_size(lab11, 60, 40);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",SystemSetting.Light);
	gt_label_set_text(lab11, buff);


	/** rect2 */
	rect2 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect2, 55, 60);
	gt_obj_set_size(rect2, 350, 40);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);


	/** cbox1 */
	cbox1 = gt_checkbox_create(NightSetting);
	gt_obj_set_pos(cbox1, 65, 63);
	gt_obj_set_size(cbox1, 350, 40);
	gt_checkbox_set_font_color(cbox1, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox1, 24);
	gt_checkbox_set_font_family_cn(cbox1, 20);
	gt_checkbox_set_font_family_en(cbox1, 33);
	gt_checkbox_set_text(cbox1, title[SystemSetting.langue][5]);
	gt_checkbox_set_font_point_offset(cbox1, 60, 0);
	gt_obj_add_event_cb(cbox1, openflag, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	if(SystemSetting.NightMode.nightmodeflag == true)
		gt_obj_set_state(cbox1, 1);
	else
		gt_obj_set_state(cbox1, 0);

	/** rect3 */
	rect3 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect3, 55, 115);
	gt_obj_set_size(rect3, 130, 40);
	gt_obj_set_opa(rect3, GT_OPA_55);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, Start_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect4, 185, 115);
	gt_obj_set_size(rect4, 120, 40);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, Start_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	rect5 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect5, 305, 115);
	gt_obj_set_size(rect5, 100, 40);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, Start_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect6 */
	rect6 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect6, 55, 170);
	gt_obj_set_size(rect6, 130, 40);
	gt_obj_set_opa(rect6, GT_OPA_55);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);
	gt_obj_add_event_cb(rect6, End_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect7 */
	rect7 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect7, 185, 170);
	gt_obj_set_size(rect7, 120, 40);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, End_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect8 */
	rect8 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect8, 305, 170);
	gt_obj_set_size(rect8, 100, 40);
	gt_obj_set_opa(rect8, GT_OPA_41);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect8, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8, End_Time, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect9 */
	rect9 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect9, 55, 225);
	gt_obj_set_size(rect9, 100, 40);
	gt_obj_set_opa(rect9, GT_OPA_55);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect9, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 4);
	

	/** rect10 */
	rect10 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect10, 155, 225);
	gt_obj_set_size(rect10, 60, 40);
	gt_obj_set_opa(rect10, GT_OPA_41);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect10, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 0);
	

	/** rect11 */
	rect11 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect11, 215, 225);
	gt_obj_set_size(rect11, 100, 40);
	gt_obj_set_opa(rect11, GT_OPA_55);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect11, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 4);
	

	/** rect12 */
	rect12 = gt_rect_create(NightSetting);
	gt_obj_set_pos(rect12, 315, 225);
	gt_obj_set_size(rect12, 60, 40);
	gt_obj_set_opa(rect12, GT_OPA_41);
	gt_rect_set_radius(rect12, 0);
	gt_rect_set_bg_color(rect12, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect12, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect12, 1);
	gt_rect_set_border(rect12, 0);
	

	/** btn1 */
	btn1 = gt_btn_create(NightSetting);
	gt_obj_set_pos(btn1, 380, 260);
	gt_obj_set_size(btn1, 100, 60);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return NightSetting;
}

