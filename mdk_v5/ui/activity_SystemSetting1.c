#include "ui.h"
#include "infusion.h"
#include "headbar_view.h"

/** SystemSetting1 */
gt_obj_st * SystemSetting1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * inputNum1 = NULL;
static gt_obj_st * inputNum2 = NULL;
static double voice =0 ;
static char buffer[30];

static const char title[5][5][50]={
	"系统设定",
	"音量",
	"亮度",
	"床号",
	"主菜单",

	"System",
	"Sound",
	"Brightness",
	"Bed Number",
	"Main Menu",

	"Sistema",
	"Sonido",
	"Brillo",
	"Número de Cama",
	"Menú Principal",

	"系統設定",
	"音量",
	"亮度",
	"床號",
	"主菜單",

	"Sistema",
	"Som",
	"Brilho",
	"Numero do leito",
	"Menu principal"

};




static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][4]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void UpPage(gt_event_st * e) {


	gt_disp_stack_load_scr_anim(GT_SCR_ID_31, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}
   
static void NextPage(gt_event_st * e) {

	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_31, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

}

static void btn1_0_cb(gt_event_st * e) {
	//在这里调节扬声器音量
	double temp =0 ;
	//Send key.wav to flash
	gt_input_number_decrease(inputNum1);
	voice =  gt_input_number_get_value(inputNum1);

	WT588F_Send_Data(0xE0 + (uint32_t)voice*2-1);
	delay_ms(8);
	WT588F_Send_Data(0x04); //Play the key.wav

	//write to flash
	SystemSetting.Volume = (short)voice;
	sprintf(buffer,"%d",SystemSetting.Volume);
	not_first_start_write_history_info(EA_Set,Ev_SoundSize,buffer);
	WriteSystemSettingMessageToFlash();
}

static void btn2_0_cb(gt_event_st * e) {
	//在这里调节扬声器音量
	double temp =0 ;
	gt_input_number_increase(inputNum1);
	voice =  gt_input_number_get_value(inputNum1);
	WT588F_Send_Data(0xE0 + (uint32_t)voice*2-1);
	delay_ms(8);
	WT588F_Send_Data(0x04); //Play the key.wav

	//write to flash
	SystemSetting.Volume = (short)voice;
	sprintf(buffer,"%d",SystemSetting.Volume);
	not_first_start_write_history_info(EA_Set,Ev_SoundSize,buffer);
	WriteSystemSettingMessageToFlash();
}


static void btn3_0_cb(gt_event_st * e) {
	//调节亮度
	double temp = 0 , temp2 = 0;
	gt_input_number_increase(inputNum2);
	temp = gt_input_number_get_value(inputNum2);
	temp2 = tmr_period_value_get(TMR13); //Get the current period value
	tmr_channel_value_set(TMR13, TMR_SELECT_CHANNEL_1, (uint32_t)(100+50 * temp -1));   //Divide 50% into eight parts
	//write to flash
	SystemSetting.Light = (uint8_t)temp;
	WriteSystemSettingMessageToFlash();
	sprintf(buffer,"%d",SystemSetting.Light);
	not_first_start_write_history_info(EA_Set,Ev_Setlightsize,buffer);
}


static void btn4_0_cb(gt_event_st * e) {
	//调节亮度
	double temp_sub = 0 , temp2_sub = 0;
	gt_input_number_decrease(inputNum2);

	temp_sub = gt_input_number_get_value(inputNum2);
	temp2_sub = tmr_period_value_get(TMR13); //Get the current period value
	tmr_channel_value_set(TMR13, TMR_SELECT_CHANNEL_1, (uint32_t)(100+50 * temp_sub -1));   //Divide 50% into eight parts
	//write to flash
	SystemSetting.Light = (uint8_t)temp_sub;
	WriteSystemSettingMessageToFlash();
	sprintf(buffer,"%d",SystemSetting.Light);
	not_first_start_write_history_info(EA_Set,Ev_Setlightsize,buffer);
	
}

static void bedchange(gt_event_st * e) {
	strcpy(keyboardi.title,title[SystemSetting.langue][3]);
	keyboardi.data = &SystemSetting.BedNumber;
	keyboardi.id=10;
	limit.lowerlimit=1;
	limit.toplimit=999;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void EventUpdata(gt_event_st * e)
{

	
	if(atoi(e->param) == 10)  
	{
		sprintf(buffer,"%d",SystemSetting.BedNumber);
		gt_label_set_text(lab7, buffer);	
		not_first_start_write_history_info(EA_Amend,Ev_BedNum,buffer);
		WriteSystemSettingMessageToFlash();
		
	}
}

gt_obj_st * gt_init_SystemSetting1(void)
{
	

	printf("SystemSetting.Light = %d\n",SystemSetting.Light);
	
	SystemSetting1 =  gt_obj_create(NULL);
	my_set_obj_title(SystemSetting1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemSetting1, gt_color_hex(0x000000));
	gt_obj_add_event_cb(SystemSetting1,EventUpdata,MY_EVENT_UPDATA,NULL);
	 


	/** lab2 */
	lab2 = gt_label_create(SystemSetting1);
	gt_obj_set_pos(lab2, 75, 70);
	gt_obj_set_size(lab2, 193, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** img1 */
	img1 = gt_img_create(SystemSetting1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(SystemSetting1);
	gt_obj_set_pos(svg1, 413, 73);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(SystemSetting1);
	gt_obj_set_pos(svg2, 413, 210);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, NextPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(SystemSetting1);
	gt_obj_set_pos(lab8, 407, 147);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "1/2");


	/** light */
	lab3 = gt_label_create(SystemSetting1);
	gt_obj_set_pos(lab3, 75, 145);
	gt_obj_set_size(lab3, 193, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][2]);


	/** bednum */
	lab4 = gt_label_create(SystemSetting1);
	gt_obj_set_pos(lab4, 75, 225);
	gt_obj_set_size(lab4, 200, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][3]);
	

	/** rect2 */
	rect2 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 200, 60);
	gt_obj_set_opa(rect2, GT_OPA_40);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect2, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);


	/** btn1 */
	btn1 = gt_btn_create(SystemSetting1);
	gt_obj_set_pos(btn1, 225, 65);
	gt_obj_set_size(btn1, 50, 60);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "-");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn2 */
	btn2 = gt_btn_create(SystemSetting1);
	gt_obj_set_pos(btn2, 75, 65);
	gt_obj_set_size(btn2, 50, 60);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_en(btn2, 33);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "+");
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn2, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2, 4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, btn2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** rect3 */
	rect3 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect3, 275, 65);
	gt_obj_set_size(rect3, 125, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);


	/** rect4 */
	rect4 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect4, 75, 145);
	gt_obj_set_size(rect4, 200, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);


	/** btn3 */
	btn3 = gt_btn_create(SystemSetting1);
	gt_obj_set_pos(btn3, 75, 145);
	gt_obj_set_size(btn3, 50, 60);
	gt_btn_set_font_color(btn3, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn3, 24);
	gt_btn_set_font_family_en(btn3, 33);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "+");
	gt_btn_set_color_background(btn3, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn3, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn3, 4);
	gt_btn_set_radius(btn3, 4);
	gt_obj_add_event_cb(btn3, btn3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn4 */
	btn4 = gt_btn_create(SystemSetting1);
	gt_obj_set_pos(btn4, 225, 145);
	gt_obj_set_size(btn4, 50, 60);
	gt_btn_set_font_color(btn4, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn4, 24);
	gt_btn_set_font_family_en(btn4, 33);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn4, "-");
	gt_btn_set_color_background(btn4, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn4, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn4, 4);
	gt_btn_set_radius(btn4, 4);
	gt_obj_add_event_cb(btn4, btn4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	rect5 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect5, 275, 145);
	gt_obj_set_size(rect5, 125, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);


	/** rect6 */
	rect6 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect6, 75, 225);
	gt_obj_set_size(rect6, 200, 60);
	gt_obj_set_opa(rect6, GT_OPA_61);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, bedchange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	lab7 = gt_label_create(SystemSetting1);
	gt_obj_set_pos(lab7, 305, 225);
	gt_obj_set_size(lab7, 60, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",SystemSetting.BedNumber);
	gt_label_set_text(lab7, buffer);


	/** rect7 */
	rect7 = gt_rect_create(SystemSetting1);
	gt_obj_set_pos(rect7, 275, 225);
	gt_obj_set_size(rect7, 125, 60);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, bedchange, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** inputNum1 */
	inputNum1 = gt_input_number_create(SystemSetting1);
	gt_obj_set_pos(inputNum1, 300, 65);
	gt_obj_set_size(inputNum1, 60, 60);
	gt_input_number_set_font_color(inputNum1, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum1, 24);
	gt_input_number_set_font_family_en(inputNum1, 33);
	gt_input_number_set_font_align(inputNum1, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum1, SystemSetting.Volume);
	gt_input_number_set_step(inputNum1, 1);
	gt_input_number_set_min(inputNum1, 1);
	gt_input_number_set_max(inputNum1, 8);
	gt_input_number_set_fill_zero_front(inputNum1, false);
	gt_input_number_set_display_integer_length(inputNum1, 2);
	gt_input_number_set_display_decimal_length(inputNum1, 0);


	/** inputNum2 */
	inputNum2 = gt_input_number_create(SystemSetting1);
	gt_obj_set_pos(inputNum2, 300, 145);
	gt_obj_set_size(inputNum2, 60, 60);
	gt_input_number_set_font_color(inputNum2, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum2, 24);
	gt_input_number_set_font_family_en(inputNum2, 33);
	gt_input_number_set_font_align(inputNum2, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum2, SystemSetting.Light);
	gt_input_number_set_step(inputNum2, 1);
	gt_input_number_set_min(inputNum2, 1);
	gt_input_number_set_max(inputNum2, 8);
	gt_input_number_set_fill_zero_front(inputNum2, false);
	gt_input_number_set_display_integer_length(inputNum2, 2);
	gt_input_number_set_display_decimal_length(inputNum2, 0);

	return SystemSetting1;
}

