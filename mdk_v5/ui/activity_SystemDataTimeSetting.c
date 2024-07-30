#include "ui.h"


/** SystemDataTimeSetting */
gt_obj_st * SystemDataTimeSetting = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * btn1 = NULL;


static const char title[5][2][50]={
	"系统日期与时间",
	"时间",

	"Date And Time",
	"Time",

	"Fecha y Hora",
	"Tiempo",

	"系統日期與時間",
	"時間",

	"Data e hora",
	"Tempo"
		
};





static TIME TIME_DATA;
//back
static void back(gt_event_st * e) {

	
	WriteSystemSettingMessageToFlash();
	gt_disp_stack_load_scr_anim(GT_SCR_ID_45, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

//系统时间设定
static void TimeSetting(gt_event_st * e) {
	
	strcpy(keyboardt.title,title[SystemSetting.langue][1]);
	keyboardt.time = &TIME_DATA;

	gt_disp_stack_load_scr_anim(GT_SCR_ID_82, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	 
}



//时间格式
static void TimeFormatSetting(gt_event_st * e) {
	

}



//系统日期设定
static void DataSetting(gt_event_st * e) {
	keyboardt.time = &TIME_DATA;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_30, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


//日期格式设定
static void DataFormat(gt_event_st * e) {
	char buffer[50];
	SystemSetting.TimeAndData.dateformat++;
	if(SystemSetting.TimeAndData.dateformat>ddmmyyyy)
	{
		SystemSetting.TimeAndData.dateformat=yyyymmdd;
	}
	if(SystemSetting.TimeAndData.dateformat==yyyymmdd){
		sprintf(buffer,"%s",DateFormat01); 
	}else if(SystemSetting.TimeAndData.dateformat==mmddyyyy){
		sprintf(buffer,"%s",DateFormat02);
	}else if(SystemSetting.TimeAndData.dateformat==ddmmyyyy){
		sprintf(buffer,"%s",DateFormat03);
	}
	gt_label_set_text(lab10,buffer);
	gt_event_send(lab8,GT_EVENT_TYPE_DRAW_REDRAW,NULL);
}


//确认
static void Confirm(gt_event_st * e) {
	
	WriteSystemSettingMessageToFlash();

	gt_disp_stack_load_scr_anim(GT_SCR_ID_45, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


static void EventUpdata(gt_event_st * e)
{
	char buff[50];
	if(strcmp(e->param,"1") == 0)  //更改了时间
	{
		calendar.hour = TIME_DATA.hour;
		calendar.min  = TIME_DATA.min;
		calendar.sec  = TIME_DATA.sec;
		rtc_time_set(&calendar);
		
		sprintf(buff,"%02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);
		gt_label_set_text(lab3, buff);
		sprintf(buff,"%02d:%02d",calendar.hour,calendar.min);
		gt_label_set_text(headclock,buff);
	}
	else if(!strcmp(e->param,"2"))//更换日期
	{
		rtc_time_set(&calendar);
		if(SystemSetting.TimeAndData.dateformat==yyyymmdd)
		{
			sprintf(buff,"%d-%d-%d",calendar.year,calendar.mon,calendar.day);
		}else if(SystemSetting.TimeAndData.dateformat==mmddyyyy)
		{
			sprintf(buff,"%d-%d-%d",calendar.mon,calendar.day,calendar.year);
		}else if(SystemSetting.TimeAndData.dateformat==ddmmyyyy)
		{
			sprintf(buff,"%d-%d-%d",calendar.day,calendar.mon,calendar.year);
		}
		
		gt_label_set_text(lab8,buff);
		WriteSystemSettingMessageToFlash();
	}
}

gt_obj_st * gt_init_SystemDataTimeSetting(void)
{
	char buff[50];
	SystemDataTimeSetting =  gt_obj_create(NULL);
	my_set_obj_title(SystemDataTimeSetting,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemDataTimeSetting, gt_color_hex(0x000000));
	gt_obj_add_event_cb(SystemDataTimeSetting,EventUpdata,MY_EVENT_UPDATA,NULL);
	 
	

	
	/** img1 */
	img1 = gt_img_create(SystemDataTimeSetting);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);





	/** lab2 */
	lab2 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab2, 80, 70);
	gt_obj_set_size(lab2, 135, 40);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "系统时间");


	/** 显示时间 */
	lab3 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab3, 215, 70);
	gt_obj_set_size(lab3, 180, 40);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	rtc_time_get();
	TIME_DATA.hour = calendar.hour;
	TIME_DATA.min = calendar.min;
	TIME_DATA.sec = calendar.sec;
	sprintf(buff,"%02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);
	gt_label_set_text(lab3, buff);


	/** lab4 */
	lab4 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab4, 80, 120);
	gt_obj_set_size(lab4, 135, 40);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "时间格式");


	/** lab5 */
	lab5 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab5, 215, 120);
	gt_obj_set_size(lab5, 180, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "24H");


	/** lab7 */
	lab7 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab7, 80, 170);
	gt_obj_set_size(lab7, 135, 40);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "系统日期");


	/** 显示日期 */
	lab8 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab8, 215, 170);
	gt_obj_set_size(lab8, 180, 40);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	if(SystemSetting.TimeAndData.dateformat==yyyymmdd)
	{
		sprintf(buff,"%d-%d-%d",calendar.year,calendar.mon,calendar.day);
	}else if(SystemSetting.TimeAndData.dateformat==mmddyyyy)
	{
		sprintf(buff,"%d-%d-%d",calendar.mon,calendar.day,calendar.year);
	}else if(SystemSetting.TimeAndData.dateformat==ddmmyyyy)
	{
		sprintf(buff,"%d-%d-%d",calendar.day,calendar.mon,calendar.year);
	}
	gt_label_set_text(lab8,buff);


	/** lab9 */
	lab9 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab9, 80, 220);
	gt_obj_set_size(lab9, 135, 40);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "日期格式");


	/** lab10 */
	lab10 = gt_label_create(SystemDataTimeSetting);
	gt_obj_set_pos(lab10, 215, 220);
	gt_obj_set_size(lab10, 180, 40);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	if(SystemSetting.TimeAndData.dateformat==yyyymmdd){
		sprintf(buff,"%s",DateFormat01); 
	}else if(SystemSetting.TimeAndData.dateformat==mmddyyyy){
		sprintf(buff,"%s",DateFormat02);
	}else if(SystemSetting.TimeAndData.dateformat==ddmmyyyy){
		sprintf(buff,"%s",DateFormat03);
	}
	gt_label_set_text(lab10, buff);


	/** rect2 */
	rect2 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect2, 80, 70);
	gt_obj_set_size(rect2, 135, 40);
	gt_obj_set_opa(rect2, GT_OPA_56);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, TimeSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect3 */
	rect3 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect3, 80, 120);
	gt_obj_set_size(rect3, 135, 40);
	gt_obj_set_opa(rect3, GT_OPA_56);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, TimeFormatSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect4 */
	rect4 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect4, 80, 170);
	gt_obj_set_size(rect4, 135, 40);
	gt_obj_set_opa(rect4, GT_OPA_56);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, DataSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect5 */
	rect5 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect5, 80, 220);
	gt_obj_set_size(rect5, 135, 40);
	gt_obj_set_opa(rect5, GT_OPA_55);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, DataFormat, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect6 */
	rect6 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect6, 215, 70);
	gt_obj_set_size(rect6, 180, 40);
	gt_obj_set_opa(rect6, GT_OPA_40);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, TimeSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** rect7 */
	rect7 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect7, 215, 120);
	gt_obj_set_size(rect7, 180, 40);
	gt_obj_set_opa(rect7, GT_OPA_40);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7, TimeFormatSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** rect8 */
	rect8 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect8, 215, 170);
	gt_obj_set_size(rect8, 180, 40);
	gt_obj_set_opa(rect8, GT_OPA_40);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect8, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8, DataSetting, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect9 */
	rect9 = gt_rect_create(SystemDataTimeSetting);
	gt_obj_set_pos(rect9, 215, 220);
	gt_obj_set_size(rect9, 180, 40);
	gt_obj_set_opa(rect9, GT_OPA_40);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);
	gt_obj_add_event_cb(rect9, DataFormat, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** btn1 */
	btn1 = gt_btn_create(SystemDataTimeSetting);
	gt_obj_set_pos(btn1, 405, 270);
	gt_obj_set_size(btn1, 75, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
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


	return SystemDataTimeSetting;
}

