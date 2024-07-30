#include "ui.h"
#include "library_drug.h"


extern _Bool enterkey;
extern char tubename[30];
extern char drugname[50];

/** Screen_KeyBoard_Soft */
gt_obj_st * Screen_KeyBoard_Soft = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * btn5 = NULL;
static gt_obj_st * btn6 = NULL;
static gt_obj_st * btn7 = NULL;
static gt_obj_st * btn8 = NULL;
static gt_obj_st * btn9 = NULL;
static gt_obj_st * btn10 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * input1 = NULL;
static gt_obj_st * btn11 = NULL;
static gt_obj_st * btn12 = NULL;
static gt_obj_st * btn13 = NULL;
static gt_obj_st * btn14 = NULL;
static gt_obj_st * btn15 = NULL;
static gt_obj_st * btn16 = NULL;
static gt_obj_st * btn17 = NULL;
static gt_obj_st * btn18 = NULL;
static gt_obj_st * btn19 = NULL;
static gt_obj_st * btn20 = NULL;
static gt_obj_st * btn21 = NULL;
static gt_obj_st * btn22 = NULL;
static gt_obj_st * btn23 = NULL;
static gt_obj_st * btn24 = NULL;
static gt_obj_st * btn25 = NULL;
static gt_obj_st * btn26 = NULL;
static gt_obj_st * btn27 = NULL;
static gt_obj_st * btn28 = NULL;
static gt_obj_st * btn29 = NULL;
static gt_obj_st * btn30 = NULL;
static gt_obj_st * btn31 = NULL;
static gt_obj_st * btn32 = NULL;
static gt_obj_st * btn33 = NULL;
static gt_obj_st * btn34 = NULL;
static gt_obj_st * btn35 = NULL;
static gt_obj_st * btn36 = NULL;
static gt_obj_st * btn37 = NULL;
static gt_obj_st * btn38 = NULL;
static gt_obj_st * btn39 = NULL;

/* back */
static void Back(gt_event_st * e) {

	headvisiable(1);
	enterkey = false;
	gt_disp_stack_go_back(1);
	
}



//delete one
static void DeleteOne(gt_event_st * e) {
	gt_input_del_value(input1);
}



