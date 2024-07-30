
#include "ui.h"



/** logo */
gt_obj_st * Logo = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * clock1 = NULL;
static gt_obj_st * timer2 = NULL;
static gt_obj_st * head = NULL;
gt_obj_st * RightVoltagevalue  =  NULL;
gt_obj_st * RightTime  =  NULL;
gt_obj_st * RightVoltagevalueimg  =  NULL;
gt_obj_st * Rightwarning  =  NULL;
gt_obj_st * content  =  NULL;
//gt_obj_st * RightTime  =  NULL;

static const gt_scr_list_st gt_scr_list[]={
	{GT_SCR_ID_HOME,gt_init_MainScreen},
	{GT_SCR_ID_1,gt_init_ModeSelect}, 
	{GT_SCR_ID_2,gt_init_ParamSetting1},
	{GT_SCR_ID_3,gt_init_SystemSetting1},
	{GT_SCR_ID_4,gt_init_screen_keyBoard_PassWord},
	{GT_SCR_ID_5,gt_init_ClearAccumVol},
	{GT_SCR_ID_6,gt_init_SpeedMode},
	{GT_SCR_ID_7,gt_init_TimeMode},
	{GT_SCR_ID_8,gt_init_WeightMode},
	{GT_SCR_ID_9,gt_init_SeqMode},
	{GT_SCR_ID_10,gt_init_DripMode},
	{GT_SCR_ID_11,NULL},
	{GT_SCR_ID_12,NULL},
	{GT_SCR_ID_13,NULL},
	{GT_SCR_ID_14,NULL},
	{GT_SCR_ID_15,NULL},
	{GT_SCR_ID_16,gt_init_DrugChoice},
	{GT_SCR_ID_17,gt_init_WeightMode2},//
	{GT_SCR_ID_18,NULL},
	{GT_SCR_ID_19,NULL},
	{GT_SCR_ID_20,NULL},
	{GT_SCR_ID_21,gt_init_ParamSetting2},
	{GT_SCR_ID_22,gt_init_ParamSetting3},
	{GT_SCR_ID_23,gt_init_ParamSetting4},
	{GT_SCR_ID_24,gt_init_PressureNumSel},
	{GT_SCR_ID_25,gt_init_PressureUnit},
	{GT_SCR_ID_26,gt_init_PurgeSizeSetting},
	{GT_SCR_ID_27,NULL},
	{GT_SCR_ID_28,NULL},
	{GT_SCR_ID_29,NULL},
	{GT_SCR_ID_30,NULL},
	{GT_SCR_ID_31,gt_init_SystemSetting2},
	{GT_SCR_ID_32,gt_init_HistoryView},
	{GT_SCR_ID_33,gt_init_Version},
	{GT_SCR_ID_34,gt_init_NightSetting},
	{GT_SCR_ID_35,NULL},
	{GT_SCR_ID_36,NULL},
	{GT_SCR_ID_37,NULL},
	{GT_SCR_ID_38,NULL},
	{GT_SCR_ID_39,NULL},
	{GT_SCR_ID_40,NULL},
	{GT_SCR_ID_41,gt_init_Maintenance1_1},
	{GT_SCR_ID_42,gt_init_Maintenance1_2},
	{GT_SCR_ID_43,gt_init_Maintenance1_3},
	{GT_SCR_ID_44,gt_init_Maintenance1_4},
	{GT_SCR_ID_45,gt_init_Maintenance1_5},
	{GT_SCR_ID_46,gt_init_Maintenance2_1},
	{GT_SCR_ID_47,gt_init_Maintenance2_2},
	{GT_SCR_ID_48,gt_init_DrugDelete},
	{GT_SCR_ID_49,gt_init_DeleteBrand},
	{GT_SCR_ID_50,gt_init_AccuracyCalibrate1},
	{GT_SCR_ID_51,gt_init_AccuracyCalibrate2},
	{GT_SCR_ID_52,gt_init_AccuracyCalibrate3},
	{GT_SCR_ID_53,gt_init_AccuracyCalibrate4},
	{GT_SCR_ID_54,gt_init_PressureCalibrate1},
	{GT_SCR_ID_55,gt_init_PressureCalibrate2},
	{GT_SCR_ID_56,gt_init_ExportHistory},
	{GT_SCR_ID_57,gt_init_RestoreFactory},
	{GT_SCR_ID_58,gt_init_SystemLanguageSetting},
	{GT_SCR_ID_59,gt_init_SystemDataTimeSetting},
	{GT_SCR_ID_60,gt_init_SystemCheck},
	{GT_SCR_ID_61,gt_init_AccuracyCalibrate2_1},
	{GT_SCR_ID_62,gt_init_SensorMonitor},
	{GT_SCR_ID_63,gt_init_DeleteHistory},
	{GT_SCR_ID_64,gt_init_BootUp},
	{GT_SCR_ID_65,gt_init_PowerOff},
	{GT_SCR_ID_66,NULL},
	{GT_SCR_ID_67,NULL},
	{GT_SCR_ID_68,NULL},
	{GT_SCR_ID_69,NULL},
	{GT_SCR_ID_70,NULL},
	{GT_SCR_ID_71,NULL},
	{GT_SCR_ID_72,NULL},
	{GT_SCR_ID_73,NULL},
	{GT_SCR_ID_74,NULL},
	{GT_SCR_ID_75,NULL},
	{GT_SCR_ID_76,NULL},
	{GT_SCR_ID_77,NULL},
	{GT_SCR_ID_78,NULL},
	{GT_SCR_ID_79,NULL},
	{GT_SCR_ID_80,gt_init_Screen_KeyBoard_Int},
	{GT_SCR_ID_81,gt_init_screen_keyBoard_float},
	{GT_SCR_ID_82,gt_init_TimeKeyBoard},
	{GT_SCR_ID_83,gt_init_Screen_KeyBoard_Soft},
	{GT_SCR_ID_84,gt_init_Standby},
	{GT_SCR_ID_85,gt_init_Purge},
	{GT_SCR_ID_86,gt_init_PurgeRun},
	{GT_SCR_ID_87,gt_init_BrandChoice},
	{GT_SCR_ID_88,gt_init_BrandChoice2},
	{GT_SCR_ID_89,gt_init_DoseUnit},
	{GT_SCR_ID_90,gt_init_KVORun},
	{GT_SCR_ID_91,gt_init_DrugUnit},
	{GT_SCR_ID_92,gt_init_GeneralBolus},
	{GT_SCR_ID_93,gt_init_GeneralBolusRun},
	{GT_SCR_ID_94,gt_init_SeqBolus},
	{GT_SCR_ID_95,gt_init_SeqBolusRun},
	{GT_SCR_ID_96,gt_init_SpeedAndTimeModeRun},
	{GT_SCR_ID_97,gt_init_WeightModeRun},
	{GT_SCR_ID_98,gt_init_SeqModeRun},
	{GT_SCR_ID_99,gt_init_DripModeRun},
	{GT_SCR_ID_100,gt_init_shutdown},
};


