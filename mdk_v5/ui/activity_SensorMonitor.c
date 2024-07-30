#include "ui.h"


/** SensorMonitor */
gt_obj_st * SensorMonitor = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
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
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * rect8 = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect10 = NULL;
static gt_obj_st * rect11 = NULL;
static gt_obj_st * rect12 = NULL;
static gt_obj_st * rect13 = NULL;
static gt_obj_st * rect14 = NULL;
static gt_obj_st * rect15 = NULL;
static gt_obj_st * rect16 = NULL;
static gt_obj_st * rect17 = NULL;
static gt_obj_st * rect18 = NULL;
static gt_obj_st * rect19 = NULL;
static gt_obj_st * rect20 = NULL;
static gt_obj_st * rect21 = NULL;
static gt_obj_st * rect22 = NULL;
static gt_obj_st * rect23 = NULL;
static gt_obj_st * rect24 = NULL;
static gt_obj_st * rect25 = NULL;
static gt_obj_st * rect26 = NULL;
static gt_obj_st * rect27 = NULL;
static gt_obj_st * rect28 = NULL;
static gt_obj_st * rect29 = NULL;
static gt_obj_st * rect30 = NULL;
static gt_obj_st * rect31 = NULL;
static gt_obj_st * rect32 = NULL;
static gt_obj_st * rect33 = NULL;
static gt_obj_st * rect34 = NULL;
static gt_obj_st * lab35 = NULL;
static gt_obj_st * rect35 = NULL;
static gt_obj_st * lab36 = NULL;
static gt_obj_st * rect36 = NULL;
static gt_obj_st * lab37 = NULL;
static gt_obj_st * rect37 = NULL;
static gt_obj_st * lab38 = NULL;
static gt_obj_st * rect38 = NULL;
static gt_obj_st * lab39 = NULL;
static gt_obj_st * rect39 = NULL;
static gt_obj_st * lab40 = NULL;
static gt_obj_st * lab41 = NULL;
static gt_obj_st * rect40 = NULL;
static gt_obj_st * rect41 = NULL;
static _gt_timer_st * timer_main_ThirmSec = NULL;

uint8_t BATTERY_FLAG_STATE=1;  //增加一个标志量用来判断电池脱落还是断电后刚上电瞬间的状态

static char buffer[50];

static int CellAD;

static _Bool LED_DT = false;
static _Bool BEEP_DT = false;
_Bool judge = false;
_Bool LedDetection = false;
static const char title[5][26][50]={
	"传感器AD",
	"无气泡",
	"有气泡",
	"转速",
	"方向",
	"电流",
	"电池",
	"设备",
	"返回",
	"顺时针",
	"充满",
	"上压力",
	"下压力",
	"上超声",
	"下超声",
	"暂停",
	"反转",
	"正转",
	"逆时针",
	"充电",
	"脱落",
	"放电",
	"灯光",
	"蜂鸣器",
	"开",
	"关",

	"Sensor AD",
	"Free",
	"Bubble",
	"Rotate Speed",
	"Direct",
	"Electric",
	"Battery",
	"Device",
	"Return",
	"CW",
	"Fully",
	"Up P",
	"Down P",
	"Up U",
	"Down U",
	"Pause",
	"Inversion",
	"Corotation",
	"CCW",
	"Charge",
	"Fall",
	"Discharge",
	"",
	"",
	"",
	"",


	"Sensor AD",
	"Gratis",
	"Burbuja",
	"Rotar la Velocidad",
	"Directo",
	"Eléctrico",
	"Batería",
	"Dispositivo",
	"Retorno",
	"CW",
	"Carga Completa",
	"Presión Superior",
	"Presión hacia abajo",
	"Ultrasonido superior",
	"Ultrasonido hacia abajo",
	"Pausa",
	"Inversión",
	"Corotación",
	"CCW",
	"Está Cargando",
	"Desconectado",
	"Discharge",
	"",
	"",
	"",
	"",
	
	"感測器AD",
	"無氣泡",
	"有氣泡",
	"轉速",
	"方向",
	"電流",
	"電池",
	"設備",
	"返回",
	"順時針",
	"充滿",
	"上壓力",
	"下壓力",
	"上超聲",
	"下超聲",
	"暫停",
	"反轉",
	"正轉",
	"逆時針",
	"充電",
	"脫落",
	"放電",
	"",
	"",
	"",
	"",

	"Sensor AD",
	"Livre",
	"Bolha",
	"Taxa de rotação",
	"Direto",
	"Eletrico",
	"Bateria",
	"Dispositivo",
	"Retornar",
	"CW",
	"Completamente",
	"Acima P",
	"Abaixo P",
	"Acima U",
	"Abaixo U",
	"Pausar",
	"Inversão",
	"Corotação",
	"CCW",
	"Carga",
	"Cair",
	"Descarga",
	"",
	"",
	"",
	""
		
};

static void rect2_0_cb(gt_event_st * e) {
	strcpy(keyboardi.title,title[SystemSetting.langue][3]);
	keyboardi.data = &sensorpack.Speed;
	keyboardi.id = 19;
	limit.toplimit=50000;
	limit.lowerlimit = 0;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}


