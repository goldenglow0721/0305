#include "ui.h"


/** SeqMode */
gt_obj_st * SeqMode = NULL;
static gt_obj_st * SeqMode_1 = NULL;
static gt_obj_st * SeqMode_2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * lab17 = NULL;
static gt_obj_st * lab18 = NULL;
static gt_obj_st * lab19 = NULL;
static gt_obj_st * lab20 = NULL;
static gt_obj_st * lab21 = NULL;
static gt_obj_st * lab22 = NULL;
static gt_obj_st * lab23 = NULL;
static gt_obj_st * lab24 = NULL;
static gt_obj_st * lab25 = NULL;
static gt_obj_st * lab26 = NULL;
static gt_obj_st * lab27 = NULL;
static gt_obj_st * lab28 = NULL;
static gt_obj_st * lab29 = NULL;
static gt_obj_st * lab30 = NULL;
static gt_obj_st * lab31 = NULL;
static gt_obj_st * lab32 = NULL;
static gt_obj_st * lab33 = NULL;
static gt_obj_st * lab34 = NULL;
static gt_obj_st * inputNum1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static _gt_timer_st * timer_run_300msec;

extern SeqMode_Run SeqMode_run;

static char buffer[30];
static uint8_t change;
static int  nowpage=1;
/*函数声明*/
static void CreatePage1();
static void CreatePage2();

uint32_t value;

static const char title[4][6][50]={
	"序列模式",
	"流速",
	"待入量",
	"时间",

	"Sequential Mode",
	"Rate",
	"VTBI",
	"Time",

	"El Modo Secuencial",
	"Tasa",
	"VTBI",
	"Tiempo",

	"序列模式",
	"流速",
	"待入量",
	"時間",

	"Modo sequencial",
	"Taxa",
	"VTBI",
	"Tempo"

};

static void total_time(void)
{
	SequenMode.time_Second = (SequenMode.S1_Time.hour+SequenMode.S2_Time.hour+SequenMode.S3_Time.hour+SequenMode.S4_Time.hour+SequenMode.S5_Time.hour)*3600+(SequenMode.S1_Time.min+SequenMode.S2_Time.min+SequenMode.S3_Time.min+SequenMode.S4_Time.min+SequenMode.S5_Time.min)*60+\
	(SequenMode.S1_Time.sec+SequenMode.S2_Time.sec+SequenMode.S3_Time.sec+SequenMode.S4_Time.sec+SequenMode.S5_Time.sec);
	SequenMode.Sequen_Time.hour = SequenMode.time_Second / 3600;
	SequenMode.Sequen_Time.min = (SequenMode.time_Second / 60) % 60;
	SequenMode.Sequen_Time.sec = SequenMode.time_Second % 60;
}

