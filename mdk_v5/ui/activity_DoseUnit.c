#include "ui.h"


/** DoseUnit */
gt_obj_st * DoseUnit = NULL;
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
static gt_obj_st * radio6 = NULL;
static gt_obj_st * radio7 = NULL;
static gt_obj_st * radio8 = NULL;



static const char title[5][1][50]={
	"剂量单位",

	"Dose Rate Unit",

	"Unidad de Tasa de Dosis",

	"劑量單位",

	"Unidade de taxa de dose"
		
};


static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void btn1_0_cb(gt_event_st * e) {

	gt_obj_st * temp = gt_group_get_active_obj(group1,GT_TYPE_RADIO);   //获取组里哪个被选中了

	if(temp == radio1)
	{
		WeightMode.DS_Uint = D_ug_kg_min;
	}
	else if(temp == radio2)
	{
		WeightMode.DS_Uint = D_ug_kg_h;
	}
	else if(temp == radio3)
	{
		WeightMode.DS_Uint = D_ng_kg_min;
	}
	else if(temp == radio4)
	{
		WeightMode.DS_Uint = D_ng_kg_h;
	}
	else if(temp == radio5)
	{
		WeightMode.DS_Uint = D_mg_kg_min;
	}
	else if(temp == radio6)
	{
		WeightMode.DS_Uint = D_mg_kg_h;
	}
	else if(temp == radio7)
	{
		WeightMode.DS_Uint = D_g_kg_min;
	}
	else if(temp == radio8)
	{
		WeightMode.DS_Uint = D_g_kg_h;
	}
	else
	{
		;
	}

	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_DoseUnit(void)
{
	DoseUnit =  gt_obj_create(NULL);
	my_set_obj_title(DoseUnit,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(DoseUnit, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(DoseUnit);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** cbox1 */


	/** btn1 */
	btn1 = gt_btn_create(DoseUnit);
	gt_obj_set_pos(btn1, 383, 278);
	gt_obj_set_size(btn1, 97, 42);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** group1 */
	group1 = gt_group_create(DoseUnit);
	gt_obj_set_pos(group1, 142, 261);
	gt_obj_set_size(group1, 2, 2);


	/** radio1 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 75, 70);
	gt_obj_set_size(radio1, 175, 35);
	gt_radio_set_font_color(radio1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio1, 24);
	gt_radio_set_font_family_en(radio1, 33);
	gt_radio_set_text(radio1, "ug/kg/min");
	gt_radio_set_font_point_offset(radio1, 10, 0);


	/** radio2 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 290, 70);
	gt_obj_set_size(radio2, 175, 35);
	gt_radio_set_font_color(radio2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio2, 24);
	gt_radio_set_font_family_en(radio2, 33);
	gt_radio_set_text(radio2, "ug/kg/h");
	gt_radio_set_font_point_offset(radio2,10, 0);


	/** radio3 */
	radio3 = gt_radio_create(group1);
	gt_obj_set_pos(radio3, 75, 120);
	gt_obj_set_size(radio3, 175, 35);
	gt_radio_set_font_color(radio3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio3, 24);
	gt_radio_set_font_family_en(radio3, 33);
	gt_radio_set_text(radio3, "ng/kg/min");
	gt_radio_set_font_point_offset(radio3, 10, 0);


	/** radio4 */
	radio4 = gt_radio_create(group1);
	gt_obj_set_pos(radio4, 290, 120);
	gt_obj_set_size(radio4, 175, 35);
	gt_radio_set_font_color(radio4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio4, 24);
	gt_radio_set_font_family_en(radio4, 33);
	gt_radio_set_text(radio4, "ng/kg/h");
	gt_radio_set_font_point_offset(radio4, 10, 0);


	/** radio5 */
	radio5 = gt_radio_create(group1);
	gt_obj_set_pos(radio5, 75, 170);
	gt_obj_set_size(radio5, 175, 35);
	gt_radio_set_font_color(radio5, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio5, 24);
	gt_radio_set_font_family_en(radio5, 33);
	gt_radio_set_text(radio5, "mg/kg/min");
	gt_radio_set_font_point_offset(radio5, 10, 0);


	/** radio6 */
	radio6 = gt_radio_create(group1);
	gt_obj_set_pos(radio6, 290, 170);
	gt_obj_set_size(radio6, 175, 35);
	gt_radio_set_font_color(radio6, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio6, 24);
	gt_radio_set_font_family_en(radio6, 33);
	gt_radio_set_text(radio6, "mg/kg/h");
	gt_radio_set_font_point_offset(radio6, 10, 0);

	/** radio7 */
	radio7 = gt_radio_create(group1);
	gt_obj_set_pos(radio7, 75, 220);
	gt_obj_set_size(radio7, 175, 35);
	gt_radio_set_font_color(radio7, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio7, 24);
	gt_radio_set_font_family_en(radio7, 33);
	gt_radio_set_text(radio7, "g/kg/min");
	gt_radio_set_font_point_offset(radio7, 10, 0);

	/** radio8 */
	radio8 = gt_radio_create(group1);
	gt_obj_set_pos(radio8, 290, 220);
	gt_obj_set_size(radio8, 175, 35);
	gt_radio_set_font_color(radio8, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio8, 24);
	gt_radio_set_font_family_en(radio8, 33);
	gt_radio_set_text(radio8, "g/kg/h");
	gt_radio_set_font_point_offset(radio8, 10, 0);


	if(WeightMode.DS_Uint == D_ug_kg_h)
	{
		gt_radio_set_selected(radio2);
	}
	else if(WeightMode.DS_Uint == D_ug_kg_min)
	{
		gt_radio_set_selected(radio1);
	}
	else if(WeightMode.DS_Uint == D_ng_kg_h)
	{
		gt_radio_set_selected(radio4);
	}
	else if(WeightMode.DS_Uint == D_ng_kg_min)
	{
		gt_radio_set_selected(radio3);
	}
	else if(WeightMode.DS_Uint == D_mg_kg_h)
	{
		gt_radio_set_selected(radio6);
	}
	else if(WeightMode.DS_Uint == D_mg_kg_min)
	{
		gt_radio_set_selected(radio5);
	}
	else if(WeightMode.DS_Uint == D_g_kg_min)
	{
		gt_radio_set_selected(radio7);
	}
	else if(WeightMode.DS_Uint == D_g_kg_h)
	{
		gt_radio_set_selected(radio8);
	}
	else
	{
		;
	}

	return DoseUnit;
}

