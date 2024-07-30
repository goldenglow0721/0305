#include "headbar_view.h"
#include "up.h"
#include "ui.h"
#include "battery_manage.h"

static const char title[5][2][50]={
    "报警音暂停",
    "报警关闭",

    "Audio Pause",
    "Alarm Off",

    "Pausa de Audio",
    "Apagado de Audio",
    
    "報警音暫停",
    "報警關閉",
    
    "Pausa de alarme",
    "Alarme desligado"

};

/* 差 报警音暂停的图标*/








_Bool enterkey = false; 
gt_obj_st * headlabel  =  NULL;
static gt_obj_st * headlab2  =  NULL;
static gt_obj_st * headbtn  =  NULL;
gt_obj_st * headrect  =  NULL;
static gt_obj_st * headtext  =  NULL;
gt_obj_st * headclock  =  NULL;
static gt_obj_st * line1  =  NULL;
static gt_obj_st * line2  =  NULL;
static gt_obj_st * line3  =  NULL;
static gt_obj_st * line4  =  NULL;
static gt_obj_st * batrect  =  NULL;
static gt_obj_st * batrect1  =  NULL;
static gt_obj_st * head = NULL;
static gt_obj_st * img1  =  NULL;
static gt_obj_st * img2  =  NULL;

extern gt_obj_st * RightVoltagevalue;
extern gt_obj_st * RightTime;
extern gt_obj_st * Rightwarning;
extern gt_obj_st * RightVoltagevalueimg;
extern gt_obj_st * content;
static void OneMin(gt_event_st* e){
    char buffer[50];
    //printf("one min timer\n");
    //时间
    rtc_time_get();
    sprintf(buffer,"%02d:%02d",calendar.hour,calendar.min);
//    gt_status_bar_right_add_text(buffer, 60);  
    gt_status_bar_right_change_text(RightTime,buffer);
    
    //电池电量百分比显示
    sprintf(buffer,"%d%%%%",sensorpack.voltagevalue);
    //gt_status_bar_right_add_text(buffer, 60);
    gt_status_bar_right_change_text(RightVoltagevalue,buffer);
   
}

static void OneSecond(gt_event_st * e){ 
	char buff[50];
    static int clock; //每1min发一个消息
    gt_obj_set_visible(img1 ,GT_INVISIBLE);
    if(my_get_now_scr_id == GT_SCR_ID_HOME)
        gt_status_bar_left_change_text(content,"主菜单");

        
    if(enterkey == false) //若不在键盘界面          前面再加一个标志判断是否消除警告来判断是否需要刷新
    {
        //每一分钟发次消息
        if(++clock > 60)
        {
            clock=0;
            gt_event_send(head,MYHEAD_ONE_MIN_TIME, NULL);
        }
        /********************************判断电池状态******************************************/
        static int lastbatflag; //记录上次电池的状态
        if(lastbatflag != sensorpack.batterystatus) //当这次状态和上次不一样时
        {
            switch(sensorpack.batterystatus)
            {
                case 1:
                    //充满
                    //让电池框变成绿色
					gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_4.png");
                    break;
                case 2:
                    //充电中
                    //让电池框变成绿色加图标		
                    gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_5.png");
                    break;
                case 3:
                    //脱落
                    //让电池框变成红色		
					gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_00.png");
                    break;
                case 4:
                    //放电中
                    //让电池框变成白色
                    if((80 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 100))
                        gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_4.png");
                    else if((60 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 80))
                        gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_3.png");
                    else if((40 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 60))
                        gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_2.png");
                    else if((20 < sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 40))
                        gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_1.png");
                    else if((5 <=  sensorpack.voltagevalue)&&(sensorpack.voltagevalue <= 20))
                        gt_status_bar_custom_change_icon(RightVoltagevalueimg,"f:img_65x35_battery_0.png");
                    break;
            } 
        }
        lastbatflag = sensorpack.batterystatus;
        
        /********************************判断是否显示出消除报警按钮******************************************/
        if(GetAlarmLevel(ALARM_Message) != N0_ALARM)
        {   

            gt_obj_set_visible(headlabel ,GT_INVISIBLE);  	
            gt_obj_set_visible(Rightwarning,GT_VISIBLE);
            gt_obj_set_visible(gt_status_bar_custom_add_text("报警音暂停", 130) ,GT_VISIBLE);
            gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_130x50_button120X50.png") ,GT_VISIBLE);
          
            if(JudgedYesNoAlarm(ALARM_NET_POWER_OFF) && (InfusionNow.glevel == L_ALARM) && !JudgedYesNoAlarm(ALARM_NEAR_DONE) && !JudgedYesNoAlarm(ALARM_NO_BATTETY) && !JudgedYesNoAlarm(ALARM_BATTERY_LOW))
            {
                #if VET_USE
                    gt_label_set_text(headbtn , title[SystemSetting.langue][1]);
                    gt_obj_set_visible(gt_status_bar_custom_add_text("报警音暂停", 130) ,GT_VISIBLE);
                #else
                    gt_obj_set_visible(gt_status_bar_custom_add_text("报警音暂停", 130) ,GT_VISIBLE);
                #endif
            }
            else
            {
				gt_obj_set_visible(gt_status_bar_custom_add_text("报警音暂停", 130) ,GT_VISIBLE);  
            }
        }
        else
        {
            gt_obj_set_visible(gt_status_bar_custom_add_text("报警音暂停", 130) ,GT_INVISIBLE);
            gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_130x50_button120X50.png") ,GT_INVISIBLE);
            gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png"),GT_INVISIBLE);
            
        }

        /*******************************绘制背景画面****************************************************/

        switch(GetAlarmLevel(ALARM_Message))
        { 
            //判断当前报警状态
            
            case H_ALARM:		 //红底	
				gt_status_bar_set_bg_color(gt_color_hex(0xDC143C));
	            gt_status_bar_set_font_color(gt_color_hex(0x000000));

                break;	   
            case M_ALARM:		 //黄底
            case L_ALARM:
	
				gt_status_bar_set_bg_color(gt_color_hex(0xFFA500));
	            gt_status_bar_set_font_color(gt_color_hex(0x000000));
                
                break;
            case T_ALARM:
            case N0_ALARM:	 		 

				gt_status_bar_set_bg_color(gt_color_hex(0x778899));
	            gt_status_bar_set_font_color(gt_color_hex(0xffffff));

                break;  
            default:

				gt_status_bar_set_bg_color(gt_color_hex(0x778899));
	            gt_status_bar_set_font_color(gt_color_hex(0xffffff));
                break; 
        }
    

        /********************************绘制报警信息******************************************/
        if(ALARM_Message>0) //有报警信息                       draw_text
        {
            sprintf(buff,"%s",alarmMessage[ALARM_Message].AlarmChar[SystemSetting.langue]);
            gt_status_bar_custom_change_text(Rightwarning,buff);	
           // gt_status_bar_center_set_text(buff);
            gt_obj_set_visible(Rightwarning ,GT_VISIBLE);
        }
        else
        {
            gt_obj_set_visible(Rightwarning ,GT_INVISIBLE);
        }
    }
    // gt_btn_set_text(headbtn , title[SystemSetting.langue][0]);//更新语言

}

