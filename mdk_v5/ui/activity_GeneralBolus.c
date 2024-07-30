#include "ui.h"


/** GeneralBolus */
gt_obj_st * GeneralBolus = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab11 = NULL;

extern BolusModeRun Bolus_ModeRun;
static int ReturnTime = 0;
static const char title[5][6][75]={
	"快进",
	"快进流速",
	"快进待入量",
	"快进时间",
	"自动快进",
	"长按快进按键开始手动快进",

	"Bolus",
	"Bolus Rate",
	"Bolus VTBI",
	"Bolus Time",
	"Auto Bolus",
	"Press and hold the fast forward button to manually fast forward.",

	"Bolo",
	"Tasa de Bolo",
	"VTBI de Bolo",
	"Tiempo de Bolo",
	"Bolo Auto",
	"Presiona y mantén el botón de avance rápido para avanzar manualmente.",

	"快進",
	"快進流速",
	"快進待入量",
	"快進時間",
	"自動快進",
	"長按快進按鍵手動快進。",

	"Bolus",
	"Taxa de Bolus",
	"VTBI Bolus",
	"Tempo de Bolus",
	"Auto Bolus",
	"Pressione e segure o botão de avanço rápido para avançar manualmente."
		
};





static void img1_0_cb(gt_event_st * e) {
	
	gt_disp_stack_go_back(1);
}


static void BolusModeSpeed(gt_event_st * e) {
	
	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &BolusMode.speed;
	keyboardf.id=20;
	limit.toplimit = SystemMaintain.MaxSpeed;
	limit.lowerlimit = 0.1;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}



static void BolusModeQuantity(gt_event_st * e) {

	strcpy(keyboardf.title,title[SystemSetting.langue][2]);
	keyboardf.data = &BolusMode.quantity;
	keyboardf.id=21;
	limit.toplimit = 50.0;
	limit.lowerlimit = 0.5;
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}

static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 20)  //修改完速度出来的
	{
		
		UpdateSpeedModeTheDisplay(CHANGE_Speed,&BolusMode.speed,&BolusMode.quantity,&BolusMode.time);
		//更新速度显示
		sprintf(buffer,"%.2f",BolusMode.speed);
		gt_label_set_text(lab5, buffer); 	
	
		if(DripMode.time.hour>99)
		{
			BolusMode.time.hour=100;
			BolusMode.time.min=0;
			BolusMode.time.sec=0;			
			sprintf(buffer,">%d:%d:%d", 99, 59, 59);
		}
		else
		{
			if(BolusMode.quantity!=0.0 && BolusMode.speed!=0.0)
				sprintf(buffer,"%d:%d:%d", BolusMode.time.hour, BolusMode.time.min, BolusMode.time.sec);
			else
				sprintf(buffer,"%s:%s:%s","--","--","--"); 
		}	
		gt_label_set_text(lab9, buffer);
	}
	if(atoi(e->param) == 21)  //修改完待入量出来的
	{
		UpdateSpeedModeTheDisplay(CHANGE_QUAN,&BolusMode.speed,&BolusMode.quantity,&BolusMode.time);
		//更新待入量
		sprintf(buffer,"%.2f",BolusMode.quantity);
		gt_label_set_text(lab7, buffer);
		if(BolusMode.time.hour>99)
		{
			BolusMode.time.hour=100;
			BolusMode.time.min=0;
			BolusMode.time.sec=0;			
			sprintf(buffer,">%d:%d:%d", 99, 59, 59);
		}
		else
		{
			if(BolusMode.quantity!=0.0 && BolusMode.speed!=0.0)
				sprintf(buffer,"%d:%d:%d", BolusMode.time.hour, BolusMode.time.min, BolusMode.time.sec);
			else
				sprintf(buffer,"%s:%s:%s","--","--","--"); 
		}
		gt_label_set_text(lab9, buffer);
	}
}

//1s的消息
static void Timer_OneSecond(gt_event_st * e){
	
	ReturnTime++;
	if(ReturnTime == 15)
		gt_disp_stack_go_back(1);

}



extern double sg_speedandtimemoderun_NowCumulant;
extern double sg_weightmoderun_NowCumulant;
extern double sg_dripmoderun_NowCumulant;

