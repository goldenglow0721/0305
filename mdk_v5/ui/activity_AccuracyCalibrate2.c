#include "ui.h"

/*

	正在校准 6min

*/


static const char title[5][3][50]={
	"精度校准",
	"正在校准...",
	"时间：",

	"IV Set Calibration",
	"Calibrating...",
	"Time:",

	"Calibración de IV Conjunto",
	"En Calibración",
	"Tiempo:",

	"精度校準",
	"正在校準...",
	"時間:",

	"Calibração de equipo",
	"Calibrando",
	"Tempo:"
		
};



/** AccuracyCalibrate2 */
gt_obj_st * AccuracyCalibrate2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * clock1 = NULL;


static int RecData;

static void Back(gt_event_st * e) {
	
	TMC2226_MotorStop();
	gt_disp_stack_go_back(2);

}


static void clock1_0_cb(gt_obj_st * obj, void * user_data) {
	printf("**************************************\n");

	//电机停
	TMC2226_MotorStop();
	//进入下个界面
	gt_disp_stack_load_scr_anim(GT_SCR_ID_52, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}

gt_obj_st * gt_init_AccuracyCalibrate2()
{

	

	if(calibrate)
	{
		RecData = 2;
	}
	else
	{
		RecData = 1;
	}

	AccuracyCalibrate2 =  gt_obj_create(NULL);
	my_set_obj_title(AccuracyCalibrate2,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(AccuracyCalibrate2, gt_color_hex(0x000000));

	 
	

	/** img1 */
	img1 = gt_img_create(AccuracyCalibrate2);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab2 */
	lab2 = gt_label_create(AccuracyCalibrate2);
	gt_obj_set_pos(lab2, 101, 95);
	gt_obj_set_size(lab2, 180, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(AccuracyCalibrate2);
	gt_obj_set_pos(lab3, 133, 150);
	gt_obj_set_size(lab3, 96, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, title[SystemSetting.langue][2]);


	/** clock1 */
	clock1 = gt_clock_create(AccuracyCalibrate2);
	gt_obj_set_pos(clock1, 201, 150);
	gt_obj_set_size(clock1, 153, 38);
	gt_clock_set_font_color(clock1, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock1, 24);
	gt_clock_set_font_family_en(clock1, 33);
	gt_clock_set_font_align(clock1, GT_ALIGN_LEFT);
	gt_clock_set_alert_time(clock1, 0, 0, 0);
	gt_clock_set_mode(clock1, GT_CLOCK_MODE_COUNTDOWN);
	if(RecData == 1)
	{
		gt_clock_set_time(clock1, 00, 06, 00);
	}
	else if(RecData == 2)
	{
		gt_clock_set_time(clock1, 00, 02, 00);
	}
	
	gt_clock_set_format(clock1, "hh:mm:ss");
	gt_clock_start(clock1);
	//添加倒计时结束回调事件及函数
	gt_clock_set_alert_cb(clock1, clock1_0_cb, NULL);

	MotorCALIBRRun(RecData);
	
	
	return AccuracyCalibrate2;
}

