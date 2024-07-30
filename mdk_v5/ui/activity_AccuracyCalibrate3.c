#include "ui.h"

/*


		输入第一次液量


	:注   刚输入就会得到保存


*/









static const char title[5][7][80]={
	"精度校准",
	"液量1",
	"第1次液量",
	"第2次液量",
	"2.请输入第1次量杯收集的实际液量。",
	"4.请输入第2次量杯收集的实际液量。",
	"确认",

	"IV Set Calibration",
	"Volume1",
	"Volume1",
	"Volume2",
	"2.First time input the value of liquid volume.",
	"4.Second time input the value of liquid volume.",
	"Confirm",

	"Calibración de IV Conjunto",
	"Volumen1",
	"Volume1",
	"Volume2",
	"2.Ingreso por primera vez el valor del volumen líquido.",
	"4.Ingreso por segunda vez el valor del volumen líquido.",
	"Confirmar",

	"精度校準",
	"液量1",
	"第1次液量",
	"第2次液量",
	"2.請輸入第1次量杯收集的實際液量。",
	"4.請輸入第2次量杯收集的實際液量。",
	"確認",

	"Calibração de equipo",
	"Volume1",
	"Volume 1",
	"Volume 2",
	"2.Insira pela primeira vez o valor do volume do líquido.",
	"4.Insira pela segunda vez o valor do volume do líquido.",
	"Confirmar"
		
};



/** AccuracyCalibrate3 */
gt_obj_st * AccuracyCalibrate3 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;

extern int BrandSerialNumber;
static int sg_RecData;

static double sg_liquid1;
static double sg_liquid2;

static char buffer[50];
/** 返回 */
static void Back(gt_event_st * e) {

	TMC2226_MotorStop();
	gt_disp_stack_go_back(4);
}

static void Confirm(gt_event_st * e){
	if(sg_RecData == 1)
	{		
		gt_disp_stack_load_scr_anim(GT_SCR_ID_50, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
	}
	else if(sg_RecData == 2)
	{
		//保存数据
		InfusionNode_t* tempnode = fineInfusionNodeByPosit(BrandSerialNumber);
		//取出内容
		infusion_data.Calibdata1 = tempnode->message.Calibdata1;
		infusion_data.Calibdata2 = tempnode->message.Calibdata2;
		infusion_data.Calibdata1 = sg_liquid1;
		infusion_data.Calibdata2 = sg_liquid2;
		//并且写入结构体

		writeInfusionTubeListToFlash();
		//校准后数据写入flash

		gt_disp_stack_load_scr_anim(GT_SCR_ID_53, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);
		//加载屏幕
	}
}

//输入
static void Input(gt_event_st* e){
	//将精度值传给相应的变量
	if(sg_RecData == 1)
	{
		strcpy(keyboardf.title,title[SystemSetting.langue][1]);
		keyboardf.data = &sg_liquid1;
		limit.lowerlimit=0.01;
		limit.toplimit=20.00;
		keyboardf.id=26;
	}
	else if(sg_RecData == 2)
	{
		strcpy(keyboardf.title,title[SystemSetting.langue][2]);
		keyboardf.data = &sg_liquid2;
		limit.lowerlimit=0.01;
		limit.toplimit=20.00;
		keyboardf.id=27;
	}
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 0, 0, false);
}


static void EventUpdata(gt_event_st * e)
{
	if(sg_RecData == 1)
	{
		if(atoi(e->param) == 26)  //修改完第一次液量出来的
		{
			sprintf(buffer,"%.2f",sg_liquid1);
			gt_label_set_text(lab4, buffer);
		}
	}
	else
	{	
		if(atoi(e->param) == 27)  //修改完第二次液量出来的
		{
			sprintf(buffer,"%.2f",sg_liquid2);
			gt_label_set_text(lab4, buffer);
		}
	}
}



gt_obj_st * gt_init_AccuracyCalibrate3()
{

	if(calibrate)
	{
		sg_RecData = 2;
	}
	else
	{
		sg_RecData = 1;
	}

	calibrate = true;

	AccuracyCalibrate3 =  gt_obj_create(NULL);
	my_set_obj_title(AccuracyCalibrate3,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(AccuracyCalibrate3, gt_color_hex(0x000000));
	gt_obj_add_event_cb(AccuracyCalibrate3,EventUpdata,MY_EVENT_UPDATA,NULL);


	/** img1 */
	/** ReturnIcon */
	img1 = gt_img_create(AccuracyCalibrate3);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, Back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab1 */
	lab1 = gt_label_create(AccuracyCalibrate3);
	gt_obj_set_pos(lab1, 50, 70);
	gt_obj_set_size(lab1, 380, 80);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 20);
	gt_label_set_font_family_en(lab1, 33);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT_MID);
	if(sg_RecData == 1)
	{
		gt_label_set_text(lab1, title[SystemSetting.langue][4]);
	}
	else if(sg_RecData == 2)
	{
		gt_label_set_text(lab1, title[SystemSetting.langue][5]);
	}
	


	

	/** btn1 */
	btn1 = gt_btn_create(AccuracyCalibrate3);
	gt_obj_set_pos(btn1, 384, 274);
	gt_obj_set_size(btn1, 80, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][6]);
	gt_btn_set_color_background(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x808080));
	gt_btn_set_color_border(btn1, gt_color_hex(0x000000));
	gt_btn_set_border_width(btn1, 1);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1,Confirm,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** lab2 */
	lab2 = gt_label_create(AccuracyCalibrate3);
	gt_obj_set_pos(lab2, 50, 160);
	gt_obj_set_size(lab2, 140, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	if(sg_RecData == 1)
	{
		gt_label_set_text(lab2,title[SystemSetting.langue][2]);
	}
	else if(sg_RecData == 2)
	{
		gt_label_set_text(lab2,title[SystemSetting.langue][3]);
	}
	


	/** lab3 */
	lab3 = gt_label_create(AccuracyCalibrate3);
	gt_obj_set_pos(lab3, 350, 160);
	gt_obj_set_size(lab3, 52, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "ml");


	/** lab4 */
	lab4 = gt_label_create(AccuracyCalibrate3);
	gt_obj_set_pos(lab4, 225, 160);
	gt_obj_set_size(lab4, 100, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	if(sg_RecData == 1)
	{
		sprintf(buffer,"%.2f",infusion_data.Calibdata1);
	}
	else if(sg_RecData == 2)
	{
		sprintf(buffer,"%.2f",infusion_data.Calibdata2);
	}
	else
	{
		;
	}
	gt_label_set_text(lab4, buffer);


	/** rect1 */
	rect1 = gt_rect_create(AccuracyCalibrate3);
	gt_obj_set_pos(rect1, 50, 160);
	gt_obj_set_size(rect1, 140, 50);
	gt_obj_set_opa(rect1, GT_OPA_50);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);
	gt_obj_add_event_cb(rect1,Input,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** rect2 */
	rect2 = gt_rect_create(AccuracyCalibrate3);
	gt_obj_set_pos(rect2, 190, 160);
	gt_obj_set_size(rect2, 220, 50);
	gt_obj_set_opa(rect2, GT_OPA_30);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);
	gt_obj_add_event_cb(rect2,Input,GT_EVENT_TYPE_INPUT_RELEASED,NULL);



	return AccuracyCalibrate3;
}

