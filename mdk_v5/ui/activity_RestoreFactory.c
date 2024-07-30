#include "ui.h"


/** RestoreFactory */
gt_obj_st * RestoreFactory = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;


static const char title[5][5][95]={
	"恢复厂家设置",
	"确定恢复厂家设置吗？",
	"确认",
	"返回",
	"恢复成功,请重启设备！",

	"Restore Factory Default",
	"Restore factory default or not?",
	"Confirm",
	"Return",
	"Restore is successed. Please press POWER to shutdown and restart the device!",

	"Restaurar la Fábrica Predeterminada",
	"Restaurar la fábrica predeterminada o no?",
	"Confirmar",
	"Retorno",
	"La restauración es exitosa.Presione\"On/Off\"para apagar y reiniciar el dispositivo!",

	"恢復廠家設置",
	"確定恢復廠家設置嗎？",
	"確認",
	"返回",
	"恢復成功,請重啟設備！",

	"Restaurar padrão de fábrica",
	"Restaurar o padrão de fábrica ou não?",
	"Confirmar",
	"Retornar",
	"A restauração foi bem sucedida. Pressione POWER para desligar e reiniciar o dispositivo!"

};




static void Confirm(gt_event_st * e) {

	crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
	bpr_reset();
	
	//隐藏btn
	gt_obj_set_visible(btn1,GT_INVISIBLE);
	gt_obj_set_visible(btn2,GT_INVISIBLE);

	//更改名称
	char buff[100];
	sprintf(buff,"%s",title[SystemSetting.langue][4]);
	gt_label_set_text(lab2,buff);


}




static void Back(gt_event_st * e) {

	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_RestoreFactory()
{
	RestoreFactory =  gt_obj_create(NULL);
	my_set_obj_title(RestoreFactory,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(RestoreFactory, gt_color_hex(0x000000));
	 

	/** lab2 */
	lab2 = gt_label_create(RestoreFactory);
	gt_obj_set_pos(lab2, 104, 146);
	gt_obj_set_size(lab2, 265, 36);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** btn1 */
	btn1 = gt_btn_create(RestoreFactory);
	gt_obj_set_pos(btn1, 60, 255);
	gt_obj_set_size(btn1, 110, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/** btn2 */
	btn2 = gt_btn_create(RestoreFactory);
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
	gt_obj_add_event_cb(btn2, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return RestoreFactory;
}

