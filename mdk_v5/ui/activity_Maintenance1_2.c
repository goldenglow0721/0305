#include "ui.h"
#include "headbar_view.h"

#include "infusion.h"

/** screen_Maintenance_Normal_Two */
gt_obj_st * screen_Maintenance_Normal_Two = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * cbox1 = NULL;
static gt_obj_st * cbox2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * cbox3 = NULL;
static gt_obj_st * rect3 = NULL;

static char buffer[30];

static const char title[5][3][50]={
	"系统维护",
	" 语音报警",
	"主菜单",


	"Maintenance",
	" Auditory Alarm",
	"Main Menu",

	
	"Mantenimiento",
	" Alarma Auditiva",
	"Menú Principal",

	
	"系統維護",
	" 語音警報",
	"主菜單",

	
	"Manutenção",
	" Alarme Auditivo",
	"Menu principal"
};



static void back(gt_event_st * e) {
	
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][2]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void rect4_0_cb(gt_event_st * e) {

	if(SystemMaintain.AntiState){
		SystemMaintain.AntiState = 0;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_AntiBolus,buffer);
	}
	else{
		SystemMaintain.AntiState = 1;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_AntiBolus,buffer);
	}
	WriteSystemMaintainMessageToFlash();
}

static void rect5_0_cb(gt_event_st * e) {
	if(SystemMaintain.KVOState){
		SystemMaintain.KVOState = 0;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_SetKVO,buffer);
	}
	else{
		SystemMaintain.KVOState = 1;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_SetKVO,buffer);
	}
	WriteSystemMaintainMessageToFlash();
		
}

static void ChangeAlarm(gt_event_st * e) {

	if(SystemMaintain.Alarm){
		SystemMaintain.Alarm = 0;
		sprintf(buffer,"关");
		not_first_start_write_history_info(EA_Set,Ev_AlarmSound,buffer);
	}
	else{
		SystemMaintain.Alarm = 1;
		sprintf(buffer,"开");
		not_first_start_write_history_info(EA_Set,Ev_AlarmSound,buffer);
	}
	WriteSystemMaintainMessageToFlash();
}

static void svg1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_41, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_43, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}






gt_obj_st * gt_init_Maintenance1_2(void)
{
	screen_Maintenance_Normal_Two =  gt_obj_create(NULL);
	my_set_obj_title(screen_Maintenance_Normal_Two,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(screen_Maintenance_Normal_Two, gt_color_hex(0x000000));
	 




	/** img1 */
	img1 = gt_img_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(rect4, 75, 150);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	rect5 = gt_rect_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(rect5, 75, 232);
	gt_obj_set_size(rect5, 325, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(svg1, 416, 74);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(lab8, 406, 157);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "2/5");

	rect3 = gt_rect_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(rect3, 75, 68);
	gt_obj_set_size(rect3, 325,60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, ChangeAlarm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** cbox1 */
	cbox3 = gt_checkbox_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(cbox3, 80, 83);
	gt_obj_set_size(cbox3, 325, 40);
	gt_checkbox_set_font_color(cbox3, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox3, 24);
	gt_checkbox_set_font_family_cn(cbox3, 20);
	gt_checkbox_set_font_family_en(cbox3, 33);
	gt_checkbox_set_font_family_fl(cbox3, 50);
	gt_checkbox_set_text(cbox3,title[SystemSetting.langue][1]);
	if(SystemMaintain.Alarm)
		gt_obj_set_state(cbox3, 1);
	else
		gt_obj_set_state(cbox3, 0);
	gt_checkbox_set_font_point_offset(cbox3, 10, 0);
	gt_obj_add_event_cb(cbox3, ChangeAlarm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** cbox1 */
	cbox1 = gt_checkbox_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(cbox1, 80, 160);
	gt_obj_set_size(cbox1, 325, 40);
	gt_checkbox_set_font_color(cbox1, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox1, 24);
	gt_checkbox_set_font_family_cn(cbox1, 20);
	gt_checkbox_set_font_family_en(cbox1, 33);
	gt_checkbox_set_font_family_fl(cbox1, 50);
	gt_checkbox_set_text(cbox1, " Anti-bolus");
	if(SystemMaintain.AntiState)
		gt_obj_set_state(cbox1, 1);
	else
		gt_obj_set_state(cbox1, 0);
	gt_checkbox_set_font_point_offset(cbox1, 10, 0);
	gt_obj_add_event_cb(cbox1, rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** cbox2 */
	cbox2 = gt_checkbox_create(screen_Maintenance_Normal_Two);
	gt_obj_set_pos(cbox2, 80, 242);
	gt_obj_set_size(cbox2, 325, 40);
	gt_checkbox_set_font_color(cbox2, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox2, 24);
	gt_checkbox_set_font_family_cn(cbox2, 20);
	gt_checkbox_set_font_family_en(cbox2, 33);
	gt_checkbox_set_font_family_fl(cbox2, 50);
	gt_checkbox_set_text(cbox2, " KVO");
	if(SystemMaintain.KVOState)
		gt_obj_set_state(cbox2, 1);
	else
		gt_obj_set_state(cbox2, 0);
	gt_checkbox_set_font_point_offset(cbox2, 10, 0);
	gt_obj_add_event_cb(cbox2, rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




	return screen_Maintenance_Normal_Two;
}