void create_headevent(gt_obj_st * obj)
{
    head =  gt_obj_create(obj);
    gt_obj_register_id(head,0);
    gt_obj_add_event_cb(head, OneSecond, MYHEAD_ONE_SECONDS_TIME, NULL);
    gt_obj_add_event_cb(head, OneMin, MYHEAD_ONE_MIN_TIME, NULL);   

    gt_obj_add_event_cb(head, OneSecond, GT_EVENT_TYPE_NOTIFY_CLOSE, NULL);
}


#if 0
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
            gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png"),GT_VISIBLE);
        }
        else if(alarmflag==5)
        {
            ClearLowAlarm();
            //gt_obj_set_visible(img1 ,GT_VISIBLE);
            gt_obj_set_visible(gt_status_bar_custom_add_icon("f:img_30x30_AudioPause.png"),GT_VISIBLE);
        }
        
        #if wait
        SendMessage(hWnd,MSG_CLOSE,0,0);
        #endif
    }

//    gt_label_set_font_color(headclock , gt_color_hex(0xffffff));
//    gt_label_set_font_color(headlab2 , gt_color_hex(0xffffff));
//    gt_rect_set_color_border(batrect , gt_color_hex(0xffffff));
//    gt_rect_set_color_border(batrect1 , gt_color_hex(0xffffff));     
    #endif
}


//用来创建头部 

