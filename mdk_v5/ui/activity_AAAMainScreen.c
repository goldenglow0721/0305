#include "ui.h"
#include "up.h"
#include "headbar_view.h"


#define recttest 1
//输注设定的其他语言都还没改

const char aaatitle[5][6][50]={
            "主菜单",
            "模式选择",		// 中
			"输注设定",
			"系统设定",
			"系统维护",
			"清除累计量",

			"Main Menu",		// 英
            "Select Mode",
			"General",
			"System",
			"Maintenance",			
			"Total Volume",

			"Menú Principal",		// 西
            "Seleccione el Modo",
			"General",
			"Sistema",
			"Mantenimiento",
			"Volumen Total",

			"主菜單",		// 繁
            "模式選擇",
			"參數設定",
			"系統設定",
			"系統維護",			
			"清除累計量",

			"Menu principal",		// 葡
            "Selecionar modo",
			"Geral",
			"Sistema",
			"Manutenção",			
			"Volume Total"
};

/** MainScreen */
gt_obj_st * MainScreen = NULL;
gt_obj_st * head_bar = NULL;
static _gt_timer_st * timer_main_onemin = NULL;
static _gt_timer_st * timer_main_ThirmSec = NULL;
static _gt_timer_st * timer_main_200mSec = NULL;
static gt_obj_st * Volume = NULL;
static gt_obj_st * Mode = NULL;
static gt_obj_st * System = NULL;
static gt_obj_st * General = NULL;
static gt_obj_st * Maintenance = NULL;
gt_obj_st * homelab[5] = {NULL, NULL, NULL, NULL, NULL};

static gt_obj_st * rect1 = NULL;
static gt_obj_st * svg6 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * modeselect = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * test = NULL;
static gt_obj_st * logo = NULL;

//Related statements
void create_headevent(gt_obj_st * obj);
extern gt_obj_st *  head;
extern _Bool enterkey;
extern gt_obj_st * content;

static void Timer_OneSecond(gt_event_st * e){
//	printf("Enter MainScreen\n");

	
	//检测电池状态
	BattetyStatusAlarm(sensorpack.batterystatus);
	BattetyLowAndDepleteAlarm(sensorpack.batterystatus);

	//检测报警
	ALARM_Message=GetCurrentAlarm(GetNowAlarmLeve1l(&InfusionNow.glevel));	//文字报警信息 已将文字报警信息放入ADDALARM中
	GetNowAlarmMessage(&InfusionNow.alarmmsg);
	
	if(GetAlarmLevel(ALARM_Message)==0) //若没有报警
	{
		SetAlarmSoundFlag(FALSE);
		alarm_data.Runtime = 0;
	}
	SoundManage(GetAlarmSoundFlag(),InfusionNow.alarmmsg);  //语音播报
	

	//头部和本部各一个一秒的消息
	gt_event_send(gt_disp_get_scr(),MY_ONE_SECONDS_TIME,NULL);
	gt_event_send_by_id(0,MYHEAD_ONE_SECONDS_TIME,NULL);
	
	/*night mode*/
	
	//WT588F_Send_Data(0x04);
	
	/*静音*/
	if((AlarmSoundTimeCountDown()==0)|| (GetNewSoundAFlag()) )  //在静音超过两分钟或者新报警标志为TRUE
	{
		//system("echo 0 > /sys/class/gpio/gpio140/value");
		SetAlarmSoundFlag(FALSE);
		SetNewSoundAFlag(FALSE);
		alarm_data.Runtime = 0;
	}

	/*电池耗尽关机*/
	if(DEPLETETimeCountDown()==0)
	{
		SetDEPLETEFlag(FALSE);
		//Write_Record_Events(EA_Shutdown,EA_Shutdown,NULL);
		ClearAllAlarm();
		//SendAckPackData(PWNID,ACK_CMD_PWN_CLOSE,0);
	}	

}


static void Timer_ThirmSec(gt_event_st * e){
	//300ms的定时器
	calpressureADandValue(ParamSetting.BlockLevel);
	//判断输液器
	if(enterkey != true && !judgeIsRunScreen())
	{
		JudgeInstallTube();
	}

}


/** enter modeselect */
static void mode_select(gt_event_st * e) {
	#if VP30
	gt_disp_stack_load_scr_anim(GT_SCR_ID_1, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
	#else
	gt_disp_stack_load_scr_anim(GT_SCR_ID_6, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
	#endif
}

/** EnterParamSetting */
static void EnterParam(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_2, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
}

/** EnterSystemSetting */
static void rect4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_3, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
}

/** maintenance */
static void rect5_0_cb(gt_event_st * e) {
	//要修改成进入键盘页面
	gt_disp_stack_load_scr_anim(GT_SCR_ID_4, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
}

/** ClearVolume */
static void rect6_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_SCR_ID_5, GT_SCR_ANIM_TYPE_NONE, 300, 0, false);
}


