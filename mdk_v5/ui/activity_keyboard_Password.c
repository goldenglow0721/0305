#include "ui.h"
#include "infusion.h"

#define PassWord1 8888
#define PassWord2 6686

static int num; //record the number that you inputed

extern _Bool enterkey;
static const char title[5][2][40]={
		"请输入密码",
		"密码错误",

		"Please input password",
		"Password error",

		"Ingrese la contraseña",
		"Error de Contraseña",

		"請輸入密碼",
		"密碼錯誤",

		"Favor inserir senha",
		"Senha incorreta"

};



/** Screen_KeyBoard_Int */
gt_obj_st * Screen_KeyBoard_PassWord = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * rect11 = NULL;
static gt_obj_st * rect12 = NULL;
static gt_obj_st * rect13 = NULL;
static gt_obj_st * rect14 = NULL;
static gt_obj_st * rect15 = NULL;
static gt_obj_st * rect16 = NULL;
static gt_obj_st * input1 = NULL;

/* back */
static void Back(gt_event_st * e) {
	//passmessage->screenaddress;
	enterkey = false;
	headvisiable(1);
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


// confirm
static void Confirm(gt_event_st * e) {
	#if 1
	int temp;
	gt_obj_st * target_scr;
	temp = atoi(gt_input_get_value(input1));
	
	if(num != 4)
	{
		num=0;
		gt_input_set_value(input1, NULL);
		gt_label_set_text(lab1, title[SystemSetting.langue][1]);	
	}
	else
	{
		if(temp == PassWord1)
		{
			//8888
			enterkey = false;
			headvisiable(1);
			gt_disp_stack_load_scr_anim(GT_SCR_ID_41, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
		}
		else if(temp == PassWord2)
		{
			//6686
			enterkey = false;
			headvisiable(1);
			gt_disp_stack_load_scr_anim(GT_SCR_ID_46, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);	
		}
		else
		{
			num=0;
			gt_input_set_value(input1, NULL);
			gt_label_set_text(lab1, title[SystemSetting.langue][1]);
		}
	}
	#endif
}


//input
static void InputValue(gt_event_st * e) {
	if(++num > 10)
		return ;

	gt_input_append_value(input1, e->user_data);
}

//delete one
static void DeleteOne(gt_event_st * e) {
	if(--num < 0)
		num=0;
	gt_input_del_value(input1);
}

//delete all
static void DeleteAll(gt_event_st * e) {
	num=0;
	gt_input_set_value(input1, NULL);
}


//create screen
gt_obj_st * gt_init_screen_keyBoard_PassWord()
 {
	//receive the sent message
	num=0;
	enterkey = true;
	Screen_KeyBoard_PassWord = gt_obj_create(NULL);
	gt_screen_set_bgcolor(Screen_KeyBoard_PassWord, gt_color_hex(0x004040));
	headvisiable(0);

	/** lab1 */
	lab1 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab1, 10, 4);
	gt_obj_set_size(lab1, 300, 35);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_text(lab1, title[SystemSetting.langue][0]);

	
	
	/** headbar */
	rect1 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect1, 0, 0);
	gt_obj_set_size(rect1, 480, 43);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x778899));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 4);


	/** 2 */
	lab2 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab2, 120, 76);
	gt_obj_set_size(lab2, 65, 33);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "1");


	

	/** 2 */
	lab3 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab3, 204, 74);
	gt_obj_set_size(lab3, 65, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "2");

	/** 3 */
	lab4 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab4, 285, 74);
	gt_obj_set_size(lab4, 65, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "3");

	/** 4 */
	lab5 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab5, 120, 165);
	gt_obj_set_size(lab5, 65, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "4");


	/** 5 */
	lab6 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab6, 206, 165);
	gt_obj_set_size(lab6, 65, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "5");


	/** 6 */
	lab7 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab7, 285, 165);
	gt_obj_set_size(lab7, 65, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "6");


	/** 7 */
	lab8 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab8, 120, 255);
	gt_obj_set_size(lab8, 65, 35);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "7");


	/** 8 */
	lab9 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab9, 205, 255);
	gt_obj_set_size(lab9, 65, 35);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "8");


	/** 9 */
	lab10 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab10, 285, 255);
	gt_obj_set_size(lab10, 65, 35);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "9");


	/** back */
	lab11 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab11, 23, 73);
	gt_obj_set_size(lab11, 80, 35);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "Back");


	/**  */
	lab12 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab12, 22, 164);
	gt_obj_set_size(lab12, 80, 35);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab12, "");


	/** 0 */
	lab13 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab13, 23, 255);
	gt_obj_set_size(lab13, 80, 35);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab13, "0");


	/** delete all */
	img1 = gt_img_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(img1, 382, 160);
	gt_obj_set_size(img1, 50, 44);
	gt_img_set_src(img1, "f:img_50x44_40_dismiss_.png");


	/** delete one */
	img2 = gt_img_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(img2, 380, 73);
	gt_obj_set_size(img2, 55, 35);
	gt_img_set_src(img2, "f:img_55x35_outline_battery_45.png");


	/** confirm */
	lab14 = gt_label_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(lab14, 367, 257);
	gt_obj_set_size(lab14, 80, 35);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_cn(lab14, 20);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab14, "OK");


	/** back */
	rect2 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect2, 20, 53);
	gt_obj_set_size(rect2, 85, 75);
	gt_obj_set_opa(rect2, GT_OPA_55);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** 1 */
	rect3 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect3, 120, 54);
	gt_obj_set_size(rect3, 65, 75);
	gt_obj_set_opa(rect3, GT_OPA_55);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899)); 
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "1");
	

	/** 2 */
	rect4 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect4, 204, 54);
	gt_obj_set_size(rect4, 65, 75);
	gt_obj_set_opa(rect4, GT_OPA_55);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "2");


	/** 3 */
	rect5 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect5, 285, 53);
	gt_obj_set_size(rect5, 65, 75);
	gt_obj_set_opa(rect5, GT_OPA_56);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "3");

	/** delete one */
	rect6 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect6, 365, 51);
	gt_obj_set_size(rect6, 85, 75);
	gt_obj_set_opa(rect6, GT_OPA_55);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0x778899));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);
	gt_obj_add_event_cb(rect6, DeleteOne, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** . */
	rect7 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect7, 20, 145);
	gt_obj_set_size(rect7, 85, 75);
	gt_obj_set_opa(rect7, GT_OPA_55);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);


	/** 4 */
	rect8 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect8, 120, 145);
	gt_obj_set_size(rect8, 65, 75);
	gt_obj_set_opa(rect8, GT_OPA_55);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0x778899));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 4);
	gt_obj_add_event_cb(rect8, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "4");


	/** 5 */
	rect9 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect9, 206, 146);
	gt_obj_set_size(rect9, 65, 75);
	gt_obj_set_opa(rect9, GT_OPA_55);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect9, gt_color_hex(0x778899));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 4);
	gt_obj_add_event_cb(rect9, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "5");


	/** 6 */
	rect10 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect10, 285, 144);
	gt_obj_set_size(rect10, 65, 75);
	gt_obj_set_opa(rect10, GT_OPA_55);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0x778899));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 4);
	gt_obj_add_event_cb(rect10, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "6");


	/** delete all */
	rect11 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect11, 365, 144);
	gt_obj_set_size(rect11, 85, 75);
	gt_obj_set_opa(rect11, GT_OPA_55);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect11, gt_color_hex(0x778899));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 4);
	gt_obj_add_event_cb(rect11, DeleteAll, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** 0 */
	rect12 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect12, 20, 233);
	gt_obj_set_size(rect12, 85, 75);
	gt_obj_set_opa(rect12, GT_OPA_55);
	gt_rect_set_radius(rect12, 0);
	gt_rect_set_bg_color(rect12, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect12, gt_color_hex(0x778899));
	gt_rect_set_fill(rect12, 1);
	gt_rect_set_border(rect12, 4);
	gt_obj_add_event_cb(rect12, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "0");


	/** 7 */
	rect13 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect13, 120, 235);
	gt_obj_set_size(rect13, 65, 75);
	gt_obj_set_opa(rect13, GT_OPA_55);
	gt_rect_set_radius(rect13, 0);
	gt_rect_set_bg_color(rect13, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect13, gt_color_hex(0x778899));
	gt_rect_set_fill(rect13, 1);                                                                            
	gt_rect_set_border(rect13, 4);
	gt_obj_add_event_cb(rect13, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "7");


	/** 8 */
	rect14 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect14, 205, 235);
	gt_obj_set_size(rect14, 65, 75);
	gt_obj_set_opa(rect14, GT_OPA_55);
	gt_rect_set_radius(rect14, 0);
	gt_rect_set_bg_color(rect14, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect14, gt_color_hex(0x778899));
	gt_rect_set_fill(rect14, 1);
	gt_rect_set_border(rect14, 4);
	gt_obj_add_event_cb(rect14, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "8");


	/** 9 */
	rect15 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect15, 285, 235);
	gt_obj_set_size(rect15, 65, 75);
	gt_obj_set_opa(rect15, GT_OPA_55);
	gt_rect_set_radius(rect15, 0);
	gt_rect_set_bg_color(rect15, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect15, gt_color_hex(0x778899));
	gt_rect_set_fill(rect15, 1);
	gt_rect_set_border(rect15, 4);
	gt_obj_add_event_cb(rect15, InputValue, GT_EVENT_TYPE_INPUT_RELEASED, "9");


	/** ok */
	rect16 = gt_rect_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(rect16, 365, 235);
	gt_obj_set_size(rect16, 85, 75);
	gt_obj_set_opa(rect16, GT_OPA_55);
	gt_rect_set_radius(rect16, 0);
	gt_rect_set_bg_color(rect16, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect16, gt_color_hex(0x778899));
	gt_rect_set_fill(rect16, 1);
	gt_rect_set_border(rect16, 4);
	gt_obj_add_event_cb(rect16, Confirm, GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** input1 */
	input1 = gt_input_create(Screen_KeyBoard_PassWord);
	gt_obj_set_pos(input1, 298, 2);
	gt_obj_set_size(input1, 181, 39);
	gt_input_set_font_color(input1, gt_color_hex(0x000000));
	gt_input_set_font_size(input1, 24);
	gt_input_set_font_family_en(input1, 33);
	gt_input_set_font_align(input1, GT_ALIGN_LEFT);
	gt_input_set_placeholder(input1,"0");
	gt_input_set_bg_color(input1, gt_color_hex(0xffffff));

	return Screen_KeyBoard_PassWord;
}

