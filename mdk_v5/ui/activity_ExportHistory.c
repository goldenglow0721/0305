#include "ui.h"


/** ExportHistory */
gt_obj_st * ExportHistory = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * btn1 = NULL;


static const char title[5][1][50]={
	"导出历史记录",

	"Export History",

	"Registro de Historia",

	"歷史記錄",

	"Registro Histórico"
		
};

static void btn1_0_cb(gt_event_st * e) {

}




static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_ExportHistory(void)
{
	ExportHistory =  gt_obj_create(NULL);
	my_set_obj_title(ExportHistory,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(ExportHistory, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(ExportHistory);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(ExportHistory);
	gt_obj_set_pos(svg1, 291, 270);
	gt_obj_set_size(svg1, 48, 48);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_down_120_3.png");


	/** svg2 */
	svg2 = gt_img_create(ExportHistory);
	gt_obj_set_pos(svg2, 190, 272);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_up_120_4.png");

	/** btn1 */
	btn1 = gt_btn_create(ExportHistory);
	gt_obj_set_pos(btn1, 120, 200);
	gt_obj_set_size(btn1, 200, 55);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][0]);
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	
	return ExportHistory;
}