//报警音暂停 关闭
static void btn_callback(gt_event_st * e){

    #if 1

    if(JudgedYesNoAlarm(ALARM_NO_OPERATION))
    {
        InfusionNow.ReminderFlag=0;
        SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
    }
    ClearAlarm(ALARM_NO_OPERATION);
    #if VET_USE
    if(JudgedYesNoAlarm(ALARM_NET_POWER_OFF))
    {
        ClearAlarm(ALARM_NET_POWER_OFF);
    }
    #endif
    /*if((GetNowAlarmLeve12()!=H_ALARM)&&(GetNowAlarmLeve12()!=M_ALARM)&&(GetNowAlarmLeve12()!=L_ALARM))
    {
        ClearLowAlarm();
    }*/
    
    alarmflag=AlarmSoundSwitch(InfusionNow.glevel,JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE)); //静音
    
    if(alarmflag!=4)
    {
        if(alarmflag==3)
        {
            CleargHintAlarm(); //清除提示信息
			gt_obj_set_visible(gt_status_bar_right_add_icon("f:img_30x30_AudioPause.png"),GT_VISIBLE);
        }
        else if(alarmflag==5)
        {
            ClearLowAlarm();
            gt_obj_set_visible(gt_status_bar_right_add_icon("f:img_30x30_AudioPause.png"),GT_VISIBLE);
        }
        
        #if wait
        SendMessage(hWnd,MSG_CLOSE,0,0);
        #endif
    }
		gt_status_bar_set_bg_color(gt_color_hex(0x778899));
		gt_status_bar_set_font_color(gt_color_hex(0xffffff));  
		gt_obj_set_visible(gt_status_bar_right_add_icon("f:img_30x30_AudioPause.png"),GT_INVISIBLE);
    #endif
}


