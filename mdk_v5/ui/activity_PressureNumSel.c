#include "ui.h"

static const char title[5][1][50]={
	"阻塞压力",

	"Occlusion Pressure",

	"Presión de Oclusión",

	"阻塞壓力",

	"Pressão de Oclusão"
		
};
extern int BlevelData[15];
#define vp10pro 0		//阻塞压力可选等级
/** PressureNumSel */
gt_obj_st * PressureNumSel = NULL;
static gt_obj_st * PressureNumSel_1 = NULL;
static gt_obj_st * PressureNumSel_2 = NULL;
static gt_obj_st * PressureNumSel_3 = NULL;
static gt_obj_st * viewPager1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * rect11 = NULL;
static gt_obj_st * rect12 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * rect13 = NULL;
static gt_obj_st * rect14 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * svg1 = NULL;

static gt_obj_st * lab20 = NULL;
static gt_obj_st * lab21 = NULL;
static gt_obj_st * lab22 = NULL;


static int  nowpage=1;
/*函数声明*/
static void CreatePage1();

#if vp10pro

static void CreatePage2();
static void CreatePage3();

static void PageShow(uint8_t temp)
{
	switch(temp)
	{
		case 1:
			gt_obj_set_visible(PressureNumSel_1,GT_VISIBLE);
			gt_obj_set_visible(PressureNumSel_2,GT_INVISIBLE);
			gt_obj_set_visible(PressureNumSel_3,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_1,GT_OBJ_PROP_TYPE_VISIBLE,GT_VISIBLE);
			gt_obj_child_set_prop(PressureNumSel_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_3,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);

			
			
			break;
		case 2:
			gt_obj_set_visible(PressureNumSel_1,GT_INVISIBLE);
			gt_obj_set_visible(PressureNumSel_2,GT_VISIBLE);
			gt_obj_set_visible(PressureNumSel_3,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_1,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_VISIBLE);
			gt_obj_child_set_prop(PressureNumSel_3,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			

				
			break;
		case 3:
			gt_obj_set_visible(PressureNumSel_1,GT_INVISIBLE);
			gt_obj_set_visible(PressureNumSel_2,GT_INVISIBLE);
			gt_obj_set_visible(PressureNumSel_3,GT_VISIBLE);
			gt_obj_child_set_prop(PressureNumSel_1,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			gt_obj_child_set_prop(PressureNumSel_3,GT_OBJ_PROP_TYPE_VISIBLE,GT_VISIBLE);

			
			break;

			default:
			break;
	}
}



//上一页
static void Page_Up(gt_event_st * e) {

	
	if(--nowpage < 1)
		nowpage=3;
 
	PageShow(nowpage);
	

}
//下一页
static void Page_Down(gt_event_st * e) {
	if(++nowpage >3)
		nowpage=1;

	PageShow(nowpage);
	
}
#endif
static void back(gt_event_st* e)
{
	
	gt_disp_stack_go_back(1);
}

static void PressureLevelChange(gt_event_st * e)
{
	char buffer[30];
	ParamSetting.BlockLevel = atoi(e->user_data);
	
	sprintf(buffer,"%.1f",PressureConversion(BlevelData[ParamSetting.BlockLevel],P_mmHg,ParamSetting.PressUint));
	WriteParamSettingMessageToFlash();
	not_first_start_write_history_info(EA_Set,Ev_PressureRating,buffer);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void CreatePage1()
{
	/** rect1 */
	rect1 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect1, 70, 65);
	gt_obj_set_size(rect1, 150, 50);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x778899));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 4);
	gt_obj_add_event_cb(rect1,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"1");


	/** rect2 */
	rect2 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect2, 260, 65);
	gt_obj_set_size(rect2, 150, 50);
	gt_obj_set_opa(rect2, GT_OPA_40);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"2");


	/** rect3 */
	rect3 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect3, 70, 140);
	gt_obj_set_size(rect3, 150, 50);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"3");

	/** lab3 */
	lab3 = gt_label_create(rect1);
	gt_obj_set_pos(lab3, 70, 65);
	gt_obj_set_size(lab3, 150, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "300");
	gt_obj_set_inside(lab3, true);
	gt_obj_set_bubble_notify(lab3, true);

	/** lab6 */
	lab6 = gt_label_create(rect2);
	gt_obj_set_pos(lab6, 260, 65);
	gt_obj_set_size(lab6, 150, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "525");
	gt_obj_set_inside(lab6, true);
	gt_obj_set_bubble_notify(lab6, true);


	/** lab11 */
	lab11 = gt_label_create(rect3);
	gt_obj_set_pos(lab11, 70, 140);
	gt_obj_set_size(lab11, 150, 50);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "900");
	gt_obj_set_inside(lab11, true);
	gt_obj_set_bubble_notify(lab11, true);
}

	/*第一页*/
	#if vp10pro
	lab20 = gt_label_create(PressureNumSel_1);
	gt_obj_set_pos(lab20, 403, 143);
	gt_obj_set_size(lab20, 69, 45);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 24);
	gt_label_set_font_family_en(lab20, 33);
	gt_label_set_font_family_cn(lab20, 20);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab20, "1/3");
	
	/** rect1 */
	rect1 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect1, 70, 65);
	gt_obj_set_size(rect1, 150, 50);
	gt_obj_set_opa(rect1, GT_OPA_41);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);
	gt_obj_add_event_cb(rect1,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"1");


	/** rect2 */
	rect2 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect2, 260, 65);
	gt_obj_set_size(rect2, 150, 50);
	gt_obj_set_opa(rect2, GT_OPA_40);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"2");


	/** rect3 */
	rect3 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect3, 70, 140);
	gt_obj_set_size(rect3, 150, 50);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"3");


	/** rect4 */
	rect4 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect4, 260, 140);
	gt_obj_set_size(rect4, 150, 50);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"4");


	/** rect5 */
	rect5 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect5, 70, 215);
	gt_obj_set_size(rect5, 150, 50);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"5");


	/** rect6 */
	rect6 = gt_rect_create(PressureNumSel_1);
	gt_obj_set_pos(rect6, 260, 215);
	gt_obj_set_size(rect6, 150, 50);
	gt_obj_set_opa(rect6, GT_OPA_40);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"6");
	
	/** lab1 */
	lab1 = gt_label_create(rect1);
	gt_obj_set_pos(lab1, 70, 65);
	gt_obj_set_size(lab1, 150, 50);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "150");
	gt_obj_set_inside(lab1, true);
	gt_obj_set_bubble_notify(lab1, true);

	/** lab2 */
	lab2 = gt_label_create(rect2);
	gt_obj_set_pos(lab2, 260, 65);
	gt_obj_set_size(lab2, 150, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "225");
	gt_obj_set_inside(lab2, true);
	gt_obj_set_bubble_notify(lab2, true);

	/** lab3 */
	lab3 = gt_label_create(rect3);
	gt_obj_set_pos(lab3, 70, 140);
	gt_obj_set_size(lab3, 150, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "300");
	gt_obj_set_inside(lab3, true);
	gt_obj_set_bubble_notify(lab3, true);

	/** lab4 */
	lab4 = gt_label_create(rect4);
	gt_obj_set_pos(lab4, 260, 140);
	gt_obj_set_size(lab4, 150, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "375");
	gt_obj_set_inside(lab4, true);
	gt_obj_set_bubble_notify(lab4, true);

	/** lab5 */
	lab5 = gt_label_create(rect5);
	gt_obj_set_pos(lab5, 70, 215);
	gt_obj_set_size(lab5, 150, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "450");
	gt_obj_set_inside(lab5, true);
	gt_obj_set_bubble_notify(lab5, true);

	/** lab6 */
	lab6 = gt_label_create(rect6);
	gt_obj_set_pos(lab6, 260, 215);
	gt_obj_set_size(lab6, 150, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "525");
	gt_obj_set_inside(lab6, true);
	gt_obj_set_bubble_notify(lab6, true);


}

