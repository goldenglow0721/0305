#include "ui.h"
#include "infusion.h"
#include "headbar_view.h"

/** ParamSetting3 */
gt_obj_st * ParamSetting3 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * cbox1 = NULL;
static gt_obj_st * cbox2 = NULL;
static gt_obj_st * cbox3 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;


static char buffer[30];

static const char title[5][5][50]={
	"输注设定",
	"自动锁时间",
	"无操作时间",
	"接近完成时间",
	"主菜单",
	
	
	"Infusion Setting",
	"Autolock Time",
	"Reminder Time",
	"Time Near End",
	"Main Menu",

	"Configuración de Infusión",
	"Tiempo de Autolock",
	"Tiempo de Recordatorio",
	"Tiempo casi terminado",
	"Menú Principal",

	"輸注設定",
	"自動鎖時間",
	"無操作時間",
	"接近完成時間",
	"主菜單",
	
	"Configuração de Infusão",
	"Tempo de bloqueio automático",
	"Tempo de lembrete",
	"Tempo próximo do fim",
	"Menu principal"
	
};


static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][4]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void UpPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_21);
}

static void DownPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_23);
}

static void AutoLockTime(gt_event_st * e) {
	keyboardi.data = &ParamSetting.LockTime;
	strcpy(keyboardi.title,title[SystemSetting.langue][1]);
	keyboardi.id=3;
	limit.lowerlimit=1;
	limit.toplimit=5;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}
static void NoOperateTime(gt_event_st * e) {
	keyboardi.data = &ParamSetting.NoOperationTime;
	strcpy(keyboardi.title,title[SystemSetting.langue][2]);
	keyboardi.id=4;
	limit.lowerlimit=1;
	limit.toplimit=5;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}