static void btn1_0_cb(gt_event_st * e) {
	char buffer[30];
	Bolus_ModeRun.quantity = &BolusMode.quantity;
	Bolus_ModeRun.speed 	= &BolusMode.speed;
	Bolus_ModeRun.time		= &BolusMode.time;

	press_Data.Pressure_newAD0 = sensorpack.DownPressure;
	if(my_judge_obj_exists(GT_SCR_ID_96)) //保存运行模式下的已入量值
	{
		SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
	}
	else if(my_judge_obj_exists(GT_SCR_ID_97))
	{
		SetNowcumulant(sg_weightmoderun_NowCumulant);
	}
	else if(my_judge_obj_exists(GT_SCR_ID_99))
	{
		SetNowcumulant(sg_dripmoderun_NowCumulant);
	}

	gt_disp_stack_load_scr_anim(GT_SCR_ID_93, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


static void KEY_EVENT(gt_event_st * e) {

	if(atoi(e->param) == 2) //up longdown
	{
		#if 0

		if(BolusMode.speed == 0)
		{
			dialog1_create("请输出快进流速！");
		}
		else if(BolusMode.speed == 0)
		{
			dialog1_create("请输入快进代入量！");
		}
		#endif

		//进入快进界面,并且判断按键电平，随后复位
		Bolus_ModeRun.quantity = &BolusMode.quantity;
		Bolus_ModeRun.speed 	= &BolusMode.speed;
		Bolus_ModeRun.time		= &BolusMode.time;

		press_Data.Pressure_newAD0 = sensorpack.DownPressure;
		if(my_judge_obj_exists(GT_SCR_ID_96)) //保存运行模式下的已入量值
		{
			SetNowcumulant(sg_speedandtimemoderun_NowCumulant);
		}
		else if(my_judge_obj_exists(GT_SCR_ID_97))
		{
			SetNowcumulant(sg_weightmoderun_NowCumulant);
		}
		
		gt_disp_stack_load_scr_anim(GT_SCR_ID_93, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
		

		gt_event_send(GeneralBolusRun,MY_EVENT_UPDATA,"1");
	}
	
}


gt_obj_st * gt_init_GeneralBolus(void)
{
	char buffer[50];
	not_first_start_write_history_info(EA_Into,Ev_EntBolus,NULL);

	GeneralBolus =  gt_obj_create(NULL);
	my_set_obj_title(GeneralBolus,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(GeneralBolus, gt_color_hex(0x000000));
	gt_obj_add_event_cb(GeneralBolus,KEY_EVENT,MY_KEY_EVENT,NULL);
	gt_obj_add_event_cb(GeneralBolus,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_obj_add_event_cb(GeneralBolus, Timer_OneSecond,MY_ONE_SECONDS_TIME, NULL);



	/** img1 */
	img1 = gt_img_create(GeneralBolus);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab2 */
	lab2 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab2, 15,60);
	gt_obj_set_size(lab2, 140, 50);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][1]);


	/** lab3 */
	lab3 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab3, 170, 60);
	gt_obj_set_size(lab3, 140, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][2]);



	/** lab4 */
	lab4 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab4, 325, 60);
	gt_obj_set_size(lab4, 140, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][3]);



	/** rect2 */
	rect2 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect2, 15, 60);
	gt_obj_set_size(rect2, 140, 50);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, BolusModeSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	rect3 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect3, 170, 60);
	gt_obj_set_size(rect3, 140, 50);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, BolusModeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect4, 325, 60);
	gt_obj_set_size(rect4, 140, 50);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	my_rect_set_feedback(rect4,false);



	/** lab5 */
	lab5 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab5, 15, 110);
	gt_obj_set_size(lab5, 140, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",BolusMode.speed);
	gt_label_set_text(lab5, buffer); 


	/** lab6 */
	lab6 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab6, 15, 160);
	gt_obj_set_size(lab6, 140, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "mL/h");


	/** rect5 */
	rect5 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect5, 15, 110);
	gt_obj_set_size(rect5, 140, 105);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, BolusModeSpeed, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab7 */
	lab7 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab7, 170, 110);
	gt_obj_set_size(lab7, 140, 50);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%.2f",BolusMode.quantity);
	gt_label_set_text(lab7,buffer);


	/** lab8 */
	lab8 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab8, 170, 160);
	gt_obj_set_size(lab8, 140, 50);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "mL/h");


	/** rect6 */
	rect6 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect6, 170, 110);
	gt_obj_set_size(rect6, 140, 105);
	gt_obj_set_opa(rect6, GT_OPA_41);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect6, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, BolusModeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab9 */
	lab9 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab9, 325, 110);
	gt_obj_set_size(lab9, 140, 50);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d:%d:%d",BolusMode.time.hour,BolusMode.time.min,BolusMode.time.sec);
	gt_label_set_text(lab9, buffer);


	/** lab10 */
	lab10 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab10, 325, 160);
	gt_obj_set_size(lab10, 140, 50);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, "h:m:s");


	/** rect7 */
	rect7 = gt_rect_create(GeneralBolus);
	gt_obj_set_pos(rect7, 325, 110);
	gt_obj_set_size(rect7, 140, 105);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);
	my_rect_set_feedback(rect7,false);



	/** btn1 */
	btn1 = gt_btn_create(GeneralBolus);
	gt_obj_set_pos(btn1, 162, 250);
	gt_obj_set_size(btn1, 163, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, title[SystemSetting.langue][4]);
	gt_btn_set_color_background(btn1, gt_color_hex(0x00ff40));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x228B22));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab11 */
	lab11 = gt_label_create(GeneralBolus);
	gt_obj_set_pos(lab11, 40, 192);
	gt_obj_set_size(lab11, 400, 75);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, title[SystemSetting.langue][5]);

	

	return GeneralBolus;
}

