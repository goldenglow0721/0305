#include "ui.h"


/** SystemCheck */
gt_obj_st * SystemCheck = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;


static const char title[5][5][65]={
	"系统自检",
	"确定进行系统自检吗？",
	"确认",
	"返回",
	"恢复成功，请重启设备",

    "System Check",
	"Confirm System Check?",
	"Confirm",
	"Return",
	"Recovery Successful. Please Restart Device.",

    "Chequeo del Sistema",
	"¿Confirmar Chequeo del Sistema?",
	"Confirmar",
	"Retorno",
	"Recuperación Exitosa. Por favor, Reinicie el Dispositivo.",

    "系統自檢",
	"確認進行系統自檢嗎？",
	"確認",
	"返回",
	"恢復成功，請重新啟動設備。",

    "Verificação do Sistema",
	"Confirmar Verificação do Sistema?",
	"Confirmar",
	"Retornar",
	"Restauração Bem-sucedida. Por favor, Reinicie o Dispositivo."

};


static void btn1_0_cb(gt_event_st * e) {
	
}

static void btn1_1_cb(gt_event_st * e) {
	
}

static void btn1_2_cb(gt_event_st * e) {
	gt_label_set_text(lab2, title[SystemSetting.langue][4]);
}

static void btn2_0_cb(gt_event_st * e) {

	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_SystemCheck(void)
{
	SystemCheck =  gt_obj_create(NULL);
	my_set_obj_title(SystemCheck,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SystemCheck, gt_color_hex(0x000000));
	 




	/** lab2 */
	lab2 = gt_label_create(SystemCheck);
	gt_obj_set_pos(lab2, 0, 137);
	gt_obj_set_size(lab2, 480, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** btn1 */
	btn1 = gt_btn_create(SystemCheck);
	gt_obj_set_pos(btn1, 60, 255);
	gt_obj_set_size(btn1, 110, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1,title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	gt_obj_add_event_cb(btn1, btn1_1_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	gt_obj_add_event_cb(btn1, btn1_2_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn2 */
	btn2 = gt_btn_create(SystemCheck);
	gt_obj_set_pos(btn2, 312, 255);
	gt_obj_set_size(btn2, 110, 50);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2,title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, btn2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return SystemCheck;
}

