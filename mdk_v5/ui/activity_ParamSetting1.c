#include "ui.h"
#include "up.h"
#include "headbar_view.h"

extern int BlevelData[15];

/** ParamSetting1 */
gt_obj_st * ParamSetting1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;

static const char title[5][6][50]={
	"输注设定",
	"输液器选择",
	"设置",
	"阻塞压力",
	"压力单位",
	"主菜单",
	
	"Infusion Setting",
	"Select IV Set Brand",
	"Setting",
	"Occlusion Pressure",
	"Unit of Pressure",
	"Main Menu",

	"Configuración de Infusión",
	"Seleccionar IV Set Marca",
	"Config.",
	"Presión de Oclusión",
	"Unidad de Presión",
	"Menú Principal",

	"輸注設定",
	"輸液器選擇",
	"設置",
	"阻塞壓力",
	"壓力單位",
	"主菜單",

	"Configuração de Infusão",
	"Selecionar marca de equipo",
	"Config.",
	"Pressão de Oclusão",
	"Unidade de pressão",
	"Menu principal"
};






static void Back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][5]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void BrandChange(gt_event_st * e) {

	gt_disp_stack_load_scr(GT_SCR_ID_87);

}

static void BlockPressure(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_24, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}




static void PressureUnitChange(gt_event_st * e) {
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_25, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
	
}


/** 上一页 */
static void UpPage(gt_event_st * e) {

	gt_disp_stack_load_scr(GT_SCR_ID_23);

}

/** 下一页 */
static void DownPage(gt_event_st * e) {

	gt_disp_stack_load_scr(GT_SCR_ID_21);

}


gt_obj_st * gt_init_ParamSetting1(void)
{
	char temp[20];
	ParamSetting1 =  gt_obj_create(NULL);
	my_set_obj_title(ParamSetting1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(ParamSetting1, gt_color_hex(0x000000));

	my_set_obj_title(ParamSetting1,title[SystemSetting.langue][0]);
	
	printf("Enter ParamSetting1\n");

	#if 0
	printf("blocklevel=%d\n",ParamSetting.BlockLevel);
	printf("blockunit=%d\n",ParamSetting.PressUint);
	gt_event_send(ParamSetting1,GT_EVENT_UPDATA,"1");
	#endif


	


	/** lab2 */
	lab2 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab2, 85, 65);
	gt_obj_set_size(lab2, 220, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab3, 310, 65);
	gt_obj_set_size(lab3, 85, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][2]);


	/** lab4 */ 
	lab4 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab4, 85, 145);
	gt_obj_set_size(lab4, 220, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][3]);


	/** lab5 */
	lab5 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab5, 85, 225);
	gt_obj_set_size(lab5, 220, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][4]);


	/** lab6 */
	lab6 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab6, 310, 145);
	gt_obj_set_size(lab6, 85, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	sprintf(temp,"%.1f",PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	
	gt_label_set_text(lab6, temp);


	/** lab7 */
	lab7 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab7, 310, 225);
	gt_obj_set_size(lab7, 85, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, GetPressUintString(ParamSetting.PressUint));

 
	/** img1 */
	/** 返回 */
	img1 = gt_img_create(ParamSetting1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect2 */
	/** 输液器选择 */
	rect2 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 230, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, BrandChange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	/** 输液器设置 */
	rect3 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect3, 305, 65);
	gt_obj_set_size(rect3, 95, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, BrandChange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	/** 阻塞压力切换 */
	rect4 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect4, 75, 145);
	gt_obj_set_size(rect4, 230, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, BlockPressure, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	/** 阻塞压力值设置 */
	rect5 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect5, 305, 145);
	gt_obj_set_size(rect5, 95, 60);
	gt_obj_set_opa(rect5, GT_OPA_40);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, BlockPressure, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect6 */
	/** 压力单位选择 */
	rect6 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect6, 75, 225);
	gt_obj_set_size(rect6, 230, 60);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, PressureUnitChange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect7 */
	/** 压力单位 */
	rect7 = gt_rect_create(ParamSetting1);
	gt_obj_set_pos(rect7, 305, 225);
	gt_obj_set_size(rect7, 95, 60);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, PressureUnitChange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	/** 上一页 */
	svg1 = gt_img_create(ParamSetting1);
	gt_obj_set_pos(svg1, 415, 70);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	/** 下一页 */
	svg2 = gt_img_create(ParamSetting1);
	gt_obj_set_pos(svg2, 415, 230);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, DownPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	/** 页数标签 */
	lab8 = gt_label_create(ParamSetting1);
	gt_obj_set_pos(lab8, 400, 157);
	gt_obj_set_size(lab8, 76, 34);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "1/4");


	return ParamSetting1;
}