static void showpage(unsigned int Surplus)  
{
	switch(Surplus)
	{
		case 2:
			gt_obj_set_visible(lab17,GT_INVISIBLE);
			gt_obj_set_visible(lab18,GT_INVISIBLE);
			gt_obj_set_visible(lab19,GT_INVISIBLE);
			gt_obj_set_visible(lab20,GT_INVISIBLE);

			gt_obj_set_visible(svg2,GT_INVISIBLE);

			gt_obj_set_visible(lab32,GT_VISIBLE);
			gt_obj_set_visible(lab33,GT_VISIBLE);
			gt_obj_set_visible(lab34,GT_VISIBLE);

			gt_obj_set_pos(lab32,0,190);
			gt_obj_set_pos(lab33,208,190);
			gt_obj_set_pos(lab34,359,190);

			SequenMode.S3Rate = 0;
			SequenMode.S3VTBI = 0;
			SequenMode.S3_Time.hour = 0;
			SequenMode.S3_Time.min = 0;
			SequenMode.S3_Time.sec = 0;

			SequenMode.SequenVTBI = SequenMode.S1VTBI+SequenMode.S2VTBI;
			sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
			gt_label_set_text(lab33,buffer);
			#if 0
			SequenMode.time_Second = (SequenMode.S1_Time.hour+SequenMode.S2_Time.hour)*3600+(SequenMode.S1_Time.min+SequenMode.S2_Time.min)*60+\
			(SequenMode.S1_Time.sec+SequenMode.S2_Time.sec);
			SequenMode.Sequen_Time.hour = SequenMode.time_Second / 3600;
			SequenMode.Sequen_Time.min = (SequenMode.time_Second / 60) % 60;
			SequenMode.Sequen_Time.sec = SequenMode.time_Second % 60;
			#endif
			total_time();
			sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);	
			gt_label_set_text(lab34,buffer);
			
			break;
		case 3:
			gt_obj_set_visible(lab17,GT_VISIBLE);
			gt_obj_set_visible(lab18,GT_VISIBLE);
			gt_obj_set_visible(lab19,GT_VISIBLE);
			gt_obj_set_visible(lab20,GT_VISIBLE);

			gt_obj_set_visible(lab21,GT_INVISIBLE);
			gt_obj_set_visible(lab22,GT_INVISIBLE);
			gt_obj_set_visible(lab23,GT_INVISIBLE);
			gt_obj_set_visible(lab24,GT_INVISIBLE);

			gt_obj_set_visible(lab25,GT_INVISIBLE);
			gt_obj_set_visible(lab26,GT_INVISIBLE);
			gt_obj_set_visible(lab27,GT_INVISIBLE);
			gt_obj_set_visible(lab28,GT_INVISIBLE);
			
			gt_obj_set_visible(svg1,GT_VISIBLE);
			gt_obj_set_visible(svg2,GT_VISIBLE);

			gt_obj_set_visible(lab32,GT_INVISIBLE);
			gt_obj_set_visible(lab33,GT_INVISIBLE);
			gt_obj_set_visible(lab34,GT_INVISIBLE);
			
			gt_obj_set_pos(lab29,0,100);
			gt_obj_set_pos(lab30,208,100);
			gt_obj_set_pos(lab31,359,100);

			SequenMode.S4Rate = 0;
			SequenMode.S4VTBI = 0;
			SequenMode.S4_Time.hour = 0;
			SequenMode.S4_Time.min = 0;
			SequenMode.S4_Time.sec = 0;
			
			SequenMode.SequenVTBI = SequenMode.S1VTBI+SequenMode.S2VTBI+SequenMode.S3VTBI;
			sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
			gt_label_set_text(lab30,buffer);
			#if 0
			SequenMode.time_Second = (SequenMode.S1_Time.hour+SequenMode.S2_Time.hour+SequenMode.S3_Time.hour)*3600+(SequenMode.S1_Time.min+SequenMode.S2_Time.min+SequenMode.S3_Time.min)*60+\
			(SequenMode.S1_Time.sec+SequenMode.S2_Time.sec+SequenMode.S3_Time.sec);
			SequenMode.Sequen_Time.hour = SequenMode.time_Second / 3600;
			SequenMode.Sequen_Time.min = (SequenMode.time_Second / 60) % 60;
			SequenMode.Sequen_Time.sec = SequenMode.time_Second % 60;
			#endif
			total_time();
			sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
			gt_label_set_text(lab31,buffer);
			break;
		case 4:

			gt_obj_set_visible(lab21,GT_VISIBLE);
			gt_obj_set_visible(lab22,GT_VISIBLE);
			gt_obj_set_visible(lab23,GT_VISIBLE);
			gt_obj_set_visible(lab24,GT_VISIBLE);

			gt_obj_set_visible(lab25,GT_INVISIBLE);
			gt_obj_set_visible(lab26,GT_INVISIBLE);
			gt_obj_set_visible(lab27,GT_INVISIBLE);
			gt_obj_set_visible(lab28,GT_INVISIBLE);
			
			
			gt_obj_set_visible(svg1,GT_VISIBLE);
			gt_obj_set_visible(svg2,GT_VISIBLE);

			gt_obj_set_visible(lab32,GT_INVISIBLE);
			gt_obj_set_visible(lab33,GT_INVISIBLE);
			gt_obj_set_visible(lab34,GT_INVISIBLE);

			gt_obj_set_pos(lab29,0,145);
			gt_obj_set_pos(lab30,208,145);
			gt_obj_set_pos(lab31,359,145);

			SequenMode.S5Rate = 0;
			SequenMode.S5VTBI = 0;
			SequenMode.S5_Time.hour = 0;
			SequenMode.S5_Time.min = 0;
			SequenMode.S5_Time.sec = 0;

			SequenMode.SequenVTBI = SequenMode.S1VTBI+SequenMode.S2VTBI+SequenMode.S3VTBI+SequenMode.S4VTBI;
			sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
			gt_label_set_text(lab30,buffer);
			#if 0
			SequenMode.time_Second = (SequenMode.S1_Time.hour+SequenMode.S2_Time.hour+SequenMode.S3_Time.hour+SequenMode.S4_Time.hour)*3600+(SequenMode.S1_Time.min+SequenMode.S2_Time.min+SequenMode.S3_Time.min+SequenMode.S4_Time.min)*60+\
			(SequenMode.S1_Time.sec+SequenMode.S2_Time.sec+SequenMode.S3_Time.sec+SequenMode.S4_Time.sec);
			SequenMode.Sequen_Time.hour = SequenMode.time_Second / 3600;
			SequenMode.Sequen_Time.min = (SequenMode.time_Second / 60) % 60;
			SequenMode.Sequen_Time.sec = SequenMode.time_Second % 60;
			#endif
			total_time();
			sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
			gt_label_set_text(lab31,buffer);

			break;
		case 5:
			gt_obj_set_visible(lab25,GT_VISIBLE);
			gt_obj_set_visible(lab26,GT_VISIBLE);
			gt_obj_set_visible(lab27,GT_VISIBLE);
			gt_obj_set_visible(lab28,GT_VISIBLE);

			gt_obj_set_visible(svg2,GT_VISIBLE);
			gt_obj_set_visible(svg1,GT_VISIBLE);

			gt_obj_set_visible(lab32,GT_INVISIBLE);
			gt_obj_set_visible(lab33,GT_INVISIBLE);
			gt_obj_set_visible(lab34,GT_INVISIBLE);

			gt_obj_set_pos(lab29,0,190);
			gt_obj_set_pos(lab30,208,190);
			gt_obj_set_pos(lab31,359,190);

			SequenMode.SequenVTBI = SequenMode.S1VTBI+SequenMode.S2VTBI+SequenMode.S3VTBI+SequenMode.S4VTBI+SequenMode.S5VTBI;
			sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
			gt_label_set_text(lab30,buffer);
			total_time();
			sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
			gt_label_set_text(lab31,buffer);
			break;
	}
}