static void CreatePage2()
{
	/*第二页*/
	lab21 = gt_label_create(PressureNumSel_2);
	gt_obj_set_pos(lab21, 403, 143);
	gt_obj_set_size(lab21, 69, 45);
	gt_label_set_font_color(lab21, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab21, 24);
	gt_label_set_font_family_en(lab21, 33);
	gt_label_set_font_family_cn(lab21, 20);
	gt_label_set_font_family_fl(lab21, 50);
	gt_label_set_font_align(lab21, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab21, "2/3");


	/** rect7 */
	rect7 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect7, 70, 65);
	gt_obj_set_size(rect7, 150, 50);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"7");


	/** rect8 */
	rect8 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect8, 260, 65);
	gt_obj_set_size(rect8, 150, 50);
	gt_obj_set_opa(rect8, GT_OPA_40);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 0);
	gt_obj_add_event_cb(rect8,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"8");


	/** rect9 */
	rect9 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect9, 70, 140);
	gt_obj_set_size(rect9, 150, 50);
	gt_obj_set_opa(rect9, GT_OPA_40);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect9, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);
	gt_obj_add_event_cb(rect9,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"9");


	/** rect10 */
	rect10 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect10, 260, 140);
	gt_obj_set_size(rect10, 150, 50);
	gt_obj_set_opa(rect10, GT_OPA_41);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 0);
	gt_obj_add_event_cb(rect10,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"10");


	/** rect11 */
	rect11 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect11, 70, 215);
	gt_obj_set_size(rect11, 150, 50);
	gt_obj_set_opa(rect11, GT_OPA_40);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect11, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 0);
	gt_obj_add_event_cb(rect11,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"11");

	/** rect12 */
	rect12 = gt_rect_create(PressureNumSel_2);
	gt_obj_set_pos(rect12, 260, 214);
	gt_obj_set_size(rect12, 150, 50);
	gt_obj_set_opa(rect12, GT_OPA_40);
	gt_rect_set_radius(rect12, 0);
	gt_rect_set_bg_color(rect12, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect12, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect12, 1);
	gt_rect_set_border(rect12, 0);
	gt_obj_add_event_cb(rect12,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"12");
	
	/** lab7 */
	lab7 = gt_label_create(rect7);
	gt_obj_set_pos(lab7, 70, 65);
	gt_obj_set_size(lab7, 150, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "600");
	gt_obj_set_inside(lab7, true);
	gt_obj_set_bubble_notify(lab7, true);
	

	/** lab8 */
	lab8 = gt_label_create(rect8);
	gt_obj_set_pos(lab8, 260, 65);
	gt_obj_set_size(lab8, 150, 50);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "675");
	gt_obj_set_inside(lab8, true);
	gt_obj_set_bubble_notify(lab8, true);


	/** lab9 */
	lab9 = gt_label_create(rect9);
	gt_obj_set_pos(lab9, 70, 140);
	gt_obj_set_size(lab9, 150, 50);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab9, "750");
	gt_obj_set_inside(lab9, true);
	gt_obj_set_bubble_notify(lab9, true);

	/** lab10 */
	lab10 = gt_label_create(rect10);
	gt_obj_set_pos(lab10, 260, 140);
	gt_obj_set_size(lab10, 150, 50);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "825");
	gt_obj_set_inside(lab10, true);
	gt_obj_set_bubble_notify(lab10, true);

	/** lab11 */
	lab11 = gt_label_create(rect11);
	gt_obj_set_pos(lab11, 70, 215);
	gt_obj_set_size(lab11, 150, 50);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "900");
	gt_obj_set_inside(lab11, true);
	gt_obj_set_bubble_notify(lab11, true);

	/** lab12 */
	lab12 = gt_label_create(rect12);
	gt_obj_set_pos(lab12, 260, 215);
	gt_obj_set_size(lab12, 150, 50);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab12, "975");
	gt_obj_set_inside(lab12, true);
	gt_obj_set_bubble_notify(lab12, true);
	

	
}
static void CreatePage3()
{

	/*第三页*/
	lab22 = gt_label_create(PressureNumSel_3);
	gt_obj_set_pos(lab22, 403, 143);
	gt_obj_set_size(lab22, 69, 45);
	gt_label_set_font_color(lab22, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab22, 24);
	gt_label_set_font_family_en(lab22, 33);
	gt_label_set_font_family_cn(lab22, 20);
	gt_label_set_font_family_fl(lab22, 50);
	gt_label_set_font_align(lab22, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab22, "3/3");

	/** rect13 */
	rect13 = gt_rect_create(PressureNumSel_3);
	gt_obj_set_pos(rect13, 70, 65);
	gt_obj_set_size(rect13, 150, 50);
	gt_obj_set_opa(rect13, GT_OPA_40);
	gt_rect_set_radius(rect13, 0);
	gt_rect_set_bg_color(rect13, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect13, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect13, 1);
	gt_rect_set_border(rect13, 0);
	gt_obj_add_event_cb(rect13,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"13");

	/** rect14 */
	rect14 = gt_rect_create(PressureNumSel_3);
	gt_obj_set_pos(rect14, 260, 65);
	gt_obj_set_size(rect14, 150, 50);
	gt_obj_set_opa(rect14, GT_OPA_41);
	gt_rect_set_radius(rect14, 0);
	gt_rect_set_bg_color(rect14, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect14, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect14, 1);
	gt_rect_set_border(rect14, 0);
	gt_obj_add_event_cb(rect14,PressureLevelChange,GT_EVENT_TYPE_INPUT_RELEASED,"14");

	/** lab13 */
	lab13 = gt_label_create(rect13);
	gt_obj_set_pos(lab13, 70, 65);
	gt_obj_set_size(lab13, 150, 50);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab13, "1050");
	gt_obj_set_inside(lab13, true);
	gt_obj_set_bubble_notify(lab13, true);


	/** lab14 */
	lab14 = gt_label_create(rect14);
	gt_obj_set_pos(lab14, 260, 65);
	gt_obj_set_size(lab14, 150, 50);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_cn(lab14, 20);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab14, "1125");
	gt_obj_set_inside(lab14, true);
	gt_obj_set_bubble_notify(lab14, true);
	

}
#endif

