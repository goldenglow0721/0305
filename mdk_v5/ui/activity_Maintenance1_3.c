#include "ui.h"
#include "headbar_view.h"
#include "library_infusion.h"
/** screen_Maintenance_Normal_Three */
gt_obj_st * screen_Maintenance_Normal_Three = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;

static const char title[5][6][50]={
	"系统维护",
	"设定品牌名",
	"新增输液器品牌",
	"删除输液器品牌",
	"请先添加输液器品牌",
	"主菜单",

	"Maintenance",
	"Set IV Set Brand Name",
	"Add IV Set Brand",
	"Delete IV Set Brand",
	"Please add an IV Set brand!",
	"Main Menu",
	
	"Mantenimiento",
	"Ajuste la marca de IV set ",
	"Agregar IV Set Marca",
	"Eliminar IV Set Marca",
	"¡Agregue una marca de IV Set!",
	"Menú Principal",
	
	"系統維護",
	"設定品牌名",
	"新增輸液器品牌",
	"刪除輸液器品牌",
	"請先添加輸液器品牌",
	"主菜單",
	
	"Manutenção",
	"Selecionar marca de equipo",
	"Adicionar marca do equipo",
	"Excluir marca do equipo",
	"Por favor, adicione uma marca de equipo!",
	"Menu principal"
};



static void img1_0_cb(gt_event_st * e) {
	my_set_obj_title(ModeSelect,title[SystemSetting.langue][5]);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_42, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void svg2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_44, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void rect2_0_cb(gt_event_st * e) {
//	gt_obj_st * target_scr = gt_init_SystemDataSetting();
//	gt_disp_set_backoff_scr(target_scr, gt_init_Maintenance1_3, 500, 0);
//	
}

static void AddBrand(gt_event_st * e) {

    int number = getNowInfusionListNum();
	
	if(number > InfusionTube_MaxNumber)
		dialog1_create("输液器品牌已满");
	else
	{
		strcpy(keyboards.title,title[SystemSetting.langue][2]);
		keyboards.id = 2;
		gt_disp_stack_load_scr_anim(GT_SCR_ID_83, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	}
}

static void DelBrand(gt_event_st * e) {
	char buffer[50];
   
    int number=getNowInfusionListNum();
	if(number <= 2)
		dialog1_create("请先添加输液器品牌");
	else
		gt_disp_stack_load_scr_anim(GT_SCR_ID_49, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void update(gt_event_st * e){
	if(atoi(e->param) == 2)  //增加输液器品牌
	{
		//printf("arrive here1!\n");
		InfusionNode_t* node=(InfusionNode_t *)malloc(sizeof(InfusionNode_t));
		InfusionNodeMessage message;


		//printf("%s\n",tubename);
		strcpy(message.ch_name,tubename);
		strcpy(message.en_name,tubename);
		strcpy(message.es_name,tubename);
		strcpy(message.pu_name,tubename);
		strcpy(message.ch2_name,tubename);

		node->message = message;
		node->nextnode = NULL;
		AddInfusionNode(node,false);
		not_first_start_write_history_info(EA_Add,Ev_Tube,tubename);
	}
}



gt_obj_st * gt_init_Maintenance1_3(void)
{
	screen_Maintenance_Normal_Three =  gt_obj_create(NULL);
	my_set_obj_title(screen_Maintenance_Normal_Two,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(screen_Maintenance_Normal_Three, gt_color_hex(0x000000));

		

	gt_obj_add_event_cb(screen_Maintenance_Normal_Three, update, MY_EVENT_UPDATA, NULL);
	 


	/** img1 */
	img1 = gt_img_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(svg1, 416, 74);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(svg2, 416, 240);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, svg2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(lab2, 406, 157);
	gt_obj_set_size(lab2, 69, 45);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "3/5");


	/** lab3 */
	lab3 = gt_label_create(screen_Maintenance_Normal_Three);
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
	rect2 = gt_rect_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(rect2, 75, 68);
	gt_obj_set_size(rect2, 325, 60);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** drug */
	lab4 = gt_label_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(lab4, 75, 150);
	gt_obj_set_size(lab4, 325, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][2]);
	



	/** lab5 */
	lab5 = gt_label_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(lab5, 75, 232);
	gt_obj_set_size(lab5, 325, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][3]);




	/** rect3 */
	rect3 = gt_rect_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(rect3, 75, 150);
	gt_obj_set_size(rect3, 325, 60);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, AddBrand, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(screen_Maintenance_Normal_Three);
	gt_obj_set_pos(rect4, 75, 232);
	gt_obj_set_size(rect4, 325, 60);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, DelBrand, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return screen_Maintenance_Normal_Three;
}