void create_head(gt_obj_st * obj,const char * str){

	char buff[50];

   
	/** 头部内容 */
	headlabel  = gt_label_create(obj);
	gt_obj_set_pos(headlabel , 5, 0);
	gt_obj_set_size(headlabel , 200, 50);
	gt_label_set_font_color(headlabel , gt_color_hex(0xffffff));
	gt_label_set_font_size(headlabel , 24);
	gt_label_set_font_family_cn(headlabel , 20);
	gt_label_set_font_family_en(headlabel , 33);
	gt_label_set_font_family_fl(headlabel , 50);
	gt_label_set_font_align(headlabel , GT_ALIGN_LEFT_MID);
	gt_label_set_text(headlabel , str);    


	/** 头部阴影 */
	headrect  = gt_rect_create(obj);
	gt_obj_set_pos(headrect , 0, 0);
	gt_obj_set_size(headrect , 480, 50);
	gt_obj_set_opa(headrect , GT_OPA_41);
	gt_rect_set_radius(headrect , 0);
	gt_rect_set_bg_color(headrect , gt_color_hex(0xffffff));
	gt_rect_set_color_border(headrect , gt_color_hex(0x778899));
	gt_rect_set_fill(headrect , 1);
	gt_rect_set_border(headrect , 4);
    my_rect_set_feedback(headrect ,false);


	
    //报警音暂停/关闭
    headbtn  = gt_btn_create(obj);
	gt_obj_set_pos(headbtn , 0, 0);
	gt_obj_set_size(headbtn , 150, 50);
	gt_btn_set_font_color(headbtn , gt_color_hex(0x000000));
	gt_btn_set_font_size(headbtn , 24);
	gt_btn_set_font_family_cn(headbtn , 20);
	gt_btn_set_font_family_en(headbtn , 33);
	gt_btn_set_font_family_fl(headbtn , 50);
	gt_btn_set_font_align(headbtn , GT_ALIGN_CENTER_MID);
	gt_btn_set_text(headbtn , title[SystemSetting.langue][0]);
	gt_btn_set_color_background(headbtn , gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(headbtn , gt_color_hex(0x808080));
	gt_btn_set_color_border(headbtn , gt_color_hex(0x778899));
    gt_btn_set_border_width(headbtn , 4);
	gt_btn_set_radius(headbtn , 4);
    gt_obj_add_event_cb(headbtn , btn_callback, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_visible(headbtn ,GT_INVISIBLE);

    
    //报警信息
    headtext  = gt_label_create(obj);
	gt_obj_set_pos(headtext , 150, 0);
    gt_obj_set_size(headtext , 150, 50);
	gt_label_set_font_color(headtext , gt_color_hex(0x000000));
	gt_label_set_font_size(headtext , 24);
    gt_label_set_font_family_cn(headtext , 20);
    gt_label_set_font_family_en(headtext , 33);
    gt_label_set_font_family_fl(headtext , 50);
	gt_label_set_font_align(headtext , GT_ALIGN_CENTER_MID);
    sprintf(buff,"%s",alarmMessage[ALARM_Message].AlarmChar[SystemSetting.langue]);
	gt_label_set_text(headtext ,buff);
    gt_obj_set_visible(headtext ,GT_INVISIBLE);
   
    /** 报警音暂停*/
	img1 = gt_img_create(obj);
	gt_obj_set_pos(img1, 287, 7);
	gt_obj_set_size(img1, 30, 30);
	gt_img_set_src(img1, "f:img_30x30_AudioPause.png");
    gt_obj_set_visible(img1 ,GT_INVISIBLE);

    /** img2 */
	img2 = gt_img_create(obj);
	gt_obj_set_pos(img2, 420, 13);
	gt_obj_set_size(img2, 15, 20);
	gt_img_set_src(img2, "f:img_15x20_charge.png");
    gt_obj_set_visible(img2 ,GT_INVISIBLE);

	/** 时钟 */
    headclock  = gt_label_create(obj);
	gt_obj_set_pos(headclock , 325, 8);
    gt_obj_set_size(headclock , 70, 35);
	gt_label_set_font_color(headclock , gt_color_hex(0xffffff));
	gt_label_set_font_size(headclock , 24);
	gt_label_set_font_align(headclock , GT_ALIGN_LEFT_MID);
    rtc_time_get();
    sprintf(buff,"%02d:%02d",calendar.hour,calendar.min);
	gt_label_set_text(headclock ,buff);

     /** 电池电量百分比 */
	headlab2  = gt_label_create(obj);
	gt_obj_set_pos(headlab2 , 408, 6);
	gt_obj_set_size(headlab2 , 70, 35);
	gt_label_set_font_color(headlab2 , gt_color_hex(0xffffff));
	gt_label_set_font_size(headlab2 , 20);
    gt_label_set_font_family_fl(headlab2, 50);
	gt_label_set_font_align(headlab2 , GT_ALIGN_CENTER_MID);
    sprintf(buff,"%d",sensorpack.voltagevalue);
    gt_label_set_text(headlab2 ,buff);
	
    /** 电池电量图标 */
	batrect  = gt_rect_create(obj);
	gt_obj_set_pos(batrect , 414, 6);
	gt_obj_set_size(batrect , 60, 35);
	gt_obj_set_opa(batrect , GT_OPA_100);
	gt_rect_set_radius(batrect , 0);
	gt_rect_set_bg_color(batrect , gt_color_hex(0xffffff));
	gt_rect_set_color_border(batrect , gt_color_hex(0xfe1b01));
	gt_rect_set_fill(batrect , 0);
	gt_rect_set_border(batrect , 4);
    my_rect_set_feedback(batrect ,false);

    batrect1  = gt_rect_create(obj);
	gt_obj_set_pos(batrect1 , 410, 17);
	gt_obj_set_size(batrect1 , 4, 14);
	gt_obj_set_opa(batrect1 , GT_OPA_100);
	gt_rect_set_radius(batrect1 , 0);
	gt_rect_set_bg_color(batrect1 , gt_color_hex(0xffffff));
	gt_rect_set_color_border(batrect , gt_color_hex(0xfe1b01));
	gt_rect_set_fill(batrect1 , 0);
	gt_rect_set_border(batrect1 , 3);
    my_rect_set_feedback(batrect1 ,false);
    

    gt_event_send(head,MYHEAD_ONE_MIN_TIME,NULL);
    
    
}
#endif   



