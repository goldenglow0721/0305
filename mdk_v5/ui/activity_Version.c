#include "ui.h"
#include "infusion.h"

/** Version */
gt_obj_st * Version = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;

static const char title[5][1][50]={
	"版本信息",

	"Version",

	"Versión",

	"版本資訊",

	"Versão"
		
};



static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_Version(void)
{
	Version =  gt_obj_create(NULL);
	my_set_obj_title(Version,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(Version, gt_color_hex(0x000000));
	 


	/** img1 */
	img1 = gt_img_create(Version);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(Version);
	gt_obj_set_pos(lab2, 30, 55);
	gt_obj_set_size(lab2, 180, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_text(lab2, "系统软件版本：");


	/** lab3 */
	lab3 = gt_label_create(Version);
	gt_obj_set_pos(lab3, 30, 100);
	gt_obj_set_size(lab3, 180, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, "驱动软件版本：");


	/** lab4 */
	lab4 = gt_label_create(Version);
	gt_obj_set_pos(lab4, 30, 145);
	gt_obj_set_size(lab4, 153, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_text(lab4, "序列号：");


	/** lab5 */
	lab5 = gt_label_create(Version);
	gt_obj_set_pos(lab5, 194, 55);
	gt_obj_set_size(lab5, 180, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_text(lab5, "V01.00.01.23");


	/** lab6 */
	lab6 = gt_label_create(Version);
	gt_obj_set_pos(lab6, 194, 100);
	gt_obj_set_size(lab6, 180, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT);
	gt_label_set_text(lab6, "V01.01.00.06");


	/** lab7 */
	lab7 = gt_label_create(Version);
	gt_obj_set_pos(lab7, 194, 190);
	gt_obj_set_size(lab7, 190, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, "NO.58-00004-00");


	/** lab8 */
	lab8 = gt_label_create(Version);
	gt_obj_set_pos(lab8, 194, 145);
	gt_obj_set_size(lab8, 140, 35);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab8, "23060025");


	/** lab9 */
	lab9 = gt_label_create(Version);
	gt_obj_set_pos(lab9, 30, 189);
	gt_obj_set_size(lab9, 151, 35);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab9, "物料号：");


	return Version;
}

