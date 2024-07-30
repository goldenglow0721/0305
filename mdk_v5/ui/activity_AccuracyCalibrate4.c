#include "ui.h"


static const char title[5][2][50]={
	"精度校准",
	"校准完成！",

	"IV Set Calibration",
	"Calibration Completed!",

	"Calibración de IV Conjunto",
	"Calibración completada",

	"精度校準",
	"校準完成！",

	"Calibração de equipo",
	"Calibração completa!"

		
};

/** AccuracyCalibrate4 */
gt_obj_st * AccuracyCalibrate4 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;

/** 返回 */
static void img1_0_cb(gt_event_st * e) {

	if(my_judge_obj_exists(GT_SCR_ID_52))
	{
		gt_disp_stack_go_back(4);
	}
	else
	{
		gt_disp_stack_go_back(3);
	}
	
}


gt_obj_st * gt_init_AccuracyCalibrate4(void)
{
	AccuracyCalibrate4 =  gt_obj_create(NULL);
	my_set_obj_title(AccuracyCalibrate4,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(AccuracyCalibrate4, gt_color_hex(0x000000));

	 

	/** img1 */
	/** ReturnIcon */
	img1 = gt_img_create(AccuracyCalibrate4);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab1 */
	lab1 = gt_label_create(AccuracyCalibrate4);
	gt_obj_set_pos(lab1, 50, 70);
	gt_obj_set_size(lab1, 380, 80);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, title[SystemSetting.langue][1]);


	return AccuracyCalibrate4;
}