/** 返回 */
static void exitlogo(gt_event_st * e) {
	
	//喇叭、灯、蜂鸣器
	WT588F_Send_Data(0x04);  //bi
	led_on(ARM_RLED);
	delay_ms(500);

	WT588F_Send_Data(0x04);
	led_off(ARM_RLED);
	led_on(ARM_YLED);
	WT588F_Send_Data(0x04);
	delay_ms(500);

	TMC2226_MotorRun(1,0,2000);
	delay_ms(1500);
	TMC2226_MotorStop();

	BeepStart();
	led_off(ARM_YLED);
	WT588F_Send_Data(0x04);

	delay_ms(500);
	BeepStop();

	//gt_disp_stack_load_scr(gt_init_BootUp);
// 	create_head();
	
// }

// void create_head(gt_obj_st * obj,const char * str)
// {
	char buffer[50];

	/** status_bar1 */
	head = gt_status_bar_create(true);
	gt_status_bar_set_height(50);
	gt_status_bar_set_scale(120, 170, 120);
	gt_status_bar_show_bg(true);
	gt_status_bar_set_bg_color(gt_color_hex(0x778899));
	//strcpy(buffer,str);
	//content = gt_status_bar_left_add_text(buffer,80);
	content = gt_status_bar_left_add_text("主菜单",140);
	
	//gt_status_bar_left_change_text(content,str);
	gt_status_bar_custom_add_icon("f:img_130x50_button120X50.png");
	
 	gt_obj_st * mute = gt_status_bar_custom_add_text("报警音暂停", 130);
	gt_obj_set_visible(mute ,GT_INVISIBLE);
	gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_130x50_button120X50.png") ,GT_INVISIBLE);
	gt_status_bar_custom_find_by("报警音暂停");
	gt_obj_add_event_cb(mute, btn_callback, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	//gt_status_bar_left_add_text("报警音暂停", 120);
	Rightwarning = gt_status_bar_custom_add_text("网电源脱落",150);
	gt_obj_set_pos(Rightwarning,135,0);
	gt_obj_set_visible(Rightwarning,GT_INVISIBLE);

	sprintf(buffer,"%d%%%%",sensorpack.voltagevalue);
	//RightVoltagevalue = gt_status_bar_right_add_text(buffer, 50);
	RightVoltagevalue = gt_status_bar_custom_add_text(buffer, 50);
	gt_obj_set_pos(RightVoltagevalue,430,5);

    //电池电量百分比显示
 
	if((80 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 100))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_4.png");
	else if((60 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 80))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_3.png");
	else if((40 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 60))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_2.png");
	else if((20 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 40))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_1.png");
	else if((5 <=  sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 20))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_0.png");
	else if((0 <=  sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 5))
        RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_00.png");
	else
		RightVoltagevalueimg = gt_status_bar_custom_add_icon("f:img_65x35_battery_5.png");
	gt_obj_set_pos(RightVoltagevalueimg,365,8);
	gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png");
	gt_obj_set_pos(gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png"),330,8);
	gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png"),GT_INVISIBLE);
	//rtc_time_get();
	sprintf(buffer,"%02d:%02d",calendar.hour,calendar.min);
	//RightTime = gt_status_bar_right_add_text(buffer, 60);

	RightTime = gt_status_bar_custom_add_text(buffer, 60);
	gt_obj_set_pos(RightTime,270,5);


	gt_status_bar_set_font_size(24);
	gt_status_bar_set_font_family_cn(GT_FAMILY_GBK_24_HT);
	gt_status_bar_set_font_family_fl(50);
	gt_status_bar_set_font_gray(1);
	gt_status_bar_set_font_color(gt_color_hex(0xffffff));
	gt_status_bar_set_font_thick_cn(22);
	gt_status_bar_set_font_thick_en(22);
	
	gt_scr_stack_register_id_list(gt_scr_list,sizeof(gt_scr_list)/sizeof(gt_scr_list[0]),20);
	gt_scr_stack_set_home_scr_id(GT_SCR_ID_HOME,true);
	gt_disp_stack_load_scr(GT_SCR_ID_HOME);





}

gt_obj_st * gt_init_Logo(void)
{
	Logo = gt_obj_create(NULL);
	gt_screen_set_bgcolor(Logo, gt_color_hex(0x000000));

	#if fydb
	img1 = gt_img_create(Logo);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 320);
	gt_img_set_src(img1, "f:img_480x320_fydb.png");

	#elif zhongke
	/** img1 */
	img1 = gt_img_create(Logo);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 320);
	gt_img_set_src(img1, "f:img_480x320_zhongke.png");
	#elif yiye
	/** img1 */
	img1 = gt_img_create(Logo);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 320);
	gt_img_set_src(img1, "f:img_480x320_yiye.png");
	#elif ansha
	img1 = gt_img_create(Logo);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 320);
	gt_img_set_src(img1, "f:img_480x320_ansha.png");
	#elif zhongxing_en
	/** img1 */
	img1 = gt_img_create(Logo);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 320);
	gt_img_set_src(img1, "f:img_480x320_zhongxing_en_vet.png");
	#endif

	clock1 = gt_clock_create(Logo);
	gt_obj_set_pos(clock1, 201, 150);
	gt_obj_set_size(clock1, 153, 38);
	gt_clock_set_font_color(clock1, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock1, 24);
	gt_clock_set_font_align(clock1, GT_ALIGN_LEFT);
	gt_clock_set_alert_time(clock1, 0, 0, 0);
	gt_clock_set_mode(clock1, GT_CLOCK_MODE_COUNTDOWN);
	gt_clock_set_time(clock1, 00, 00, 02);
	gt_clock_start(clock1);
	gt_clock_set_alert_cb(clock1, exitlogo, NULL);
	gt_obj_set_visible(clock1,GT_INVISIBLE);

	return Logo;
}

