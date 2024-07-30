#include "ui.h"
/*
		6686界面
		输入第一次液量 第二次液量的界面


*/




/** AccuracyCalibrate2_1 */
gt_obj_st * AccuracyCalibrate2_1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab8 = NULL;


static char buffer[50];

static const char title[5][4][80]={
	"精度校准",
	"第1次液量",
	"第2次液量",
	"请确认是否已正确输入所有校准参数",

	"IV Set Calibration",
	"Volume1",
	"Volume2",
	"If you input all correct parameter to finish Calibration?",

	"Calibración de IV Conjunto",
	"Volume1",
	"Volume2",
	"Si ingresa todo el parámetro correcto para finalizar la calibración?",

	"精度校準",
	"第1次液量",
	"第2次液量",
	"請確認是否已正確輸入所有校準參數？",

	"Calibração de equipo",
	"Volume 1",
	"Volume 2",
	"Se você inserir todos os parâmetros corretos para finalizar a calibração?"
		
};

static double sg_liquid1;
static double sg_liquid2;


static void ChangeLiquid1(gt_event_st * e){

	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &sg_liquid1;
	limit.toplimit = 9999.9;
	limit.lowerlimit = 0.01;
	keyboardf.id=24;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ChangeLiquid2(gt_event_st * e){
	strcpy(keyboardf.title,title[SystemSetting.langue][2]);
	keyboardf.data = &sg_liquid2;
	limit.toplimit = 9999.9;
	limit.lowerlimit = 0.01;
	keyboardf.id=25;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
	
}

static void back(gt_event_st * e) {
	gt_disp_stack_go_back(2);
}

static void Confirm(gt_event_st * e) {
	//保存数据
	infusion_data.Calibdata1 = sg_liquid1;
	infusion_data.Calibdata2 = sg_liquid2;
	//并且写入结构体
	writeInfusionTubeListToFlash();
	//修改的数据写入flash
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_53, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
	//加载屏幕
}

static void EventUpdata(gt_event_st * e)
{
	if(atoi(e->param) == 24)  //第一次液量
	{
		sprintf(buffer,"%.2f",sg_liquid1);
		gt_label_set_text(lab4,buffer);
	}
	if(atoi(e->param) == 25)  //第二次液量
	{
		sprintf(buffer,"%.2f",sg_liquid2);
		gt_label_set_text(lab5,buffer);
	}

}


gt_obj_st * gt_init_AccuracyCalibrate2_1(void)
{
	
	AccuracyCalibrate2_1 =  gt_obj_create(NULL);
	my_set_obj_title(AccuracyCalibrate2_1,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(AccuracyCalibrate2_1, gt_color_hex(0x000000));
	gt_obj_add_event_cb(AccuracyCalibrate2_1,EventUpdata,MY_EVENT_UPDATA,NULL);

	 



	/** img1 */
	img1 = gt_img_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab2 */
	lab2 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab2, 93, 70);
	gt_obj_set_size(lab2, 130, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab3, 93, 140);
	gt_obj_set_size(lab3, 130, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%s",title[SystemSetting.langue][2]);
	gt_label_set_text(lab3, buffer);


	/** lab4 */
	lab4 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab4, 223, 70);
	gt_obj_set_size(lab4, 118, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",sg_liquid1);
	gt_label_set_text(lab4,buffer);


	/** lab5 */
	lab5 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab5, 223, 140);
	gt_obj_set_size(lab5, 118, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",sg_liquid2);
	gt_label_set_text(lab5,buffer);


	/** lab6 */
	lab6 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab6, 341, 70);
	gt_obj_set_size(lab6, 75, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "mL");


	/** lab7 */
	lab7 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab7, 341, 140);
	gt_obj_set_size(lab7, 75, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "mL");


	/** rect2 */
	rect2 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect2, 93, 70);
	gt_obj_set_size(rect2, 130, 50);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,ChangeLiquid1,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect3 */
	rect3 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect3, 223, 70);
	gt_obj_set_size(rect3, 118, 50);
	gt_obj_set_opa(rect3, GT_OPA_41);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3,ChangeLiquid1,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** rect4 */
	rect4 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect4, 341, 70);
	gt_obj_set_size(rect4, 75, 50);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect4, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4,ChangeLiquid1,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** rect5 */
	rect5 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect5, 93, 140);
	gt_obj_set_size(rect5, 130, 50);
	gt_obj_set_opa(rect5, GT_OPA_50);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5,ChangeLiquid2,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect6 */
	rect6 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect6, 223, 140);
	gt_obj_set_size(rect6, 118, 50);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6,ChangeLiquid2,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** rect7 */
	rect7 = gt_rect_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(rect7, 341, 140);
	gt_obj_set_size(rect7, 75, 50);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	gt_obj_add_event_cb(rect7,ChangeLiquid2,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** btn1 */
	btn1 = gt_btn_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(btn1, 390, 274);
	gt_obj_set_size(btn1, 76, 46);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "OK");
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(AccuracyCalibrate2_1);
	gt_obj_set_pos(lab8, 94, 200);
	gt_obj_set_size(lab8, 321, 74);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_LEFT);
	sprintf(buffer,"%s",title[SystemSetting.langue][3]);
	gt_label_set_text(lab8,buffer);


	return AccuracyCalibrate2_1;
}

