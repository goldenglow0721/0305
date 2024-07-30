#include "ui.h"
#include "headbar_view.h"

/** screen_Maintenance_Two */
gt_obj_st * screen_Maintenance_Two = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab3 = NULL;


static const char title[5][6][50]={
	"系统维护",
	"传感器AD",
	"恢复厂家设置",
	"删除历史记录",
	"序列号",
	"主菜单",


	"Maintenance",
	"Sensor AD",
	"Restore Factory Default",
	"Delete History Record",
	"S/N",
	"Main Menu",
	
	"Mantenimiento",
	"Sensor AD",
	"Restaurar la Fábrica Predeterminada",
	"Eliminar Registro de Historia",
	"S/N",
	"Menú Principal",
	
	"系統維護",
	"感測器AD",
	"恢復廠家設置",
	"刪除歷史記錄",
	"序列號",
	"主菜單",
	
	"Manutenção",
	"Sensor AD",
	"Restaurar padrão de fábrica",
	"Excluir registro histórico",
	"S/N",
	"Menu principal"
};

static void back(gt_event_st * e) {
	
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][5]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void SensorAD(gt_event_st * e) {
	
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_62, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
	
}

static void ChangeSeriesNumber(gt_event_st * e) {
	
	strcpy(keyboards.title,title[SystemSetting.langue][4]);
	keyboards.id = 1;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_83, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	
}

static void up(gt_event_st * e) {
	gt_obj_st * target_scr = gt_init_Maintenance2_1();
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_46, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void down(gt_event_st * e) {
	gt_obj_st * target_scr = gt_init_Maintenance2_1();
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_46, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}




static void Delete_History(gt_event_st * e) {

	gt_disp_stack_load_scr_anim(GT_SCR_ID_63, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void EventUpdata(gt_event_st * e){
	if(atoi(e->param) == 1) //从序列号软键盘中返回
	{
		char buff[50];
		sprintf(buff,"%s",SystemSetting.Version.SerialNumber);
		gt_label_set_text(lab3, buff);
	}
	else
	{
		;
	}

}



gt_obj_st * gt_init_Maintenance2_2(void)
{
	char buffer[50];
	screen_Maintenance_Two =  gt_obj_create(NULL);
	my_set_obj_title(screen_Maintenance_Two,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(screen_Maintenance_Two, gt_color_hex(0x000000));
	gt_obj_add_event_cb(screen_Maintenance_Two, EventUpdata, MY_EVENT_UPDATA, NULL);
	 


	/** lab2 */
	lab2 = gt_label_create(screen_Maintenance_Two);
	gt_obj_set_pos(lab2, 75, 150);
	gt_obj_set_size(lab2, 325, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** img1 */
	img1 = gt_img_create(screen_Maintenance_Two);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect2 */
	rect2 = gt_rect_create(screen_Maintenance_Two);
	gt_obj_set_pos(rect2, 75, 150);
	gt_obj_set_size(rect2, 325, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, SensorAD, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(screen_Maintenance_Two);
	gt_obj_set_pos(svg1, 416, 74);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_Maintenance_Two);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(screen_Maintenance_Two);
	gt_obj_set_pos(lab8, 406, 157);
	gt_obj_set_size(lab8, 69, 45);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "2/2");


	
	

		/** lab6 */
	lab6 = gt_label_create(screen_Maintenance_Two);
	gt_obj_set_pos(lab6,75, 68);
	gt_obj_set_size(lab6, 130, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][4]);


	/** lab7 */
	lab7 = gt_label_create(screen_Maintenance_Two);
	gt_obj_set_pos(lab7,205, 68);
	gt_obj_set_size(lab7, 195, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%s",SystemSetting.Version.SerialNumber);
	gt_label_set_text(lab7, buffer);


	/** rect5 */
	rect5 = gt_rect_create(screen_Maintenance_Two);
	gt_obj_set_pos(rect5, 75, 68);
	gt_obj_set_size(rect5, 130, 60);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, ChangeSeriesNumber, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect6 */
	rect6 = gt_rect_create(screen_Maintenance_Two);
	gt_obj_set_pos(rect6, 205, 68);
	gt_obj_set_size(rect6, 195, 60);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, ChangeSeriesNumber, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




	/** lab5 */
	lab5 = gt_label_create(screen_Maintenance_Two);
	gt_obj_set_pos(lab5, 75, 232);
	gt_obj_set_size(lab5, 325, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);


	/** rect4 */
	rect4 = gt_rect_create(screen_Maintenance_Two);
	gt_obj_set_pos(rect4, 75, 232);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_50); 
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, Delete_History, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	return screen_Maintenance_Two;
}

