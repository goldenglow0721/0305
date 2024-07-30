#include "ui.h"


/** Standby */
gt_obj_st * Standby = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static int StandbySec; 

static const char title[5][3][65]={
	"待机",
	"唤醒时间",
    "待机时间结束",


    "Standby",
	"Wake Up",
    "Standby Time Expired",


    "En Espera",
	"Despertar",
    "Tiempo de Espera Expirado",


    "待機",
	"喚醒時間",
    "待機時間結束",


    "Espera",
	"Acordar",
    "Tempo de espera expirado"
};

static void ChangeTime(gt_event_st * e) {

	strcpy(keyboardt.title,title[SystemSetting.langue][0]);
	keyboardt.time =&ParamSetting.Standbytime; 
	gt_disp_stack_load_scr_anim(GT_SCR_ID_82, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void back(gt_event_st * e) {

	gt_disp_stack_go_back(1);
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	if(atoi(e->param) == 1)  //修改完时间出来的
	{
		sprintf(buffer,"%02d:%02d:%02d",ParamSetting.Standbytime.hour,ParamSetting.Standbytime.min,ParamSetting.Standbytime.sec);
		StandbySec = ParamSetting.Standbytime.hour*3600+ParamSetting.Standbytime.min*60+ParamSetting.Standbytime.sec;
		gt_label_set_text(lab4, buffer);
		WriteParamSettingMessageToFlash();
	}
}

static void one_sec_timer(gt_event_st * e)
{
    char buffer[50];
    StandbySec -- ;
    ParamSetting.Standbytime.hour = StandbySec/3600;
    ParamSetting.Standbytime.min = (StandbySec/60)%60;
    ParamSetting.Standbytime.sec = StandbySec%60;
    sprintf(buffer,"%02d:%02d:%02d",ParamSetting.Standbytime.hour,ParamSetting.Standbytime.min,ParamSetting.Standbytime.sec);
    gt_label_set_text(lab4, buffer);

	/*接近完成*/
	if(JudgedinfusionNeaeTimeAlarm(&ParamSetting.Standbytime))
	{
		if(GetNerDoneFlag() == 0)
		{
			AddAlarm(ALARM_NEAR_DONE);
			SetNerDoneFlag(0xFF);
		}
	}
	if(StandbySec <= 0)
	{
		AddAlarm(ALARM_DAJI_FINISH);
		SetNerDoneFlag(0xFF);
		
		gt_disp_stack_go_back(1);
		ClearAlarm(ALARM_DAJI_FINISH);
	}
}

gt_obj_st * gt_init_Standby(void)
{
	
    char buffer[50];
	StandbySec = ParamSetting.Standbytime.hour*3600+ParamSetting.Standbytime.min*60+ParamSetting.Standbytime.sec;

	Standby =  gt_obj_create(NULL);
    gt_obj_add_event_cb(Standby,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_obj_add_event_cb(Standby,one_sec_timer,MY_ONE_SECONDS_TIME,NULL);
	my_set_obj_title(Standby,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(Standby, gt_color_hex(0x000000));


	/** rect1 */
	rect1 = gt_rect_create(Standby);
	gt_obj_set_pos(rect1, 290, 90);
	gt_obj_set_size(rect1, 130, 40);
	gt_obj_set_opa(rect1, GT_OPA_56);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);
	gt_obj_add_event_cb(rect1, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	 

	/** lab2 */
	lab2 = gt_label_create(Standby);
	gt_obj_set_pos(lab2, 290, 86);
	gt_obj_set_size(lab2, 130, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);
	gt_obj_add_event_cb(lab2, ChangeTime, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    

    /** lab3 */
	lab3 = gt_label_create(Standby);
	gt_obj_set_pos(lab3, 290, 180);
	gt_obj_set_size(lab3, 100, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "h:m:s");

    /** lab4 */
	lab4 = gt_label_create(Standby);
	gt_obj_set_pos(lab4, 290, 150);
	gt_obj_set_size(lab4, 130, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
    sprintf(buffer,"%02d:%02d:%02d",ParamSetting.Standbytime.hour,ParamSetting.Standbytime.min,ParamSetting.Standbytime.sec);
	gt_label_set_text(lab4, buffer);

	img2 = gt_img_create(Standby);
	gt_obj_set_pos(img2, 1, 80);
	gt_obj_set_size(img2, 242, 162);
	gt_img_set_src(img2, "f:img_242x162_1717237298272.jpg");

    /** img1 */
	img1 = gt_img_create(Standby);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return Standby;
}

