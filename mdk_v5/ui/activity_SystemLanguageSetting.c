#include "ui.h"
#include "infusion.h"


static const char title[5][1][50]={
	"系统语言",
	

	"Language",
	

	"Idioma",
	

	"系統語言",
	

	"Linguagem",
	
		
};

static const char LanguageTitle [5][50]={"中文简体","English","Spanish","中文繁体","Portuguese"};







/** SystemLanguageSetting */
gt_obj_st * SystemLanguageSetting = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * radio3 = NULL;
static gt_obj_st * radio1 = NULL;
static gt_obj_st * radio2 = NULL;
static gt_obj_st * radio4 = NULL;
static gt_obj_st * radio5 = NULL;
extern gt_obj_st * homelab[5];

extern const char aaatitle[5][6][50];

static uint8_t temp;

//back
static void img1_0_cb(gt_event_st * e) {
	
	
	gt_disp_stack_go_back(1);
}

//ok
static void btn1_0_cb(gt_event_st * e) {
	char buffer[30];
	SystemSetting.langue = temp;
	WriteSystemSettingMessageToFlash();

	gt_label_set_text(homelab[0], aaatitle[SystemSetting.langue][5]);
	gt_label_set_text(homelab[2], aaatitle[SystemSetting.langue][1]);
	gt_label_set_text(homelab[3], aaatitle[SystemSetting.langue][2]);
	gt_label_set_text(homelab[4], aaatitle[SystemSetting.langue][3]);
	gt_label_set_text(homelab[1], aaatitle[SystemSetting.langue][4]);
	sprintf(buffer,"%s",LanguageTitle[temp]);
	not_first_start_write_history_info(EA_Amend,Ev_langue,buffer);

	gt_disp_stack_go_back(1);
}

static void Select_English(gt_event_st * e){
	temp = 1;
}

static void Select_Chinese(gt_event_st * e){

	temp = 0;
}

static void Select_Spanish(gt_event_st * e){

	temp = 2;
}

static void Select_Chinese2(gt_event_st * e){

	temp = 3;
}

static void Select_Portuguese(gt_event_st * e){

	temp = 4;
}



gt_obj_st * gt_init_SystemLanguageSetting(void)
{
	SystemLanguageSetting =  gt_obj_create(NULL);
	my_set_obj_title(SystemLanguageSetting,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemLanguageSetting, gt_color_hex(0x000000));
	 
	
	/** img1 */
	img1 = gt_img_create(SystemLanguageSetting);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn1 */
	btn1 = gt_btn_create(SystemLanguageSetting);
	gt_obj_set_pos(btn1, 399, 264);
	gt_obj_set_size(btn1, 75, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** group1 */
	group1 = gt_group_create(SystemLanguageSetting);
	gt_obj_set_pos(group1, 311, 164);
	gt_obj_set_size(group1, 2, 2);
	gt_obj_set_opa(group1, GT_OPA_0);


	/** radio3 */
	radio3 = gt_radio_create(group1);
	gt_obj_set_pos(radio3, 80, 140);
	gt_obj_set_size(radio3, 150, 40);
	gt_radio_set_font_color(radio3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio3, 24);
	gt_radio_set_font_family_en(radio3, 33);
	gt_radio_set_text(radio3, LanguageTitle[2]);
	gt_radio_set_font_point_offset(radio3, 10, 0);
	gt_obj_add_event_cb(radio3, Select_Spanish, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** radio1 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 80, 75);
	gt_obj_set_size(radio1, 150, 40);
	gt_radio_set_font_color(radio1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio1, 24);
	gt_radio_set_font_family_cn(radio1, 20);
	gt_radio_set_text(radio1,LanguageTitle[0]);
	gt_radio_set_selected(radio1);
	gt_radio_set_font_point_offset(radio1, 10, 0);
	gt_obj_add_event_cb(radio1, Select_Chinese, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** radio2 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 250, 75);
	gt_obj_set_size(radio2, 150, 40);
	gt_radio_set_font_color(radio2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio2, 24);
	gt_radio_set_font_family_en(radio2, 33);
	gt_radio_set_text(radio2,LanguageTitle[1]);
	gt_radio_set_font_point_offset(radio2, 10, 0);
	gt_obj_add_event_cb(radio2, Select_English, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** radio4 */
	radio4 = gt_radio_create(group1);
	gt_obj_set_pos(radio4, 250, 140);
	gt_obj_set_size(radio4, 150, 40);
	gt_radio_set_font_color(radio4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio4, 24);
	gt_radio_set_font_family_cn(radio4, 20);
	gt_radio_set_text(radio4, LanguageTitle[3]);
	gt_radio_set_font_point_offset(radio4, 10, 0);
	gt_obj_add_event_cb(radio4, Select_Chinese2, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** radio5 */
	radio5 = gt_radio_create(group1);
	gt_obj_set_pos(radio5, 80, 205);
	gt_obj_set_size(radio5, 150, 40);
	gt_radio_set_font_color(radio5, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio5, 24);
	gt_radio_set_font_family_en(radio5, 33);
	gt_radio_set_font_family_fl(radio5, 50);
	gt_radio_set_text(radio5, LanguageTitle[4]);
	gt_radio_set_font_point_offset(radio5, 10, 0);
	gt_obj_add_event_cb(radio5, Select_Portuguese, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	if(SystemSetting.langue == 0)
		gt_radio_set_selected(radio1);
	else if(SystemSetting.langue == 1)
		gt_radio_set_selected(radio2);
	else if(SystemSetting.langue == 2)
		gt_radio_set_selected(radio3);
	else if(SystemSetting.langue == 3)
		gt_radio_set_selected(radio4);
	else if(SystemSetting.langue == 4)
		gt_radio_set_selected(radio5);


	return SystemLanguageSetting;
}