static void EventUpdata(gt_event_st * e){

	//关机
	if(atoi(e->param) == 999)  
	{
		//printf("enter main eventupdata\n");
		if(judgeIsRunScreen() || enterkey == true) //运行和键盘界面不能关机
		{
			return ;
		}
		//保存当前的窗口，进入关机界面
		if(gt_disp_get_scr() != shutdown)
		{
			gt_disp_stack_load_scr_anim(GT_SCR_ID_100, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
		}
		else
		{
			gt_disp_stack_go_back(1);
		}
	
	}
	else if(atoi(e->param) == 888)
	{
//		DeviceFlag = DEVICE_STOP;
//		vtaskmanage(1);
//		gpio_bits_reset(GPIOC,GPIO_PINS_13);
	}

}




gt_obj_st * gt_init_MainScreen(void)
{
	
	MainScreen =  gt_obj_create(NULL);

	my_set_obj_title(MainScreen,aaatitle[SystemSetting.langue][0]);

	gt_screen_set_bgcolor(MainScreen, gt_color_hex(0x000000));
	printf("Enter MainScreen\r\n");
	gt_obj_add_event_cb(MainScreen,EventUpdata,MY_EVENT_UPDATA,NULL);
	
	head_bar = gt_obj_create(MainScreen);

	ObDefValue();

	

	//gt_disp_st * temp1 = gt_disp_get_default();
	#if 0
	gt_obj_st *temp_obj = gt_obj_create(gt_disp_get_layer_top());
//	gt_btn_create(temp_obj);
	#endif
	//create_head(temp1->layer_top,aaatitle[SystemSetting.langue][0]);

	
	
	//初始化无操作报警
	InfusionNow.ReminderFlag = 1;
	create_headevent(MainScreen);

	/** Volume */
	Volume = gt_img_create(MainScreen);
	gt_obj_set_pos(Volume, 301, 186);
	gt_obj_set_size(Volume, 60, 60);
	gt_img_set_src(Volume, "f:img_60x60_refresh_0_1.png");

	/** select Mode */
	Mode = gt_img_create(MainScreen);
	gt_obj_set_pos(Mode, 77, 70);
	gt_obj_set_size(Mode, 60, 60);
	gt_img_set_src(Mode, "f:img_60x60_more_app_0_2.png");

	/** SystemSetting */
	System = gt_img_create(MainScreen);
	gt_obj_set_pos(System, 362, 70);
	gt_obj_set_size(System, 58, 60);
	gt_img_set_src(System, "f:img_58x60_setting_two_0_2.png");

	/** GeneralSetting */
	General = gt_img_create(MainScreen);
	gt_obj_set_pos(General, 218, 70);
	gt_obj_set_size(General, 60, 60);
	gt_img_set_src(General, "f:img_60x60_hamburger_button_0_3.png");
	gt_obj_add_event_cb(General, EnterParam, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** Maintenance */
	Maintenance = gt_img_create(MainScreen);
	gt_obj_set_pos(Maintenance, 130, 185);
	gt_obj_set_size(Maintenance, 60, 60);
	gt_img_set_src(Maintenance, "f:img_60x60_tool_0_4.png");

	
	/** lab1 */
	homelab[0] = gt_label_create(MainScreen);
	gt_obj_set_pos(homelab[0], 239, 253);
	gt_obj_set_size(homelab[0], 185, 35);
	gt_label_set_font_color(homelab[0], gt_color_hex(0xffffff));
	gt_label_set_font_size(homelab[0], 24);
	gt_label_set_font_family_cn(homelab[0], 20);
	gt_label_set_font_family_en(homelab[0], 33);
	gt_label_set_font_family_fl(homelab[0], 50);
	gt_label_set_font_align(homelab[0], GT_ALIGN_CENTER_MID);
	gt_label_set_text(homelab[0], aaatitle[SystemSetting.langue][5]);
	gt_obj_add_event_cb(homelab[0], rect6_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** lab3 */
	/** 模式选择-lab */
	homelab[2] = gt_label_create(MainScreen);
	gt_obj_set_pos(homelab[2], 31, 132);
	gt_obj_set_size(homelab[2], 150, 35);
	gt_label_set_font_family_cn(homelab[2], 20);
	gt_label_set_font_family_en(homelab[2], 33);
	gt_label_set_font_family_fl(homelab[2], 50);
	gt_label_set_font_color(homelab[2], gt_color_hex(0xffffff));
	gt_label_set_font_size(homelab[2], 24);
	gt_label_set_font_align(homelab[2], GT_ALIGN_CENTER_MID);
	gt_label_set_text(homelab[2], aaatitle[SystemSetting.langue][1]);
	gt_obj_add_event_cb(homelab[2], mode_select, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab4 */
	/** 参数设定-lab */
	homelab[3] = gt_label_create(MainScreen);
	gt_obj_set_pos(homelab[3], 181, 132);
	gt_obj_set_size(homelab[3], 138, 35);
	gt_label_set_font_family_cn(homelab[3], 20);
	gt_label_set_font_family_en(homelab[3], 33);
	gt_label_set_font_family_fl(homelab[3], 50);
	gt_label_set_font_color(homelab[3], gt_color_hex(0xffffff));
	gt_label_set_font_size(homelab[3], 24);
	gt_label_set_font_align(homelab[3], GT_ALIGN_CENTER_MID);
	gt_label_set_text(homelab[3], aaatitle[SystemSetting.langue][2]);
	gt_obj_add_event_cb(homelab[3], EnterParam, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab5 */
	/** 系统设定-lab */
	homelab[4] = gt_label_create(MainScreen);
	gt_obj_set_pos(homelab[4], 320, 132);
	gt_obj_set_size(homelab[4], 142, 35);
	gt_label_set_font_family_cn(homelab[4], 20);
	gt_label_set_font_family_en(homelab[4], 33);
	gt_label_set_font_family_fl(homelab[4], 50);
	gt_label_set_font_color(homelab[4], gt_color_hex(0xffffff));
	gt_label_set_font_size(homelab[4], 24);
	gt_label_set_font_align(homelab[4], GT_ALIGN_CENTER_MID);
	gt_label_set_text(homelab[4], aaatitle[SystemSetting.langue][3]);
	gt_obj_add_event_cb(homelab[4], rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab7 */
	/** 系统维护-lab */
	homelab[1] = gt_label_create(MainScreen);
	gt_obj_set_pos(homelab[1], 77, 252);
	gt_obj_set_size(homelab[1], 165, 35);
	gt_label_set_font_size(homelab[1], 24);
	gt_label_set_font_family_cn(homelab[1], 20);
	gt_label_set_font_family_en(homelab[1], 33);
	gt_label_set_font_family_fl(homelab[1], 50);
	gt_label_set_font_color(homelab[1], gt_color_hex(0xffffff));
	gt_label_set_font_align(homelab[1], GT_ALIGN_CENTER_MID);
	gt_label_set_text(homelab[1], aaatitle[SystemSetting.langue][4]);
	gt_obj_add_event_cb(homelab[1], rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	
	

	#if 0
	/** bat */
	svg6 = gt_img_create(MainScreen);
	gt_obj_set_pos(svg6, 388, 0);
	gt_obj_set_size(svg6, 48, 48);
	gt_img_set_src(svg6, "f:img_48x48_battery_charge_0_14.png");
	#endif

	#if 0
	/** btn1 */
	btn1 = gt_btn_create(MainScreen);
	gt_obj_set_pos(btn1, 0, 192);
	gt_obj_set_size(btn1, 60, 30);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 18);
	gt_btn_set_font_family_en(btn1, 33);
	gt_btn_set_font_family_fl(btn1, 50);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "btn");
	gt_btn_set_color_background(btn1, gt_color_hex(0x3580bb));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	#endif

	
	/** modeselect */
	modeselect = gt_rect_create(MainScreen);
	gt_obj_set_pos(modeselect, 56, 70);
	gt_obj_set_size(modeselect, 100, 94);
	gt_obj_set_opa(modeselect, GT_OPA_0);
	gt_rect_set_radius(modeselect, 0);
	gt_rect_set_bg_color(modeselect, gt_color_hex(0xffffff));
	gt_rect_set_color_border(modeselect, gt_color_hex(0xffffff));
	gt_rect_set_fill(modeselect, 0);
	gt_rect_set_border(modeselect, 0);
	gt_obj_add_event_cb(modeselect, mode_select, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	
	
	/** param */
	rect3 = gt_rect_create(MainScreen);
	gt_obj_set_pos(rect3, 203, 82);
	gt_obj_set_size(rect3, 93, 79);
	gt_obj_set_opa(rect3, GT_OPA_0);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect3, 0);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, EnterParam, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** systemsetting */
	rect4 = gt_rect_create(MainScreen);
	gt_obj_set_pos(rect4, 345, 78);
	gt_obj_set_size(rect4, 91, 86);
	gt_obj_set_opa(rect4, GT_OPA_0);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);
	gt_obj_add_event_cb(rect4, rect4_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	
	/** rect5 */
	rect5 = gt_rect_create(MainScreen);
	gt_obj_set_pos(rect5, 112, 190);
	gt_obj_set_size(rect5, 93, 96);
	gt_obj_set_opa(rect5, GT_OPA_0);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);
	gt_obj_add_event_cb(rect5, rect5_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	
	
	/** rect6 */
	rect6 = gt_rect_create(MainScreen);
	gt_obj_set_pos(rect6, 269, 191);
	gt_obj_set_size(rect6, 122, 100);
	gt_obj_set_opa(rect6, GT_OPA_0);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);
	gt_obj_add_event_cb(rect6, rect6_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	


	/**********************Other Message**********************************/


	/**********************************************************************/
	timer_main_onemin   =  _gt_timer_create(Timer_OneSecond,1000,NULL);
	timer_main_ThirmSec =  _gt_timer_create(Timer_ThirmSec,300,NULL);


	return MainScreen;
}

