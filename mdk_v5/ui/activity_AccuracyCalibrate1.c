#include "ui.h"

/*
	将输液器尾端放入空的量杯中

*/





static const char title[5][4][70]={
	"精度校准",
	"1.请将输液器终端放入空的量杯。",
	"3.请将输液器终端再次放入空的量杯。",
	"运行",
		
	"IV Set Calibration",
	"1.Put the IV set into empty counting cup.",
	"3.Put the IV set into empty counting cup again.",
	"Start",

	"Calibración de IV Conjunto",
	"1.Pon el conjunto IV en una taza de conteo vacía.",
	"3.Pon el conjunto IV en una taza de conteo vacía nuevamente.",
	"Inicio",

	"精度校準",
	"1.請將輸液器終端放入空的量杯。",
	"3.請將輸液器終端再次放入空的量杯。",
	"運行",

	"Calibração de equipo",
	"1.Coloque o equipo em um copo de contagem vazio.",
	"3.Coloque novamente o equipo no copo de contagem vazio.",
	"Inicio"
};


static int RecData;

/** AccuracyCalibrate1 */
gt_obj_st * AccuracyCalibrate1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn2 = NULL;

static void Back(gt_event_st * e) {
	
	TMC2226_MotorStop();
	gt_disp_stack_go_back(2);
}


static void Run(gt_event_st * e) {

	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_51, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_AccuracyCalibrate1()
{

	if(calibrate == true)
	{
		RecData = 2;
	}
	else
	{
		RecData = 1;
	}

	AccuracyCalibrate1 =  gt_obj_create(NULL);
	my_set_obj_title(AccuracyCalibrate1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(AccuracyCalibrate1, gt_color_hex(0x000000));

	 

	/** img1 */
	img1 = gt_img_create(AccuracyCalibrate1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** lab2 */
	lab2 = gt_label_create(AccuracyCalibrate1);
	gt_obj_set_pos(lab2, 29, 140);
	gt_obj_set_size(lab2, 420, 37);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	if(RecData == 1)
	{
		gt_label_set_text(lab2, title[SystemSetting.langue][1]);
	}
	else if(RecData == 2)
	{
		gt_label_set_text(lab2, title[SystemSetting.langue][2]);
	}
	


	/** btn2 */
	btn2 = gt_btn_create(AccuracyCalibrate1);
	gt_obj_set_pos(btn2, 389, 270);
	gt_obj_set_size(btn2, 78, 50);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn2, gt_color_hex(0xffffff));
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, Run, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return AccuracyCalibrate1;
}

