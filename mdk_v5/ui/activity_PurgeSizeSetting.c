#include "ui.h"


/** PurgeSizeSetting */
gt_obj_st * PurgeSizeSetting = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * radio1 = NULL;
static gt_obj_st * radio2 = NULL;
static gt_obj_st * radio3 = NULL;
static gt_obj_st * radio4 = NULL;
static gt_obj_st * radio5 = NULL;

uint16_t g_temp;


static const char title[5][1][50]={
	"气泡大小",

	"Bubble Size",

	"Tamaño de Burbuja",

	"氣泡大小",

	"Tamanho da bolha"
		
};


static void back(gt_event_st * e) {	
	gt_disp_stack_go_back(1);
}

static void Confirm(gt_event_st * e){
	char buffer[30];

	ParamSetting.BubbleSize = g_temp;
	WriteParamSettingMessageToFlash();
	sprintf(buffer,"%s",ParamSetting.BubbleSize);
	not_first_start_write_history_info(EA_Amend,Ev_SetBubbleSize,buffer);
	gt_disp_stack_go_back(1);
}



static void purgesizechange(gt_event_st * e){
	if(atoi(e->user_data) == 1)
	{
		g_temp = 50;
	}
	else if(atoi(e->user_data) == 2)
	{
		g_temp = 100;
	}
	else if(atoi(e->user_data) == 3)
	{
		g_temp = 250;
	}
	else if(atoi(e->user_data) == 4)
	{
		g_temp = 500;
	}
	else if(atoi(e->user_data) == 5)
	{
		g_temp = 800;
	}
	else
	{
		;
	}
}

#if 0
static void purgesizechange1(gt_event_st * e){
	g_temp = 50;
}

static void purgesizechange2(gt_event_st * e){
	g_temp = 100;
}

static void purgesizechange3(gt_event_st * e){
	g_temp = 250;
}

static void purgesizechange4(gt_event_st * e){
	g_temp = 500;
}

static void purgesizechange5(gt_event_st * e){
	g_temp = 800;
}
#endif



gt_obj_st * gt_init_PurgeSizeSetting(void)
{
	PurgeSizeSetting =  gt_obj_create(NULL);
	my_set_obj_title(PurgeSizeSetting,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PurgeSizeSetting, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(PurgeSizeSetting);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** group1 */
	group1 = gt_group_create(PurgeSizeSetting);
	gt_obj_set_pos(group1, 287, 216);
	gt_obj_set_size(group1, 2, 2);


	/** radio1 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 85, 80);
	gt_obj_set_size(radio1, 175, 46);
	gt_radio_set_font_color(radio1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio1, 24);
	gt_radio_set_font_family_en(radio1, 33);
	gt_radio_set_text(radio1, "50uL");
	gt_radio_set_font_point_offset(radio1, 10, 0);
	gt_obj_add_event_cb(radio1, purgesizechange, GT_EVENT_TYPE_INPUT_RELEASED, "1");

	/** radio2 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 290, 80);
	gt_obj_set_size(radio2, 173, 46);
	gt_radio_set_font_color(radio2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio2, 24);
	gt_radio_set_font_family_en(radio2, 33);
	gt_radio_set_text(radio2, "100uL");
	gt_radio_set_font_point_offset(radio2, 10, 0);
	gt_obj_add_event_cb(radio2, purgesizechange, GT_EVENT_TYPE_INPUT_RELEASED, "2");

	/** radio3 */
	radio3 = gt_radio_create(group1);
	gt_obj_set_pos(radio3, 85, 135);
	gt_obj_set_size(radio3, 175, 46);
	gt_radio_set_font_color(radio3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio3, 24);
	gt_radio_set_font_family_en(radio3, 33);
	gt_radio_set_text(radio3, "250uL");
	gt_radio_set_font_point_offset(radio3, 10, 0);
	gt_obj_add_event_cb(radio3, purgesizechange, GT_EVENT_TYPE_INPUT_RELEASED, "3");

	/** radio4 */
	radio4 = gt_radio_create(group1);
	gt_obj_set_pos(radio4, 290, 135);
	gt_obj_set_size(radio4, 175, 46);
	gt_radio_set_font_color(radio4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio4, 24);
	gt_radio_set_font_family_en(radio4, 33);
	gt_radio_set_text(radio4, "500uL");
	gt_radio_set_font_point_offset(radio4, 10, 0);
	gt_obj_add_event_cb(radio4, purgesizechange, GT_EVENT_TYPE_INPUT_RELEASED, "4");

	/** btn1 */
	btn1 = gt_btn_create(PurgeSizeSetting);
	gt_obj_set_pos(btn1, 383, 278);
	gt_obj_set_size(btn1, 97, 42);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


		/** radio5 */
	radio5 = gt_radio_create(group1);
	gt_obj_set_pos(radio5, 85, 190);
	gt_obj_set_size(radio5, 175, 46);
	gt_radio_set_font_color(radio5, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio5, 24);
	gt_radio_set_font_family_en(radio5, 33);
	gt_radio_set_text(radio5, "800uL");
	gt_radio_set_font_point_offset(radio5, 10, 0);
	gt_obj_add_event_cb(radio5, purgesizechange, GT_EVENT_TYPE_INPUT_RELEASED, "5");


	if(ParamSetting.BubbleSize == 50)
	{
		gt_radio_set_selected(radio1);
	}
	else if(ParamSetting.BubbleSize == 100)
	{
		gt_radio_set_selected(radio2);
	}
	else if(ParamSetting.BubbleSize == 250)
	{
		gt_radio_set_selected(radio3);
	}
	else if(ParamSetting.BubbleSize == 500)
	{
		gt_radio_set_selected(radio4);
	}
	else if(ParamSetting.BubbleSize == 800)
	{
		gt_radio_set_selected(radio5);
	}
	else
	{
		;
	}


	return PurgeSizeSetting;
}

