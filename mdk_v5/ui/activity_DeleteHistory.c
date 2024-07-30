#include "ui.h"
#include "library_history.h"

/** DeleteHistory */
gt_obj_st * DeleteHistory = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;

static const char title[5][4][50]={
	"删除历史记录",
	"确定删除历史记录？",
	"确认",
	"返回",

	"Delete History Record",
	"Delete history list or not?",
	"Confirm",
	"Return",

	"Eliminar Registro de Historia",
	"Eliminar la lista de historial o no?",
	"Confirmar",
	"Retorno",

	"刪除歷史記錄",
	"確定刪除歷史記錄？",
	"確認",
	"返回",

	"Excluir registro histórico",
	"Excluir lista de histórico ou não?",
	"Confirmar",
	"Retornar"
		
};

static void btn1_0_cb(gt_event_st * e) {
	
	gt_disp_stack_go_back(1);
}

static void btn2_0_cb(gt_event_st * e) {
		destroyHistoryList();
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_DeleteHistory(void)
{
	DeleteHistory =  gt_obj_create(NULL);
	my_set_obj_title(DeleteHistory,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(DeleteHistory, gt_color_hex(0x000000));
	 

	


	


	/** lab2 */
	lab2 = gt_label_create(DeleteHistory);
	gt_obj_set_pos(lab2, 104, 145);
	gt_obj_set_size(lab2, 265, 36);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** btn1 */
	btn1 = gt_btn_create(DeleteHistory);
	gt_obj_set_pos(btn1, 60, 255);
	gt_obj_set_size(btn1, 110, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** btn2 */
	btn2 = gt_btn_create(DeleteHistory);
	gt_obj_set_pos(btn2, 313, 256);
	gt_obj_set_size(btn2, 110, 50);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, btn2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return DeleteHistory;
}

