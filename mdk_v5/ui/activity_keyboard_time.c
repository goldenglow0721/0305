#include "ui.h"
#include "up.h"


extern _Bool enterkey;

static const char title[5][4][50]={
	"时间",
	"时"
	"分",
	"秒",

	"Time",
	"H.",
	"M.",
	"S.",

	"Tiempo",
	"H.",
	"M.",
	"S.",

	"時間",
	"時",
	"分",
	"秒",

	"Tempo",
	"H.",
	"M.",
	"S."

};




/** TimeKeyBoard */
gt_obj_st * TimeKeyBoard = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * rect10 = NULL;

static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;

static TIME sg_timetemp;
static _Bool sg_flag = true;  //判断是否是第一次进这个键盘


static void back(gt_event_st * e) {
	sg_flag = true;
	enterkey = false;
	headvisiable(1);
	gt_disp_stack_go_back(1);
}

static void Confirm(gt_event_st * e) {
	
	*keyboardt.time = sg_timetemp;

	gt_event_send(gt_scr_stack_get_prev_scr(),MY_EVENT_UPDATA,"1");
	sg_flag = true;
	enterkey = false;
	headvisiable(1);
	gt_disp_stack_go_back(1);

}


//更改 hour
static void rect2_0_cb(gt_event_st * e) {

	strcpy(keyboardi.title,"时");
	keyboardi.data = &sg_timetemp.hour; 
	keyboardi.id=14;
	limit.toplimit = 99;
	limit.lowerlimit = 0;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}
static void rect5_0_cb(gt_event_st * e) {
	char buff[50];
	if(my_judge_obj_exists(GT_SCR_ID_7)||my_judge_obj_exists(GT_SCR_ID_84))
	{
		if(++sg_timetemp.hour > 99)
		{
			sg_timetemp.hour = 0;
		}
	}
	else
	{
		if(++sg_timetemp.hour > 23)
		{
			sg_timetemp.hour = 0;
		}
	}
	
	sprintf(buff,"%d",sg_timetemp.hour);
	gt_label_set_text(lab11, buff);

}
static void rect6_0_cb(gt_event_st * e) {
	char buff[50];
	
	if(my_judge_obj_exists(GT_SCR_ID_7)||my_judge_obj_exists(GT_SCR_ID_84))
	{
		if(--sg_timetemp.hour < 0)
		{
			sg_timetemp.hour = 99;
		}
	}
	else
	{
		if(--sg_timetemp.hour < 0)
		{
			sg_timetemp.hour = 23;
		}
	}
	sprintf(buff,"%d",sg_timetemp.hour);
	gt_label_set_text(lab11, buff);
}

//更改 min
static void rect3_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,"分");
	keyboardi.data = &sg_timetemp.min;
	keyboardi.id=13;
	limit.toplimit = 59;
	limit.lowerlimit = 0;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}
static void rect7_0_cb(gt_event_st * e) {
	char buff[50];
	if(++sg_timetemp.min > 59)
	{
		sg_timetemp.min = 0;
	}
	sprintf(buff,"%d",sg_timetemp.min);
	gt_label_set_text(lab12, buff);

}
static void rect8_0_cb(gt_event_st * e) {
	char buff[50];
	if(--sg_timetemp.min < 0)
	{
		sg_timetemp.min = 59;
	}
	sprintf(buff,"%d",sg_timetemp.min);
	gt_label_set_text(lab12, buff);
}


//更改 sec
static void rect4_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,"秒");
	keyboardi.data = &sg_timetemp.sec; 
	keyboardi.id=12;
	limit.toplimit = 59;
	limit.lowerlimit = 0;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}
static void rect9_0_cb(gt_event_st * e) {
	char buff[50];
	if(++sg_timetemp.sec > 59)
	{
		sg_timetemp.sec = 0;
	}
	sprintf(buff,"%d",sg_timetemp.sec);
	gt_label_set_text(lab13, buff);
}
static void rect10_0_cb(gt_event_st * e) {
	char buff[50];
	if(--sg_timetemp.sec < 0)
	{
		sg_timetemp.sec = 59;
	}
	sprintf(buff,"%d",sg_timetemp.sec);
	gt_label_set_text(lab13, buff);

}
static void EventUpdata(gt_event_st * e)
{
	char buff[50];
	if(atoi(e->param) == 12)  //修改完秒出来的
	{
		sprintf(buff,"%d",sg_timetemp.sec);
		gt_label_set_text(lab13, buff);
	}
	if(atoi(e->param) == 13)  //修改完分出来的
	{
		sprintf(buff,"%d",sg_timetemp.min);
		gt_label_set_text(lab12, buff);
	}
	if(atoi(e->param) == 14)  //修改完时出来的
	{
		sprintf(buff,"%d",sg_timetemp.hour);
		gt_label_set_text(lab11, buff);
	}

}

