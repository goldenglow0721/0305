
#include "library_history.h"
#include "gt.h"
#include "ui.h"

#include "fatfs_history.h"
#include <string.h>
#include "bsp_qspi_flash.h"
#include "my_flash.h"
#include "infusion.h"

//用链表的形式做 (结构体)




const RecordEv recordEv[5][92]={
	{
	/*******************动作*******************************************/
	EA_Starting,  				 "开机",
	EA_Shutdown,	  			 "关机",
	EA_Await,		  			 "待机",		
	EA_Alarm,		  			 "报警",
	EA_CleAlarm,	  			 "消警",
	EA_CleCumulant,  			 "清零",	
	EA_Amend,		  			 "修改",
	EA_start,		  			 "启动",
	EA_stop,		 			 "暂停",
	EA_Set,		  				 "设置",
	EA_Adjust,					 "校准",	
	EA_Into,		 			 "进入",
	EA_Delete,			         "删除",
	EA_Add,			             "添加",
	/*******************描述*******************************************/
	Ev_Startup,				     "开机",
    Ev_EntMODE,	     		     "进入模式选择",
	Ev_EntSpeed,				 "进入速度模式",
	Ev_EntTime, 				 "进入时间模式",
	Ev_EntWeight,				 "进入体重模式",
	Ev_EntSequential,			 "进入序列模式",
    Ev_EntDrip,				     "进入滴定模式",
	Ev_EntDruglib,               "进入药品库",
	Ev_SystemSetting,            "进入系统设定",
	Ev_General,                  "进入输注设定",
	Ev_Maintenance1,             "进入系统维护8888",
    Ev_Maintenance2,             "进入系统维护6686",
	Ev_EntBolus,				 "进入快进菜单",
	Ev_EntExhaust,				 "进入排气菜单",
	Ev_SetSpeed,				 "速度为:",
	Ev_SetTime, 				 "时间为:",
	Ev_SetLiquid,				 "液量为:",
	Ev_SetWeight,				 "体重为:",
	Ev_SetWeightUint,			 "体重单位:",
	Ev_SetMeDose,				 "药量为:",
	Ev_SetDose, 				 "剂量:",
	Ev_SetQuantity, 			 "待入量:",
    Ev_GetVolume,	     	  	 "累计量:",
    Ev_SetDripswitch,	     	 "设置滴数为:",
	Ev_SetKVO,					 "设置KVO:",
	Ev_SetBubbleSize,			 "设置气泡大小:",
	Ev_AccumBubble,	     	  	 "设置累计气泡:",
	Ev_EnterKVO,				 "进入KVO",
	Ev_ConfirmBrand,			 "品牌确认:",
	Ev_SetMedicineUint, 		 "药量单位:",
	Ev_SetDoseSpeed,			 "剂量速度:",
	Ev_SetDoseUnit, 		     "剂量单位:",
	Ev_SetPressUnit,			 "压力单位:",
	Ev_Setlightsize,			 "亮度:",	
	Ev_SetLockTime, 			 "自动锁为:",
	Ev_SetNoOperationTime,		 "无操作为:",
	Ev_SetNearDoneTime, 		 "接近完成:",
    Ev_BedNum,  	             "床号",
	Ev_StarInjection,			 "开始输液",
	Ev_FinishInjection, 		 "输液完成",
	Ev_StopInjection,			 "停止输液",
	Ev_KeySound,				 "按键声音",	  
	Ev_AlarmSound,				 "设置报警声:",	
	Ev_CloseAlarmS, 			 "关闭报警",
	Ev_langue,					 "语言:",
	Ev_SoundSize,				 "音量:",
	Ev_NightMode,				 "夜间模式",
	Ev_ClearAccVolu,			 "清除累计量",
	Ev_AntiBolus,				 "Anti-Bolus:", 				
	Ev_CorrectSucceed,			 "校准成功",
	Ev_CorrectFail, 			 "校准失败",
	Ev_ChangeSysTime,			 "设置系统时间", 
	Ev_Shutdown,				 "关机",
	Ev_InfusionAdjust,			 "精度校准",		
	Ev_PressureAdjust,			 "压力校准",
	Ev_RecoverSet,				 "恢复厂家设置:",
	Ev_MaxSpeed, 		    	 "最大速度",  	
	Ev_NetworkDown, 			 "网电掉电报警",   
	Ev_BolusSpeed,				 "快进速度",
	Ev_BolusQuantity,			 "快进预置量", 
	Ev_BolusTime,				 "快进时间",	
	Ev_ExhaustSpeed,			 "排气速度",				
	Ev_SpeedERRALARM,			 "速度错误报警",
	Ev_CleSpeedEALARM,			 "清除速度错误报警",
	Ev_ELELowALARM, 			 "电量低报警",	
	Ev_CleELELowALARM,			 "清除电量低报警", 
	Ev_ChokeALARM,				 "上阻塞",
	Ev_CleChokeALARM,			 "清除阻塞报警",
	Ev_CleOverALARM,			 "清除完成报警",
	Ev_EnterBlous,				 "开始手动快进",
	Ev_AutoBlous,				 "自动快进",
	Ev_ExitBlous,				 "结束快进",
	Ev_EnterExhaust,			 "排气",
    Ev_ExitExhaust,				 "排气量:",
    Ev_ConfirmDrug,			  	 "药物:",
    Ev_Tube,					 "输液器品牌",	
	Ev_PressureRating,			 "阻塞等级为:",
	Ev_Drip,					 "滴系数:",
 },
	

  {
    /*******************动作*******************************************/
	EA_Starting,  				 "Start up",
	EA_Shutdown,	  			 "Shutdown",
	EA_Await,		  			 "Standby",		
	EA_Alarm,		  			 "Alarm",
	EA_CleAlarm,	  			 "Clear ",
	EA_CleCumulant,  			 "Clear",	
	EA_Amend,		  			 "Change",
	EA_start,		  			 "Start",
	EA_stop,		 			 "Pause",
	EA_Set,		  				 "Setting",
	EA_Adjust,					 "Calibration",	
	EA_Into,		 			 "Into",
	EA_Delete,			         "Delete",
	EA_Add,			             "Add",
	/*******************描述*******************************************/	
	Ev_Startup,				     "Start up",
    Ev_EntMODE,	     		     "",
	Ev_EntSpeed,				 "",
	Ev_EntTime, 				 "",
	Ev_EntWeight,				 "",
	Ev_EntSequential,			 "",
    Ev_EntDrip,				     "",
	Ev_EntDruglib,               "",
	Ev_SystemSetting,            "",
	Ev_General,                  "",
	Ev_Maintenance1,             "",
    Ev_Maintenance2,             "",
	Ev_EntBolus,				 "",		
	Ev_EntExhaust,				 "", 		
	Ev_SetSpeed,				 "Rate:",
	Ev_SetTime, 				 "Time:",
	Ev_SetLiquid,				 "Liquid:",
	Ev_SetWeight,				 "Weight:",
	Ev_SetWeightUint,			 "Weight Unit:",
	Ev_SetMeDose,				 "Dose:",
	Ev_SetDose, 				 "Dose Rate:",
	Ev_SetQuantity, 			 "VTBI:",	
    Ev_GetVolume,	     	  	 "Total Volume:",
    Ev_SetDripswitch,	     	 "Set Drops to:",
	Ev_SetKVO,					 "KVO:",	
	Ev_SetBubbleSize,			 "bubble size:",	 
	Ev_AccumBubble,	     	  	 "accumulate bubble:",	  
	Ev_EnterKVO,				 "Into KVO",		
	Ev_ConfirmBrand,			 "Brand:",		
	Ev_SetMedicineUint, 		 "Dose Unit:",		
	Ev_SetDoseSpeed,			 "Dose Rate:",	
	Ev_SetDoseUnit, 		     "Dose Rate Unit:",    
	Ev_SetPressUnit,			 "Unit of Pressure:",
	Ev_Setlightsize,			 "Brightness:",	
	Ev_SetLockTime, 			 "AutoLock:",
	Ev_SetNoOperationTime,		 "Reminder:",
	Ev_SetNearDoneTime, 		 "Near done:",
    Ev_BedNum,  	             "Bed Number",
	Ev_StarInjection,			 "StartRun",
	Ev_FinishInjection, 		 "VTBI Completed",
	Ev_StopInjection,			 "StopRun",
	Ev_KeySound,				 "Key Sound",
	Ev_AlarmSound,				 "Alarm Sound",
	Ev_CloseAlarmS, 			 "Alarm Off",
	Ev_langue,					 "Language:",
	Ev_SoundSize,				 "Volume:",
	Ev_NightMode,				 "Night Mode",
	Ev_ClearAccVolu,			 "Total Volume",
	Ev_AntiBolus,				 "Anti-Bolus:",
	Ev_CorrectSucceed,			 "Calibration completed!",
	Ev_CorrectFail, 			 "Calibration failure!",
	Ev_ChangeSysTime,			 "System Time",  /* "设置系统时间", */
	Ev_Shutdown,				 "Shutdown",
	Ev_InfusionAdjust,			 "IV Set Calibration",
	Ev_PressureAdjust,			 "Pressure Calibration",
	Ev_RecoverSet,				 "Restore Factory Default",
	Ev_MaxSpeed, 		    	 "Max Rate",
	Ev_NetworkDown, 			 "",
	Ev_BolusSpeed,				 "Bolus Rate:",
	Ev_BolusQuantity,			 "Bolus VTBI:",
	Ev_BolusTime,				 "Bolus Time",
	Ev_ExhaustSpeed,			 "Purge Rate",
	Ev_SpeedERRALARM,			 "",
	Ev_CleSpeedEALARM,			 "",
	Ev_ELELowALARM, 			 "",
	Ev_CleELELowALARM,			 "",
	Ev_ChokeALARM,				 "Upstream Occlusion",
	Ev_CleChokeALARM,			 "",
	Ev_CleOverALARM,			 "",
	Ev_EnterBlous,				 "to manual bolus.",
	Ev_AutoBlous,				 "Auto Bolus",
	Ev_ExitBlous,				 "Stop Bolus",
	Ev_EnterExhaust,			 "Purge",
    Ev_ExitExhaust,				 "Purge Volume:",
    Ev_ConfirmDrug,			  	 "Drug:",
    Ev_Tube,					 "IV Set Brand",	
	Ev_PressureRating,			 "Block level:",
	Ev_Drip,					 "drip:",
},
  {

        /*******************动作*******************************************/
	EA_Starting,  				 "Encender",
	EA_Shutdown,	  			 "Apagar",
	EA_Await,		  			 "En Espera",		
	EA_Alarm,		  			 "Alarma",
	EA_CleAlarm,	  			 "Apagar la Alarma",
	EA_CleCumulant,  			 "Borrar la Alarma",	
	EA_Amend,		  			 "Cambio",
	EA_start,		  			 "Inicio",
	EA_stop,		 			 "Pausa",
	EA_Set,		  				 "Config.",
	EA_Adjust,					 "Calibración",	
	EA_Into,		 			 "Entrar",
	EA_Delete,			         "Eliminar",
	EA_Add,			             "Agregar",
	/*******************描述*******************************************/	
	Ev_Startup,				     "Encender",
    Ev_EntMODE,	     		     "",
	Ev_EntSpeed,				 "",
	Ev_EntTime, 				 "",
	Ev_EntWeight,				 "",
	Ev_EntSequential,			 "",
    Ev_EntDrip,				     "",
	Ev_EntDruglib,               "",
	Ev_SystemSetting,            "",
	Ev_General,                  "",
	Ev_Maintenance1,             "",
    Ev_Maintenance2,             "",
	Ev_EntBolus,				 "",		
	Ev_EntExhaust,				 "", 		
	Ev_SetSpeed,				 "Velocidad:",
	Ev_SetTime, 				 "Tiempo:",
	Ev_SetLiquid,				 "Líquido:",
	Ev_SetWeight,				 "Peso:",
	Ev_SetWeightUint,			 "Unidad de Peso:",
	Ev_SetMeDose,				 "Dosis:",
	Ev_SetDose, 				 "Tasa de Dosis:",
	Ev_SetQuantity, 			 "VTBI:",	
    Ev_GetVolume,	     	  	 "Volumen total:",
    Ev_SetDripswitch,	     	 "Establecer Gotas en:",
	Ev_SetKVO,					 "KVO:",	
	Ev_SetBubbleSize,			 "Medida de Burbuja:",	 
	Ev_AccumBubble,	     	  	 "Acumular burbuja:",	  
	Ev_EnterKVO,				 "Entrar KVO",		
	Ev_ConfirmBrand,			 "Marca:",		
	Ev_SetMedicineUint, 		 "Unidad de Dosis:",		
	Ev_SetDoseSpeed,			 "Tasa de Dosis:",	
	Ev_SetDoseUnit, 		     "Unidad de Tasa de dosis:",    
	Ev_SetPressUnit,			 "Unidad de Presión:",
	Ev_Setlightsize,			 "Brillo:",	
	Ev_SetLockTime, 			 "Autolock:",
	Ev_SetNoOperationTime,		 "Recordatorio:",
	Ev_SetNearDoneTime, 		 "Cerca de hecho:",
    Ev_BedNum,  	             "Número de Cama",
	Ev_StarInjection,			 "Empezar",
	Ev_FinishInjection, 		 "VTBI Completado",
	Ev_StopInjection,			 "Parar",
	Ev_KeySound,				 "Sonido Clave",	  
	Ev_AlarmSound,				 "Sonido de Alarma",
	Ev_CloseAlarmS, 			 "Apagado de Audio",
	Ev_langue,					 "Idioma:",
	Ev_SoundSize,				 "Volumen:",
	Ev_NightMode,				 "Modo Nocturno",
	Ev_ClearAccVolu,			 "Volumen Total",
	Ev_AntiBolus,				 "Anti-Bolus:", 				
	Ev_CorrectSucceed,			 "Calibración completa!",
	Ev_CorrectFail, 			 "Falla de calibración!",
	Ev_ChangeSysTime,			 "Tiempo",  /* "设置系统时间", */
	Ev_Shutdown,				 "Apagar",
	Ev_InfusionAdjust,			 "Calibración de IV Conjunto",		
	Ev_PressureAdjust,			 "Calibración de Presión",
	Ev_RecoverSet,				 "Restaurar la Fábrica Predeterminada",
	Ev_MaxSpeed, 		    	 "Tasa máxima",  	
	Ev_NetworkDown, 			 "",   
	Ev_BolusSpeed,				 "Tasa de Dolo:",
	Ev_BolusQuantity,			 "VTBI de Dolo:", 
	Ev_BolusTime,				 "Tiempo de Bolo",	
	Ev_ExhaustSpeed,			 "Tasa de Purga",				
	Ev_SpeedERRALARM,			 "",
	Ev_CleSpeedEALARM,			 "",
	Ev_ELELowALARM, 			 "",	
	Ev_CleELELowALARM,			 "", 
	Ev_ChokeALARM,				 "Oclusión Aguas Arriba",
	Ev_CleChokeALARM,			 "",
	Ev_CleOverALARM,			 "",
	Ev_EnterBlous,				 "al bolo Manual.",
	Ev_AutoBlous,				 "Bolo Auto",
	Ev_ExitBlous,				 "Parar el Bolo",
	Ev_EnterExhaust,			 "Purga",
    Ev_ExitExhaust,				 "Volumen de Purga:",
    Ev_ConfirmDrug,			  	 "Medicamentos:",
    Ev_Tube,					 "IV Set Marca",	
	Ev_PressureRating,			 "Nivel de bloque:",
	Ev_Drip,					 "Diámetro de Goteo:",
},
  {

       /*******************动作*******************************************/
	EA_Starting,  				 "開機",
	EA_Shutdown,	  			 "關機",
	EA_Await,		  			 "待機",		
	EA_Alarm,		  			 "報警",
	EA_CleAlarm,	  			 "消警",
	EA_CleCumulant,  			 "清除",	
	EA_Amend,		  			 "修改",
	EA_start,		  			 "啟動",
	EA_stop,		 			 "暫停",
	EA_Set,		  				 "設置",
	EA_Adjust,					 "校準",	
	EA_Into,		 			 "進入",
	EA_Delete,			         "刪除",
	EA_Add,			             "增加",
	/*******************描述*******************************************/	
	Ev_Startup,				     "開機",
    Ev_EntMODE,	     		     "",
	Ev_EntSpeed,				 "",
	Ev_EntTime, 				 "",
	Ev_EntWeight,				 "",
	Ev_EntSequential,			 "",
    Ev_EntDrip,				     "",
	Ev_EntDruglib,               "",
	Ev_SystemSetting,            "",
	Ev_General,                  "",
	Ev_Maintenance1,             "",
    Ev_Maintenance2,             "",
	Ev_EntBolus,				 "",		
	Ev_EntExhaust,				 "", 		
	Ev_SetSpeed,				 "速度為:",
	Ev_SetTime, 				 "時間為:",
	Ev_SetLiquid,				 "液量為:",
	Ev_SetWeight,				 "體重為:",
	Ev_SetWeightUint,			 "體重單位為:",
	Ev_SetMeDose,				 "藥量為:",
	Ev_SetDose, 				 "劑量為:",
	Ev_SetQuantity, 			 "待入量為:",	
    Ev_GetVolume,	     	  	 "累計量:",
    Ev_SetDripswitch,	     	 "設定滴數為:",
	Ev_SetKVO,					 "KVO為:",	
	Ev_SetBubbleSize,			 "設置氣泡大小:",	 
	Ev_AccumBubble,	     	  	 "設置累積氣泡:",	  
	Ev_EnterKVO,				 "進入KVO",		
	Ev_ConfirmBrand,			 "品牌確認:",		
	Ev_SetMedicineUint, 		 "藥量單位為:",		
	Ev_SetDoseSpeed,			 "劑量速度:",	
	Ev_SetDoseUnit, 		     "劑量單位為:",    
	Ev_SetPressUnit,			 "壓力單位:",
	Ev_Setlightsize,			 "亮度:",	
	Ev_SetLockTime, 			 "自動鎖為:",
	Ev_SetNoOperationTime,		 "無操作為:",
	Ev_SetNearDoneTime, 		 "接近完成為:",
    Ev_BedNum,  	             "床號",
	Ev_StarInjection,			 "開始輸液",
	Ev_FinishInjection, 		 "輸液完成",
	Ev_StopInjection,			 "停止輸液",
	Ev_KeySound,				 "按鍵聲音",	  
	Ev_AlarmSound,				 "報警聲音",
	Ev_CloseAlarmS, 			 "報警關閉",
	Ev_langue,					 "語言為:",
	Ev_SoundSize,				 "音量為:",
	Ev_NightMode,				 "夜間模式",
	Ev_ClearAccVolu,			 "清除累計量",
	Ev_AntiBolus,				 "Anti-Bolus:", 				
	Ev_CorrectSucceed,			 "校準成功",
	Ev_CorrectFail, 			 "校準失敗",
	Ev_ChangeSysTime,			 "系統時間",  /* "设置系统时间", */
	Ev_Shutdown,				 "關機",
	Ev_InfusionAdjust,			 "精度校準",		
	Ev_PressureAdjust,			 "壓力校準",
	Ev_RecoverSet,				 "恢復廠家設置",
	Ev_MaxSpeed, 		    	 "最大速度",  	
	Ev_NetworkDown, 			 "",   
	Ev_BolusSpeed,				 "快進速度為:",
	Ev_BolusQuantity,			 "快進待入量為:", 
	Ev_BolusTime,				 "快進時間",	
	Ev_ExhaustSpeed,			 "排氣速度",				
	Ev_SpeedERRALARM,			 "",
	Ev_CleSpeedEALARM,			 "",
	Ev_ELELowALARM, 			 "",	
	Ev_CleELELowALARM,			 "", 
	Ev_ChokeALARM,				 "上阻塞",
	Ev_CleChokeALARM,			 "",
	Ev_CleOverALARM,			 "",
	Ev_EnterBlous,				 "開始手動快進",
	Ev_AutoBlous,				 "自動快進",
	Ev_ExitBlous,				 "停止快進",
	Ev_EnterExhaust,			 "排氣",
    Ev_ExitExhaust,				 "排氣量:",
    Ev_ConfirmDrug,			  	 "藥物:",
    Ev_Tube,					 "輸液器品牌",	
	Ev_PressureRating,			 "阻塞等級為:",
	Ev_Drip,					 "滴係數:",
},
  
{

        /*******************动作*******************************************/
	EA_Starting,  				 "Começar",
	EA_Shutdown,	  			 "Desligar",
	EA_Await,		  			 "Espera",		
	EA_Alarm,		  			 "Alarme",
	EA_CleAlarm,	  			 "Limpar",
	EA_CleCumulant,  			 "Limpar",	
	EA_Amend,		  			 "Trocar",
	EA_start,		  			 "Iniciar",
	EA_stop,		 			 "Pausar",
	EA_Set,		  				 "Config.",
	EA_Adjust,					 "Calibração",	
	EA_Into,		 			 "Em",
	EA_Delete,			         "Deletar",
	EA_Add,			             "Adicionar",
	/*******************描述*******************************************/	
	Ev_Startup,				     "Começar",
    Ev_EntMODE,	     		     "",
	Ev_EntSpeed,				 "",
	Ev_EntTime, 				 "",
	Ev_EntWeight,				 "",
	Ev_EntSequential,			 "",
    Ev_EntDrip,				     "",
	Ev_EntDruglib,               "",
	Ev_SystemSetting,            "",
	Ev_General,                  "",
	Ev_Maintenance1,             "",
    Ev_Maintenance2,             "",
	Ev_EntBolus,				 "",		
	Ev_EntExhaust,				 "", 		
	Ev_SetSpeed,				 "Taxa:",
	Ev_SetTime, 				 "Tempo:",
	Ev_SetLiquid,				 "Liquido:",
	Ev_SetWeight,				 "Peso:",
	Ev_SetWeightUint,			 "Unidade de peso:",
	Ev_SetMeDose,				 "Dose:",
	Ev_SetDose, 				 "Taxa de dose:",
	Ev_SetQuantity, 			 "VTBI:",	
    Ev_GetVolume,	     	  	 "Volume total",
    Ev_SetDripswitch,	     	 "Definir Gotas como:",
	Ev_SetKVO,					 "KVO finalizado:",	
	Ev_SetBubbleSize,			 "Tamanho da bolha:",	 
	Ev_AccumBubble,	     	  	 "Acumulo de bolha:",	  
	Ev_EnterKVO,				 "Em KVO",		
	Ev_ConfirmBrand,			 "Marca",		
	Ev_SetMedicineUint, 		 "Unidade de dose:",		
	Ev_SetDoseSpeed,			 "Taxa de dose:",	
	Ev_SetDoseUnit, 		     "Unidade de taxa de dose:",    
	Ev_SetPressUnit,			 "Unidade de pressão:",
	Ev_Setlightsize,			 "Brilho:",
	Ev_SetLockTime, 			 "Bloqueio automático:",
	Ev_SetNoOperationTime,		 "Lembrete:",
	Ev_SetNearDoneTime, 		 "Quase pronto:",
    Ev_BedNum,  	             "Numero do leito",
	Ev_StarInjection,			 "StartRun",
	Ev_FinishInjection, 		 "VTBI completo",
	Ev_StopInjection,			 "StopRun",
	Ev_KeySound,				 "Som chave",
	Ev_AlarmSound,				 "Som de alarme",
	Ev_CloseAlarmS, 			 "Alarme desligado",
	Ev_langue,					 "Linguagem:",
	Ev_SoundSize,				 "Volume:",
	Ev_NightMode,				 "Modo noturno",
	Ev_ClearAccVolu,			 "Volume Total",
	Ev_AntiBolus,				 "Anti-Bolus:", 				
	Ev_CorrectSucceed,			 "Calibração completa",
	Ev_CorrectFail, 			 "Falha na calibração",
	Ev_ChangeSysTime,			 "Hora do sistema",  /* "设置系统时间", */
	Ev_Shutdown,				 "Desligar",
	Ev_InfusionAdjust,			 "Calibração de equipo",
	Ev_PressureAdjust,			 "Pressão de calibração",
	Ev_RecoverSet,				 "Restaurar padrão de fábrica",
	Ev_MaxSpeed, 		    	 "Taxa máxima",
	Ev_NetworkDown, 			 "",
	Ev_BolusSpeed,				 "Taxa de Bolus:",
	Ev_BolusQuantity,			 "VTBI Bolus:",
	Ev_BolusTime,				 "Tempo de Bolus",
	Ev_ExhaustSpeed,			 "Taxa de Purga",
	Ev_SpeedERRALARM,			 "Oclusão a montante",
	Ev_CleSpeedEALARM,			 "",
	Ev_ELELowALARM, 			 "",
	Ev_CleELELowALARM,			 "",
	Ev_ChokeALARM,				 "Oclusão a montante",
	Ev_CleChokeALARM,			 "",
	Ev_CleOverALARM,			 "",
	Ev_EnterBlous,				 "para bolus manual.",
	Ev_AutoBlous,				 "Auto Bolus",
	Ev_ExitBlous,				 "Para Bolus",
	Ev_EnterExhaust,			 "Purga",
    Ev_ExitExhaust,				 "Volume de purga:",
    Ev_ConfirmDrug,			  	 "Droga:",
    Ev_Tube,					 "Marca do equipo",	
	Ev_PressureRating,			 "Nível de bloqueio:",
	Ev_Drip,					 "Gotas:"
  }
};




