#include "ui.h"


/** PressureUnit */
gt_obj_st * PressureUnit = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * cbox3 = NULL;
static gt_obj_st * cbox4 = NULL;
static gt_obj_st * cbox2 = NULL;
static gt_obj_st * cbox1 = NULL;


Pressure_Uint temp;

static const char title[5][1][50]={
	"压力单位",

	"Unit of Pressure",

	"Unidad de Presión",

	"壓力單位",

	"Unidade de pressão"
};


/*Back*/
static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
	
}


/*OK*/
static void btn1_0_cb(gt_event_st * e) {
	char buffer[30];
	ParamSetting.PressUint = temp;
	WriteParamSettingMessageToFlash();
	sprintf(buffer,"%s",GetPressUintString(ParamSetting.PressUint));
	not_first_start_write_history_info(EA_Amend,Ev_SetPressUnit,buffer);

	gt_disp_stack_go_back(1);
}

static void Select_bar(gt_event_st * e) {
	
	temp = P_bar;
}
static void Select_psi(gt_event_st * e) {
	
	temp = P_psi;
}
static void Select_kpa(gt_event_st * e) {
	
	temp = P_KPa;
}
static void Select_mmhg(gt_event_st * e) {
	
	temp = P_mmHg;
}

gt_obj_st * gt_init_PressureUnit(void)
{
	PressureUnit =  gt_obj_create(NULL);
	my_set_obj_title(PressureUnit,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PressureUnit, gt_color_hex(0x000000));
	 
	


	/** img1 */
	/** 压力单位--返回 */
	img1 = gt_img_create(PressureUnit);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn1 */
	/** 压力单位--确认 */
	btn1 = gt_btn_create(PressureUnit);
	gt_obj_set_pos(btn1, 383, 278);
	gt_obj_set_size(btn1, 97, 42);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** group1 */
	group1 = gt_group_create(PressureUnit);
	gt_obj_set_pos(group1, 63, 183);
	gt_obj_set_size(group1, 2, 2);
	gt_obj_set_opa(group1, GT_OPA_0);


	/** cbox3 */
	/** 单位选择--bar */
	cbox3 = gt_radio_create(group1);
	gt_obj_set_pos(cbox3, 100, 200);
	gt_obj_set_size(cbox3, 150, 50);
	gt_radio_set_font_color(cbox3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(cbox3, 24);
	gt_radio_set_font_family_en(cbox3, 33);
	gt_radio_set_text(cbox3, "bar");
	gt_radio_set_font_point_offset(cbox3, 3, 0);
	gt_obj_add_event_cb(cbox3, Select_bar, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** cbox4 */
	/** 单位选择--psi */
	cbox4 = gt_radio_create(group1);
	gt_obj_set_pos(cbox4, 280, 200);
	gt_obj_set_size(cbox4, 150, 50);
	gt_radio_set_font_color(cbox4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(cbox4, 24);
	gt_radio_set_font_family_en(cbox4, 33);
	gt_radio_set_text(cbox4, "psi");
	gt_radio_set_font_point_offset(cbox4, 3, 0);
	gt_obj_add_event_cb(cbox4, Select_psi, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** cbox2 */
	/** 单位选择--kPa */
	cbox2 = gt_radio_create(group1);
	gt_obj_set_pos(cbox2, 280, 100);
	gt_obj_set_size(cbox2, 150, 50);
	gt_radio_set_font_color(cbox2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(cbox2, 24);
	gt_radio_set_font_family_en(cbox2, 33);
	gt_radio_set_text(cbox2, "kPa");
	gt_radio_set_font_point_offset(cbox2, 3, 0);
	gt_obj_add_event_cb(cbox2, Select_kpa, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** cbox1 */
	/** 单位选择--mmHg */
	cbox1 = gt_radio_create(group1);
	gt_obj_set_pos(cbox1, 100, 100);
	gt_obj_set_size(cbox1, 150, 50);
	gt_radio_set_font_color(cbox1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(cbox1, 24);
	gt_radio_set_font_family_en(cbox1, 33);
	gt_radio_set_text(cbox1, "mmHg");
	gt_radio_set_font_point_offset(cbox1, 3, 0);
	gt_obj_add_event_cb(cbox1, Select_mmhg, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	if(ParamSetting.PressUint == P_KPa)
		gt_radio_set_selected(cbox2);
	else if(ParamSetting.PressUint == P_mmHg)
		gt_radio_set_selected(cbox1);
	else if(ParamSetting.PressUint == P_psi)
		gt_radio_set_selected(cbox4);
	else if(ParamSetting.PressUint == P_bar)
		gt_radio_set_selected(cbox3);
	
	return PressureUnit;
}

