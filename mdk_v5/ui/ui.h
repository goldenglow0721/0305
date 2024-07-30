#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"
#include "up.h"
#include "headbar_view.h"
#include "library_history.h"
#include "library_infusion.h"
#include "library_drug.h"


#define _GT_HMI_BOARD_CONFIG_VERTICAL     0

#define DEL_TIMER_VAL(val)                do { _gt_timer_del(val); val = NULL; } while(0)


typedef struct 
{
    char                 title[32]; 
    double*               data;  
    int                 id;
    
}KeyBoardF;
extern KeyBoardF keyboardf;

typedef struct 
{
    char                 title[32]; 
    int*                 data;  
    int                  id;
    
}KeyBoardI;
extern KeyBoardI keyboardi;


typedef struct 
{
    char                 title[32];   
    uint8_t              id;  //用来做标识 及 返回
    
}KeyBoardS;
extern KeyBoardS keyboards;


typedef struct 
{
    char                 title[32]; 
    TIME*                time;
    int                  id;
}KeyBoardT;
extern KeyBoardT keyboardt;


typedef struct{
	double toplimit;
	double lowerlimit;
	double softtoplimit;
	double softlowlimit;
	_Bool  FLiimit;   
}Limit;
extern Limit limit;

#define MAXLINES 128

typedef enum{
    GT_SCR_ID_HOME = 0 ,//主界面
    GT_SCR_ID_1,//模式选择
    GT_SCR_ID_2, //输注设定page1
    GT_SCR_ID_3,//系统设定page1
    GT_SCR_ID_4,//密码键盘
    GT_SCR_ID_5,//清除累积量
    GT_SCR_ID_6,//速度模式
    GT_SCR_ID_7,//时间模式
    GT_SCR_ID_8,//体重模式
    GT_SCR_ID_9,//序列模式
    GT_SCR_ID_10,//滴定模式
    GT_SCR_ID_11,//微量模式
    GT_SCR_ID_12,//梯度模式
    GT_SCR_ID_13,//首剂量模式
    GT_SCR_ID_14,//剂量时间模式
    GT_SCR_ID_15,//间断给药模式
    GT_SCR_ID_16,//药物库
    GT_SCR_ID_17,//体重模式2
    GT_SCR_ID_18,
    GT_SCR_ID_19,
    GT_SCR_ID_20,
    GT_SCR_ID_21,//输注设定page2
    GT_SCR_ID_22,//输注设定page3
    GT_SCR_ID_23,//输注设定page4
    GT_SCR_ID_24,//阻塞压力
    GT_SCR_ID_25,//压力单位
    GT_SCR_ID_26,//气泡大小
    GT_SCR_ID_27,
    GT_SCR_ID_28,
    GT_SCR_ID_29,
    GT_SCR_ID_30,
    GT_SCR_ID_31,//系统设定page2
    GT_SCR_ID_32,//历史记录
    GT_SCR_ID_33,//版本信息
    GT_SCR_ID_34,//夜间模式
    GT_SCR_ID_35,
    GT_SCR_ID_36,
    GT_SCR_ID_37,
    GT_SCR_ID_38,
    GT_SCR_ID_39,
    GT_SCR_ID_40,
    GT_SCR_ID_41,//8888page1
    GT_SCR_ID_42,//8888page2
    GT_SCR_ID_43,//8888page3
    GT_SCR_ID_44,//8888page4
    GT_SCR_ID_45,//8888page5
    GT_SCR_ID_46,//6686page1
    GT_SCR_ID_47,//6686page2
    GT_SCR_ID_48,//删除药物名称
    GT_SCR_ID_49,//删除品牌
    GT_SCR_ID_50,//精度校准1
    GT_SCR_ID_51,//精度校准2
    GT_SCR_ID_52,//精度校准3
    GT_SCR_ID_53,//精度校准4
    GT_SCR_ID_54,//压力校准1
    GT_SCR_ID_55,//压力校准2
    GT_SCR_ID_56,//导出历史记录
    GT_SCR_ID_57,//恢复出厂设置
    GT_SCR_ID_58,//系统语言设定
    GT_SCR_ID_59,//系统日期时间与日期
    GT_SCR_ID_60,//系统自检
    GT_SCR_ID_61,//精度校准2_1
    GT_SCR_ID_62,//传感器ADs
    GT_SCR_ID_63,//删除历史记录
    GT_SCR_ID_64,//开机演示界面
    GT_SCR_ID_65,//关机动画界面
    GT_SCR_ID_66,
    GT_SCR_ID_67,
    GT_SCR_ID_68,
    GT_SCR_ID_69,
    GT_SCR_ID_70,
    GT_SCR_ID_71,
    GT_SCR_ID_72,
    GT_SCR_ID_73,
    GT_SCR_ID_74,
    GT_SCR_ID_75,
    GT_SCR_ID_76,
    GT_SCR_ID_77,
    GT_SCR_ID_78,
    GT_SCR_ID_79,
    GT_SCR_ID_80,//int键盘
    GT_SCR_ID_81,//float键盘
    GT_SCR_ID_82,//time键盘
    GT_SCR_ID_83,//soft键盘
    GT_SCR_ID_84,//待机界面
    GT_SCR_ID_85,//排气
    GT_SCR_ID_86,//排气运行
    GT_SCR_ID_87,//输液器选择1
    GT_SCR_ID_88,//输液器选择2
    GT_SCR_ID_89,//剂量单位
    GT_SCR_ID_90,//KVO模式
    GT_SCR_ID_91,//药量单位
    GT_SCR_ID_92,//快进(普通)
    GT_SCR_ID_93,//快进运行(普通)
    GT_SCR_ID_94,//序列模式快进
    GT_SCR_ID_95,//序列模式快进运行
    GT_SCR_ID_96,//速度时间模式运行
    GT_SCR_ID_97,//体重模式运行
    GT_SCR_ID_98,//序列模式运行
    GT_SCR_ID_99,//滴定模式运行
    GT_SCR_ID_100//关机
}gt_scr_id_et;



