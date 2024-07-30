#include "ui.h"
#include "headbar_view.h"
#include "library_drug.h"
/** screen_Maintenance_Normal_Four */
gt_obj_st * screen_Maintenance_Normal_Four = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;

static const char title[5][8][55]={
	"系统维护",
	"添加药物名",
	"删除药物名",
	"滴系数",
	"滴/ml",
	"导出历史记录",
	"请先添加药物名",
	"主菜单",

	"Maintenance",
	"Add Drug Name",
	"Delete Drug Name",
	"drip",
	"drip/ml",
	"Export Medical History",
	"Please add a drug name firstly!",
	"Main Menu",
	
	"Mantenimiento",
	"Agregar Medicamento",
	"Eliminar Medicamento",
	"Diámetro de Goteo",
	"Goteo/ml",
	"Exportar Historial Médico",
	"Por favor agregue primero el nombre del medicamento",
	"Menú Principal",
	
	"系統維護",
	"添加藥物名",
	"刪除藥物名",
	"滴係數",
	"滴/ml",
	"導出歷史記錄",
	"請先添加藥物名",
	"主菜單",
	
	"Manutenção",
	"Add Nome do Medicamento",
	"Excluir nome do medicamento",
	"Gotas",
	"Gotas/ml",
	"Exportar Histórico Médico",
	"Por favor, adicione um nome de medicamento primeiro!",
	"Menu principal"
};



static void img1_0_cb(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][7]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_43, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_45, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void ExportHistory(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_56, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void AddDrug(gt_event_st * e) {
	char buffer[50];
	int number = getNowDrugListNum();
	if(number > DrugTube_MaxNumber)
		dialog1_create("药物库已满");
	else
	{
		strcpy(keyboards.title,title[SystemSetting.langue][1]);
		keyboards.id = 3;
		gt_disp_stack_load_scr_anim(GT_SCR_ID_83, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	}
}

static void DeleteDrug(gt_event_st * e) {
	char buffer[50];
	int number = getNowDrugListNum();
	if(number <= 35)
		dialog1_create("请先添加药物名称");
	else
		gt_disp_stack_load_scr_anim(GT_SCR_ID_48, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void EventUpdata(gt_event_st * e)
{
	if(atoi(e->param) == 3)  //增加药品名
	{
		//printf("arrive here1!\n");
		DrugNode_t* node=(DrugNode_t *)malloc(sizeof(DrugNode_t));
		DrugNodeMessage message;

		//printf("%s\n",drugname);
		strcpy(message.ch_name,drugname);
		strcpy(message.en_name,drugname);
		strcpy(message.es_name,drugname);
		strcpy(message.pu_name,drugname);
		strcpy(message.ch2_name,drugname);

		node->message = message;
		node->nextnode = NULL;
		AddDrugNode(node,false);
		not_first_start_write_history_info(EA_Add,Ev_ConfirmDrug,drugname);
	}
}


gt_obj_st * gt_init_Maintenance1_4(void)
{
	char buffer[50];
	screen_Maintenance_Normal_Four =  gt_obj_create(NULL);
	my_set_obj_title(screen_Maintenance_Normal_Four,title[SystemSetting.langue][0]);
	gt_obj_add_event_cb(screen_Maintenance_Normal_Four,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_screen_set_bgcolor(screen_Maintenance_Normal_Four, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(svg1, 416, 75);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(lab2, 406, 156);
	gt_obj_set_size(lab2, 69, 45);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "4/5");


	/** lab3 */
	lab3 = gt_label_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(lab3, 75, 68);
	gt_obj_set_size(lab3, 325, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][1]);



	/** rect2 */
	rect2 = gt_rect_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(rect2, 75, 68);
	gt_obj_set_size(rect2, 325, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, AddDrug, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab4 */
	lab4 = gt_label_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(lab4, 75, 150);
	gt_obj_set_size(lab4, 325, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);


	/** rect3 */
	rect3 = gt_rect_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(rect3, 75, 150);
	gt_obj_set_size(rect3, 325, 60);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, DeleteDrug, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(rect4, 75, 232);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, ExportHistory,GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	lab5 = gt_label_create(screen_Maintenance_Normal_Four);
	gt_obj_set_pos(lab5, 75, 232);
	gt_obj_set_size(lab5, 325, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][5]);
	gt_obj_add_event_cb(lab5, ExportHistory,GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return screen_Maintenance_Normal_Four;
}