// confirm
static void Confirm(gt_event_st * e) {
	if(my_judge_obj_exists(GT_SCR_ID_47) && keyboards.id == 1) //修改序列号
	{
		strcpy(SystemSetting.Version.SerialNumber,gt_input_get_value(input1));
		gt_event_send(screen_Maintenance_Two,MY_EVENT_UPDATA,"1");
		enterkey = false;
		headvisiable(1);
		WriteSystemSettingMessageToFlash();
		gt_disp_stack_load_scr_anim(GT_SCR_ID_47, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
	}
	else if(my_judge_obj_exists(GT_SCR_ID_43) && keyboards.id == 2) //增加输液器品牌
	{	
		strcpy(tubename,gt_input_get_value(input1));
		gt_event_send(screen_Maintenance_Normal_Three,MY_EVENT_UPDATA,"2");
		enterkey = false;
		headvisiable(1);
		gt_disp_stack_load_scr_anim(GT_SCR_ID_43, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
	}
	else if(my_judge_obj_exists(GT_SCR_ID_44) && keyboards.id == 3) //增加药物名
	{	
		strcpy(drugname,gt_input_get_value(input1));
		gt_event_send(screen_Maintenance_Normal_Four,MY_EVENT_UPDATA,"3");
		enterkey = false;
		headvisiable(1);
		gt_disp_stack_load_scr_anim(GT_SCR_ID_44, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
	}
	else
	{
		
		enterkey = false;
		headvisiable(1);
		gt_disp_stack_go_back(1);
	}

	//memset(EditBuF, 0, sizeof(EditBuF));
}



static void Input(gt_event_st * e) {

	gt_input_append_value(input1, e->user_data);

}



gt_obj_st * gt_init_Screen_KeyBoard_Soft(void)
{
	Screen_KeyBoard_Soft = gt_obj_create(NULL);
	gt_screen_set_bgcolor(Screen_KeyBoard_Soft, gt_color_hex(0x000000));
    char temp[50];
	enterkey = true;
	headvisiable(0);

    /** lab1 */
	lab1 = gt_label_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(lab1, 0, 0);
	gt_obj_set_size(lab1, 200, 50);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT_MID);
    sprintf(temp,"%s",keyboards.title);
	gt_label_set_text(lab1,temp);


	/** btn1 */
	btn1 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn1, 192, 117);
	gt_obj_set_size(btn1, 48, 67);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "T");
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
    gt_obj_add_event_cb(btn1, Input, GT_EVENT_TYPE_INPUT_RELEASED, "T");

	/** btn2 */
	btn2 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn2, 0, 117);
	gt_obj_set_size(btn2, 48, 67);
	gt_btn_set_font_color(btn2, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn2, 16);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "Q");
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn2, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2, 4);
	gt_btn_set_radius(btn2, 4);
    gt_obj_add_event_cb(btn2, Input, GT_EVENT_TYPE_INPUT_RELEASED, "Q");

	/** btn3 */
	btn3 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn3, 48, 117);
	gt_obj_set_size(btn3, 48, 67);
	gt_btn_set_font_color(btn3, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn3, 16);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "W");
	gt_btn_set_color_background(btn3, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn3, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn3, 4);
	gt_btn_set_radius(btn3, 4);
    gt_obj_add_event_cb(btn3, Input, GT_EVENT_TYPE_INPUT_RELEASED, "W");

	/** btn4 */
	btn4 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn4, 336, 117);
	gt_obj_set_size(btn4, 48, 67);
	gt_btn_set_font_color(btn4, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn4, 16);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn4, "I");
	gt_btn_set_color_background(btn4, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn4, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn4, 4);
	gt_btn_set_radius(btn4, 4);
    gt_obj_add_event_cb(btn4, Input, GT_EVENT_TYPE_INPUT_RELEASED, "I");

	/** btn5 */
	btn5 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn5, 288, 117);
	gt_obj_set_size(btn5, 48, 67);
	gt_btn_set_font_color(btn5, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn5, 16);
	gt_btn_set_font_align(btn5, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn5, "U");
	gt_btn_set_color_background(btn5, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn5, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn5, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn5, 4);
	gt_btn_set_radius(btn5, 4);
    gt_obj_add_event_cb(btn5, Input, GT_EVENT_TYPE_INPUT_RELEASED, "U");

	/** btn6 */
	btn6 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn6, 96, 117);
	gt_obj_set_size(btn6, 48, 67);
	gt_btn_set_font_color(btn6, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn6, 16);
	gt_btn_set_font_align(btn6, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn6, "E");
	gt_btn_set_color_background(btn6, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn6, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn6, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn6, 4);
	gt_btn_set_radius(btn6, 4);
    gt_obj_add_event_cb(btn6, Input, GT_EVENT_TYPE_INPUT_RELEASED, "E");

	/** btn7 */
	btn7 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn7, 144, 117);
	gt_obj_set_size(btn7, 48, 67);
	gt_btn_set_font_color(btn7, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn7, 16);
	gt_btn_set_font_align(btn7, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn7, "R");
	gt_btn_set_color_background(btn7, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn7, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn7, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn7, 4);
	gt_btn_set_radius(btn7, 4);
    gt_obj_add_event_cb(btn7, Input, GT_EVENT_TYPE_INPUT_RELEASED, "R");

	/** btn8 */
	btn8 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn8, 240, 117);
	gt_obj_set_size(btn8, 48, 67);
	gt_btn_set_font_color(btn8, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn8, 16);
	gt_btn_set_font_align(btn8, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn8, "Y");
	gt_btn_set_color_background(btn8, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn8, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn8, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn8, 4);
	gt_btn_set_radius(btn8, 4);
    gt_obj_add_event_cb(btn8, Input, GT_EVENT_TYPE_INPUT_RELEASED, "Y");

	/** btn9 */
	btn9 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn9, 432, 117);
	gt_obj_set_size(btn9, 48, 67);
	gt_btn_set_font_color(btn9, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn9, 16);
	gt_btn_set_font_align(btn9, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn9, "P");
	gt_btn_set_color_background(btn9, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn9, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn9, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn9, 4);
	gt_btn_set_radius(btn9, 4);
    gt_obj_add_event_cb(btn9, Input, GT_EVENT_TYPE_INPUT_RELEASED, "P");

	/** btn10 */
	btn10 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn10, 384, 117);
	gt_obj_set_size(btn10, 48, 67);
	gt_btn_set_font_color(btn10, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn10, 16);
	gt_btn_set_font_align(btn10, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn10, "O");
	gt_btn_set_color_background(btn10, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn10, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn10, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn10, 4);
	gt_btn_set_radius(btn10, 4);
    gt_obj_add_event_cb(btn10, Input, GT_EVENT_TYPE_INPUT_RELEASED, "O");


	/** rect1 */
	rect1 = gt_rect_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(rect1, 0, 0);
	gt_obj_set_size(rect1, 200, 50);
	gt_obj_set_opa(rect1, GT_OPA_48);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x778899));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 4);


	/** input1 */
	input1 = gt_input_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(input1, 200, 0);
	gt_obj_set_size(input1, 180, 50);
	gt_input_set_font_color(input1, gt_color_hex(0xffffff));
	gt_input_set_font_size(input1, 24);
	gt_input_set_font_family_cn(input1, 18);
	gt_input_set_font_family_en(input1, 33);
	gt_input_set_font_family_fl(input1, 50);
	gt_input_set_font_align(input1, GT_ALIGN_LEFT_MID);
	gt_input_set_placeholder(input1, NULL);
	gt_input_set_bg_color(input1, gt_color_hex(0x000000));


	/** btn11 */
	btn11 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn11, 0, 50);
	gt_obj_set_size(btn11, 48, 67);
	gt_btn_set_font_color(btn11, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn11, 16);
	gt_btn_set_font_align(btn11, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn11, "0");
	gt_btn_set_color_background(btn11, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn11, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn11, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn11, 4);
	gt_btn_set_radius(btn11, 4);
	gt_obj_add_event_cb(btn11, Input, GT_EVENT_TYPE_INPUT_RELEASED, "0");


	/** btn12 */
	btn12 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn12, 288, 50);
	gt_obj_set_size(btn12, 48, 67);
	gt_btn_set_font_color(btn12, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn12, 16);
	gt_btn_set_font_align(btn12, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn12, "6");
	gt_btn_set_color_background(btn12, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn12, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn12, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn12, 4);
	gt_btn_set_radius(btn12, 4);
    gt_obj_add_event_cb(btn12, Input, GT_EVENT_TYPE_INPUT_RELEASED, "6");

	/** btn13 */
	btn13 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn13, 144, 50);
	gt_obj_set_size(btn13, 48, 67);
	gt_btn_set_font_color(btn13, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn13, 16);
	gt_btn_set_font_align(btn13, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn13, "3");
	gt_btn_set_color_background(btn13, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn13, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn13, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn13, 4);
	gt_btn_set_radius(btn13, 4);
    gt_obj_add_event_cb(btn13, Input, GT_EVENT_TYPE_INPUT_RELEASED, "3");

	/** btn14 */
	btn14 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn14, 240, 50);
	gt_obj_set_size(btn14, 48, 67);
	gt_btn_set_font_color(btn14, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn14, 16);
	gt_btn_set_font_align(btn14, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn14, "5");
	gt_btn_set_color_background(btn14, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn14, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn14, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn14, 4);
	gt_btn_set_radius(btn14, 4);
    gt_obj_add_event_cb(btn14, Input, GT_EVENT_TYPE_INPUT_RELEASED, "5");

	/** btn15 */
	btn15 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn15, 336, 50);
	gt_obj_set_size(btn15, 48, 67);
	gt_btn_set_font_color(btn15, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn15, 16);
	gt_btn_set_font_align(btn15, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn15, "7");
	gt_btn_set_color_background(btn15, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn15, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn15, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn15, 4);
	gt_btn_set_radius(btn15, 4);
    gt_obj_add_event_cb(btn15, Input, GT_EVENT_TYPE_INPUT_RELEASED, "7");

	/** btn16 */
	btn16 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn16, 432, 50);
	gt_obj_set_size(btn16, 48, 67);
	gt_btn_set_font_color(btn16, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn16, 16);
	gt_btn_set_font_align(btn16, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn16, "9");
	gt_btn_set_color_background(btn16, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn16, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn16, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn16, 4);
	gt_btn_set_radius(btn16, 4);
    gt_obj_add_event_cb(btn16, Input, GT_EVENT_TYPE_INPUT_RELEASED, "9");

	/** btn17 */
	btn17 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn17, 96, 50);
	gt_obj_set_size(btn17, 48, 67);
	gt_btn_set_font_color(btn17, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn17, 16);
	gt_btn_set_font_align(btn17, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn17, "2");
	gt_btn_set_color_background(btn17, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn17, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn17, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn17, 4);
	gt_btn_set_radius(btn17, 4);
    gt_obj_add_event_cb(btn17, Input, GT_EVENT_TYPE_INPUT_RELEASED, "2");

	/** btn18 */
	btn18 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn18, 48, 50);
	gt_obj_set_size(btn18, 48, 67);
	gt_btn_set_font_color(btn18, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn18, 16);
	gt_btn_set_font_align(btn18, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn18, "1");
	gt_btn_set_color_background(btn18, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn18, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn18, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn18, 4);
	gt_btn_set_radius(btn18, 4);
    gt_obj_add_event_cb(btn18, Input, GT_EVENT_TYPE_INPUT_RELEASED, "1");

	/** btn19 */
	btn19 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn19, 192, 50);
	gt_obj_set_size(btn19, 48, 67);
	gt_btn_set_font_color(btn19, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn19, 16);
	gt_btn_set_font_align(btn19, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn19, "4");
	gt_btn_set_color_background(btn19, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn19, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn19, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn19, 4);
	gt_btn_set_radius(btn19, 4);
    gt_obj_add_event_cb(btn19, Input, GT_EVENT_TYPE_INPUT_RELEASED, "4");

	/** btn20 */
	btn20 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn20, 384, 50);
	gt_obj_set_size(btn20, 48, 67);
	gt_btn_set_font_color(btn20, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn20, 16);
	gt_btn_set_font_align(btn20, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn20, "8");
	gt_btn_set_color_background(btn20, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn20, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn20, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn20, 4);
	gt_btn_set_radius(btn20, 4);
    gt_obj_add_event_cb(btn20, Input, GT_EVENT_TYPE_INPUT_RELEASED, "8");

	/** btn21 */
	btn21 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn21, 81, 184);
	gt_obj_set_size(btn21, 48, 67);
	gt_btn_set_font_color(btn21, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn21, 16);
	gt_btn_set_font_align(btn21, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn21, "S");
	gt_btn_set_color_background(btn21, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn21, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn21, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn21, 4);
	gt_btn_set_radius(btn21, 4);
    gt_obj_add_event_cb(btn21, Input, GT_EVENT_TYPE_INPUT_RELEASED, "S");

	/** btn22 */
	btn22 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn22, 33, 184);
	gt_obj_set_size(btn22, 48, 67);
	gt_btn_set_font_color(btn22, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn22, 16);
	gt_btn_set_font_align(btn22, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn22, "A");
	gt_btn_set_color_background(btn22, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn22, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn22, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn22, 4);
	gt_btn_set_radius(btn22, 4);
    gt_obj_add_event_cb(btn22, Input, GT_EVENT_TYPE_INPUT_RELEASED, "A");

	/** btn23 */
	btn23 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn23, 129, 184);
	gt_obj_set_size(btn23, 48, 67);
	gt_btn_set_font_color(btn23, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn23, 16);
	gt_btn_set_font_align(btn23, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn23, "D");
	gt_btn_set_color_background(btn23, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn23, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn23, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn23, 4);
	gt_btn_set_radius(btn23, 4);
    gt_obj_add_event_cb(btn23, Input, GT_EVENT_TYPE_INPUT_RELEASED, "D");

	/** btn24 */
	btn24 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn24, 177, 184);
	gt_obj_set_size(btn24, 48, 67);
	gt_btn_set_font_color(btn24, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn24, 16);
	gt_btn_set_font_align(btn24, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn24, "F");
	gt_btn_set_color_background(btn24, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn24, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn24, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn24, 4);
	gt_btn_set_radius(btn24, 4);
    gt_obj_add_event_cb(btn24, Input, GT_EVENT_TYPE_INPUT_RELEASED, "F");

	/** btn25 */
	btn25 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn25, 225, 184);
	gt_obj_set_size(btn25, 48, 67);
	gt_btn_set_font_color(btn25, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn25, 16);
	gt_btn_set_font_align(btn25, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn25, "G");
	gt_btn_set_color_background(btn25, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn25, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn25, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn25, 4);
	gt_btn_set_radius(btn25, 4);
    gt_obj_add_event_cb(btn25, Input, GT_EVENT_TYPE_INPUT_RELEASED, "G");

	/** btn26 */
	btn26 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn26, 369, 184);
	gt_obj_set_size(btn26, 48, 67);
	gt_btn_set_font_color(btn26, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn26, 16);
	gt_btn_set_font_align(btn26, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn26, "K");
	gt_btn_set_color_background(btn26, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn26, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn26, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn26, 4);
	gt_btn_set_radius(btn26, 4);
    gt_obj_add_event_cb(btn26, Input, GT_EVENT_TYPE_INPUT_RELEASED, "K");

	/** btn27 */
	btn27 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn27, 321, 184);
	gt_obj_set_size(btn27, 48, 67);
	gt_btn_set_font_color(btn27, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn27, 16);
	gt_btn_set_font_align(btn27, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn27, "J");
	gt_btn_set_color_background(btn27, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn27, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn27, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn27, 4);
	gt_btn_set_radius(btn27, 4);
    gt_obj_add_event_cb(btn27, Input, GT_EVENT_TYPE_INPUT_RELEASED, "J");

	/** btn28 */
	btn28 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn28, 273, 184);
	gt_obj_set_size(btn28, 48, 67);
	gt_btn_set_font_color(btn28, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn28, 16);
	gt_btn_set_font_align(btn28, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn28, "H");
	gt_btn_set_color_background(btn28, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn28, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn28, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn28, 4);
	gt_btn_set_radius(btn28, 4);
    gt_obj_add_event_cb(btn28, Input, GT_EVENT_TYPE_INPUT_RELEASED, "H");

	/** btn29 */
	btn29 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn29, 417, 183);
	gt_obj_set_size(btn29, 48, 67);
	gt_btn_set_font_color(btn29, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn29, 16);
	gt_btn_set_font_align(btn29, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn29, "L");
	gt_btn_set_color_background(btn29, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn29, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn29, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn29, 4);
	gt_btn_set_radius(btn29, 4);
    gt_obj_add_event_cb(btn29, Input, GT_EVENT_TYPE_INPUT_RELEASED, "L");

	/** btn30 */
	btn30 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn30, 72, 251);
	gt_obj_set_size(btn30, 48, 67);
	gt_btn_set_font_color(btn30, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn30, 16);
	gt_btn_set_font_align(btn30, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn30, "Z");
	gt_btn_set_color_background(btn30, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn30, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn30, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn30, 4);
	gt_btn_set_radius(btn30, 4);
    gt_obj_add_event_cb(btn30, Input, GT_EVENT_TYPE_INPUT_RELEASED, "Z");

	/** btn31 */
	btn31 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn31, 120, 251);
	gt_obj_set_size(btn31, 48, 67);
	gt_btn_set_font_color(btn31, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn31, 16);
	gt_btn_set_font_align(btn31, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn31, "X");
	gt_btn_set_color_background(btn31, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn31, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn31, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn31, 4);
	gt_btn_set_radius(btn31, 4);
    gt_obj_add_event_cb(btn31, Input, GT_EVENT_TYPE_INPUT_RELEASED, "X");

	/** btn32 */
	btn32 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn32, 216, 251);
	gt_obj_set_size(btn32, 48, 67);
	gt_btn_set_font_color(btn32, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn32, 16);
	gt_btn_set_font_align(btn32, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn32, "V");
	gt_btn_set_color_background(btn32, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn32, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn32, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn32, 4);
	gt_btn_set_radius(btn32, 4);
    gt_obj_add_event_cb(btn32, Input, GT_EVENT_TYPE_INPUT_RELEASED, "V");

	/** btn33 */
	btn33 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn33, 264, 251);
	gt_obj_set_size(btn33, 48, 67);
	gt_btn_set_font_color(btn33, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn33, 16);
	gt_btn_set_font_align(btn33, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn33, "B");
	gt_btn_set_color_background(btn33, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn33, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn33, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn33, 4);
	gt_btn_set_radius(btn33, 4);
    gt_obj_add_event_cb(btn33, Input, GT_EVENT_TYPE_INPUT_RELEASED, "B");

	/** btn34 */
	btn34 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn34, 360, 251);
	gt_obj_set_size(btn34, 48, 67);
	gt_btn_set_font_color(btn34, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn34, 16);
	gt_btn_set_font_align(btn34, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn34, "M");
	gt_btn_set_color_background(btn34, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn34, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn34, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn34, 4);
	gt_btn_set_radius(btn34, 4);
    gt_obj_add_event_cb(btn34, Input, GT_EVENT_TYPE_INPUT_RELEASED, "M");

	/** btn35 */
	btn35 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn35, 168, 251);
	gt_obj_set_size(btn35, 48, 67);
	gt_btn_set_font_color(btn35, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn35, 16);
	gt_btn_set_font_align(btn35, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn35, "C");
	gt_btn_set_color_background(btn35, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn35, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn35, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn35, 4);
	gt_btn_set_radius(btn35, 4);
    gt_obj_add_event_cb(btn35, Input, GT_EVENT_TYPE_INPUT_RELEASED, "C");

	/** btn36 */
	btn36 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn36, 312, 251);
	gt_obj_set_size(btn36, 48, 67);
	gt_btn_set_font_color(btn36, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn36, 16);
	gt_btn_set_font_align(btn36, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn36, "N");
	gt_btn_set_color_background(btn36, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn36, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn36, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn36, 4);
	gt_btn_set_radius(btn36, 4);
    gt_obj_add_event_cb(btn36, Input, GT_EVENT_TYPE_INPUT_RELEASED, "N");

	/** btn37 */
	btn37 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn37, 380, 0);
	gt_obj_set_size(btn37, 100, 50);
	gt_btn_set_font_color(btn37, gt_color_hex(0x0080ff));
	gt_btn_set_font_size(btn37, 16);
	gt_btn_set_font_align(btn37, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn37, "OK");
	gt_btn_set_color_background(btn37, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn37, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn37, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn37, 4);
	gt_btn_set_radius(btn37, 4);
    gt_obj_add_event_cb(btn37, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** btn38 */
	btn38 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn38, 0, 251);
	gt_obj_set_size(btn38, 72, 67);
	gt_btn_set_font_color(btn38, gt_color_hex(0x0080ff));
	gt_btn_set_font_size(btn38, 16);
	gt_btn_set_font_align(btn38, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn38, "Back");
	gt_btn_set_color_background(btn38, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn38, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn38, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn38, 4);
	gt_btn_set_radius(btn38, 4);
   gt_obj_add_event_cb(btn38, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** btn39 */
	btn39 = gt_btn_create(Screen_KeyBoard_Soft);
	gt_obj_set_pos(btn39, 408, 251);
	gt_obj_set_size(btn39, 72, 67);
	gt_btn_set_font_color(btn39, gt_color_hex(0x0080ff));
	gt_btn_set_font_size(btn39, 24);
	gt_btn_set_font_family_cn(btn39, 20);
	gt_btn_set_font_align(btn39, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn39, "<--");
	gt_btn_set_color_background(btn39, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn39, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn39, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn39, 4);
	gt_btn_set_radius(btn39, 4);
    gt_obj_add_event_cb(btn39, DeleteOne, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	return Screen_KeyBoard_Soft;
}