static void img1_0_cb(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);

	lab5 = NULL;
	lab10 = NULL;
	lab7 = NULL;
	img1 = NULL;
	DEL_TIMER_VAL(timer_run_300msec);
	
	gt_disp_stack_go_back(1);
}

static void Run(gt_event_st * e) {
	char buffer[20];
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	value = gt_input_number_get_value(inputNum1);


	#if 1  //运行前检测
	if(SequenMode.S1Rate==0){
		dialog1_create("请输入序列1流速");
		return;
	}
	if(SequenMode.S1VTBI==0){
		dialog1_create("请输入序列1待入量");
		return;
	}
	else if(sensorpack.BubbleStatus == Bubble_TRUE)
	{
		dialog1_create("右边管路有气泡");
		return;
	}
	else
	{
		;
	}
	#endif
	SeqMode_run.title = (char*)&title[SystemSetting.langue][0];
	SeqMode_run.value = &value;
	SeqMode_run.quantity = &SequenMode.SequenVTBI;
	SeqMode_run.quantity1 = &SequenMode.S1VTBI;
	SeqMode_run.quantity2 = &SequenMode.S2VTBI;
	SeqMode_run.quantity3 = &SequenMode.S3VTBI;
	SeqMode_run.quantity4 = &SequenMode.S4VTBI;
	SeqMode_run.quantity5 = &SequenMode.S5VTBI;
	SeqMode_run.speed1 = &SequenMode.S1Rate;
	SeqMode_run.speed2 = &SequenMode.S2Rate;
	SeqMode_run.speed3 = &SequenMode.S3Rate;
	SeqMode_run.speed4 = &SequenMode.S4Rate;
	SeqMode_run.speed5 = &SequenMode.S5Rate;
	SeqMode_run.time1 = &SequenMode.S1_Time;
	SeqMode_run.time2 = &SequenMode.S2_Time;
	SeqMode_run.time3 = &SequenMode.S3_Time;
	SeqMode_run.time4 = &SequenMode.S4_Time;
	SeqMode_run.time5 = &SequenMode.S5_Time;
	SeqMode_run.time = &SequenMode.Sequen_Time;
	SeqMode_run.init_func_cb = gt_init_SeqMode;
	press_Data.Pressure_newAD0 = sensorpack.DownPressure;
	WriteSeqModeMessageToFlash();
	gt_disp_stack_load_scr_anim(GT_SCR_ID_98, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void Timer_300mSecond(gt_event_st* e){
	if(gpio_input_data_bit_read(GPIOB, GPIO_PINS_11) == RESET)
	{
		Run(NULL);
		DEL_TIMER_VAL(timer_run_300msec);
	}
}

static void PageShow(uint8_t temp)
{
	switch(temp)
	{
		case 1:
			gt_obj_set_visible(SeqMode_1,GT_VISIBLE);
			gt_obj_set_visible(SeqMode_2,GT_INVISIBLE);
			gt_obj_child_set_prop(SeqMode_1,GT_OBJ_PROP_TYPE_VISIBLE,GT_VISIBLE);
			gt_obj_child_set_prop(SeqMode_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
	
			break;
		case 2:
			gt_obj_set_visible(SeqMode_1,GT_INVISIBLE);
			gt_obj_set_visible(SeqMode_2,GT_VISIBLE);
			gt_obj_child_set_prop(SeqMode_1,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
			gt_obj_child_set_prop(SeqMode_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_VISIBLE);
				
			break;
	}
}

//上一页
static void Page_Up(gt_event_st * e) {

	if(--nowpage < 1)
		nowpage=2;
	PageShow(nowpage);
	showpage(value);

}
//下一页
static void Page_Down(gt_event_st * e) {
	if(++nowpage >2)
		nowpage=1;
	PageShow(nowpage);
	showpage(value);
}

static void purge(gt_event_st * e) {
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_85, GT_SCR_ANIM_TYPE_NONE, 50, 0, true);
}

static void Add(gt_event_st * e) {
	gt_input_number_increase(inputNum1);
	value = gt_input_number_get_value(inputNum1);
	showpage(value);
}

static void Del(gt_event_st * e) {
	gt_input_number_decrease(inputNum1);
	value = gt_input_number_get_value(inputNum1);
	showpage(value);
}

static void SpeedChange(gt_event_st * e) {
	uint8_t temp;
	temp = atoi(e->user_data);
	change = temp;
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);
	strcpy(keyboardf.title,title[SystemSetting.langue][1]);
	keyboardf.data = &SequenMode.Rate;
	limit.toplimit=SystemMaintain.MaxSpeed;
	limit.lowerlimit = 0.01;
	keyboardf.id=22;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void ChangeQuantity(gt_event_st * e) {
	uint8_t temp;
	temp= atoi(e->user_data);
	change = temp;
	SetNoOperFunctionTimeAlarm(ParamSetting.NoOperationTime);
	ClearAlarm(ALARM_NO_OPERATION);

	strcpy(keyboardf.title,title[SystemSetting.langue][2]);
	keyboardf.data = &SequenMode.VTBI;
	limit.toplimit = 9999.9;
	limit.lowerlimit = 0.01;
	keyboardf.id=23;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_81, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	
	if(atoi(e->param) == 22)  //修改完速度出来的
	{

		//更新速度显示
		switch(change)
		{
			case 1:
			SequenMode.S1Rate = SequenMode.Rate;
			UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.S1Rate,&SequenMode.S1VTBI,&SequenMode.S1_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S1Rate);
			gt_label_set_text(lab10, buffer);
			break;
			case 2:
			SequenMode.S2Rate = SequenMode.Rate;
			UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.S2Rate,&SequenMode.S2VTBI,&SequenMode.S2_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S2Rate);
			gt_label_set_text(lab14, buffer);
			break;
			case 3:
			SequenMode.S3Rate = SequenMode.Rate;
			UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.S3Rate,&SequenMode.S3VTBI,&SequenMode.S3_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S3Rate);
			gt_label_set_text(lab18, buffer);
			break;
			case 4:
			SequenMode.S4Rate = SequenMode.Rate;
			UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.S4Rate,&SequenMode.S4VTBI,&SequenMode.S4_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S4Rate);
			gt_label_set_text(lab22, buffer);
			break;
			case 5:
			SequenMode.S5Rate = SequenMode.Rate;
			UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.S5Rate,&SequenMode.S5VTBI,&SequenMode.S5_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S5Rate);
			gt_label_set_text(lab26, buffer);
			break;
		}//修改速度后更新时间
		if(SequenMode.Time.hour>99)
		{
			SequenMode.Time.hour=100;
			SequenMode.Time.min=0;
			SequenMode.Time.sec=0;			
			sprintf(buffer,">%02d:%02d:%02d", 99, 59, 59);
		}
		else
		{
			switch(change)
			{
				case 1:
				if(SequenMode.S1VTBI!=0.0 && SequenMode.S1Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S1_Time.hour, SequenMode.S1_Time.min, SequenMode.S1_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab12,buffer);
				break;
				case 2:
				if(SequenMode.S2VTBI!=0.0 && SequenMode.S2Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S2_Time.hour, SequenMode.S2_Time.min, SequenMode.S2_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab16,buffer);
				break;
				case 3:
				if(SequenMode.S3VTBI!=0.0 && SequenMode.S3Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S3_Time.hour, SequenMode.S3_Time.min, SequenMode.S3_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab20,buffer);
				break;
				case 4:
				if(SequenMode.S4VTBI!=0.0 && SequenMode.S4Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S4_Time.hour, SequenMode.S4_Time.min, SequenMode.S4_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab24,buffer);
				break;
				case 5:
				if(SequenMode.S5VTBI!=0.0 && SequenMode.S5Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S5_Time.hour, SequenMode.S5_Time.min, SequenMode.S5_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab28,buffer);
				break;
			}
		}
		total_time();
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
		if(value == 2)
			gt_label_set_text(lab34,buffer);
		else
			gt_label_set_text(lab31,buffer);
	}
	if(atoi(e->param) == 23)  //修改完待入量出来的
	{
		value = gt_input_number_get_value(inputNum1);
		//更新待入量
		switch(change)
		{
			case 1:
			SequenMode.S1VTBI = SequenMode.VTBI;
			UpdateSpeedModeTheDisplay(CHANGE_QUAN,&SequenMode.S1Rate,&SequenMode.S1VTBI,&SequenMode.S1_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S1VTBI);
			gt_label_set_text(lab11, buffer);
			break;
			case 2:
			SequenMode.S2VTBI = SequenMode.VTBI;
			UpdateSpeedModeTheDisplay(CHANGE_QUAN,&SequenMode.S2Rate,&SequenMode.S2VTBI,&SequenMode.S2_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S2VTBI);
			gt_label_set_text(lab15, buffer);
			break;
			case 3:
			SequenMode.S3VTBI = SequenMode.VTBI;
			UpdateSpeedModeTheDisplay(CHANGE_QUAN,&SequenMode.S3Rate,&SequenMode.S3VTBI,&SequenMode.S3_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S3VTBI);
			gt_label_set_text(lab19, buffer);	
			break;
			case 4:
			SequenMode.S4VTBI = SequenMode.VTBI;
			UpdateSpeedModeTheDisplay(CHANGE_QUAN,&SequenMode.S4Rate,&SequenMode.S4VTBI,&SequenMode.S4_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S4VTBI);
			gt_label_set_text(lab23, buffer);
			break;
			case 5:
			SequenMode.S5VTBI = SequenMode.VTBI;
			UpdateSpeedModeTheDisplay(CHANGE_QUAN,&SequenMode.S5Rate,&SequenMode.S5VTBI,&SequenMode.S5_Time);
			sprintf(buffer,"%.2f",(float)SequenMode.S5VTBI);
			gt_label_set_text(lab27, buffer);
			break;
		}
		SequenMode.SequenVTBI = SequenMode.S1VTBI+SequenMode.S2VTBI+SequenMode.S3VTBI+SequenMode.S4VTBI+SequenMode.S5VTBI;
		sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
		if(value == 2)
			gt_label_set_text(lab33,buffer);
		else
			gt_label_set_text(lab30,buffer);
		if(SequenMode.Time.hour>99) //修改待入量后更新时间
		{
			SequenMode.Time.hour=100;
			SequenMode.Time.min=0;
			SequenMode.Time.sec=0;			
			sprintf(buffer,">%d:%d:%d", 99, 59, 59);
		}
		else  
		{
			switch(change)
			{
				case 1:
				if(SequenMode.S1VTBI!=0.0 && SequenMode.S1Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S1_Time.hour, SequenMode.S1_Time.min, SequenMode.S1_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab12,buffer);
				break;
				case 2:
				if(SequenMode.S2VTBI!=0.0 && SequenMode.S2Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S2_Time.hour, SequenMode.S2_Time.min, SequenMode.S2_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab16,buffer);
				break;
				case 3:
				if(SequenMode.S3VTBI!=0.0 && SequenMode.S3Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S3_Time.hour, SequenMode.S3_Time.min, SequenMode.S3_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab20,buffer);
				break;
				case 4:
				if(SequenMode.S4VTBI!=0.0 && SequenMode.S4Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S4_Time.hour, SequenMode.S4_Time.min, SequenMode.S4_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab24,buffer);
				break;
				case 5:
				if(SequenMode.S5VTBI!=0.0 && SequenMode.S5Rate!=0.0)
					sprintf(buffer,"%02d:%02d:%02d", SequenMode.S5_Time.hour, SequenMode.S5_Time.min, SequenMode.S5_Time.sec);
				else
					sprintf(buffer,"%s:%s:%s","--","--","--"); 
				gt_label_set_text(lab28,buffer);
				break;
			}
		}
		total_time();
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
		if(value == 2)
			gt_label_set_text(lab34,buffer);
		else
			gt_label_set_text(lab31,buffer);
	}
}
static void CreatePage1()
{
	/*第一页*/
	
	/** lab9 */
	lab9 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab9, 0, 100);
	gt_obj_set_size(lab9, 40, 35);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_en(lab9, 33);
	gt_label_set_font_family_cn(lab9, 20);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT);
	gt_label_set_text(lab9, "S1");

	/** lab10 */
	lab10 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab10, 56, 100);
	gt_obj_set_size(lab10, 120, 35);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 33);
	gt_label_set_font_family_cn(lab10, 20);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	if(SequenMode.S1Rate)
		sprintf(buffer,"%.2f",(float)SequenMode.S1Rate);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab10, buffer);
	gt_obj_add_event_cb(lab10, SpeedChange, GT_EVENT_TYPE_INPUT_RELEASED, "1");

	/** lab11 */
	lab11 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab11, 208, 100);
	gt_obj_set_size(lab11, 120, 35);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_en(lab11, 33);
	gt_label_set_font_family_cn(lab11, 20);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	if(SequenMode.S1VTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.S1VTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab11,buffer);
	gt_obj_add_event_cb(lab11, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, "1");

	/** lab12 */
	lab12 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab12, 359, 100);
	gt_obj_set_size(lab12, 120, 35);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	if(SequenMode.S1VTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.S1_Time.hour, SequenMode.S1_Time.min, SequenMode.S1_Time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab12,buffer);

	/** lab13 */
	lab13 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab13, 0, 145);
	gt_obj_set_size(lab13, 40, 35);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_en(lab13, 33);
	gt_label_set_font_family_cn(lab13, 20);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_LEFT);
	gt_label_set_text(lab13, "S2");

	/** lab14 */
	lab14 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab14, 56, 145);
	gt_obj_set_size(lab14, 120, 35);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_en(lab14, 33);
	gt_label_set_font_family_cn(lab14, 20);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	if(SequenMode.S2Rate)
		sprintf(buffer,"%.2f",(float)SequenMode.S2Rate);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab14, buffer);
	gt_obj_add_event_cb(lab14, SpeedChange, GT_EVENT_TYPE_INPUT_RELEASED, "2");

	/** lab15 */
	lab15 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab15, 208, 145);
	gt_obj_set_size(lab15, 120, 35);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 24);
	gt_label_set_font_family_en(lab15, 33);
	gt_label_set_font_family_cn(lab15, 20);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_CENTER_MID);
	if(SequenMode.S2VTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.S2VTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab15,buffer);
	gt_obj_add_event_cb(lab15, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, "2");

	/** lab16 */
	lab16 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab16, 359, 145);
	gt_obj_set_size(lab16, 120, 35);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 24);
	gt_label_set_font_family_en(lab16, 33);
	gt_label_set_font_family_cn(lab16, 20);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_CENTER_MID);
	if(SequenMode.S2VTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.S2_Time.hour, SequenMode.S2_Time.min, SequenMode.S2_Time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab16, buffer);

	/** lab17 */
	lab17 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab17, 0, 190);
	gt_obj_set_size(lab17, 40, 35);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 24);
	gt_label_set_font_family_en(lab17, 33);
	gt_label_set_font_family_cn(lab17, 20);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_LEFT);
	gt_label_set_text(lab17, "S3");

	/** lab18 */
	lab18 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab18, 56, 190);
	gt_obj_set_size(lab18, 120, 35);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 24);
	gt_label_set_font_family_en(lab18, 33);
	gt_label_set_font_family_cn(lab18, 20);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_CENTER_MID);
	if(SequenMode.S3Rate)
		sprintf(buffer,"%.2f",(float)SequenMode.S3Rate);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab18, buffer);
	gt_obj_add_event_cb(lab18, SpeedChange, GT_EVENT_TYPE_INPUT_RELEASED, "3");

	/** lab19 */
	lab19 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab19, 208, 190);
	gt_obj_set_size(lab19, 120, 35);
	gt_label_set_font_color(lab19, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab19, 24);
	gt_label_set_font_family_en(lab19, 33);
	gt_label_set_font_family_cn(lab19, 20);
	gt_label_set_font_family_fl(lab19, 50);
	gt_label_set_font_align(lab19, GT_ALIGN_CENTER_MID);
	if(SequenMode.S3VTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.S3VTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab19,buffer);
	gt_obj_add_event_cb(lab19, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, "3");

	/** lab20 */
	lab20 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab20, 359, 190);
	gt_obj_set_size(lab20, 120, 35);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 24);
	gt_label_set_font_family_en(lab20, 33);
	gt_label_set_font_family_cn(lab20, 20);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_CENTER_MID);
	if(SequenMode.S3VTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.S3_Time.hour, SequenMode.S3_Time.min, SequenMode.S3_Time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab20, buffer);

	/** lab32 */
	lab32 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab32, 0, 190);
	gt_obj_set_size(lab32, 40, 35);
	gt_label_set_font_color(lab32, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab32, 24);
	gt_label_set_font_family_en(lab32, 33);
	gt_label_set_font_family_cn(lab32, 20);
	gt_label_set_font_family_fl(lab32, 50);
	gt_label_set_font_align(lab32, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab32, "∑");

	/** lab33 */
	lab33 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab33, 208, 190);
	gt_obj_set_size(lab33, 120, 35);
	gt_label_set_font_color(lab33, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab33, 24);
	gt_label_set_font_family_en(lab33, 33);
	gt_label_set_font_family_cn(lab33, 20);
	gt_label_set_font_family_fl(lab33, 50);
	gt_label_set_font_align(lab33, GT_ALIGN_CENTER_MID);
	if(SequenMode.SequenVTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab33, buffer);

	/** lab34 */
	lab34 = gt_label_create(SeqMode_1);
	gt_obj_set_pos(lab34, 359, 190);
	gt_obj_set_size(lab34, 120, 35);
	gt_label_set_font_color(lab34, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab34, 24);
	gt_label_set_font_family_en(lab34, 33);
	gt_label_set_font_family_cn(lab34, 20);
	gt_label_set_font_family_fl(lab34, 50);
	gt_label_set_font_align(lab34, GT_ALIGN_CENTER_MID);
	if(SequenMode.SequenVTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
	else	
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab34, buffer);

	/** svg2 */
	svg2 = gt_img_create(SeqMode_1);
	gt_obj_set_pos(svg2, 430, 270);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, Page_Down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
}