extern gt_obj_st * MainScreen;
extern gt_obj_st * ModeSelect;
extern gt_obj_st * BrandChoice;
extern gt_obj_st * PressureUnit;
extern gt_obj_st * Maintenance2;
extern gt_obj_st * screen_Maintenance_Two;
extern gt_obj_st * SensorMonitor;
extern gt_obj_st * RestoreFactory;
extern gt_obj_st * BootUp;
extern gt_obj_st * DeleteHistory;
extern gt_obj_st * Maintenance1;
extern gt_obj_st * screen_Maintenance_Normal_Two;
extern gt_obj_st * screen_Maintenance_Normal_Three;
extern gt_obj_st * screen_Maintenance_Normal_Four;
extern gt_obj_st * ClearAccumVol;
extern gt_obj_st * BrandChioce;
extern gt_obj_st * BrandChoice2;
extern gt_obj_st * UiSpeedMode;
extern gt_obj_st * Purge;
extern gt_obj_st * PurgeRun;
extern gt_obj_st * SpeedAndTimeModeRun;
extern gt_obj_st * GeneralBolus;
extern gt_obj_st * GeneralBolusRun;
extern gt_obj_st * UiTimeMode;
extern gt_obj_st * TimeKeyBoard;
extern gt_obj_st * UiWeightMode;
extern gt_obj_st * Uiweightmode2;

extern gt_obj_st * DrugUnit;
extern gt_obj_st * DoseUnit;
extern gt_obj_st * WeightModeRun;
extern gt_obj_st * SeqMode;
extern gt_obj_st * SeqModeRun;
extern gt_obj_st * SeqBolus;
extern gt_obj_st * SeqBolusRun;
extern gt_obj_st * DrugChoice;
extern gt_obj_st * NightSetting;
extern gt_obj_st * PurgeSizeSetting;
extern gt_obj_st * SystemDataTimeSetting;
extern gt_obj_st * SystemDataSetting;
extern gt_obj_st * SystemLanguageSetting;
extern gt_obj_st * HistoryView;
extern gt_obj_st * Version;
extern gt_obj_st * screen_DrugLibrary_One;
extern gt_obj_st * UiDripMode;
extern gt_obj_st * SystemSetting1;
extern gt_obj_st * SystemSetting2;
/*persion*/
extern gt_obj_st * Screen_KeyBoard_PassWord;
extern gt_obj_st * Screen_KeyBoard_Int;
extern gt_obj_st * Screen_KeyBoard_Float;
extern gt_obj_st * Screen_KeyBoard_Soft;
extern gt_obj_st * ParamSetting1;
extern gt_obj_st * ParamSetting2;
extern gt_obj_st * ParamSetting3;
extern gt_obj_st * PressureNumSel;
extern gt_obj_st * AccuracyCalibrate3;
extern gt_obj_st * AccuracyCalibrate4;
extern gt_obj_st * AccuracyCalibrate2_1;
extern gt_obj_st * PressureCalibrate2;
extern gt_obj_st * PressureCalibrate1;
extern gt_obj_st * Logo;
extern gt_obj_st * DripModeRun;
extern gt_obj_st * shutdown;
extern gt_obj_st * PowerOff;
extern gt_obj_st * headclock;
extern gt_obj_st * headrect;
extern gt_obj_st * headlabel;
extern gt_obj_st * DrugDelete;
extern gt_obj_st * KVORun;
extern gt_obj_st * dialog1;
extern gt_obj_st * Standby;