gt_obj_st * gt_init_TimeKeyBoard(void)
{
	if(sg_flag == true) //是第一次进来
	{
		sg_timetemp = *keyboardt.time;
		sg_flag = false;
	}
	enterkey = true;
	


	char buff[50];
	TimeKeyBoard = gt_obj_create(NULL);
	gt_screen_set_bgcolor(TimeKeyBoard, gt_color_hex(0x000000));
	gt_obj_add_event_cb(TimeKeyBoard,EventUpdata,MY_EVENT_UPDATA,NULL);
	headvisiable(0);
	
	/** img1 */
	img1 = gt_img_create(TimeKeyBoard);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x75_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab1 */
	lab1 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab1, 0, 0);
	gt_obj_set_size(lab1, 150, 50);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab1, "时间");


	/** rect1 */
	rect1 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect1, 0, 0);
	gt_obj_set_size(rect1, 480, 50);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x778899));
	gt_rect_set_fill(rect1, 4);
	gt_rect_set_border(rect1, 0);


	/** btn1 */
	btn1 = gt_btn_create(TimeKeyBoard);
	gt_obj_set_pos(btn1, 380, 266);
	gt_obj_set_size(btn1, 100, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab2, 145, 133);
	gt_obj_set_size(lab2, 50, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, "时");


	/** lab3 */
	lab3 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab3, 270, 133);
	gt_obj_set_size(lab3, 50, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab3, "分");


	/** lab4 */
	lab4 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab4, 395, 133);
	gt_obj_set_size(lab4, 50, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab4, "秒");

	/** lab4 */
	lab11 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab11, 90, 120);
	gt_obj_set_size(lab11, 50, 75);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",sg_timetemp.hour);
	gt_label_set_text(lab11, buff);

	/** lab12 */
	lab12 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab12, 215, 120);
	gt_obj_set_size(lab12, 50, 75);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",sg_timetemp.min);
	gt_label_set_text(lab12, buff);

	/*lab13*/
	lab13 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab13, 340, 120);
	gt_obj_set_size(lab13, 50, 75);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",sg_timetemp.sec);
	gt_label_set_text(lab13, buff);


	/** rect2 */
	rect2 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect2, 90, 120);
	gt_obj_set_size(rect2, 50, 75);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** rect3 */
	rect3 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect3, 215, 120);
	gt_obj_set_size(rect3, 50, 75);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, rect3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** rect4 */
	rect4 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect4, 340, 120);
	gt_obj_set_size(rect4, 50, 75);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** lab5 */
	lab5 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab5, 90, 70);
	gt_obj_set_size(lab5, 50, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "+");


	/** rect5 */
	rect5 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect5, 90, 70);
	gt_obj_set_size(rect5, 50, 50);
	gt_obj_set_opa(rect5, GT_OPA_55);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** lab6 */
	lab6 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab6, 90, 195);
	gt_obj_set_size(lab6, 50, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "-");


	/** rect6 */
	rect6 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect6, 90, 195);
	gt_obj_set_size(rect6, 50, 50);
	gt_obj_set_opa(rect6, GT_OPA_55);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0x778899));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);
	gt_obj_add_event_cb(rect6, rect6_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	lab7 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab7, 215, 70);
	gt_obj_set_size(lab7, 50, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "+");


	/** lab8 */
	lab8 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab8, 215, 195);
	gt_obj_set_size(lab8, 50, 50);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "-");


	/** rect7 */
	rect7 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect7, 215, 70);
	gt_obj_set_size(rect7, 50, 50);
	gt_obj_set_opa(rect7, GT_OPA_55);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, rect7_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** rect8 */
	rect8 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect8, 215, 195);
	gt_obj_set_size(rect8, 50, 50);
	gt_obj_set_opa(rect8, GT_OPA_55);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0x778899));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 4);
	gt_obj_add_event_cb(rect8, rect8_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** lab9 */
	lab9 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab9, 340, 70);
	gt_obj_set_size(lab9, 50, 50);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "+");


	/** rect9 */
	rect9 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect9, 340, 70);
	gt_obj_set_size(rect9, 50, 50);
	gt_obj_set_opa(rect9, GT_OPA_55);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect9, gt_color_hex(0x778899));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 4);
	gt_obj_add_event_cb(rect9, rect9_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** lab10 */
	lab10 = gt_label_create(TimeKeyBoard);
	gt_obj_set_pos(lab10, 340, 195);
	gt_obj_set_size(lab10, 50, 50);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "-");


	/** rect10 */
	rect10 = gt_rect_create(TimeKeyBoard);
	gt_obj_set_pos(rect10, 340, 195);
	gt_obj_set_size(rect10, 50, 50);
	gt_obj_set_opa(rect10, GT_OPA_55);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0x778899));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 4);
	gt_obj_add_event_cb(rect10, rect10_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return TimeKeyBoard;
}