static void NearFinishTime(gt_event_st * e) {
	keyboardi.data = &ParamSetting.NearDoneTime;
	strcpy(keyboardi.title,title[SystemSetting.langue][3]);
	keyboardi.id=5;
	limit.lowerlimit=1;
	limit.toplimit=30;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void AutoLockTime_state(gt_event_st * e){

	if(ParamSetting.LockState == true){
		ParamSetting.LockState = false;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
	else{
		ParamSetting.LockState = true;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
}

static void NoOperateTime_state(gt_event_st * e){

	if(ParamSetting.NoOperationState == true){
		ParamSetting.NoOperationState = false;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
	else{
		ParamSetting.NoOperationState = true;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
}

static void NearFinishTime_state(gt_event_st * e){

	if(ParamSetting.NearDoneState == true){
		ParamSetting.NearDoneState = false;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
	else{
		ParamSetting.NearDoneState = true;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
	}
}

static void EventUpdata(gt_event_st * e)
{
	
	
	if(atoi(e->param) == 3)  //修改完自动锁时间出来的
	{
		sprintf(buffer,"%d",ParamSetting.LockTime);
		gt_label_set_text(lab3, buffer);
		not_first_start_write_history_info(EA_Set,Ev_SetLockTime,buffer);
		WriteParamSettingMessageToFlash();
	}
	if(atoi(e->param) == 4)  //修改完无操作时间出来的
	{
		sprintf(buffer,"%d",ParamSetting.NoOperationTime);
		gt_label_set_text(lab4, buffer);
		not_first_start_write_history_info(EA_Set,Ev_SetNoOperationTime,buffer);
		WriteParamSettingMessageToFlash();
	}
	if(atoi(e->param) == 5)  //修改完接近完成时间出来的
	{
		printf("NearDoneTime");
		sprintf(buffer,"%d",ParamSetting.NearDoneTime);
		gt_label_set_text(lab5, buffer);
		not_first_start_write_history_info(EA_Set,Ev_SetNearDoneTime,buffer);
		WriteParamSettingMessageToFlash();
	}
}


gt_obj_st * gt_init_ParamSetting3(void)
{
	
	ParamSetting3 =  gt_obj_create(NULL);
	my_set_obj_title(ParamSetting3,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(ParamSetting3, gt_color_hex(0x000000));
	gt_obj_add_event_cb(ParamSetting3,EventUpdata,MY_EVENT_UPDATA,NULL);

	// 
	my_set_obj_title(ParamSetting3,title[SystemSetting.langue][0]);
	
	/** img1 */
	img1 = gt_img_create(ParamSetting3);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(ParamSetting3);
	gt_obj_set_pos(svg1, 415, 70);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(ParamSetting3);
	gt_obj_set_pos(svg2, 416, 230);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, DownPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab2, 400, 157);
	gt_obj_set_size(lab2, 76, 34);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "3/4");

	/** lab3 */
	lab3 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab3, 310, 65);
	gt_obj_set_size(lab3, 40, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",ParamSetting.LockTime);
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	lab4 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab4, 310, 145);
	gt_obj_set_size(lab4, 40, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",ParamSetting.NoOperationTime);
	gt_label_set_text(lab4, buffer);


	/** lab5 */
	lab5 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab5, 310, 225);
	gt_obj_set_size(lab5, 40, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",ParamSetting.NearDoneTime);
	gt_label_set_text(lab5, buffer);


	/** lab6 */
	lab6 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab6, 350, 65);
	gt_obj_set_size(lab6, 45, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "min");


	/** lab7 */
	lab7 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab7, 350, 145);
	gt_obj_set_size(lab7, 45, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "min");


	/** lab8 */
	lab8 = gt_label_create(ParamSetting3);
	gt_obj_set_pos(lab8, 350, 225);
	gt_obj_set_size(lab8, 45, 60);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "min");


	/** rect5 */
	rect5 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect5, 310, 65);
	gt_obj_set_size(rect5, 40, 60);
	gt_obj_set_opa(rect5, GT_OPA_46);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);

	/** rect6 */
	rect6 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect6, 310, 145);
	gt_obj_set_size(rect6, 40, 60);
	gt_obj_set_opa(rect6, GT_OPA_46);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);


	/** rect7 */
	rect7 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect7, 310, 225);
	gt_obj_set_size(rect7, 40, 60);
	gt_obj_set_opa(rect7, GT_OPA_45);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0xA9A9A9));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);


	/** rect2 */
	rect2 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 325, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,AutoLockTime,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect3 */
	rect3 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect3, 75, 145);
	gt_obj_set_size(rect3, 325, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3,NoOperateTime,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect4 */
	rect4 = gt_rect_create(ParamSetting3);
	gt_obj_set_pos(rect4, 75, 225);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4,NearFinishTime,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** cbox1 */
	cbox1 = gt_checkbox_create(ParamSetting3);
	gt_obj_set_pos(cbox1, 80, 75);
	gt_obj_set_size(cbox1, 215, 40);
	gt_checkbox_set_font_color(cbox1, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox1, 24);
	gt_checkbox_set_font_family_cn(cbox1, 20);
	gt_checkbox_set_font_family_en(cbox1, 33);
	gt_checkbox_set_font_family_fl(cbox1, 50);
	gt_checkbox_set_text(cbox1, title[SystemSetting.langue][1]);
	if(ParamSetting.LockState == true)
		gt_obj_set_state(cbox1, 1);
	else
	{
		gt_obj_set_state(cbox1, 0);
	}
	gt_checkbox_set_font_point_offset(cbox1, 10, 0);
	gt_obj_add_event_cb(cbox1,AutoLockTime_state,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** cbox2 */
	cbox2 = gt_checkbox_create(ParamSetting3);
	gt_obj_set_pos(cbox2, 80, 155);
	gt_obj_set_size(cbox2, 215, 45);
	gt_checkbox_set_font_color(cbox2, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox2, 24);
	gt_checkbox_set_font_family_cn(cbox2, 20);
	gt_checkbox_set_font_family_en(cbox2, 33);
	gt_checkbox_set_font_family_fl(cbox2, 50);
	gt_checkbox_set_text(cbox2,title[SystemSetting.langue][2]);
	if(ParamSetting.NoOperationState == true)
		gt_obj_set_state(cbox2, 1);
	else
		gt_obj_set_state(cbox2, 0);
	gt_checkbox_set_font_point_offset(cbox2, 10, 0);
	gt_obj_add_event_cb(cbox2,NoOperateTime_state,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** cbox3 */
	cbox3 = gt_checkbox_create(ParamSetting3);
	gt_obj_set_pos(cbox3, 80, 235);
	gt_obj_set_size(cbox3, 215, 40);
	gt_checkbox_set_font_color(cbox3, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox3, 24);
	gt_checkbox_set_font_family_cn(cbox3, 20);
	gt_checkbox_set_font_family_en(cbox3, 33);
	gt_checkbox_set_font_family_fl(cbox3, 50);
	gt_checkbox_set_text(cbox3, title[SystemSetting.langue][3]);
	if(ParamSetting.NearDoneState == true)
		gt_obj_set_state(cbox3, 1);
	else
		gt_obj_set_state(cbox3, 0);
	gt_checkbox_set_font_point_offset(cbox3, 10, 0);
	gt_obj_add_event_cb(cbox3,NearFinishTime_state,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	return ParamSetting3;
}

