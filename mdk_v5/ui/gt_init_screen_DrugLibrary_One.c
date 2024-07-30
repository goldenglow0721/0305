#include "ui.h"


/** screen_DrugLibrary_One */
gt_obj_st * screen_DrugLibrary_One = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;


static const char title[5][1][50]={
	"药物库",

	"",

	"",

	"",
	
	""
		
};
static void img1_0_cb(gt_event_st * e) {
	gt_obj_st * target_scr = gt_init_ModeSelect();
	
}

static void svg1_0_cb(gt_event_st * e) {
	gt_obj_st * target_scr = gt_init_DrugChoice();
	
}

gt_obj_st * gt_init_screen_DrugLibrary_One(void)
{
	screen_DrugLibrary_One =  gt_obj_create(NULL);
	my_set_obj_title(screen_DrugLibrary_One,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(screen_DrugLibrary_One, gt_color_hex(0x000000));
	 

	/** img1 */
	img1 = gt_img_create(screen_DrugLibrary_One);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_60x60_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);



	/** lab2 */
	lab2 = gt_label_create(screen_DrugLibrary_One);
	gt_obj_set_pos(lab2, 420, 146);
	gt_obj_set_size(lab2, 55, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "2/8");


	/** svg1 */
	svg1 = gt_img_create(screen_DrugLibrary_One);
	gt_obj_set_pos(svg1, 425, 65);
	gt_obj_set_size(svg1, 48, 48);
	gt_img_set_src(svg1, "f:img_48x48_arrow_circle_up_101_4.png");
	gt_obj_add_event_cb(svg1, svg1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** svg2 */
	svg2 = gt_img_create(screen_DrugLibrary_One);
	gt_obj_set_pos(svg2, 425, 220);
	gt_obj_set_size(svg2, 48, 48);
	gt_img_set_src(svg2, "f:img_48x48_arrow_circle_down_101_5.png");


	/** lab3 */
	lab3 = gt_label_create(screen_DrugLibrary_One);
	gt_obj_set_pos(lab3, 150, 50);
	gt_obj_set_size(lab3, 180, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "去甲肾上腺素");


	/** lab4 */
	lab4 = gt_label_create(screen_DrugLibrary_One);
	gt_obj_set_pos(lab4, 166, 110);
	gt_obj_set_size(lab4, 150, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "西地兰");


	/** lab5 */
	lab5 = gt_label_create(screen_DrugLibrary_One);
	gt_obj_set_pos(lab5, 143, 170);
	gt_obj_set_size(lab5, 200, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "盐酸多巴酚丁胺");


	/** lab6 */
	lab6 = gt_label_create(screen_DrugLibrary_One);
	gt_obj_set_pos(lab6, 155, 230);
	gt_obj_set_size(lab6, 186, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "米力农");


	/** rect2 */
	rect2 = gt_rect_create(screen_DrugLibrary_One);
	gt_obj_set_pos(rect2, 90, 50);
	gt_obj_set_size(rect2, 300, 35);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);


	/** rect3 */
	rect3 = gt_rect_create(screen_DrugLibrary_One);
	gt_obj_set_pos(rect3, 90, 110);
	gt_obj_set_size(rect3, 300, 35);
	gt_obj_set_opa(rect3, GT_OPA_38);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);


	/** rect4 */
	rect4 = gt_rect_create(screen_DrugLibrary_One);
	gt_obj_set_pos(rect4, 90, 170);
	gt_obj_set_size(rect4, 300, 35);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);


	/** rect5 */
	rect5 = gt_rect_create(screen_DrugLibrary_One);
	gt_obj_set_pos(rect5, 90, 230);
	gt_obj_set_size(rect5, 300, 35);
	gt_obj_set_opa(rect5, GT_OPA_37);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);


	return screen_DrugLibrary_One;
}