gt_obj_st * gt_init_SensorMonitor(void);
gt_obj_st * gt_init_MainScreen(void);
gt_obj_st * gt_init_ModeSelect(void);
gt_obj_st * gt_init_PressureUnit(void);
gt_obj_st * gt_init_Maintenance2_1(void);
gt_obj_st * gt_init_Maintenance2_2(void);
gt_obj_st * gt_init_SensorMonitor(void);
gt_obj_st * gt_init_RestoreFactory(void);
gt_obj_st * gt_init_BootUp(void);
gt_obj_st * gt_init_DeleteHistory(void);
gt_obj_st * gt_init_Maintenance1_1(void);
gt_obj_st * gt_init_SystemSetting1(void);
gt_obj_st * gt_init_SystemSetting2(void);
gt_obj_st * gt_init_Maintenance1_2(void);
gt_obj_st * gt_init_Maintenance1_3(void);
gt_obj_st * gt_init_Maintenance1_4(void);
gt_obj_st * gt_init_Maintenance1_5(void);
gt_obj_st * gt_init_ExportHistory(void);
gt_obj_st * gt_init_ClearAccumVol(void);
gt_obj_st * gt_init_SpeedMode(void);
gt_obj_st * gt_init_Purge(void);
gt_obj_st * gt_init_PurgeRun(void);
gt_obj_st * gt_init_SpeedAndTimeModeRun(void);
gt_obj_st * gt_init_GeneralBolus(void);
gt_obj_st * gt_init_GeneralBolusRun(void);
gt_obj_st * gt_init_TimeMode(void);
gt_obj_st * gt_init_TimeKeyBoard(void);
gt_obj_st * gt_init_WeightMode(void);
gt_obj_st * gt_init_DrugUnit(void);
gt_obj_st * gt_init_DoseUnit(void);
gt_obj_st * gt_init_WeightModeRun(void);
gt_obj_st * gt_init_SeqMode(void);
gt_obj_st * gt_init_SeqModeRun(void);
gt_obj_st * gt_init_SeqBolus(void);
gt_obj_st * gt_init_SeqBolusRun(void);
gt_obj_st * gt_init_DrugChoice(void);
gt_obj_st * gt_init_NightSetting(void);
gt_obj_st * gt_init_PurgeSizeSetting(void);
gt_obj_st * gt_init_SystemDataTimeSetting(void);
gt_obj_st * gt_init_SystemDataSetting(void);
gt_obj_st * gt_init_SystemLanguageSetting(void);
gt_obj_st * gt_init_HistoryView(void);
gt_obj_st * gt_init_Version(void);
gt_obj_st * gt_init_DripModeRun(void);
gt_obj_st * gt_init_screen_DrugLibrary_One(void);
gt_obj_st * gt_init_DripMode(void);
gt_obj_st * gt_init_shutdown(void);
gt_obj_st * gt_init_PowerOff(void);
gt_obj_st * gt_init_Standby(void);


/*persion*/
gt_obj_st * gt_init_screen_keyBoard_PassWord(void);
gt_obj_st * gt_init_Screen_KeyBoard_Int(void);
gt_obj_st * gt_init_screen_keyBoard_float(void);
gt_obj_st * gt_init_Screen_KeyBoard_Soft(void);
gt_obj_st * gt_init_ParamSetting1(void);
gt_obj_st * gt_init_ParamSetting2(void);
gt_obj_st * gt_init_ParamSetting3(void);
gt_obj_st * gt_init_ParamSetting4(void);
gt_obj_st * gt_init_BrandChoice2();
gt_obj_st * gt_init_SystemCheck(void);
gt_obj_st * gt_init_BrandChoice(void);
gt_obj_st * gt_init_PressureNumSel(void);
gt_obj_st * gt_init_AccuracyCalibrate1();
gt_obj_st * gt_init_AccuracyCalibrate2();
gt_obj_st * gt_init_AccuracyCalibrate3();
gt_obj_st * gt_init_AccuracyCalibrate4(void);
gt_obj_st * gt_init_AccuracyCalibrate2_1(void);
extern gt_obj_st * ModeSelect_cp;
gt_obj_st * gt_init_ModeSelect_cp(void);
gt_obj_st * gt_init_PressureCalibrate1(void);
gt_obj_st * gt_init_PressureCalibrate2(void);
gt_obj_st * gt_init_Logo(void);
gt_obj_st * gt_init_WeightMode2(void);
gt_obj_st * gt_init_WeightMode(void);
gt_obj_st * gt_init_DrugDelete(void);
gt_obj_st * gt_init_KVORun(void);
gt_obj_st * dialog1_create(char * str);
gt_obj_st * dialog2_create(char * str,gt_event_st * e);
void Drugaffirm(gt_event_st * e);
void Brandaffirm(gt_event_st * e);
gt_obj_st * gt_init_DeleteBrand(void);


extern _Bool calibrate;
extern int  brandchoice2_from;






void headvisiable(gt_visible_et temp);
_Bool judgeIsRunScreen();


#endif

