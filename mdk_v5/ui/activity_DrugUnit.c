#include "ui.h"


/** DrugUnit */
gt_obj_st * DrugUnit = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * radio4 = NULL;
static gt_obj_st * radio1 = NULL;
static gt_obj_st * radio2 = NULL;
static gt_obj_st * radio3 = NULL;



static const char title[5][1][50]={
	"药量单位",

	"Dose Unit",

	"Unidad de Dosis",

	"藥量單位",

	"Unidade de dose"
		
};


static void back(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Confirm(gt_event_st * e) {

	gt_obj_st * temp = gt_group_get_active_obj(group1,GT_TYPE_RADIO);   //获取组里哪个被选中了

	if(temp == radio1)
	{
		WeightMode.Med_Uint = M_ug;
	}
	else if(temp == radio2)
	{
		WeightMode.Med_Uint = M_g;
	}
	else if(temp == radio3)
	{
		WeightMode.Med_Uint = M_ng;
	}
	else if(temp == radio4)
	{
		WeightMode.Med_Uint = M_mg;
	}
	else
	{
		;
	}

	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_DrugUnit(void)
{
	DrugUnit =  gt_obj_create(NULL);
	my_set_obj_title(DrugUnit,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(DrugUnit, gt_color_hex(0x000000));
	 
	/** img1 */
	img1 = gt_img_create(DrugUnit);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** btn1 */
	btn1 = gt_btn_create(DrugUnit);
	gt_obj_set_pos(btn1, 383, 278);
	gt_obj_set_size(btn1, 97, 42);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** group1 */
	group1 = gt_group_create(DrugUnit);
	gt_obj_set_pos(group1, 201, 251);
	gt_obj_set_size(group1, 2, 2);


	/** radio4 */
	radio4 = gt_radio_create(group1);
	gt_obj_set_pos(radio4, 290, 100);
	gt_obj_set_size(radio4, 118, 46);
	gt_radio_set_font_color(radio4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio4, 24);
	gt_radio_set_font_family_en(radio4, 33);
	gt_radio_set_text(radio4, "mg");
	gt_radio_set_font_point_offset(radio4, 10, 0);


	/** radio1 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 140, 100);
	gt_obj_set_size(radio1, 118, 46);
	gt_radio_set_font_color(radio1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio1, 24);
	gt_radio_set_font_family_en(radio1, 33);
	gt_radio_set_text(radio1, "ug");
	gt_radio_set_font_point_offset(radio1, 10, 0);


	/** radio2 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 140, 180);
	gt_obj_set_size(radio2, 118, 46);
	gt_radio_set_font_color(radio2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio2, 24);
	gt_radio_set_font_family_en(radio2, 33);
	gt_radio_set_text(radio2, "g");
	gt_radio_set_font_point_offset(radio2, 10, 0);


	/** radio3 */
	radio3 = gt_radio_create(group1);
	gt_obj_set_pos(radio3, 290, 180);
	gt_obj_set_size(radio3, 118, 46);
	gt_radio_set_font_color(radio3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio3, 24);
	gt_radio_set_font_family_en(radio3, 33);
	gt_radio_set_text(radio3, "ng");
	gt_radio_set_font_point_offset(radio3, 10, 0);


	if(WeightMode.Med_Uint == M_ug)
	{
		gt_radio_set_selected(radio1);
	}
	else if(WeightMode.Med_Uint == M_mg)
	{
		gt_radio_set_selected(radio4);
	}
	else if(WeightMode.Med_Uint == M_g)
	{
		gt_radio_set_selected(radio2);
	}
	else if(WeightMode.Med_Uint == M_ng)
	{
		gt_radio_set_selected(radio3);
	}
	else
	{
		;
	}	
	

	return DrugUnit;
}

