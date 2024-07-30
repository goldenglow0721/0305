#include "ui.h"


/** Purge */
gt_obj_st * Purge = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
//static gt_obj_st * lastScreen = NULL;


static const char title[5][3][50]={
	"排气",
	"排气速度",
	"请断开泵与动物的连接！",

	"Purge",
	"Purge Rate",
	"Please disconnect the pump from the animal!",

	"Purga",
	"Tasa de Purga",
	"Desconecte la bomba del animal!"
	
	"排氣",
	"排氣速度",
	"請斷開泵與動物的連接！",

	"Purga",
	"Taxa de Purga",
	"Por favor, desconecte a bomba do animal!"
		
};


static void back(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	lab3 = NULL;

	gt_disp_stack_go_back(1);
}


static void EnterPurgeRun(gt_event_st * e) {
	//排气运行
	gt_disp_stack_load_scr_anim(GT_SCR_ID_86, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
	
}

static void ChangeRate(gt_event_st * e) {
	keyboardf.data = &exhaustMode.speed;
	
	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.id=16;
	limit.lowerlimit=0.10;
	limit.toplimit=SystemMaintain.MaxSpeed;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 16)  //修改完时间出来的
	{
		sprintf(buffer,"%.2f",exhaustMode.speed);
		gt_label_set_text(lab3, buffer);
	}
		
}



gt_obj_st * gt_init_Purge(void)
{
	
	Purge =  gt_obj_create(NULL);
	my_set_obj_title(Purge,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(Purge, gt_color_hex(0x000000));
	char buffer[50];
	gt_obj_add_event_cb(Purge,EventUpdata,MY_EVENT_UPDATA,NULL);
	not_first_start_write_history_info(EA_Into,Ev_EnterExhaust,NULL);
	
	

	/** img1 */
	img1 = gt_img_create(Purge);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn1 */
	btn1 = gt_btn_create(Purge);
	gt_obj_set_pos(btn1, 175, 170);
	gt_obj_set_size(btn1, 105, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][0]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, EnterPurgeRun, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(Purge);
	gt_obj_set_pos(lab2, 50, 90);
	gt_obj_set_size(lab2, 125, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(Purge);
	gt_obj_set_pos(lab3, 187, 90);
	gt_obj_set_size(lab3, 100, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",exhaustMode.speed);
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	lab4 = gt_label_create(Purge);
	gt_obj_set_pos(lab4, 310, 90);
	gt_obj_set_size(lab4, 110, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab4, "mL/h");


	/** rect2 */
	rect2 = gt_rect_create(Purge);
	gt_obj_set_pos(rect2, 50, 90);
	gt_obj_set_size(rect2, 125, 50);
	gt_obj_set_opa(rect2, GT_OPA_55);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, ChangeRate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** rect3 */
	rect3 = gt_rect_create(Purge);
	gt_obj_set_pos(rect3, 175, 90);
	gt_obj_set_size(rect3, 125, 50);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, ChangeRate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** rect4 */
	rect4 = gt_rect_create(Purge);
	gt_obj_set_pos(rect4, 300, 90);
	gt_obj_set_size(rect4, 127, 50);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, ChangeRate, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** lab5 */
	lab5 = gt_label_create(Purge);
	gt_obj_set_pos(lab5, 65, 200);
	gt_obj_set_size(lab5, 341, 100);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	
	gt_label_set_text(lab5, title[SystemSetting.langue][2]);
	
	


	return Purge;
}