gt_obj_st * gt_init_PressureNumSel(void)
{
	nowpage = 1;
	PressureNumSel =  gt_obj_create(NULL);
	my_set_obj_title(PressureNumSel,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(PressureNumSel, gt_color_hex(0x000000));
	 

	PressureNumSel_1 =  gt_obj_create(PressureNumSel);
	gt_obj_set_pos(PressureNumSel_1, 0, 0);
	gt_obj_set_size(PressureNumSel_1, 480, 270);
	#if vp10pro
	PressureNumSel_2 =  gt_obj_create(PressureNumSel);
	gt_obj_set_pos(PressureNumSel_2, 0, 0);
	gt_obj_set_size(PressureNumSel_2, 480, 270);
	PressureNumSel_3 =  gt_obj_create(PressureNumSel);
	gt_obj_set_pos(PressureNumSel_3, 0, 0);
	gt_obj_set_size(PressureNumSel_3, 480, 270);
	


	/** svg1 */
	svg1 = gt_img_create(PressureNumSel);
	gt_obj_set_pos(svg1, 416, 68);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, Page_Up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(PressureNumSel);
	gt_obj_set_pos(svg2, 417, 216);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, Page_Down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	#endif

	img1 = gt_img_create(PressureNumSel);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	
	CreatePage1();
	#if vp10pro
	CreatePage2();
	CreatePage3();
	

	gt_obj_set_visible(PressureNumSel_2,GT_INVISIBLE);
	gt_obj_set_visible(PressureNumSel_3,GT_INVISIBLE);
	gt_obj_child_set_prop(PressureNumSel_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
	gt_obj_child_set_prop(PressureNumSel_3,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
	#endif


	return PressureNumSel;
}

