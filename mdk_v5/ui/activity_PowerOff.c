#include "ui.h"
static const char title[5][1][50]={
	"关机",

	"Shutdown",

	"Apagar",

	"關機",

	"Desligar"

};

/** PowerOff */
gt_obj_st * PowerOff = NULL;
static gt_obj_st * img1 = NULL;
static _gt_timer_st * timer_main_ThirmSec = NULL;
/** 返回 */
static int buffer=0;
static void Timer_ThirmSec(gt_event_st * e){
	//300ms的定时器
	
	vtaskmanage(1);
}


gt_obj_st * gt_init_PowerOff(void)
{
	PowerOff =  gt_obj_create(NULL);	img1 = gt_img_create(PowerOff);
	gt_obj_set_pos(img1, 70, 100);
	gt_obj_set_size(img1, 325, 160);
	gt_img_set_src(img1, "f:img_325x160_PowerOff.png");
	my_set_obj_title(PowerOff,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PowerOff, gt_color_hex(0x000000));
	 

	timer_main_ThirmSec =  _gt_timer_create(Timer_ThirmSec,300,NULL);
	return PowerOff;
}

