static void CreatePage2()
{
	/*第二页*/
	/** lab21 */
	lab21 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab21, 0, 100);
	gt_obj_set_size(lab21, 40, 35);
	gt_label_set_font_color(lab21, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab21, 24);
	gt_label_set_font_family_en(lab21, 33);
	gt_label_set_font_family_cn(lab21, 20);
	gt_label_set_font_family_fl(lab21, 50);
	gt_label_set_font_align(lab21, GT_ALIGN_LEFT);
	gt_label_set_text(lab21, "S4");

	/** lab22 */
	lab22 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab22, 56, 100);
	gt_obj_set_size(lab22, 120, 35);
	gt_label_set_font_color(lab22, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab22, 24);
	gt_label_set_font_family_en(lab22, 33);
	gt_label_set_font_family_cn(lab22, 20);
	gt_label_set_font_family_fl(lab22, 50);
	gt_label_set_font_align(lab22, GT_ALIGN_CENTER_MID);
	if(SequenMode.S4Rate)
		sprintf(buffer,"%.2f",(float)SequenMode.S4Rate);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab22, buffer);
	gt_obj_add_event_cb(lab22, SpeedChange, GT_EVENT_TYPE_INPUT_RELEASED, "4");

	/** lab23 */
	lab23 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab23, 208, 100);
	gt_obj_set_size(lab23, 120, 35);
	gt_label_set_font_color(lab23, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab23, 24);
	gt_label_set_font_family_en(lab23, 33);
	gt_label_set_font_family_cn(lab23, 20);
	gt_label_set_font_family_fl(lab23, 50);
	gt_label_set_font_align(lab23, GT_ALIGN_CENTER_MID);
	if(SequenMode.S4VTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.S4VTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab23,buffer);
	gt_obj_add_event_cb(lab23, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, "4");

	/** lab24 */
	lab24 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab24, 359, 100);
	gt_obj_set_size(lab24, 120, 35);
	gt_label_set_font_color(lab24, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab24, 24);
	gt_label_set_font_family_en(lab24, 33);
	gt_label_set_font_family_cn(lab24, 20);
	gt_label_set_font_family_fl(lab24, 50);
	gt_label_set_font_align(lab24, GT_ALIGN_CENTER_MID);
	if(SequenMode.S4VTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.S4_Time.hour, SequenMode.S4_Time.min, SequenMode.S4_Time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab24, buffer);

	/** lab25 */
	lab25 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab25, 0, 145);
	gt_obj_set_size(lab25, 40, 35);
	gt_label_set_font_color(lab25, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab25, 24);
	gt_label_set_font_family_en(lab25, 33);
	gt_label_set_font_family_cn(lab25, 20);
	gt_label_set_font_family_fl(lab25, 50);
	gt_label_set_font_align(lab25, GT_ALIGN_LEFT);
	gt_label_set_text(lab25, "S5");

	/** lab26 */
	lab26 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab26, 56, 145);
	gt_obj_set_size(lab26, 120, 35);
	gt_label_set_font_color(lab26, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab26, 24);
	gt_label_set_font_family_en(lab26, 33);
	gt_label_set_font_family_cn(lab26, 20);
	gt_label_set_font_family_fl(lab26, 50);
	gt_label_set_font_align(lab26, GT_ALIGN_CENTER_MID);
	if(SequenMode.S5Rate)
		sprintf(buffer,"%.2f",(float)SequenMode.S5Rate);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab26, buffer);
	gt_obj_add_event_cb(lab26, SpeedChange, GT_EVENT_TYPE_INPUT_RELEASED, "5");

	/** lab27 */
	lab27 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab27, 208, 145);
	gt_obj_set_size(lab27, 120, 35);
	gt_label_set_font_color(lab27, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab27, 24);
	gt_label_set_font_family_en(lab27, 33);
	gt_label_set_font_family_cn(lab27, 20);
	gt_label_set_font_family_fl(lab27, 50);
	gt_label_set_font_align(lab27, GT_ALIGN_CENTER_MID);
	if(SequenMode.S5VTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.S5VTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab27,buffer);
	gt_obj_add_event_cb(lab27, ChangeQuantity, GT_EVENT_TYPE_INPUT_RELEASED, "5");

	/** lab28 */
	lab28 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab28, 359, 145);
	gt_obj_set_size(lab28, 120, 35);
	gt_label_set_font_color(lab28, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab28, 24);
	gt_label_set_font_family_en(lab28, 33);
	gt_label_set_font_family_cn(lab28, 20);
	gt_label_set_font_family_fl(lab28, 50);
	gt_label_set_font_align(lab28, GT_ALIGN_CENTER_MID);
	if(SequenMode.S5VTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.S5_Time.hour, SequenMode.S5_Time.min, SequenMode.S5_Time.sec);
	else	
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab28, buffer);

	/** lab29 */
	lab29 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab29, 0, 190);
	gt_obj_set_size(lab29, 40, 35);
	gt_label_set_font_color(lab29, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab29, 24);
	gt_label_set_font_family_en(lab29, 33);
	gt_label_set_font_family_cn(lab29, 20);
	gt_label_set_font_family_fl(lab29, 50);
	gt_label_set_font_align(lab29, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab29, "∑");

	/** lab30 */
	lab30 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab30, 208, 190);
	gt_obj_set_size(lab30, 120, 35);
	gt_label_set_font_color(lab30, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab30, 24);
	gt_label_set_font_family_en(lab30, 33);
	gt_label_set_font_family_cn(lab30, 20);
	gt_label_set_font_family_fl(lab30, 50);
	gt_label_set_font_align(lab30, GT_ALIGN_CENTER_MID);
	if(SequenMode.SequenVTBI)
		sprintf(buffer,"%.2f",(float)SequenMode.SequenVTBI);
	else
		sprintf(buffer,"--");
	gt_label_set_text(lab30, buffer);

	/** lab31 */
	lab31 = gt_label_create(SeqMode_2);
	gt_obj_set_pos(lab31, 359, 190);
	gt_obj_set_size(lab31, 120, 35);
	gt_label_set_font_color(lab31, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab31, 24);
	gt_label_set_font_family_en(lab31, 33);
	gt_label_set_font_family_cn(lab31, 20);
	gt_label_set_font_family_fl(lab31, 50);
	gt_label_set_font_align(lab31, GT_ALIGN_CENTER_MID);
	if(SequenMode.SequenVTBI)
		sprintf(buffer,"%02d:%02d:%02d",SequenMode.Sequen_Time.hour,SequenMode.Sequen_Time.min,SequenMode.Sequen_Time.sec);
	else
		sprintf(buffer,"--:--:--");
	gt_label_set_text(lab31, buffer);

	/** svg1 */
	svg1 = gt_img_create(SeqMode_2);
	gt_obj_set_pos(svg1, 430, 270);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1, Page_Up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
}



