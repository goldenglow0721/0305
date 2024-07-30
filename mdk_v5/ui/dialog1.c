/*
*     对话框文件。 仅含有确定按键
*
*/

#include "ui.h"



gt_obj_st * dialog1 = NULL;
static gt_obj_st * btn = NULL;
static gt_obj_st * lab =NULL;

static void btn_callback(gt_event_st * e) {

	gt_event_send(dialog1,GT_EVENT_TYPE_NOTIFY_CLOSE,"1");
}



gt_obj_st * dialog1_create(char * str) {
		
	

	gt_dialog_param_st param;
	param.cancel_cb = NULL;
	param.cancel_cb_user_data = NULL;
	param.confirm_cb = btn_callback;
	param.confirm_cb_user_data = NULL;
	param.title = NULL;
	param.content = str;
	
	dialog1 = gt_dialog_create_issue(false,&param);
	gt_obj_set_pos(dialog1, 120, 90);
	gt_obj_set_size(dialog1, 240, 130);
	gt_dialog_set_bgcolor(dialog1, gt_color_hex(0xffffff));
	gt_dialog_set_border_color(dialog1, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog1, 4);
	gt_dialog_set_border_radius(dialog1, 2);
	gt_dialog_set_content_font_size(dialog1, 24);
	gt_dialog_set_content_font_family_cn(dialog1, 20);
	gt_dialog_set_content_font_family_en(dialog1, 33);
	gt_dialog_set_content_font_family_fl(dialog1, 50);
	gt_dialog_set_outside_auto_hide(dialog1, false);
	gt_dialog_set_anim_time(dialog1,50);
	gt_dialog_show(dialog1);

	#if 0
	/** btn */
	btn = gt_btn_create(dialog1);
	gt_obj_set_pos(btn, 190, 160);
	gt_obj_set_size(btn, 100, 50);
	gt_btn_set_font_color(btn, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn, 24);
	gt_btn_set_font_family_cn(btn,18);
	gt_btn_set_font_align(btn, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn, "确认");
	gt_btn_set_color_background(btn, gt_color_hex(0x0097e6));
	gt_btn_set_color_pressed(btn, gt_color_hex(0xc0c0c0));
	gt_btn_set_radius(btn, 4);
	gt_obj_add_event_cb(btn, btn_callback, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** lab */
	lab = gt_label_create(dialog1);
	gt_obj_set_pos(lab, 120, 115);
	gt_obj_set_size(lab, 240, 35);
	gt_label_set_font_color(lab, gt_color_hex(0x000000));
	gt_label_set_font_size(lab, 24);
	gt_label_set_font_family_en(lab, 33);
	gt_label_set_font_family_cn(lab, 18);
	gt_label_set_font_family_fl(lab, 50);
	gt_label_set_font_align(lab, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab, str);
	gt_dialog_show(dialog1);
	#endif

	return dialog1;
}