static struct historyList* list;

char historyname1[30];
char historyname2[30];
char historyname3[30];
char historyname4[30];
char historyname5[30];
char historyname6[50];
char historyname7[50];
char historyname8[50];
char historyname9[50];
char historyname10[50];
char historytime1[50];
char historytime2[50];
char historytime3[50];
char historytime4[50];
char historytime5[50];

char historyData1[30];
char historyData2[30];
char historyData3[30];
char historyData4[30];
char historyData5[30];



//删除历史记录
void destroyHistoryList()
{
	//读取历史记录 计数值
	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
	
	//将historynumber置0
    ParamSetting.historynumber = 0; //更新历史记录数据写入flash
	ParamSetting.history_full_flag = 0;
	
	flash_write(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
		
}


//void history_write_to_flash(HistoryNodeMessage* message)
//{
//     //更新时间
//	 rtc_time_get();

//	//读取历史记录 计数值
//	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
//	
//	//更新参数	
//    spiflash_write((uint8_t *)message,History_Flash_ADDRESS_Start+sizeof(HistoryNodeMessage)*ParamSetting.historynumber,sizeof(HistoryNodeMessage));
//	
//	//更新历史记录计数值
//    ParamSetting.historynumber ++; //更新历史记录数据写入flash
//	
//	flash_write(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType));
//}


void history_write_to_flash(HistoryNodeMessage* message)
{
     //更新时间
	 rtc_time_get();

	 //读取历史记录 计数值
	 flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
	
	if(ParamSetting.historynumber == History_max_num){ //读取的计数值满了  存储0-19
		
	   ParamSetting.historynumber = 0;
	   ParamSetting.history_full_flag = 1; //历史记录满标志位
	}
	
	//更新历史记录
    spiflash_write((uint8_t *)message,History_Flash_ADDRESS_Start+sizeof(HistoryNodeMessage)*ParamSetting.historynumber,sizeof(HistoryNodeMessage));
	
	//更新历史记录计数值
    ParamSetting.historynumber ++; //更新历史记录数据写入flash
	
	flash_write(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
}



void history_info_langue(char* Historytime,char* Historyname_O,char* Historyname_T,char* historyData,HistoryNodeMessage* message)
{
	char buffer[50];
	
	//更新时间
	 rtc_time_get();

	if(SystemSetting.langue==Chinese)
	{
		sprintf(buffer,"%d/%d/%d %02d:%02d",message->TIME_DATA.year,message->TIME_DATA.mon,message->TIME_DATA.day,message->TIME_DATA.hour,message->TIME_DATA.min);
		strcpy(Historytime,buffer);
		strcpy(Historyname_O,message->ch_name1);   
		strcpy(Historyname_T,message->ch_name2); 
		if(*message->Data){
			sprintf(buffer,"%s",message->Data);
			strcpy(historyData,buffer);
		}
	}
	else if(SystemSetting.langue==English)
	{
		sprintf(buffer,"%d/%d/%d %02d:%02d",message->TIME_DATA.year,message->TIME_DATA.mon,message->TIME_DATA.day,message->TIME_DATA.hour,message->TIME_DATA.min);
		strcpy(Historytime,buffer);
		strcpy(Historyname_O,message->en_name1);   
		strcpy(Historyname_T,message->en_name2); 
		if(*message->Data){
		sprintf(buffer,"%s",message->Data);
			strcpy(historyData,buffer);
		}
	}
	else if(SystemSetting.langue==Spanish)
	{
			sprintf(buffer,"%d/%d/%d %02d:%02d",message->TIME_DATA.year,message->TIME_DATA.mon,message->TIME_DATA.day,message->TIME_DATA.hour,message->TIME_DATA.min);
		strcpy(Historytime,buffer);
		strcpy(Historyname_O,message->es_name1);   
		strcpy(Historyname_T,message->es_name2); 
		if(*message->Data){
		sprintf(buffer,"%s",message->Data);
			strcpy(historyData,buffer);
		}
	}
	else if(SystemSetting.langue==Chinese2)
	{
			sprintf(buffer,"%d/%d/%d %02d:%02d",message->TIME_DATA.year,message->TIME_DATA.mon,message->TIME_DATA.day,message->TIME_DATA.hour,message->TIME_DATA.min);
		strcpy(Historytime,buffer);
		strcpy(Historyname_O,message->ch2_name1);   
		strcpy(Historyname_T,message->ch2_name2); 
		if(*message->Data){
		sprintf(buffer,"%s",message->Data);
			strcpy(historyData,buffer);
		}
	}
	else if(SystemSetting.langue==Portuguese) 
	{
			sprintf(buffer,"%d/%d/%d %02d:%02d",message->TIME_DATA.year,message->TIME_DATA.mon,message->TIME_DATA.day,message->TIME_DATA.hour,message->TIME_DATA.min);
		strcpy(Historytime,buffer);
		strcpy(Historyname_O,message->pu_name1);   
		strcpy(Historyname_T,message->pu_name2); 
		if(*message->Data){
		sprintf(buffer,"%s",message->Data);
			strcpy(historyData,buffer);
		}
	}
}




HistoryNodeMessage HistoryNodeMessage_buff[5]= {0};

//通过传入的page来获取5个历史数据
void get_history_info(uint32_t history_info_page)
{
	for(int i=0;i<5;i++){
		
	  spiflash_read((uint8_t *)&HistoryNodeMessage_buff[i],History_Flash_ADDRESS_Start+sizeof(HistoryNodeMessage)*((history_info_page-1)*5+i),sizeof(HistoryNodeMessage));
	  
	   switch(i){
	   
		   case 0:
			   history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[i]);
			   break;
		   case 1:
			   history_info_langue(historytime2,historyname2,historyname7,historyData2,&HistoryNodeMessage_buff[i]);
			   break;
		   case 2:
			   history_info_langue(historytime3,historyname3,historyname8,historyData3,&HistoryNodeMessage_buff[i]);
			   break;
		   case 3:
			   history_info_langue(historytime4,historyname4,historyname9,historyData4,&HistoryNodeMessage_buff[i]);
			   break;
		   case 4:
			   history_info_langue(historytime5,historyname5,historyname10,historyData5,&HistoryNodeMessage_buff[i]);
			   break;
	   }

	}

}







