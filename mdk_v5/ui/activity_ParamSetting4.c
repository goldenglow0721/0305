#include "ui.h"
#include "infusion.h"
#include "headbar_view.h"

/** ParamSetting4 */
gt_obj_st * ParamSetting4 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;



static const char title[5][4][50]={
		"输注设定",
		"滴系数",
		"滴/ml",
		"主菜单",
		
		"Infusion Setting",
		"drip",
		"drip/ml",
		"Main Menu",
		
		"Configuración de Infusión",
		"Diámetro de Goteo",
		"Goteo/ml",
		"Menú Principal",
		
        "輸注設定",
		"滴係數",
		"滴/ml",
		"主菜單",
	
        "Configuração de Infusão",
		"Gotas",
		"Gotas/ml",
		"Menu principal",
	
};


static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][3]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void UpPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_22);
}

static void DownPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_2);
}

static void ChangeDrips(gt_event_st * e) {
	strcpy(keyboardi.title,title[SystemSetting.langue][1]);
	keyboardi.data = &DripMode.drips;
	keyboardi.id=2;
	limit.toplimit = 60;
	limit.lowerlimit = 10;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 2)  //修改完滴系数出来的
	{
		sprintf(buffer,"%d",DripMode.drips);
		gt_label_set_text(lab6, buffer);
		not_first_start_write_history_info(EA_Set,Ev_Drip,buffer);
	}
	WriteDripModeMessageToFlash();
}


gt_obj_st * gt_init_ParamSetting4(void)
{
	char buffer[50];
	ParamSetting4 =  gt_obj_create(NULL);
	my_set_obj_title(ParamSetting4,title[SystemSetting.langue][0]);
	gt_obj_add_event_cb(ParamSetting4,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_screen_set_bgcolor(ParamSetting4, gt_color_hex(0x000000));

	// 
	my_set_obj_title(ParamSetting4,title[SystemSetting.langue][0]);
	/** img1 */
	img1 = gt_img_create(ParamSetting4);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(ParamSetting4);
	gt_obj_set_pos(svg1, 415, 70);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(ParamSetting4);
	gt_obj_set_pos(svg2, 416, 230);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, DownPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(ParamSetting4);
	gt_obj_set_pos(lab2, 400, 157);
	gt_obj_set_size(lab2, 76, 34);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "4/4");

    /** lab5 */
	lab5 = gt_label_create(ParamSetting4);
	gt_obj_set_pos(lab5, 85, 65);
	gt_obj_set_size(lab5, 140, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][1]);

	/** lab6 */
	lab6 = gt_label_create(ParamSetting4);
	gt_obj_set_pos(lab6, 235, 65);
	gt_obj_set_size(lab6, 40, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",DripMode.drips);
	gt_label_set_text(lab6, buffer);

	/** lab7 */
	lab7 = gt_label_create(ParamSetting4);
	gt_obj_set_pos(lab7, 283, 65);
	gt_obj_set_size(lab7, 90, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_RIGHT_MID);
	gt_label_set_text(lab7, title[SystemSetting.langue][2]);

    	/** rect4 */
	rect4 = gt_rect_create(ParamSetting4);
	gt_obj_set_pos(rect4, 75, 65);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, ChangeDrips, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

    /** rect5 */
	rect5 = gt_rect_create(ParamSetting4);
	gt_obj_set_pos(rect5, 235, 65);
	gt_obj_set_size(rect5, 40, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0x000000));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, ChangeDrips, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	return ParamSetting4;
}

