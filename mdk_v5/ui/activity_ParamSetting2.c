#include "ui.h"
#include "infusion.h"
#include "headbar_view.h"


/** ParamSetting2 */
gt_obj_st * ParamSetting2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * rect11 = NULL;

static const char title[5][5][50]={
		"输注设定",
		"KVO流速",
		"气泡大小",
		"累计气泡",
		"主菜单",
		
		
		"Infusion Setting",
		"",
		"",
		"",
		"Main Menu",
		

		"Configuración de Infusión",
		"",
		"",
		"",
		"Menú Principal",
		
		"輸注設定",
		"",
		"",
		"",
		"主菜單",

		"Configuração de Infusão",
		"",
		"",
		"",
		"Menu principal"
		
	
};









static void back(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][4]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}




static void UpPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_2);
}

static void DownPage(gt_event_st * e) {
	gt_disp_stack_load_scr(GT_SCR_ID_22);
}

/** 进入键盘修改KVO流速并存储 */
static void ChangKVO(gt_event_st * e) {

	keyboardf.data = &ParamSetting.KVOSpeed;
	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.id=11;
	limit.lowerlimit=0.10;
	limit.toplimit=5.00;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}

/** 修改气泡大小并存储 */
static void BubbleSize(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_26, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 进入键盘修改累积气泡大小并存储 */
static void AccumBubble(gt_event_st * e) {
	keyboardf.data = &ParamSetting.AccumBubbleSize;
	strcpy(keyboardf.title,title[SystemSetting.langue][3]);
	keyboardf.id=12;
	limit.lowerlimit=0.10;
	limit.toplimit=4.00;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 11)  //修改完KVO流速出来的
	{
		sprintf(buffer,"%.1f",ParamSetting.KVOSpeed);
		gt_label_set_text(lab3, buffer);
		not_first_start_write_history_info(EA_Set,Ev_SetKVO,buffer);
	}
	if(atoi(e->param) == 12)  //修改完累积气泡大小出来的
	{
		sprintf(buffer,"%.1f",ParamSetting.AccumBubbleSize);
		gt_label_set_text(lab7, buffer);
		not_first_start_write_history_info(EA_Set,Ev_AccumBubble,buffer);
	}
	WriteParamSettingMessageToFlash();
}


gt_obj_st * gt_init_ParamSetting2(void)
{
	char buffer[50];
	ParamSetting2 =  gt_obj_create(NULL);
	my_set_obj_title(ParamSetting2,title[SystemSetting.langue][0]);
	gt_obj_add_event_cb(ParamSetting2,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_screen_set_bgcolor(ParamSetting2, gt_color_hex(0x000000));

	my_set_obj_title(ParamSetting2,title[SystemSetting.langue][0]);
	// 

	/** KVOlab */
	lab2 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab2, 85, 65);
	gt_obj_set_size(lab2, 165, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	/** KVO_Numlab */
	lab3 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab3, 260, 65);
	gt_obj_set_size(lab3, 70, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.1f",ParamSetting.KVOSpeed);
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	/** 气泡lab */
	lab4 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab4, 85, 145);
	gt_obj_set_size(lab4, 165, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);


	/** lab5 */
	/** 累积气泡lab */
	lab5 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab5, 85, 225);
	gt_obj_set_size(lab5, 165, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** lab6 */
	/** 气泡大小lab */
	lab6 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab6, 260, 145);
	gt_obj_set_size(lab6, 70, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",ParamSetting.BubbleSize);
	not_first_start_write_history_info(EA_Set,Ev_SetBubbleSize,buffer);
	gt_label_set_text(lab6, buffer);


	/** lab7 */
	/** 累积气泡lab */
	lab7 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab7, 260, 225);
	gt_obj_set_size(lab7, 70, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.1f",ParamSetting.AccumBubbleSize);
	gt_label_set_text(lab7, buffer);


	/** img1 */
	img1 = gt_img_create(ParamSetting2);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect2 */
	/** KVO流速矩形 */
	rect2 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 185, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,ChangKVO,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect3 */
	/** KVO流速数值设置矩形 */
	rect3 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect3, 260, 65);
	gt_obj_set_size(rect3, 70, 60);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3,ChangKVO,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect4 */
	/** 气泡大小修改并在气泡大小lab显示事件 */
	rect4 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect4, 75, 145);
	gt_obj_set_size(rect4, 185, 60);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, BubbleSize, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect5 */
	/** 气泡大小修改并在气泡大小lab显示事件 */
	rect5 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect5, 260, 145);
	gt_obj_set_size(rect5, 70, 60);
	gt_obj_set_opa(rect5, GT_OPA_40);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, BubbleSize, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect6 */
	/** 累积气泡修改并在累积气泡lab显示事件 */
	rect6 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect6, 75, 225);
	gt_obj_set_size(rect6, 185, 60);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, AccumBubble, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect7 */
	/** 累积气泡修改并在累积气泡lab显示事件 */
	rect7 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect7, 260, 225);
	gt_obj_set_size(rect7, 70, 60);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, AccumBubble, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** svg1 */
	svg1 = gt_img_create(ParamSetting2);
	gt_obj_set_pos(svg1, 415, 69);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, UpPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(ParamSetting2);
	gt_obj_set_pos(svg2, 415, 230);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, DownPage, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab8, 400, 157);
	gt_obj_set_size(lab8, 76, 34);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "2/4");


	/** lab9 */
	lab9 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab9, 330, 65);
	gt_obj_set_size(lab9, 70, 60);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "mL/h");


	/** rect8 */
	/** KVO流速单位矩形 */
	rect8 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect8, 330, 65);
	gt_obj_set_size(rect8, 70, 60);
	gt_obj_set_opa(rect8, GT_OPA_40);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8,ChangKVO,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** lab11 */
	lab11 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab11, 330, 225);
	gt_obj_set_size(lab11, 70, 60);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "mL");


	/** rect10 */
	/** 累积气泡单位矩形 */
	rect10 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect10, 330, 225);
	gt_obj_set_size(rect10, 70, 60);
	gt_obj_set_opa(rect10, GT_OPA_40);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 0);
	gt_obj_add_event_cb(rect10, AccumBubble, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** lab10 */
	lab10 = gt_label_create(ParamSetting2);
	gt_obj_set_pos(lab10, 330, 145);
	gt_obj_set_size(lab10, 70, 60);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "uL");


	/** rect11 */
	/** 气泡大小单位 */
	rect11 = gt_rect_create(ParamSetting2);
	gt_obj_set_pos(rect11, 330, 145);
	gt_obj_set_size(rect11, 70, 60);
	gt_obj_set_opa(rect11, GT_OPA_40);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect11, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 0);
	gt_obj_add_event_cb(rect11, BubbleSize, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return ParamSetting2;
}