gt_obj_st * gt_init_SeqMode(void)
{
	SeqMode =  gt_obj_create(NULL);
	my_set_obj_title(SeqMode,title[SystemSetting.langue][0]);
	gt_obj_add_event_cb(SeqMode,EventUpdata,MY_EVENT_UPDATA,NULL);
	gt_screen_set_bgcolor(SeqMode, gt_color_hex(0x000000));
	 
	SeqMode_1 =  gt_obj_create(SeqMode);
	gt_obj_set_pos(SeqMode_1, 0, 0);
	gt_obj_set_size(SeqMode_1, 480, 320);

	SeqMode_2 =  gt_obj_create(SeqMode);
	gt_obj_set_pos(SeqMode_2, 0, 0);
	gt_obj_set_size(SeqMode_2, 480, 320);

	CreatePage1();
	CreatePage2();

	gt_obj_set_visible(SeqMode_2,GT_INVISIBLE);
	gt_obj_child_set_prop(SeqMode_2,GT_OBJ_PROP_TYPE_VISIBLE,GT_INVISIBLE);
	
	/** img1 */
	img1 = gt_img_create(SeqMode);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** lab18 */
	lab1 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab1, 110, 227);
	gt_obj_set_size(lab1, 120, 25);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 9);
	gt_label_set_font_family_en(lab1, 30);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "当前序列数");

	/** lab2 */
	lab2 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab2, 0, 60);
	gt_obj_set_size(lab2, 37, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_text(lab2, "ID");

	/** lab3 */
	lab3 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab3, 54, 55);
	gt_obj_set_size(lab3, 70, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][1]);

	/** lab4 */
	lab4 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab4, 205, 55);
	gt_obj_set_size(lab4, 100, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4,title[SystemSetting.langue][2]);

	/** lab5 */
	lab5 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab5, 351, 55);
	gt_obj_set_size(lab5, 70, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5,title[SystemSetting.langue][3]);
	
	/** inputNum1 */
	inputNum1 = gt_input_number_create(SeqMode);
	gt_obj_set_pos(inputNum1, 235, 226);
	gt_obj_set_size(inputNum1, 35, 24);
	gt_input_number_set_font_color(inputNum1, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum1, 16);
	gt_input_number_set_font_family_en(inputNum1,30);
	gt_input_number_set_font_align(inputNum1, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum1, 2);
	gt_input_number_set_step(inputNum1, 1);
	gt_input_number_set_min(inputNum1, 2);
	gt_input_number_set_max(inputNum1, 5);
	gt_input_number_set_fill_zero_front(inputNum1, false);
	gt_input_number_set_display_integer_length(inputNum1, 2);
	gt_input_number_set_display_decimal_length(inputNum1, 0);
	
	
	/** btn1 */
	btn1 = gt_btn_create(SeqMode);
	gt_obj_set_pos(btn1, 76, 260);
	gt_obj_set_size(btn1, 70, 60);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 20);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "运行");
	gt_btn_set_color_background(btn1, gt_color_hex(0x00ff00));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn1, gt_color_hex(0x228B22));
	gt_btn_set_border_width(btn1, 4);
	gt_btn_set_radius(btn1, 4);
	gt_obj_add_event_cb(btn1, Run, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	
	/** btn2 */
	btn2 = gt_btn_create(SeqMode);
	gt_obj_set_pos(btn2, 167, 260);
	gt_obj_set_size(btn2, 70, 60);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 20);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "排气");
	gt_btn_set_color_background(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn2, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn2, 4);
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, purge, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** btn3 */
	btn3 = gt_btn_create(SeqMode);
	gt_obj_set_pos(btn3, 257, 260);
	gt_obj_set_size(btn3, 70, 60);
	gt_btn_set_font_color(btn3, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn3, 24);
	gt_btn_set_font_family_cn(btn3, 20);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "增加");
	gt_btn_set_color_background(btn3, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn3, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn3, 4);
	gt_btn_set_radius(btn3, 4);
	gt_obj_add_event_cb(btn3, Add, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** btn4 */
	btn4 = gt_btn_create(SeqMode);
	gt_obj_set_pos(btn4, 351, 260);
	gt_obj_set_size(btn4, 70, 60);
	gt_btn_set_font_color(btn4, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn4, 24);
	gt_btn_set_font_family_cn(btn4, 20);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn4, "删除");
	gt_btn_set_color_background(btn4, gt_color_hex(0xc0c0c0));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x00a8ff));
	gt_btn_set_color_border(btn4, gt_color_hex(0x778899));
	gt_btn_set_border_width(btn4, 4);
	gt_btn_set_radius(btn4, 4);
	gt_obj_add_event_cb(btn4, Del, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** lab19 */
	lab6 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab6, 115, 55);
	gt_obj_set_size(lab6, 70, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "mL/h");

	/** lab20 */
	lab7 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab7, 294, 55);
	gt_obj_set_size(lab7, 40, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "mL");

	/** lab21 */
	lab8 = gt_label_create(SeqMode);
	gt_obj_set_pos(lab8, 409, 55);
	gt_obj_set_size(lab8, 70, 35);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, "h:m:s");

	UpdateSpeedModeTheDisplay(CHANGE_Speed,&SequenMode.Rate,&SequenMode.VTBI,&SequenMode.Time);

	value = gt_input_number_get_value(inputNum1);

	timer_run_300msec = _gt_timer_create(Timer_300mSecond,300,NULL);

	showpage(value);

	return SeqMode;
}