static void AD_U(gt_event_st * e) {
	strcpy(keyboardi.title,"AD_U");
	keyboardi.data = &SystemMaintain.ADU_Notube;
	keyboardi.id = 20;
	limit.toplimit=18000;
	limit.lowerlimit = 12000;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

static void back(gt_event_st * e) {

	DEL_TIMER_VAL(timer_main_ThirmSec);
	TMC2226_MotorStop();
	led_off(ARM_RLED);
	led_off(ARM_YLED);
	led_off(M4_RLED);
	led_off(BAT_LED);
	led_off(AC_LED);
	LedDetection = false;
	BeepStop();
	gt_disp_stack_go_back(1);
}


static void ad0_change(gt_event_st * e){
	strcpy(keyboardi.title,"AD0");
	keyboardi.data = &SystemMaintain.AD0_Notube;
	keyboardi.id=11;
	limit.lowerlimit=12000;
	limit.toplimit=18000;
	gt_disp_stack_load_scr_anim(GT_SCR_ID_80, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);

}
static void EventUpdata(gt_event_st * e)
{
	char buffer[50];
	if(atoi(e->param) == 11)  //修改完AD0出来的
	{
		sprintf(buffer,"%d",SystemMaintain.AD0_Notube);
		gt_label_set_text(lab34, buffer);
		WriteSystemMaintainMessageToFlash();
	}
	else if(atoi(e->param) == 19) //修改转速出来的
	{
		sprintf(buffer,"%d",sensorpack.Speed);
		gt_label_set_text(lab9,buffer);
		sensorpack.electricity = TMC2226_speed2force(sensorpack.Speed);
		sprintf(buffer,"%d",sensorpack.electricity);
		gt_label_set_text(lab11,buffer);
		if(judge == true)
			TMC2226_MotorRun(1,0,sensorpack.Speed);
		WriteSystemMaintainMessageToFlash();
	}
	if(atoi(e->param) == 20)  //修改完AD_U出来的
	{
		sprintf(buffer,"%d",SystemMaintain.ADU_Notube);
		gt_label_set_text(lab14, buffer);
		WriteSystemMaintainMessageToFlash();
	}
}

static void RTLrun(gt_event_st * e)
{
	judge = true;
	TMC2226_MotorRun(1,0,sensorpack.Speed);
	gt_label_set_text(lab10, title[SystemSetting.langue][18]);
}

static void AgainstRun(gt_event_st * e)
{
	TMC2226_MotorRun(0,0,sensorpack.Speed);
	gt_label_set_text(lab10, title[SystemSetting.langue][9]);
}

static void Pause(gt_event_st * e){
	judge = false;
	TMC2226_MotorStop();
}

static void LED_detection(gt_event_st * e){
	if(LED_DT == false)
	{
		LED_DT = true;
		led_on(ARM_RLED);
		led_on(ARM_YLED);
		led_on(M4_RLED);
		led_on(BAT_LED);
		led_on(AC_LED);
		gt_label_set_text(lab40, title[SystemSetting.langue][24]);
	}
	else
	{
		LED_DT = false;
		led_off(ARM_RLED);
		led_off(ARM_YLED);
		led_off(M4_RLED);
		led_off(BAT_LED);
		led_off(AC_LED);
		gt_label_set_text(lab40, title[SystemSetting.langue][25]);
	}
}

static void BEEP_detection(gt_event_st * e){
	if(BEEP_DT == false)
	{
		BEEP_DT = true;
		BeepStart();
		gt_label_set_text(lab41, title[SystemSetting.langue][24]);
	}
	else 
	{
		BEEP_DT = false;
		BeepStop();
		gt_label_set_text(lab41, title[SystemSetting.langue][25]);
	}
}

static void Timer_ThirmSec(gt_event_st * e){
	char buff[50];
	//气泡
	if(sensorpack.BubbleStatus == Bubble_FALSE)
		gt_label_set_text(lab30, title[SystemSetting.langue][1]);
	else if(sensorpack.BubbleStatus == Bubble_TRUE)
		gt_label_set_text(lab30, title[SystemSetting.langue][2]);
	//压力值
	sprintf(buff,"%d",sensorpack.DownPressure);
	gt_label_set_text(lab22, buff);
	sprintf(buff,"%d",sensorpack.UpPressure);
	gt_label_set_text(lab21, buff);
	if(sensorpack.RightKnobStatus == 1)
	{
		gt_label_set_text(lab32, "1");
	}
	else
	{
		gt_label_set_text(lab32, "0");
	}

	if(optocoupler_motor_arrive_motor_point==get_optocoupler_signal()||optocoupler_motor_run==get_optocoupler_signal())
	{
		gt_label_set_text(lab23, "1");
	}
	else
		gt_label_set_text(lab23, "0");



	// if(sensorpack.LeftknobStatus == 1)
	// 	gt_label_set_text(lab32, "1");
	// else
	// 	gt_label_set_text(lab32, "0");

	if((DC_PWR)&&( battery_status.StatusFlag == 0)&&(BatteryStatus)) //充满	
	{
		BATTERY_FLAG_STATE=0;
		gt_label_set_text(lab12, title[SystemSetting.langue][10]);
	}
	else if((DC_PWR)&&(battery_status.StatusFlag == 0)&&(!BatteryStatus)) //充电
	{
		BATTERY_FLAG_STATE=1;
		gt_label_set_text(lab12, title[SystemSetting.langue][19]);
	}
	else if((DC_PWR)&&(battery_status.StatusFlag == 1)&&(BATTERY_FLAG_STATE)) //脱落
	{
		BATTERY_FLAG_STATE=1;
		gt_label_set_text(lab12, title[SystemSetting.langue][20]);
	}
	else if((!DC_PWR)&&( battery_status.StatusFlag == 0)&&(BatteryStatus)) //放电
	{
		BATTERY_FLAG_STATE=0;
		gt_label_set_text(lab12, title[SystemSetting.langue][21]);
	}

	CellAD = sensorpack.voltagevalue*(3600.0-2772.0)/100+2772.0;
	sprintf(buffer,"%d",CellAD);
	gt_label_set_text(lab20, buffer);
}



gt_obj_st * gt_init_SensorMonitor(void)
{
	char buff[50];
	SensorMonitor =  gt_obj_create(NULL);

	LedDetection = true;
	my_set_obj_title(SensorMonitor,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(SensorMonitor, gt_color_hex(0x000000));
	gt_obj_add_event_cb(SensorMonitor,EventUpdata,MY_EVENT_UPDATA,NULL);
	 

	/** lab2 */
	lab2 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab2, 0, 54);
	gt_obj_set_size(lab2, 60, 25);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 9);
	gt_label_set_font_family_en(lab2, 30);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, title[SystemSetting.langue][3]);


	/** lab3 */
	lab3 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab3, 0, 90);
	gt_obj_set_size(lab3, 60, 25);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 9);
	gt_label_set_font_family_en(lab3, 30);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, title[SystemSetting.langue][4]);


	/** lab4 */
	lab4 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab4, 0, 127);
	gt_obj_set_size(lab4, 60, 25);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 9);
	gt_label_set_font_family_en(lab4, 30);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, title[SystemSetting.langue][5]);


	/** lab5 */
	lab5 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab5, 0, 164);
	gt_obj_set_size(lab5, 60, 25);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 16);
	gt_label_set_font_family_cn(lab5, 9);
	gt_label_set_font_family_en(lab5, 30);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, title[SystemSetting.langue][6]);


	/** lab6 */
	lab6 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab6, 0, 204);
	gt_obj_set_size(lab6, 60, 25);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 16);
	gt_label_set_font_family_cn(lab6, 9);
	gt_label_set_font_family_en(lab6, 30);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, title[SystemSetting.langue][7]);


	/** lab7 */
	lab7 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab7, 0, 240);
	gt_obj_set_size(lab7, 60, 25);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 16);
	gt_label_set_font_family_en(lab7, 30);
	gt_label_set_font_family_cn(lab7, 9);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "AD_U");


	/** lab8 */
	lab8 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab8, 14, 281);
	gt_obj_set_size(lab8, 85, 37);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, title[SystemSetting.langue][8]);


	/** lab9 */
	lab9 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab9, 68, 54);
	gt_obj_set_size(lab9, 65, 24);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 16);
	gt_label_set_font_family_cn(lab9, 9);
	gt_label_set_font_family_en(lab9, 30);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",sensorpack.Speed);
	gt_label_set_text(lab9, buffer);


	/** lab10 */
	lab10 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab10, 68, 91);
	gt_obj_set_size(lab10, 65, 24);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 16);
	gt_label_set_font_family_cn(lab10, 9);
	gt_label_set_font_family_en(lab10, 30);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10, title[SystemSetting.langue][9]);


	/** lab11 */
	lab11 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab11, 68, 127);
	gt_obj_set_size(lab11, 65, 24);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 16);
	gt_label_set_font_family_cn(lab11, 9);
	gt_label_set_font_family_en(lab11, 30);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, "30");


	/** lab12 */
	lab12 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab12, 68, 165);
	gt_obj_set_size(lab12, 65, 24);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 16);
	gt_label_set_font_family_cn(lab12, 9);
	gt_label_set_font_family_en(lab12, 30);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab12, title[SystemSetting.langue][10]);


	/** lab13 */
	lab13 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab13, 68, 204);
	gt_obj_set_size(lab13, 65, 24);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 16);
	gt_label_set_font_family_en(lab13, 30);
	gt_label_set_font_family_cn(lab13, 9);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab13, "VP30");


	/** lab14 */
	lab14 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab14, 69, 241);
	gt_obj_set_size(lab14, 65, 24);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 16);
	gt_label_set_font_family_en(lab14, 30);
	gt_label_set_font_family_cn(lab14, 9);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",SystemMaintain.ADU_Notube);
	gt_label_set_text(lab14, buffer);


	/** lab15 */
	lab15 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab15, 169, 54);
	gt_obj_set_size(lab15, 60, 24);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 16);
	gt_label_set_font_family_cn(lab15, 9);
	gt_label_set_font_family_en(lab15, 30);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab15, "BatAD");


	/** lab16 */
	lab16 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab16, 169, 90);
	gt_obj_set_size(lab16, 60, 24);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 16);
	gt_label_set_font_family_cn(lab16, 9);
	gt_label_set_font_family_en(lab16, 30);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab16, title[SystemSetting.langue][11]);


	/** lab17 */
	lab17 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab17, 169, 127);
	gt_obj_set_size(lab17, 60, 24);
	gt_label_set_font_color(lab17, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab17, 16);
	gt_label_set_font_family_cn(lab17, 9);
	gt_label_set_font_family_en(lab17, 30);
	gt_label_set_font_family_fl(lab17, 50);
	gt_label_set_font_align(lab17, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab17, title[SystemSetting.langue][12]);


	/** lab18 */
	lab18 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab18, 169, 163);
	gt_obj_set_size(lab18, 60, 24);
	gt_label_set_font_color(lab18, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab18, 16);
	gt_label_set_font_family_en(lab18, 30);
	gt_label_set_font_family_cn(lab18, 9);
	gt_label_set_font_family_fl(lab18, 50);
	gt_label_set_font_align(lab18, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab18, "P9");


	/** lab19 */
	lab19 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab19, 169, 204);
	gt_obj_set_size(lab19, 60, 24);
	gt_label_set_font_color(lab19, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab19, 16);
	gt_label_set_font_family_cn(lab19, 9);
	gt_label_set_font_family_en(lab19, 30);
	gt_label_set_font_family_fl(lab19, 50);
	gt_label_set_font_align(lab19, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab19, "P10");


	/** lab20 */
	lab20 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab20, 238, 55);
	gt_obj_set_size(lab20, 60, 24);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 16);
	gt_label_set_font_family_en(lab20, 30);
	gt_label_set_font_family_cn(lab20, 9);
	gt_label_set_font_family_fl(lab20, 50);
	gt_label_set_font_align(lab20, GT_ALIGN_CENTER_MID);
	CellAD = sensorpack.voltagevalue*(3600.0-2772.0)/100+2772.0;
	sprintf(buffer,"%d",CellAD);
	gt_label_set_text(lab20, buffer);


	/** lab21 */
	lab21 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab21, 237, 91);
	gt_obj_set_size(lab21, 60, 24);
	gt_label_set_font_color(lab21, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab21, 16);
	gt_label_set_font_family_en(lab21, 30);
	gt_label_set_font_family_cn(lab21, 9);
	gt_label_set_font_family_fl(lab21, 50);
	gt_label_set_font_align(lab21, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab21, "16587");


	/** lab22 */
	lab22 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab22, 237, 128);
	gt_obj_set_size(lab22, 60, 24);
	gt_label_set_font_color(lab22, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab22, 16);
	gt_label_set_font_family_en(lab22, 30);
	gt_label_set_font_family_cn(lab22, 9);
	gt_label_set_font_family_fl(lab22, 50);
	gt_label_set_font_align(lab22, GT_ALIGN_CENTER_MID);
	sprintf(buff,"%d",sensorpack.DownPressure);
	gt_label_set_text(lab22, buff);


	/** lab23 */
	lab23 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab23, 237, 165);
	gt_obj_set_size(lab23, 60, 24);
	gt_label_set_font_color(lab23, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab23, 16);
	gt_label_set_font_family_en(lab23, 30);
	gt_label_set_font_family_cn(lab23, 9);
	gt_label_set_font_family_fl(lab23, 50);
	gt_label_set_font_align(lab23, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab23, "0");


	/** lab24 */
	lab24 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab24, 237, 205);
	gt_obj_set_size(lab24, 60, 24);
	gt_label_set_font_color(lab24, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab24, 16);
	gt_label_set_font_family_en(lab24, 30);
	gt_label_set_font_family_cn(lab24, 9);
	gt_label_set_font_family_fl(lab24, 50);
	gt_label_set_font_align(lab24, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab24, "0");


	/** lab25 */
	lab25 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab25, 335, 54);
	gt_obj_set_size(lab25, 60, 24);
	gt_label_set_font_color(lab25, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab25, 16);
	gt_label_set_font_family_cn(lab25, 9);
	gt_label_set_font_family_en(lab25, 30);
	gt_label_set_font_family_fl(lab25, 50);
	gt_label_set_font_align(lab25, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab25, title[SystemSetting.langue][13]);


	/** lab26 */
	lab26 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab26, 335, 90);
	gt_obj_set_size(lab26, 60, 24);
	gt_label_set_font_color(lab26, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab26, 16);
	gt_label_set_font_family_cn(lab26, 9);
	gt_label_set_font_family_en(lab26, 30);
	gt_label_set_font_family_fl(lab26, 50);
	gt_label_set_font_align(lab26, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab26,title[SystemSetting.langue][14]);


	/** lab27 */
	lab27 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab27, 335, 127);
	gt_obj_set_size(lab27, 60, 24);
	gt_label_set_font_color(lab27, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab27, 16);
	gt_label_set_font_family_en(lab27, 30);
	gt_label_set_font_family_cn(lab27, 9);
	gt_label_set_font_family_fl(lab27, 50);
	gt_label_set_font_align(lab27, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab27, "R");


	/** lab28 */
	lab28 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab28, 335, 164);
	gt_obj_set_size(lab28, 60, 24);
	gt_label_set_font_color(lab28, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab28, 16);
	gt_label_set_font_family_en(lab28, 30);
	gt_label_set_font_family_cn(lab28, 9);
	gt_label_set_font_family_fl(lab28, 50);
	gt_label_set_font_align(lab28, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab28, "L");


	/** lab29 */
	lab29 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab29, 335, 204);
	gt_obj_set_size(lab29, 60, 24);
	gt_label_set_font_color(lab29, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab29, 16);
	gt_label_set_font_family_en(lab29, 30);
	gt_label_set_font_family_cn(lab29, 9);
	gt_label_set_font_family_fl(lab29, 50);
	gt_label_set_font_align(lab29, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab29, "AD0");


	/** lab30 */
	lab30 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab30, 402, 55);
	gt_obj_set_size(lab30, 60, 24);
	gt_label_set_font_color(lab30, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab30, 16);
	gt_label_set_font_family_cn(lab30, 9);
	gt_label_set_font_family_en(lab30, 30);
	gt_label_set_font_family_fl(lab30, 50);
	gt_label_set_font_align(lab30, GT_ALIGN_CENTER_MID);
	if(sensorpack.BubbleStatus == Bubble_FALSE)
		gt_label_set_text(lab30, title[SystemSetting.langue][1]);
	else if(sensorpack.BubbleStatus == Bubble_TRUE)
		gt_label_set_text(lab30, title[SystemSetting.langue][2]);

	/** lab31 */
	lab31 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab31, 402, 89);
	gt_obj_set_size(lab31, 60, 24);
	gt_label_set_font_color(lab31, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab31, 16);
	gt_label_set_font_family_cn(lab31, 9);
	gt_label_set_font_family_en(lab31, 30);
	gt_label_set_font_family_fl(lab31, 50);
	gt_label_set_font_align(lab31, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab31, title[SystemSetting.langue][2]);


	/** lab32 */
	lab32 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab32, 402, 128);
	gt_obj_set_size(lab32, 60, 24);
	gt_label_set_font_color(lab32, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab32, 16);
	gt_label_set_font_family_en(lab32, 30);
	gt_label_set_font_family_cn(lab32, 9);
	gt_label_set_font_family_fl(lab32, 50);
	gt_label_set_font_align(lab32, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab32, "0");


	/** lab33 */
	lab33 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab33, 402, 165);
	gt_obj_set_size(lab33, 60, 24);
	gt_label_set_font_color(lab33, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab33, 16);
	gt_label_set_font_family_en(lab33, 30);
	gt_label_set_font_family_cn(lab33, 9);
	gt_label_set_font_family_fl(lab33, 50);
	gt_label_set_font_align(lab33, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab33, "0");


	/** lab34 */
	lab34 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab34, 402, 205);
	gt_obj_set_size(lab34, 60, 24);
	gt_label_set_font_color(lab34, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab34, 16);
	gt_label_set_font_family_en(lab34, 30);
	gt_label_set_font_family_cn(lab34, 9);
	gt_label_set_font_family_fl(lab34, 50);
	gt_label_set_font_align(lab34, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"%d",SystemMaintain.AD0_Notube);
	gt_label_set_text(lab34, buffer);


	/** rect2 */
	rect2 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect2, 0, 51);
	gt_obj_set_size(rect2, 63, 30);
	gt_obj_set_opa(rect2, GT_OPA_47);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect3 */
	rect3 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect3, 63, 51);
	gt_obj_set_size(rect3, 75, 30);
	gt_obj_set_opa(rect3, GT_OPA_40);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect3, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);
	gt_obj_add_event_cb(rect3, rect2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect4 */
	rect4 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect4, 0, 88);
	gt_obj_set_size(rect4, 63, 30);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);


	/** rect5 */
	rect5 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect5, 63, 88);
	gt_obj_set_size(rect5, 75, 30);
	gt_obj_set_opa(rect5, GT_OPA_41);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect5, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);


	/** rect6 */
	rect6 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect6, 0, 124);
	gt_obj_set_size(rect6, 63, 30);
	gt_obj_set_opa(rect6, GT_OPA_50);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0x778899));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);


	/** rect7 */
	rect7 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect7, 63, 124);
	gt_obj_set_size(rect7, 75, 30);
	gt_obj_set_opa(rect7, GT_OPA_41);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect7, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);


	/** rect8 */
	rect8 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect8, 0, 162);
	gt_obj_set_size(rect8, 63, 30);
	gt_obj_set_opa(rect8, GT_OPA_50);
	gt_rect_set_radius(rect8, 0);
	gt_rect_set_bg_color(rect8, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect8, gt_color_hex(0x778899));
	gt_rect_set_fill(rect8, 1);
	gt_rect_set_border(rect8, 4);


	/** rect9 */
	rect9 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect9, 63, 162);
	gt_obj_set_size(rect9, 75, 30);
	gt_obj_set_opa(rect9, GT_OPA_41);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect9, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);


	/** rect10 */
	rect10 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect10, 0, 201);
	gt_obj_set_size(rect10, 63, 30);
	gt_obj_set_opa(rect10, GT_OPA_50);
	gt_rect_set_radius(rect10, 0);
	gt_rect_set_bg_color(rect10, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect10, gt_color_hex(0x778899));
	gt_rect_set_fill(rect10, 1);
	gt_rect_set_border(rect10, 4);


	/** rect11 */
	rect11 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect11, 63, 201);
	gt_obj_set_size(rect11, 75, 30);
	gt_obj_set_opa(rect11, GT_OPA_41);
	gt_rect_set_radius(rect11, 0);
	gt_rect_set_bg_color(rect11, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect11, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect11, 1);
	gt_rect_set_border(rect11, 0);


	/** rect12 */
	rect12 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect12, 0, 238);
	gt_obj_set_size(rect12, 63, 30);
	gt_obj_set_opa(rect12, GT_OPA_50);
	gt_rect_set_radius(rect12, 0);
	gt_rect_set_bg_color(rect12, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect12, gt_color_hex(0x778899));
	gt_rect_set_fill(rect12, 1);
	gt_rect_set_border(rect12, 4);
	gt_obj_add_event_cb(rect12, AD_U, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect13 */
	rect13 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect13, 63, 238);
	gt_obj_set_size(rect13, 75, 30);
	gt_obj_set_opa(rect13, GT_OPA_41);
	gt_rect_set_radius(rect13, 0);
	gt_rect_set_bg_color(rect13, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect13, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect13, 1);
	gt_rect_set_border(rect13, 0);
	gt_obj_add_event_cb(rect13, AD_U, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect14 */
	rect14 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect14, 9, 277);
	gt_obj_set_size(rect14, 95, 43);
	gt_obj_set_opa(rect14, GT_OPA_54);
	gt_rect_set_radius(rect14, 0);
	gt_rect_set_bg_color(rect14, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect14, gt_color_hex(0x778899));
	gt_rect_set_fill(rect14, 1);
	gt_rect_set_border(rect14, 4);
	gt_obj_add_event_cb(rect14, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect15 */
	rect15 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect15, 167, 51);
	gt_obj_set_size(rect15, 63, 30);
	gt_obj_set_opa(rect15, GT_OPA_50);
	gt_rect_set_radius(rect15, 0);
	gt_rect_set_bg_color(rect15, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect15, gt_color_hex(0x778899));
	gt_rect_set_fill(rect15, 1);
	gt_rect_set_border(rect15, 4);


	/** rect16 */
	rect16 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect16, 230, 51);
	gt_obj_set_size(rect16, 75, 30);
	gt_obj_set_opa(rect16, GT_OPA_41);
	gt_rect_set_radius(rect16, 0);
	gt_rect_set_bg_color(rect16, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect16, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect16, 1);
	gt_rect_set_border(rect16, 0);


	/** rect17 */
	rect17 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect17, 167, 88);
	gt_obj_set_size(rect17, 63, 30);
	gt_obj_set_opa(rect17, GT_OPA_50);
	gt_rect_set_radius(rect17, 0);
	gt_rect_set_bg_color(rect17, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect17, gt_color_hex(0x778899));
	gt_rect_set_fill(rect17, 1);
	gt_rect_set_border(rect17, 4);


	/** rect18 */
	rect18 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect18, 230, 88);
	gt_obj_set_size(rect18, 75, 30);
	gt_obj_set_opa(rect18, GT_OPA_41);
	gt_rect_set_radius(rect18, 0);
	gt_rect_set_bg_color(rect18, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect18, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect18, 1);
	gt_rect_set_border(rect18, 0);


	/** rect19 */
	rect19 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect19, 167, 124);
	gt_obj_set_size(rect19, 63, 30);
	gt_obj_set_opa(rect19, GT_OPA_50);
	gt_rect_set_radius(rect19, 0);
	gt_rect_set_bg_color(rect19, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect19, gt_color_hex(0x778899));
	gt_rect_set_fill(rect19, 1);
	gt_rect_set_border(rect19, 4);


	/** rect20 */
	rect20 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect20, 230, 124);
	gt_obj_set_size(rect20, 75, 30);
	gt_obj_set_opa(rect20, GT_OPA_41);
	gt_rect_set_radius(rect20, 0);
	gt_rect_set_bg_color(rect20, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect20, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect20, 1);
	gt_rect_set_border(rect20, 0);


	/** rect21 */
	rect21 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect21, 167, 162);
	gt_obj_set_size(rect21, 63, 30);
	gt_obj_set_opa(rect21, GT_OPA_50);
	gt_rect_set_radius(rect21, 0);
	gt_rect_set_bg_color(rect21, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect21, gt_color_hex(0x778899));
	gt_rect_set_fill(rect21, 1);
	gt_rect_set_border(rect21, 4);


	/** rect22 */
	rect22 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect22, 230, 162);
	gt_obj_set_size(rect22, 75, 30);
	gt_obj_set_opa(rect22, GT_OPA_41);
	gt_rect_set_radius(rect22, 0);
	gt_rect_set_bg_color(rect22, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect22, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect22, 1);
	gt_rect_set_border(rect22, 0);


	/** rect23 */
	rect23 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect23, 167, 201);
	gt_obj_set_size(rect23, 63, 30);
	gt_obj_set_opa(rect23, GT_OPA_50);
	gt_rect_set_radius(rect23, 0);
	gt_rect_set_bg_color(rect23, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect23, gt_color_hex(0x778899));
	gt_rect_set_fill(rect23, 1);
	gt_rect_set_border(rect23, 4);


	/** rect24 */
	rect24 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect24, 230, 201);
	gt_obj_set_size(rect24, 75, 30);
	gt_obj_set_opa(rect24, GT_OPA_41);
	gt_rect_set_radius(rect24, 0);
	gt_rect_set_bg_color(rect24, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect24, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect24, 1);
	gt_rect_set_border(rect24, 0);


	/** rect25 */
	rect25 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect25, 331, 51);
	gt_obj_set_size(rect25, 63, 30);
	gt_obj_set_opa(rect25, GT_OPA_50);
	gt_rect_set_radius(rect25, 0);
	gt_rect_set_bg_color(rect25, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect25, gt_color_hex(0x778899));
	gt_rect_set_fill(rect25, 1);
	gt_rect_set_border(rect25, 4);


	/** rect26 */
	rect26 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect26, 394, 51);
	gt_obj_set_size(rect26, 75, 30);
	gt_obj_set_opa(rect26, GT_OPA_41);
	gt_rect_set_radius(rect26, 0);
	gt_rect_set_bg_color(rect26, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect26, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect26, 1);
	gt_rect_set_border(rect26, 0);


	/** rect27 */
	rect27 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect27, 332, 88);
	gt_obj_set_size(rect27, 63, 30);
	gt_obj_set_opa(rect27, GT_OPA_50);
	gt_rect_set_radius(rect27, 0);
	gt_rect_set_bg_color(rect27, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect27, gt_color_hex(0x778899));
	gt_rect_set_fill(rect27, 1);
	gt_rect_set_border(rect27, 4);


	/** rect28 */
	rect28 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect28, 395, 88);
	gt_obj_set_size(rect28, 75, 30);
	gt_obj_set_opa(rect28, GT_OPA_41);
	gt_rect_set_radius(rect28, 0);
	gt_rect_set_bg_color(rect28, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect28, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect28, 1);
	gt_rect_set_border(rect28, 0);


	/** rect29 */
	rect29 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect29, 332, 124);
	gt_obj_set_size(rect29, 63, 30);
	gt_obj_set_opa(rect29, GT_OPA_50);
	gt_rect_set_radius(rect29, 0);
	gt_rect_set_bg_color(rect29, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect29, gt_color_hex(0x778899));
	gt_rect_set_fill(rect29, 1);
	gt_rect_set_border(rect29, 4);


	/** rect30 */
	rect30 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect30, 395, 124);
	gt_obj_set_size(rect30, 75, 30);
	gt_obj_set_opa(rect30, GT_OPA_40);
	gt_rect_set_radius(rect30, 0);
	gt_rect_set_bg_color(rect30, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect30, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect30, 1);
	gt_rect_set_border(rect30, 0);


	/** rect31 */
	rect31 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect31, 332, 162);
	gt_obj_set_size(rect31, 63, 30);
	gt_obj_set_opa(rect31, GT_OPA_50);
	gt_rect_set_radius(rect31, 0);
	gt_rect_set_bg_color(rect31, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect31, gt_color_hex(0x778899));
	gt_rect_set_fill(rect31, 1);
	gt_rect_set_border(rect31, 4);


	/** rect32 */
	rect32 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect32, 395, 162);
	gt_obj_set_size(rect32, 75, 30);
	gt_obj_set_opa(rect32, GT_OPA_41);
	gt_rect_set_radius(rect32, 0);
	gt_rect_set_bg_color(rect32, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect32, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect32, 1);
	gt_rect_set_border(rect32, 0);


	/** rect33 */
	rect33 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect33, 332, 201);
	gt_obj_set_size(rect33, 63, 30);
	gt_obj_set_opa(rect33, GT_OPA_50);
	gt_rect_set_radius(rect33, 0);
	gt_rect_set_bg_color(rect33, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect33, gt_color_hex(0x778899));
	gt_rect_set_fill(rect33, 1);
	gt_rect_set_border(rect33, 4);
	gt_obj_add_event_cb(rect33, ad0_change, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** rect34 */
	rect34 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect34, 395, 201);
	gt_obj_set_size(rect34, 75, 30);
	gt_obj_set_opa(rect34, GT_OPA_41);
	gt_rect_set_radius(rect34, 0);
	gt_rect_set_bg_color(rect34, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect34, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect34, 1);
	gt_rect_set_border(rect34, 0);
	gt_obj_add_event_cb(rect34, ad0_change, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** lab35 */
	lab35 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab35, 135, 281);
	gt_obj_set_size(lab35, 83, 37);
	gt_label_set_font_color(lab35, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab35, 24);
	gt_label_set_font_family_cn(lab35, 20);
	gt_label_set_font_family_en(lab35, 33);
	gt_label_set_font_family_fl(lab35, 50);
	gt_label_set_font_align(lab35, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab35,title[SystemSetting.langue][15]);


	/** rect35 */
	rect35 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect35, 129, 277);
	gt_obj_set_size(rect35, 95, 43);
	gt_obj_set_opa(rect35, GT_OPA_50);
	gt_rect_set_radius(rect35, 0);
	gt_rect_set_bg_color(rect35, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect35, gt_color_hex(0x778899));
	gt_rect_set_fill(rect35, 1);
	gt_rect_set_border(rect35, 4);
	gt_obj_add_event_cb(rect35,Pause,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab36 */
	lab36 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab36, 257, 281);
	gt_obj_set_size(lab36, 90, 37);
	gt_label_set_font_color(lab36, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab36, 24);
	gt_label_set_font_family_cn(lab36, 20);
	gt_label_set_font_family_en(lab36, 33);
	gt_label_set_font_family_fl(lab36, 50);
	gt_label_set_font_align(lab36, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab36, title[SystemSetting.langue][16]);


	/** rect36 */
	rect36 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect36, 255, 276);
	gt_obj_set_size(rect36, 95, 43);
	gt_obj_set_opa(rect36, GT_OPA_50);
	gt_rect_set_radius(rect36, 0);
	gt_rect_set_bg_color(rect36, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect36, gt_color_hex(0x778899));
	gt_rect_set_fill(rect36, 1);
	gt_rect_set_border(rect36, 4);
	gt_obj_add_event_cb(rect36,AgainstRun,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab37 */
	lab37 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab37, 378, 281);
	gt_obj_set_size(lab37, 90, 37);
	gt_label_set_font_color(lab37, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab37, 24);
	gt_label_set_font_family_cn(lab37, 20);
	gt_label_set_font_family_en(lab37, 33);
	gt_label_set_font_family_fl(lab37, 50);
	gt_label_set_font_align(lab37, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab37, title[SystemSetting.langue][17]);


	/** rect37 */
	rect37 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect37, 375, 277);
	gt_obj_set_size(rect37, 95, 43);
	gt_obj_set_opa(rect37, GT_OPA_50);
	gt_rect_set_radius(rect37, 0);
	gt_rect_set_bg_color(rect37, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect37, gt_color_hex(0x778899));
	gt_rect_set_fill(rect37, 1);
	gt_rect_set_border(rect37, 4);
	gt_obj_add_event_cb(rect37,RTLrun,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab38 灯光检测*/
	lab38 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab38, 169, 240);
	gt_obj_set_size(lab38, 60, 24);
	gt_label_set_font_color(lab38, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab38, 16);
	gt_label_set_font_family_cn(lab38, 9);
	gt_label_set_font_family_en(lab38, 30);
	gt_label_set_font_family_fl(lab38, 50);
	gt_label_set_font_align(lab38, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab38, title[SystemSetting.langue][22]);

	/** lab40 */
	lab40 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab40, 237, 240);
	gt_obj_set_size(lab40, 60, 24);
	gt_label_set_font_color(lab40, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab40, 16);
	gt_label_set_font_family_cn(lab40, 9);
	gt_label_set_font_family_en(lab40, 30);
	gt_label_set_font_family_fl(lab40, 50);
	gt_label_set_font_align(lab40, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab40, title[SystemSetting.langue][25]);

	/** rect40 */
	rect40 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect40, 230, 240);
	gt_obj_set_size(rect40, 75, 30);
	gt_obj_set_opa(rect40, GT_OPA_41);
	gt_rect_set_radius(rect40, 0);
	gt_rect_set_bg_color(rect40, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect40, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect40, 1);
	gt_rect_set_border(rect40, 0);
	gt_obj_add_event_cb(rect40,LED_detection,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** rect38 */
	rect38 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect38, 167, 240);
	gt_obj_set_size(rect38, 63, 30);
	gt_obj_set_opa(rect38, GT_OPA_50);
	gt_rect_set_radius(rect38, 0);
	gt_rect_set_bg_color(rect38, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect38, gt_color_hex(0x778899));
	gt_rect_set_fill(rect38, 1);
	gt_rect_set_border(rect38, 4);
	gt_obj_add_event_cb(rect38,LED_detection,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** lab39 蜂鸣器检测*/
	lab39 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab39, 335, 240);
	gt_obj_set_size(lab39, 60, 24);
	gt_label_set_font_color(lab39, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab39, 16);
	gt_label_set_font_family_cn(lab39, 9);
	gt_label_set_font_family_en(lab39, 30);
	gt_label_set_font_family_fl(lab39, 50);
	gt_label_set_font_align(lab39, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab39, title[SystemSetting.langue][23]);

	/** lab41 */
	lab41 = gt_label_create(SensorMonitor);
	gt_obj_set_pos(lab41, 402, 240);
	gt_obj_set_size(lab41, 60, 24);
	gt_label_set_font_color(lab41, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab41, 16);
	gt_label_set_font_family_cn(lab41, 9);
	gt_label_set_font_family_en(lab41, 30);
	gt_label_set_font_family_fl(lab41, 50);
	gt_label_set_font_align(lab41, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab41, title[SystemSetting.langue][25]);

	/** rect41 */
	rect41 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect41, 395, 240);
	gt_obj_set_size(rect41, 75, 30);
	gt_obj_set_opa(rect41, GT_OPA_41);
	gt_rect_set_radius(rect41, 0);
	gt_rect_set_bg_color(rect41, gt_color_hex(0xc0c0c0));
	gt_rect_set_color_border(rect41, gt_color_hex(0xc0c0c0));
	gt_rect_set_fill(rect41, 1);
	gt_rect_set_border(rect41, 0);
	gt_obj_add_event_cb(rect41,BEEP_detection,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** rect39 */
	rect39 = gt_rect_create(SensorMonitor);
	gt_obj_set_pos(rect39, 332, 240);
	gt_obj_set_size(rect39, 63, 30);
	gt_obj_set_opa(rect39, GT_OPA_50);
	gt_rect_set_radius(rect39, 0);
	gt_rect_set_bg_color(rect39, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect39, gt_color_hex(0x778899));
	gt_rect_set_fill(rect39, 1);
	gt_rect_set_border(rect39, 4);
	gt_obj_add_event_cb(rect39,BEEP_detection,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	timer_main_ThirmSec =  _gt_timer_create(Timer_ThirmSec,300,NULL);

	return SensorMonitor;
}

