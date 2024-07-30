#include "infusion.h"
#include "alarm.h"
#include "ui.h"
#include "fatfs_history.h"
#include "at32f403a_407_board.h"
#include "HX711.h"
#include "bsp_usb.h"
#include "FreeRTOS.h" 
#include "task.h"

#define SECTOR_SIZE                      				2048   /* this parameter depends on the specific model of the chip */




SensorPack sensorpack; 

Cumulant_Mode cumulantMode;

Speed_Mode SpeedModeconfig;
Time_Mode TimeModeconfig;
Weight_Mode WeightModeconfig;
Sequen_Mode SequenModeconfig;
Drip_Mode DripModeconfig;

Bolus_Mode BolusMode;
Exhaust_Mode exhaustMode;


System_Setting SystemSettingconfig;
Param_Setting ParamSettingconfig;
System_Maintain SystemMaintainconfig;

//int BlevelData[15]={0,150,225,300,375,450,525,600,675,750,825,900,975,1050,1125};

int BlevelData[4]={0,300,525,900};
uint16_t flash_buf[SECTOR_SIZE / 2];


static _Bool LockTimeFlag=FALSE;    /*TRUE 表示上锁，FALSE 解锁*/
static int  LockTimeSec=5*60;      /*为0，表示上锁，其他为解锁*/
static unsigned int StaringOldPhoto;




Press_Data press_Data=
{
	16765,16613,16692,16852,
	0.0,
	16457,
	0,
	0,0
};

Infusion_Now InfusionNow={
	0,0,1,"未选药","安得"
};


AirBubble_Data airbubble_Data = {0};

Infusion_Data infusion_data=
{
	7.48,7.21,
	18530,18826,19166,19592,40.00,70.00,120.00
};	


static Bolus_Mode sDefBolusMode=  
{
	800.0,
	2.0,
	{0,0,0,0,0,10},
};


//����ϵͳ���úͲ������õ�Ĭ��ֵ
static Speed_ModeType sDefSpeedMode= 
{
	0.0,
	0.0,
	{0,0,0,0,0,0}
};


static Time_ModeType sDefTimeMode= 
{
	0.0,
	0.0,
	{0,0,0,0,0,0}
};

static Weight_ModeType sDefWeightMode= 
{
	0.0,0.0,
	M_mg,
	0.0,0.0,
	D_mg_kg_h,
	0.0,0.0,0
};

static Drip_ModeType sDefDripMode=
{
	20,
	FALSE,
	133,
	0,
	20,
	{0,0,0,0,0,0},
	0.0
};

static Sequen_ModeType sSequenMode=
{
	0.0,0.0,0.0,0.0,0.0,0.0,
	0.0,0.0,0.0,0.0,0.0,0.0,
	{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},
	0.0,
	{0,0,0,0,0,0},
	0
};


static Param_SettingType sDefParamSetting=
{
	"aeiou","aeiou","aeiou",3,P_mmHg,
	0.5,50,1.5,
	FALSE,5,TRUE,2,TRUE,3,0,0,0,{0,0,0,24,0,0}
	
};

static System_SettingType sDefSystemSetting=
{
		4,4,1,
		{{2021,1,1,0,0,0},timeformat_24,yyyymmdd},             //国内yyyy-mm-dd			国外dd-mm-yyyy
		Chinese,
		{FALSE,{0,0,0,8,30,00},{0,0,0,12,00,00},1,1},
		{"V01.00.00.00","24060010","58-00001-00"}
    
};

static System_MaintainType sDefSystemMaintain=
{
		2000,
		TRUE,TRUE,TRUE,16500,16000
	
};


Exhaust_Mode sDefExhaustMode= 
{
	800, 
};


/**
  * @brief  write data using halfword mode without checking
  * @param  write_addr: the address of writing
  * @param  p_buffer: the buffer of writing data
  * @param  num_write: the number of writing data
  * @retval result
  */
error_status flash_write_nocheck(uint32_t write_addr, uint16_t *p_buffer, uint16_t num_write)
{
  uint16_t i;
  flash_status_type status = FLASH_OPERATE_DONE; 
  for(i = 0; i < num_write; i++)
  {
    status = flash_halfword_program(write_addr, p_buffer[i]);
    if(status != FLASH_OPERATE_DONE)
      return ERROR;
    write_addr += 2;
  }
  return SUCCESS;
}



/**
  * @brief  read data using halfword mode
  * @param  read_addr: the address of reading
  * @param  p_buffer: the buffer of reading data
  * @param  num_read: the number of reading data
  * @retval none
  */
//void flash_read(uint32_t read_addr, uint16_t *p_buffer, uint16_t num_read)
//{
//	//�ýṹ�� ���ϵķ�ʽ
//  int i;
//  for(i = 0; i < num_read; i++)
//  {
//    p_buffer[i] = *(uint16_t*)(read_addr);
//    read_addr += 2;
//  }
//}



void flash_read(uint32_t read_addr, uint16_t *p_buffer, uint16_t num_read)
{
	
    // 检查地址是否对齐
    if (read_addr % 2 != 0)
    {
        printf("读取地址未对齐!\n");
        return;
    }

    for (int i = 0; i < num_read; i++)
    {
        p_buffer[i] = *(uint16_t *)(read_addr);
        read_addr += 2;
    }
}
/**
  * @brief  write data using halfword mode with checking
  * @param  write_addr: the address of writing
  * @param  p_buffer: the buffer of writing data
  * @param  num_write: the number of writing data
  * @retval result
  */
error_status flash_write(uint32_t write_addr, uint16_t *p_buffer, uint16_t num_write)
{
	
  uint32_t offset_addr;
  uint32_t sector_position;
  uint16_t sector_offset;
  uint16_t sector_remain;
  uint16_t i;
  flash_status_type status = FLASH_OPERATE_DONE;
	
  flash_unlock();
  offset_addr = write_addr - FLASH_BASE;
  sector_position = offset_addr / SECTOR_SIZE;
  sector_offset = (offset_addr % SECTOR_SIZE) / 2;
  sector_remain = SECTOR_SIZE / 2 - sector_offset;
  if(num_write <= sector_remain)
    sector_remain = num_write;
  while(1)
  {
    flash_read(sector_position * SECTOR_SIZE + FLASH_BASE, flash_buf, SECTOR_SIZE / 2);
    for(i = 0; i < sector_remain; i++)
    {
      if(flash_buf[sector_offset + i] != 0xFFFF)
        break;
    }
    if(i < sector_remain)
    {
      /* wait for operation to be completed */
      status = flash_operation_wait_for(ERASE_TIMEOUT);
     
      if((status == FLASH_PROGRAM_ERROR) || (status == FLASH_EPP_ERROR))
        flash_flag_clear(FLASH_PRGMERR_FLAG | FLASH_EPPERR_FLAG);
      else if(status == FLASH_OPERATE_TIMEOUT)
        return ERROR;
      status = flash_sector_erase(sector_position * SECTOR_SIZE + FLASH_BASE);
      if(status != FLASH_OPERATE_DONE)
        return ERROR;
      for(i = 0; i < sector_remain; i++)
      {
        flash_buf[i + sector_offset] = p_buffer[i];
      }
      if(flash_write_nocheck(sector_position * SECTOR_SIZE + FLASH_BASE, flash_buf, SECTOR_SIZE / 2) != SUCCESS)
        return ERROR;
    }
    else
    {
      if(flash_write_nocheck(write_addr, p_buffer, sector_remain) != SUCCESS)
        return ERROR;
    }
    if(num_write == sector_remain)
      break;
    else
    {
      sector_position++;
      sector_offset = 0;
      p_buffer += sector_remain;
      write_addr += (sector_remain * 2);
      num_write -= sector_remain;
      if(num_write > (SECTOR_SIZE / 2))
        sector_remain = SECTOR_SIZE / 2;
      else
        sector_remain = num_write;
    }
  }
  flash_lock();
	
  return SUCCESS;
}

/*ϵͳ�趨FlASH��������*/
void ReadSystemSettingMessageFromFlash(void )  
{
	#if 0
	flash_read(SystemSetting_Flash_ADDRESS_START,SystemSetting->BUF,sizeof(System_SettingType));
	#else
	flash_read(SystemSetting_Flash_ADDRESS_START,(uint16_t *)&SystemSetting,sizeof(System_SettingType)/2);
	#endif
}

void WriteSystemSettingMessageToFlash(void )    
{
	#if 0
	flash_write(SystemSetting_Flash_ADDRESS_START,SystemSetting->BUF,sizeof(System_SettingType));
	#else
	flash_write(SystemSetting_Flash_ADDRESS_START,(uint16_t *)&SystemSetting,sizeof(System_SettingType)/2);
	#endif
}


/*�����趨FlASH��������*/
void ReadParamSettingMessageFromFlash(void )   
{
	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
}


Param_Setting ParaSetting;

void WriteParamSettingMessageToFlash(void)    
{
//	ParaSetting.ParamSetting;
	flash_sector_erase(ParamSetting_Flash_ADDRESS_START);
	flash_sector_erase(ParamSetting_Flash_ADDRESS_START+0x800);
	
	if(SUCCESS == flash_write(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2))
	printf("WriteParamSettingMessageToFlash success\r\n ");	
	else
	printf("WriteParamSettingMessageToFlash err\r\n ");		
	
	//比较写入flash的数据是否一致
	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParaSetting,sizeof(Param_SettingType)/2);	
	if(0==memcmp(&ParamSetting,&ParaSetting,sizeof(Param_SettingType)))
	printf(" read and write data check success \r\n");
	else
	printf(" read and write data check err");	
}


/*ϵͳά��FlASH��������*/
void ReadSystemMaintainMessageFromFlash(void )   
{
	flash_read(SystemMaintain_Flash_Address_Start,(uint16_t *)&SystemMaintain,sizeof(System_MaintainType)/2);
}
void WriteSystemMaintainMessageToFlash(void )   
{
	flash_write(SystemMaintain_Flash_Address_Start,(uint16_t *)&SystemMaintain,sizeof(System_MaintainType)/2);
}

void WriteSpeedModeMessageToFlash(void )   
{
	flash_write(SpeedMode_Flash_Address_Start,(uint16_t *)&SpeedMode,sizeof(Speed_Mode)/2);
}
void ReadSpeedModeMessageFromFlash(void )   
{
	flash_read(SpeedMode_Flash_Address_Start,(uint16_t *)&SpeedMode,sizeof(Speed_Mode)/2);
}

void WriteTimeModeMessageToFlash(void )   
{
	flash_write(TimeMode_Flash_Address_Start,(uint16_t *)&TimeMode,sizeof(Time_Mode)/2);
}
void ReadTimeModeMessageFromFlash(void )   
{
	flash_read(TimeMode_Flash_Address_Start,(uint16_t *)&TimeMode,sizeof(Time_Mode)/2);
}

void WriteWeightModeMessageToFlash(void )   
{
	flash_write(WeightMode_Flash_Address_Start,(uint16_t *)&WeightMode,sizeof(Weight_Mode)/2);
}
void ReadWeightModeMessageFromFlash(void )
{
	flash_read(WeightMode_Flash_Address_Start,(uint16_t *)&WeightMode,sizeof(Weight_Mode)/2);
}

void WriteSeqModeMessageToFlash(void )   
{
	flash_write(SeqMode_Flash_Address_Start,(uint16_t *)&SequenMode,sizeof(Sequen_Mode)/2);
}
void ReadSeqModeMessageFromFlash(void )   
{
	flash_read(SeqMode_Flash_Address_Start,(uint16_t *)&SequenMode,sizeof(Sequen_Mode)/2);
}

void WriteDripModeMessageToFlash(void )   
{
	flash_write(DripMode_Flash_Address_Start,(uint16_t *)&DripMode,sizeof(Drip_Mode)/2);
}
void ReadDripModeMessageFromFlash(void )   
{
	flash_read(DripMode_Flash_Address_Start,(uint16_t *)&DripMode,sizeof(Drip_Mode)/2);
}

int readInfusionTubeListFromFlash(void)	
{
	int count; 
	InfusionNode_t * node[ParamSetting.brandnumber];

	//分配空间
	for(int i=0;i<ParamSetting.brandnumber; i++)
	{
		node[i] =  (InfusionNode_t *)malloc(sizeof(InfusionNode_t));
		if(node[i] == NULL)
		{
			usb_print("从flash中读输液器列表分配内存失败!\n");
			return -1;
		}
	}

	initInfusionList();
	
	for(count=0;count < ParamSetting.brandnumber;count++)
	{
		flash_read(InfusionTube_Flash_ADDRESS_Start+sizeof(InfusionNode_t)*count,(uint16_t *)node[count],sizeof(InfusionNode_t)/2);
        usb_print("read Infusion[%d]:%s \r\n",count+1,node[count]->message.ch_name);
		node[count]->nextnode = NULL; //让他下一个节点成null
		addInfusionNode(node[count],false);
	}
	 //printf("read infusion tube over!\n");
		
}

int readDrugListFromFlash(void)
{
	int count; 	
	//DrugNode_t * node[ParamSetting.brandnumber] = (DrugNode_t *)malloc(sizeof(DrugNode_t)); //指向当前节点
	DrugNode_t * node[ParamSetting.drugnumber];
	//printf("read drug flash begin ParamSetting.drugnumber is %d!\r\n",ParamSetting.drugnumber);

	//分配空间
	for(int i=0; i<ParamSetting.drugnumber; i++)
	{
		node[i] =  (DrugNode_t *)malloc(sizeof(DrugNode_t));

		if(node[i] == NULL)
		{
			printf("从flash中读药物库列表分配内存失败!\n");
			return -1;
		}
	}
	initDrugList();
	
	//printf("------------------------------------------------------");
	
	for(count=0;count < ParamSetting.drugnumber;count++)
	{
		flash_read(DrugTube_Flash_ADDRESS_Start+sizeof(DrugNode_t)*count,(uint16_t *)node[count],sizeof(DrugNode_t)/2);
        printf("read Drug[%d]:%s \r\n",count+1,node[count]->message.ch_name);
		node[count]->nextnode = NULL; //让他下一个节点成null
		addDrugNode(node[count],false);
	}
	//printf("------------------------------------------------------");
	//printf("read drug over ParamSetting.drugnumber is %d\r\n",ParamSetting.drugnumber);		
}


void writeInfusionTubeListToFlash(void)
{
		int count,max; //用来记录已经到第几个品牌名了
		max = getNowInfusionListNum();
		InfusionNode_t * node = getThefirstInfusionNode();   //找到第一个节点
		
		//printf("brandnumber = %d\n",ParamSetting.brandnumber);
	
	for(int address =0;address<0x7800;address+=2048)
	{
	 flash_sector_erase(InfusionTube_Flash_ADDRESS_Start+address);
	}

	for(count = 0;count < ParamSetting.brandnumber; count++)
	{
		if(SUCCESS == flash_write(InfusionTube_Flash_ADDRESS_Start+sizeof(InfusionNode_t)*count,(uint16_t *)node,sizeof(InfusionNode_t)/2))
		{
			printf("write Infusion To Flash address:%08x data:%s\r\n",InfusionTube_Flash_ADDRESS_Start+sizeof(InfusionNode_t)*count,node->message.ch_name);
		}else{
		    printf("write Infusion To Flash err\r\n");
		}
		
		node = node->nextnode;
	}	
}

void writeAddInfusionTubeListToFlash(void)
{
	uint32_t node_count = getNowInfusionListNum();

	InfusionNode_t * node = getThefirstInfusionNode();   //找到第一个节点
	
	//printf("brandnumber = %d\n",node_count);

	//printf("WriteAddDrugListToFlash is %s \r\n",node->message.ch_name);
	while(node->nextnode)//有下个节点
	{
		node = node->nextnode;
	}
	
    flash_write(InfusionTube_Flash_ADDRESS_Start+sizeof(InfusionNode_t)*(node_count-1),(uint16_t *)node,sizeof(InfusionNode_t)/2);
  
    	
}


void WriteDrugListToFlash(void)
{
	int count =0; //用来记录已经到第几个药物名了
	DrugNode_t * node = getThefirstDrugNode();   //找到第一个节点
	
	//printf("drugnumber = %d\n",ParamSetting.drugnumber);
	
	for(int address =0;address<0x7800;address+=2048)
	{
	 flash_sector_erase(DrugTube_Flash_ADDRESS_Start + address);
	}
	
	for(count = 0;count < ParamSetting.drugnumber; count++)
	{
		if( SUCCESS == flash_write(DrugTube_Flash_ADDRESS_Start+sizeof(DrugNode_t)*count,(uint16_t *)node,sizeof(DrugNode_t)/2))
		printf("Write Drug To Flash address:%08x data:%s\r\n",DrugTube_Flash_ADDRESS_Start+sizeof(DrugNode_t)*count,node->message.ch_name);
		else
		printf("Write Drug To Flash err \r\n");
		
		node = node->nextnode;
	}	
}


#if 1
void WriteAddDrugListToFlash()
{	
	uint32_t node_count = getNowDrugListNum();
	
	DrugNode_t * node = getThefirstDrugNode();   //找到第一个
	while(node->nextnode)//有下个节点
	{
		node = node->nextnode;
	}//最后一个节点
	
	//printf("WriteAddDrugListToFlash count is %d\r\n",node_count);
	
	//printf("WriteAddDrugListToFlash is %s \r\n",node->message.ch_name);
	
	flash_write(DrugTube_Flash_ADDRESS_Start+sizeof(DrugNode_t)*(node_count-1),(uint16_t *)node,sizeof(DrugNode_t)/2);
}
#endif


#define CRC32_POLYNOMIAL 0xEDB88320u


//传入参数：                   数据首地址     数据大小
uint32_t calculate_crc32(const void *data, size_t size) {
    const uint8_t *byteData = (const uint8_t *)data;
    uint32_t crc = 0xFFFFFFFFu;

    for (size_t i = 0; i < size; ++i) {
        crc ^= byteData[i];
        for (int j = 0; j < 8; ++j) {
            crc = (crc >> 1) ^ ((crc & 1) ? CRC32_POLYNOMIAL : 0);
        }
    }

    return ~crc;
}




//��ʼʹ��ʱҪ���еĲ���
int ObDefValue(void)
{   
    //crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);
	//if(bpr_data_read(BPR_DATA2) != 0x1234) 
	uint16_t temp = 1;
    uint16_t temp2;
    flash_read(FirstComeFlagAddress,&temp2,sizeof(temp2)/2);

	if(temp2 != 0x1234) 
    {
		temp = 0x1234;
		flash_write(FirstComeFlagAddress,&temp,sizeof(temp)/2);
		//printf("first come\n");
	
		ParamSetting=sDefParamSetting;
		SystemMaintain=sDefSystemMaintain;
		SystemSetting=sDefSystemSetting;

		SpeedMode=sDefSpeedMode;
		TimeMode=sDefTimeMode;
		WeightMode=sDefWeightMode;
		SequenMode=sSequenMode;
		DripMode=sDefDripMode;
		

		createInfusionLib(); //要放在paramsetting后面
		createDrugLib();

		not_first_start_write_history_info(EA_Starting,EA_Starting,NULL);
				
		WriteSystemSettingMessageToFlash();
		WriteSystemMaintainMessageToFlash();
		WriteParamSettingMessageToFlash();

		WriteSpeedModeMessageToFlash();
		WriteTimeModeMessageToFlash();
		WriteWeightModeMessageToFlash();
		WriteSeqModeMessageToFlash();
		WriteDripModeMessageToFlash();

		exhaustMode.speed = 800.0;
		//bpr_data_write(BPR_DATA2,0x1234);	
	}
    else
    {	
		//createInfusionLib(); //要放在paramsetting后面
		ReadParamSettingMessageFromFlash();
		ReadSystemSettingMessageFromFlash();
		ReadSystemMaintainMessageFromFlash();
			
		exhaustMode.speed = 800.0;
		
		readInfusionTubeListFromFlash(); //必须放在系统维护后面
		readDrugListFromFlash();
		
		not_first_start_write_history_info(EA_Starting,EA_Starting,NULL);
			
		uint8_t temp = SystemSetting.Light;
		double temp2 = tmr_period_value_get(TMR13);
		tmr_channel_value_set(TMR13, TMR_SELECT_CHANNEL_1, (uint32_t)(100+50 * temp -1));
		
		#if 1
		ReadSpeedModeMessageFromFlash();
		ReadTimeModeMessageFromFlash();
		ReadWeightModeMessageFromFlash();
		ReadSeqModeMessageFromFlash();
		ReadDripModeMessageFromFlash();			
		#endif
    }

    return 0;
		
}


void ChangeScreenBlk(AddOrRdc cmd)
{

   static uint8_t nowblk =4;
   if(cmd == add)
   {
      nowblk++;
   }
   else if(cmd == reduce)
   {
      nowblk--;
   }
   else
   {
      return;
   }

    if(nowblk<1)
     nowblk=8;
    if(nowblk>8)
     nowblk=1;


  tmr_channel_value_set(TMR13, TMR_SELECT_CHANNEL_1, nowblk*10-1);   //c1dt  c1dtΪռ�ձ�
}


char* GetPressUintString(Pressure_Uint Press_Uint)
{
	if(Press_Uint==P_mmHg)
	{
		return PRESSUREUNIT00;
	}
	else if(Press_Uint==P_KPa)
	{
		return PRESSUREUNIT01;
	}
	else if(Press_Uint==P_bar)
	{
		return PRESSUREUNIT02;
	}
	else if(Press_Uint==P_psi)
	{
		return PRESSUREUNIT03;
	}
	else
	{
		return NULL;
	}	
}

/*
	 Get the current pressure mmHg
	 return mmHg;
*/
double PressureConversion(double NowPressure,Pressure_Uint FromPressUint,Pressure_Uint ToPressUint)
{
	double NowPressure_KPa=0.0;
	double ToNowPressure=0.0;
	
	switch(FromPressUint)
	{
		case P_mmHg: 
			NowPressure_KPa=NowPressure*0.13332;
			break;
		case P_KPa:
			NowPressure_KPa=NowPressure;
			break;
	    case P_bar:
			NowPressure_KPa=NowPressure*100;
			break;	
		case P_psi:
			NowPressure_KPa=NowPressure*6.89475;
			break;	
		default:
			break;	
   }
	switch(ToPressUint)
	{
		case P_mmHg: 
			ToNowPressure=NowPressure_KPa*7.5006;		    
			break;
		case P_KPa:
			ToNowPressure=NowPressure_KPa;
			break;
	    case P_bar:
			ToNowPressure=NowPressure_KPa*0.01;
			break;	
		case P_psi:
			ToNowPressure=NowPressure_KPa*0.14503;
			break;	
		default:
			break;		
	}
	return ToNowPressure;
}



//��ѹ��ֵת��ΪADֵ
void calpressureADandValue(int blocklevel)
{
	press_Data.k =(double)(press_Data.Pressure_newAD0 /(double)infusion_data.Pressure_AD0);
	//blocklevel = getParamsettingBlockLevel();

	if(sensorpack.RightKnobStatus == 1 && MotorControl.status!= MOTOR_STOP)
	{
		if(press_Data.Pressure_newAD0 > sensorpack.DownPressure)
		{
			if(press_Data.AD0num <= 180)
			{
				press_Data.AD0num++;
				press_Data.Pressure_AD0temp = press_Data.Pressure_newAD0;
				press_Data.Pressure_newAD0 = sensorpack.DownPressure;
			}
		}

		switch (blocklevel)
		{
			case 1:
				press_Data.Pressure_newAD40 = (unsigned int)((infusion_data.Pressure_AD40 - infusion_data.Pressure_AD0) \
												/ press_Data.k + press_Data.Pressure_newAD0);
				#if 0
				printf("1.\t=%d\n",press_Data.Pressure_newAD40);
				printf("2.\t%f\n",infusion_data.Pressure_value40);
				printf("3.\t%d\n",press_Data.Pressure_newAD0);
				printf("4.\t%d\n",sensorpack.DownPressure);
				#endif
				press_Data.Pressure_valuenow = infusion_data.Pressure_value40  \
												/ (press_Data.Pressure_newAD40 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);		
				break;
			case 2:
				press_Data.Pressure_newAD70 = (unsigned int)((infusion_data.Pressure_AD70 - infusion_data.Pressure_AD0)  \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value70 \
												/ (press_Data.Pressure_newAD70 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);			
				break;
			case 3:
				press_Data.Pressure_newAD120 = (unsigned int)((infusion_data.Pressure_AD120 - infusion_data.Pressure_AD0) \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value120  \
												/ (press_Data.Pressure_newAD120 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);	
				break;
			default:
				press_Data.Pressure_newAD70 = (unsigned int)((infusion_data.Pressure_AD70 - infusion_data.Pressure_AD0)  \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value70 \
												/ (press_Data.Pressure_newAD70 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);	
				break;
		}
		if((press_Data.Pressure_valuenow <= 0.0) || (press_Data.Pressure_valuenow >= 5000.0))
		{
			press_Data.Pressure_valuenow = 0.0;
		}

	}
	//报警时
	else if(SpeedAndTimeModeRun == gt_disp_get_scr() || gt_disp_get_scr()== WeightModeRun|| gt_disp_get_scr()== SeqModeRun)
	{
		switch (blocklevel)
		{
			case 1:
				press_Data.Pressure_newAD40 = (unsigned int)((infusion_data.Pressure_AD40 - infusion_data.Pressure_AD0) \
												/ press_Data.k + press_Data.Pressure_newAD0);
				#if 0
				printf("1.\t=%d\n",press_Data.Pressure_newAD40);
				printf("2.\t%f\n",infusion_data.Pressure_value40);
				printf("3.\t%d\n",press_Data.Pressure_newAD0);
				printf("4.\t%d\n",sensorpack.DownPressure);
				#endif
				press_Data.Pressure_valuenow = infusion_data.Pressure_value40  \
												/ (press_Data.Pressure_newAD40 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);		
				break;
			case 2:
				press_Data.Pressure_newAD70 = (unsigned int)((infusion_data.Pressure_AD70 - infusion_data.Pressure_AD0)  \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value70 \
												/ (press_Data.Pressure_newAD70 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);			
				break;
			case 3:
				press_Data.Pressure_newAD120 = (unsigned int)((infusion_data.Pressure_AD120 - infusion_data.Pressure_AD0) \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value120  \
												/ (press_Data.Pressure_newAD120 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);	
				break;
			default:
				press_Data.Pressure_newAD70 = (unsigned int)((infusion_data.Pressure_AD70 - infusion_data.Pressure_AD0)  \
												/ press_Data.k + press_Data.Pressure_newAD0);
				press_Data.Pressure_valuenow = infusion_data.Pressure_value70 \
												/ (press_Data.Pressure_newAD70 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);	
				break;
		}
		if((press_Data.Pressure_valuenow <= 0.0) || (press_Data.Pressure_valuenow >= 5000.0))
		{
			press_Data.Pressure_valuenow = 0.0;
		}
	}
	else if(sensorpack.RightKnobStatus == 0)
	{
		press_Data.Pressure_valuenow = 0.0;
	}
	else
	{
		press_Data.Pressure_valuenow = 0.0;
	}

	//快进模式时
	if((blocklevel !=3)&&(gt_disp_get_scr()== SeqBolusRun))
	{
		press_Data.Pressure_newAD120 = (unsigned int)((infusion_data.Pressure_AD120 - infusion_data.Pressure_AD0) \
										/ press_Data.k + press_Data.Pressure_newAD0);
		press_Data.Pressure_valuenow = infusion_data.Pressure_value120  \
										/ (press_Data.Pressure_newAD120 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);		   		
	}
	else if((blocklevel !=3)&&(gt_disp_get_scr()== GeneralBolusRun))
	{
		press_Data.Pressure_newAD120 = (unsigned int)((infusion_data.Pressure_AD120 - infusion_data.Pressure_AD0) \
										/ press_Data.k + press_Data.Pressure_newAD0);
		press_Data.Pressure_valuenow = infusion_data.Pressure_value120  \
										/ (press_Data.Pressure_newAD120 - press_Data.Pressure_newAD0)*(sensorpack.DownPressure - press_Data.Pressure_newAD0);		   		
	}


  	//printf("press_Data.Pressure_valuenow0=%.f",press_Data.Pressure_valuenow);

}






void SoundManage(_Bool SoundOnAndOffFlag,unsigned int glevel) //当前报警级别  高、中、低、提示
{
	//static int Runtime=0;
	static int GlevelOld=0; //上次响应的报警信息(若有高级报警则不响应低级报警)
	int addr;
	static int lastsound=T_ALARM;//记录上次响的报警内容
	

	if(SoundOnAndOffFlag) //如果静音就退出
	{ 
		return; 
	}
	if(SystemSetting.langue == Chinese2 || SystemSetting.langue == Chinese)
	{
		addr = 10;
	}
	else if(SystemSetting.langue == English)
	{
		addr = 30;
	}
	else if(SystemSetting.langue == Spanish)
	{
		addr = 50;
	}
	else if(SystemSetting.langue == Portuguese)
	{
		addr = 70;
	}
	
	if(glevel!=0) //如果报警存在，设置报警响应时间
	{	
	
		if(alarm_data.Runtime == 0) //如果首次响应立马报警
		{
			alarm_data.Runtime = 0;
		}
		else
		{
			alarm_data.Runtime --; 
		}

		if(GetAlarmLevel(glevel) < GetAlarmLevel(GlevelOld) &&  glevel != ALARM_MAX)  //如果有更高等级的报警
		{
			alarm_data.Runtime = 0;   
		}
	}
	
	if(alarm_data.Runtime > 0)  //结束该函数
	{ 
	
		return;
	} 

	switch(glevel)
	{
	case 0: 
		alarm_data.Runtime = 1;
		break;
	case 1:  //高级报警
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 8:
	case 9:
	case 10:
		alarm_data.Runtime = 10;

		if(glevel == lastsound)
		{
			GetNowAlarmMessage(&InfusionNow.alarmmsg); //再另外取一次内容		
			while(InfusionNow.alarmmsg==ALARM_MAX || InfusionNow.alarmmsg > ALARM_HIGH)//如果后面的数组没有报警信息 或者 取出来的报警信息为非高级报警
			{
				GetNowAlarmMessage(&InfusionNow.alarmmsg);  //则再取
			}
			glevel=InfusionNow.alarmmsg;
		}
		lastsound=glevel;

		if(SystemMaintain.Alarm == TRUE)
		{
			WT588F_Send_Data(0xF3); //连码
			delay_ms(2);
			WT588F_Send_Data(0x01);
			delay_ms(5);
			WT588F_Send_Data(0xF3); //连码
			delay_ms(2);
			WT588F_Send_Data(addr+glevel);
			delay_ms(5);
		}
		else
		{
			WT588F_Send_Data(0x01);
		}
		break;
	case 12: //中级报警
		if(H_ALARM == GetNowAlarmLeve12()) //如果有高级报警存在
			break;
			
		alarm_data.Runtime = 15;
		if (glevel == lastsound)
		{
			GetNowAlarmMessage(&InfusionNow.alarmmsg); //再另外取一次内容
			while(InfusionNow.alarmmsg==ALARM_MAX || InfusionNow.alarmmsg > ALARM_MID)//如果后面的数组没有报警信息 或者 取出来的报警信息为非高级报警
			{
				GetNowAlarmMessage(&InfusionNow.alarmmsg);  //则再取
			}
			glevel=InfusionNow.alarmmsg;
			
		}
		lastsound=glevel;

		if(SystemMaintain.Alarm == TRUE)
		{
			WT588F_Send_Data(0xF3);
			delay_ms(2);
			WT588F_Send_Data(0x02);
			delay_ms(5);
			WT588F_Send_Data(0xF3);
			delay_ms(2);
			WT588F_Send_Data(addr+glevel);
			delay_ms(5);
		}
		else
		{
			WT588F_Send_Data(0x02);
		}	
		break;
		
	case 14:  //低级报警
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		if(H_ALARM == GetNowAlarmLeve12()) //如果有高级报警存在
			break;

		alarm_data.Runtime = 20;
		if(glevel==lastsound) //如果这次和上次响的一样 并且有高级报警存在，则不响应低级报警
		{
			GetNowAlarmMessage(&InfusionNow.alarmmsg); //再另外取一次内容
			while(InfusionNow.alarmmsg==ALARM_MAX || InfusionNow.alarmmsg > ALARM_LOW)//如果后面的数组没有报警信息 或者 取出来的报警信息为非高级报警
			{
				GetNowAlarmMessage(&InfusionNow.alarmmsg);  //则再取
			}
			glevel=InfusionNow.alarmmsg;
		
		}
		lastsound=glevel;

		if(SystemMaintain.Alarm == TRUE)
		{
			WT588F_Send_Data(0xF3);
			delay_ms(2);
			WT588F_Send_Data(0x03);
			delay_ms(5);
			WT588F_Send_Data(0xF3);
			delay_ms(2);
			WT588F_Send_Data(addr+glevel);
			delay_ms(5);
		}
		else
		{
			WT588F_Send_Data(0x03);
		}
		break;
		
	default:
		
		break;
	}
	
	

	GlevelOld=InfusionNow.glevel;
	
	return ;
}




int GetNowAlarmLeve12()
{
	int i=1;
	int MAX=ALARM_MAX;
	for(i=1;i<ALARM_MAX;i++)
	{
		if(NowAlarmMessage[i]!=0)
		{
			if(MAX>NowAlarmMessage[i])
			{
				MAX=NowAlarmMessage[i];     //取非0的最小值就是最高级报警
			}
		}
	}
	
	return GetAlarmLevel(MAX);
}


/*
***************************************************************************
* Function: // CalSpeed
* Description: //将速度ml/h换算成r/h
* @param[in]   speed 输液流速
* @return	  流速对应的电机转速
* Others:    CYLINDER_ML是每毫升液量对应的电机圈数，校准值为100r所的的液量，默认为7.485

******800ml/h~1200ml/h每圈液量为CYLINDER_ML*1.15 ***********************
******500ml/h~800ml/h 每圈液量为CYLINDER_ML*1.05***********************
******150ml/h~500ml/h 每圈液量为CYLINDER_ML*1.0***********************
******50ml/h~150ml/h  每圈液量为CYLINDER_ML*1  .0 ***********************
******25ml/h~50ml/h   每圈液量为CYLINDER_ML*0.95***********************
******5ml/h~25ml/h    每圈液量为CYLINDER_ML*1.2 ***********************
******0.1ml/h~5ml/h   每圈液量为CYLINDER_ML*1.25***********************

***************************************************************************
*/
double CalSpeed(double speed)
{
	double SPeed=0;

	if(speed>=1300.0)  //(800ml/h~1200ml/h) 
	{
	
		SPeed=(CYLINDER_MAXHIGH_ML)*speed*1;
		//printf("800\n");
	}
	else if(speed>=800.0)  //(800ml/h~1200ml/h)
	{
		SPeed=(CYLINDER_HIGH_ML)*speed*1;
		//printf("800\n");
	}
	else if(speed>=700.0) //(500ml/h~800ml/h)
	{
	
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("500\n");
	}
	else if(speed>=600.0) //(500ml/h~800ml/h)
	{
	
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("500\n");
	}
	else if(speed>=500.0) //(500ml/h~800ml/h)
	{
	
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("500\n");
	}
	else if(speed>=400.0) //(500ml/h~800ml/h)
	{
	
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("500\n");
	}
	else if(speed>=300.0) //(500ml/h~800ml/h)
	{
	
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("500\n");
	}
	else if(speed>=200.0) //(150ml/h~500ml/h)
	{
		SPeed=(CYLINDER_HIGH_ML)*speed *1;
		//printf("200\n");
	}
	else if(speed>=50.0) //(50ml/h~150ml/h)
	{
		SPeed=(CYLINDER_ML)*speed *1;
		//printf("50\n");
	}
	else if(speed>=25.0) //(25ml/h~50ml/h)
	{
		SPeed=(CYLINDER_ML)*speed *1;
		//printf("25\n");
	}
	else if(speed>=5.0) //(5ml/h~25ml/h)
	{
		SPeed=(CYLINDER_ML)*speed *1;
		//printf("5\n");
	}
	else if(speed>=0.1) //(0.1ml/h~5ml/h)
	{
		SPeed=(CYLINDER_ML)*speed *1;
		//printf("0.1\n");
		//printf("SPeed=%d\n",SPeed);
	}
	else //防呆
	{
		SPeed=(CYLINDER_ML)*speed *1;
		//printf("else\n");
	}

	return SPeed;

} 



char* GetMedicineUintString(MedicineUint MUint)
{
	if(MUint==M_ug)
	{
		return MEDICINEUNIT00;
	}
	else if(MUint==M_mg)
	{
		return MEDICINEUNIT01;
	}
	else if(MUint==M_g)
	{
		return MEDICINEUNIT02;
	}
	else if(MUint==M_ng)
	{
		return MEDICINEUNIT03;
	}
	else
	{
		return NULL;
	}	
}





char* GetDoseUintString(DoseUint DUint)
{
	if(DUint==D_ug_kg_min)
	{
		return DOSESPEEDUNIT00;
	}
	else if(DUint==D_ug_kg_h)
	{
		return DOSESPEEDUNIT01;
	}
	else if(DUint==D_ng_kg_min)
	{
		return DOSESPEEDUNIT02;
	}
	else if(DUint==D_ng_kg_h)
	{
		return DOSESPEEDUNIT03;
	}
	else if(DUint==D_mg_kg_min)
	{
		return DOSESPEEDUNIT04;
	}
	else if(DUint==D_mg_kg_h)
	{
		return DOSESPEEDUNIT05;
	}
	else if(DUint==D_g_kg_min)
	{
		return DOSESPEEDUNIT06;
	}
	else if(DUint==D_g_kg_h)
	{
		return DOSESPEEDUNIT07;
	}
	else
	{
		return NULL;
	}	
}


void UpdateSpeedModeTheDisplay(int id,double* FlowRate ,double* Quantity, TIME* Time)
{
    double timeV_H=0.0;
    int miao=0;
    if(id==CHANGE_Speed)
    {
        //timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
        if(*FlowRate <= 0.0)
        {
        	*FlowRate = 0.0;
            Time->hour= 0;
            Time->min =0;
            Time->sec= 0;
            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);
        }
        else
        {
        	if(*FlowRate >= SystemMaintain.MaxSpeed)
        	{
        		*FlowRate = SystemMaintain.MaxSpeed;
        	}
        	if(*Quantity <= 0.0)
        	{
				*Quantity = 0.0;
				Time->hour= 0;
	            Time->min =0;
	            Time->sec= 0;
	           // SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);        		
        	}
			else
			{
                timeV_H = ((*Quantity)/(*FlowRate))*3600;    
                if(timeV_H<=1&&timeV_H!=0)
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
                }
				// SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);				
			}
        }
    }
    else if(id==CHANGE_QUAN)
    {

		if(*Quantity <= 0.0)
        {
        	*Quantity = 0.0;
            Time->hour= 0;
            Time->min =0;
            Time->sec= 0;
            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);
        }
		else
		{
        	if(*FlowRate <= 0.0)
        	{
				*FlowRate = 0.0;
				Time->hour= 0;
	            Time->min =0;
	            Time->sec= 0;
	            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);        		
        	}	
			else
			{
                timeV_H = ((*Quantity)/(*FlowRate))*3600;    //预置量可能为0
                if(timeV_H<=1&&timeV_H!=0)
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
                }
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);				
			}
		}
    }
}


void UpdateTimeModeTheDisplay(int id,double* FlowRate ,double* Quantity, TIME* Time) //nick 20191021
{
    double timeV_H;
    int miao=0;
    if(id==CHANGE_TIME)
    {
        timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
        if(timeV_H <= 0.0)//分母不能为0
        {
            *FlowRate=0.0;
        }
        else
        {
            if((*Quantity == 0.0)&&(*FlowRate != 0.0)) //求预置量
            {
                 
                if((* FlowRate)*timeV_H>=9999.99)
                {
                    *Quantity=9999.99;
                    timeV_H=(*Quantity)/(* FlowRate)*3600;
                    if(timeV_H<=1&&timeV_H!=0)
                    {
                        Time->hour = 0;
                        Time->min = 0;
                        Time->sec = 1;
                    }
                    else
                    {
                        miao = (int)(timeV_H+0.5);
                        Time->hour = miao/3600;
                        Time->min = (miao/60)%60;
                        Time->sec = miao%60;
                    }
                    //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle152);
                }
                else if((* FlowRate)*timeV_H<=0.1)
                {
                    *Quantity=0.1;
                    timeV_H=(*Quantity)/(* FlowRate)*3600;
                    if(timeV_H<=1&&timeV_H!=0)
                    {
                        Time->hour = 0;
                        Time->min = 0;
                        Time->sec = 1;
                    }
                    else
                    {
                        miao = (int)(timeV_H+0.5);
                        Time->hour = miao/3600;
                        Time->min = (miao/60)%60;
                        Time->sec = miao%60;    
                    }
                    //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle152);
                }
                else
                {
                    *Quantity=(* FlowRate)*timeV_H;
                }
            }
            else //求速度 预置量、流速都为0 流速为0预置量不为0 预置量、流速都不为0
            {
                 if((*Quantity)/timeV_H>=SystemMaintain.MaxSpeed)
                 {
                     timeV_H=(*Quantity)*3600/SystemMaintain.MaxSpeed;
                    if(timeV_H<=1&&timeV_H!=0)
                    {
                        Time->hour = 0;
                        Time->min = 0;
                        Time->sec = 1;
                    }
                    else
                    {
                        miao = (int)(timeV_H+0.5);
                        Time->hour = miao/3600;
                        Time->min = (miao/60)%60;
                        Time->sec = miao%60;
                    }
                    * FlowRate=SystemMaintain.MaxSpeed;
                  //  SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
                 }
                else if(((*Quantity)/timeV_H<=0.1)&&((*Quantity)/timeV_H!=0))
                {
                     timeV_H=(*Quantity)*3600/(0.1);
                    if(timeV_H<=1&&timeV_H!=0)
                    {
                        Time->hour = 0;
                        Time->min = 0;
                        Time->sec = 1;
                    }
                    else
                    {
                        miao = (int)(timeV_H+0.5);
                        Time->hour = miao/3600;
                        Time->min = (miao/60)%60;
                        Time->sec = miao%60;
                    }
                    * FlowRate=0.1;            
                    //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle01);
                }
                else
                {
                    (* FlowRate)=(*Quantity)/timeV_H;
                }
            }
         }
    }
    else if(id==CHANGE_QUAN)
    {
        timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
        if((timeV_H <= 0.0) && (*FlowRate <= 0.0))//分母不能为0
        {
           *FlowRate=0.0;
           Time->hour= 0;
           Time->min =0;
           Time->sec= 0;    
        }
        else
        {
           if((timeV_H <= 0.0) && (*FlowRate > 0.0))//求时间
           {
                timeV_H = ((*Quantity)/(*FlowRate))*3600;    
                if(timeV_H<=1&&timeV_H!=0)
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;
					#if 0
					timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
					*Quantity=(*FlowRate)*timeV_H;
					SetWindowCaption(mhWnd,MENUNAME39);
					#endif
					
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
					//SetWindowCaption(mhWnd,MENUNAME02);
                } 
            }
            else //求速度
            {
                if((*Quantity)/timeV_H>=SystemMaintain.MaxSpeed)
                {
                	(*Quantity)=timeV_H*SystemMaintain.MaxSpeed;
                   * FlowRate=SystemMaintain.MaxSpeed;
				   //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
                }
                else if(((*Quantity)/timeV_H<=0.1)&&((*Quantity)/timeV_H!=0))
                {
                   (*Quantity)=timeV_H*(0.1);
                   * FlowRate=0.1;     
			 	  // SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
                }
                else
                {
                   (* FlowRate)=(*Quantity)/timeV_H;
                }
            }
        }
    }
    else if(id==CHANGE_Speed)
    {
        timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
        if(*FlowRate <= 0.0)//分母不能为0
        {
           Time->hour= 0;
           Time->min =0;
           Time->sec= 0;
        }
        else
        {
        	if(* FlowRate >= SystemMaintain.MaxSpeed)
        	{
        		* FlowRate=SystemMaintain.MaxSpeed;
        	}
            if((*Quantity)==0 && timeV_H!=0) //求预置量
            {
                if((* FlowRate)*timeV_H>=9999.99)
                {
                    *Quantity=9999.99;
                    * FlowRate=(*Quantity)/(timeV_H);
					//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle152);
                
                }
                else if((* FlowRate)*timeV_H<=0.1)
                {
                    *Quantity=0.1;
                    * FlowRate=(*Quantity)/(timeV_H);       
					//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle152);
                }
                else
                {
                    *Quantity=(* FlowRate)*timeV_H;
                }

            }
            else //求时间
            {
                timeV_H = ((*Quantity)/(*FlowRate))*3600;
                if(timeV_H<=1 && timeV_H!=0) //情况2：当所求时间小于1秒时，时间设置为1秒，其他不变
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;  
					#if 0
					timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
					 * FlowRate=(*Quantity)/(timeV_H);  
					SetWindowCaption(mhWnd,MENUNAME39); 
					#endif
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
					//SetWindowCaption(mhWnd,MENUNAME02);
                }
            }
        }
    }
}

void UpdateWeightModeTheDisplay(int id)
{
    double mg_data2= 0.0;
    double mg_data1= 0.0;
    int num = 0;
    double Speed_ML_h = 0.0;
    int BODY;
    int nu;  
	Limit nowlimit;
	MedicineUint temp_medicineUnit;
	DoseUint temp_doseUnit;

    //将单位换成标准单位
    BODY = WeightMode.Body;//体重
    mg_data2=MedicineUintComeToConversion(WeightMode.Med_Uint,WeightMode.Medicine,M_mg);//药量
    mg_data1=DOSEUintComeToConversion(WeightMode.DS_Uint,WeightMode.DoseSpeed,D_mg_kg_h); //剂量速度
    if(id==CHANGE_WEIGHT)
    {
        if(mg_data2==0) //分母不能为0
        {
        	WeightMode.Speed=0;
        }
        else
        {
			if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
			{
				BODY=(SystemMaintain.MaxSpeed*mg_data2)/(mg_data1*WeightMode.Liquid);
				#if 1
				if(BODY < 0.1)
				{
					BODY = 0.0;
					WeightMode.Body = 0.0;
					WeightMode.Speed = 0.0;
				}
				else if(BODY > 300.0)
				{
					BODY = 0.0;
					WeightMode.Body = 0.0;
					WeightMode.Speed = 0.0;						
				}
				else
				{
					
					WeightMode.Speed=SystemMaintain.MaxSpeed;
				}
				#else
					WeightMode.Body=BodyUintComeToConversion(W_KG,BODY,ParamSetting.bodyUint);
					WeightMode.Speed=SystemMaintain.MaxSpeed;					
				#endif
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
			{
				BODY=((0.1)*mg_data2)/(mg_data1*WeightMode.Liquid);
				#if 1
				if(BODY < 0.1)
				{
					BODY = 0.0;
					WeightMode.Body = 0.0;
					WeightMode.Speed = 0.0;
				}
				else if(BODY > 300.0)
				{
					BODY = 0.0;
					WeightMode.Body = 0.0;
					WeightMode.Speed = 0.0;						
				}
				else
				{
					
					WeightMode.Speed=0.1;
				}
				#else
					WeightMode.Body=BodyUintComeToConversion(W_KG,BODY,ParamSetting.bodyUint);
					WeightMode.Speed=0.1;					
				#endif
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else
			{
				WeightMode.Speed=((mg_data1*BODY*WeightMode.Liquid)/(mg_data2))*100/100.0;	
			}
         }
    }
	else if(id==CHANGE_Medicine)
	{
		if(mg_data2==0)//分母不能为0
		{
			WeightMode.Speed=0;
		}
		else
		{
			if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
			{
				mg_data2=((BODY*mg_data1*WeightMode.Liquid)/SystemMaintain.MaxSpeed);
				WeightMode.Medicine=MedicineUintComeToConversion(M_mg,mg_data2,WeightMode.Med_Uint);
				if((WeightMode.Medicine>nowlimit.toplimit)||(WeightMode.Medicine<nowlimit.lowerlimit))
				{
					WeightMode.Medicine=0;
					WeightMode.Speed=0;
				}
				else
				{
					//WeightMode.Medicine=MedicineUintComeToConversion(M_mg,mg_data2,WeightMode.Med_Uint);
					WeightMode.Speed=SystemMaintain.MaxSpeed;
				}	
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
			{
				mg_data2=((BODY*mg_data1*WeightMode.Liquid)/(0.1));
				WeightMode.Medicine=MedicineUintComeToConversion(M_mg,mg_data2,WeightMode.Med_Uint);
				if((WeightMode.Medicine>nowlimit.toplimit)||(WeightMode.Medicine<nowlimit.lowerlimit))
				{
					WeightMode.Medicine=0;
					WeightMode.Speed=0;
				}
				else
				{		
					WeightMode.Speed=0.1;
				}
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else
			{
				WeightMode.Speed=(((mg_data1)*(BODY)*(WeightMode.Liquid))/(mg_data2))*100/100.0;	
			}
		}
	}
	else if(id==CHANGE_Liquid)
	{
		if(mg_data2==0)//分母不能为0
		{
			WeightMode.Speed=0;
		}
		else
		{
			if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
			{
				WeightMode.Liquid=(SystemMaintain.MaxSpeed*mg_data2)/(mg_data1*BODY);
				WeightMode.Speed=SystemMaintain.MaxSpeed;
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
				if((WeightMode.Liquid>nowlimit.toplimit)||(WeightMode.Liquid<nowlimit.lowerlimit))
				{
					WeightMode.Liquid=0;
					WeightMode.Speed=0;
				}
				else
				{
					WeightMode.Speed=SystemMaintain.MaxSpeed;
				}
			}
			else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
			{
				WeightMode.Liquid=((0.1)*mg_data2)/(mg_data1*BODY);
				WeightMode.Speed=0.1;
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
				if((WeightMode.Liquid>nowlimit.toplimit)||(WeightMode.Liquid<nowlimit.lowerlimit))
				{
					WeightMode.Liquid=0;
					WeightMode.Speed=0;
				}
				else
				{
					WeightMode.Speed=0.1;
				}
			}
			else
			{
				WeightMode.Speed=(((mg_data1)*(BODY)*(WeightMode.Liquid))/(mg_data2))*100/100.0;	
			}
		}
	}
	else if(id==CHANGE_DOS)
	{
		nowlimit.toplimit= 999.99;
		nowlimit.lowerlimit=0.01; 
	 	nowlimit.FLiimit=FALSE;		
		//GetLimitvalue(&nowlimit,0,Li_DOSE);
		if(mg_data2==0)//分母不能为0
		{
			WeightMode.Speed=0;
		}
		else
		{
			if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
			{
				mg_data1=(SystemMaintain.MaxSpeed*mg_data2)/(WeightMode.Liquid*BODY);
				WeightMode.DS_Uint=DOSEUintComeToConversion(D_mg_kg_h,mg_data1,WeightMode.DS_Uint);
				if((WeightMode.DS_Uint>nowlimit.toplimit)||(WeightMode.DS_Uint<nowlimit.lowerlimit))
				{
					WeightMode.DS_Uint=0;
					WeightMode.Speed=0;
				}
				else
				{		
					WeightMode.Speed=SystemMaintain.MaxSpeed;
				}
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
			{
				mg_data1=(0.1*mg_data2)/(WeightMode.Liquid*BODY);
				//printf("data1=%f",mg_data1);
				WeightMode.DS_Uint=DOSEUintComeToConversion(D_mg_kg_h,mg_data1,WeightMode.DS_Uint);
				if((WeightMode.DS_Uint>nowlimit.toplimit)||(WeightMode.DS_Uint<nowlimit.lowerlimit))
				{
					WeightMode.DS_Uint=0;
					WeightMode.Speed=0;
				}
				else
				{			
					WeightMode.Speed=0.1;
				}
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
			}
			else
			{
				WeightMode.Speed=(((mg_data1)*(BODY)*(WeightMode.Liquid))/(mg_data2))*100/100.0;	
			}
		}			
	}
	else if(id==CHANGE_MedicineUNIT)
	{
		if((mg_data2==0)||(mg_data1*BODY*WeightMode.Liquid/mg_data2==0))
		{
			return ;
		}
		if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
		{
			WeightMode.Med_Uint=temp_medicineUnit;
		}
		else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
		{
			WeightMode.Med_Uint=temp_medicineUnit;
		}
		else
		{
			WeightMode.Speed=mg_data1*BODY*WeightMode.Liquid/mg_data2;
			//if(WeightMode.Speed)
		}
	}
	else if(id==CHANGE_DOSUNIT)
	{
		if((mg_data2==0)||(mg_data1*BODY*WeightMode.Liquid/mg_data2==0))
		{
			return ;
		}
		if((mg_data1*BODY*WeightMode.Liquid/mg_data2)>=(SystemMaintain.MaxSpeed))
		{
			WeightMode.DS_Uint=temp_doseUnit;
			//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
		}
		else if(((mg_data1*BODY*WeightMode.Liquid/mg_data2)<=0.1)&&((mg_data1*BODY*WeightMode.Liquid/mg_data2)!=0))
		{
			WeightMode.DS_Uint=temp_doseUnit;
			//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle154);
		}	
		else
		{
			WeightMode.Speed=mg_data1*BODY*WeightMode.Liquid/mg_data2;
			//if(WeightMode.Speed)
		}
	}
}


double MedicineUintComeToConversion(MedicineUint SourceUint,double SourceData,MedicineUint ToUint)
{
	double DATA1=0.0;
	double DATA2=0.0;
	switch(SourceUint){
		case M_ug:	
			DATA1 =	SourceData/1000.0 ;	//ug ->mg
			break;
		case M_mg:
			DATA1 =	SourceData;	        //mg
			break;	
		case M_ng:
			DATA1 =	SourceData/1000000.0;  // ng ->ug->mg
			break;		
 		case M_g:
			DATA1 =	SourceData*1000.0;    // g->mg
			break;
		default:
			break;	
	}
	switch(ToUint){
		case M_ug:
			DATA2 = DATA1*1000.0;
			break;
		case M_mg:
			DATA2 = DATA1;
			break;	
		case M_ng:
			DATA2 = DATA1*1000000.0;
			break;
		case M_g:
			DATA2 =	DATA1/1000.0; 
			break;
		default:
			break;	
	}
	return DATA2;

}

double DOSEUintComeToConversion(DoseUint SourceUint,double SourceData,DoseUint ToUint)
{
	double DATA1=0.0;
	double DATA2=0.0;
	switch(SourceUint){
		case D_ug_kg_min:	
			DATA1 =	(SourceData/1000)*60;  
			break;
		case D_ug_kg_h:
			DATA1 =	(SourceData/1000);
			break;	
		case D_ng_kg_min:
			DATA1 =	(SourceData/1000000.0)*60;
			break;	
		case D_ng_kg_h:
			DATA1 =	(SourceData/1000000.0);;
			break;	
		case D_mg_kg_min:
			DATA1 =	(SourceData)*60;
			break;
		case D_mg_kg_h:			
			DATA1 = SourceData;   //10*70*50/20
			break;		
		default:
			break;	
	}
	switch(ToUint){
		case D_ug_kg_min:
			DATA2 = DATA1*1000/60;
			break;
		case D_ug_kg_h:
			DATA2 = DATA1*1000;
			break;	
		case D_ng_kg_min:
			DATA2 = DATA1*1000000.0/60;
			break;
		case D_ng_kg_h:
			DATA2 = DATA1*1000000.0;
			break;	
		case D_mg_kg_min:
			DATA2 =	DATA1/60; 
			break;
		case D_mg_kg_h:			
			DATA2 = DATA1;
		default:
			break;	
	}
	return DATA2;
}

#if 0
void GetLimitvalue(Limit *limit,int num,ELim eLim) 
{
	switch(eLim)
	{
 	case Li_SYS:	
		limit->toplimit= SystemMaintain.MaxSpeed;
		limit->lowerlimit=0.1;
		limit->FLiimit=FALSE;
	 	break;
	 case Li_QUANTI:
		limit->toplimit=9999.99;
		limit->lowerlimit=0.1; 
	 	limit->FLiimit=TRUE;
	 	break;
	 case Li_BODY:
		limit->toplimit= 300.0;
		limit->lowerlimit=0.1; 
	 	limit->FLiimit=TRUE;	
	 	break;	
	 case Li_MEDICINE:
	 	limit->toplimit= 999.9;
		limit->lowerlimit=0.1;  
	 	limit->FLiimit=TRUE;	
	 	break;	
	 case Li_LIQUID:
	 	limit->toplimit= 9999.99;
		limit->lowerlimit=0.1;
	 	limit->FLiimit=TRUE;	
	 	break;	
	 case Li_DOSE:
	 	limit->toplimit= 999.99;
		limit->lowerlimit=0.01; 
	 	limit->FLiimit=FALSE;	
	 	break;			
	 case Li_KVO:
		limit->toplimit= 5.0;
		limit->lowerlimit=0.1; 
	 	limit->FLiimit=FALSE;
	 	break;	
	 case Li_ACCUMBUBBLE:
		limit->toplimit= 4.0;
		limit->lowerlimit=0.1;
	 	limit->FLiimit=FALSE;
	 	break;				
	 case Li_AOTULOCK:
		limit->toplimit= 5;
		limit->lowerlimit=1; 
	 	limit->FLiimit=FALSE;
		break;
	 case Li_NO:
		limit->toplimit= 5;
		limit->lowerlimit=1;  
	 	limit->FLiimit=FALSE;
		break;
	 case Li_NEAR:
		limit->toplimit= 30;
		limit->lowerlimit=1; 
		limit->FLiimit=FALSE;
		break;
	 case Li_SOUND:
		limit->toplimit= 8;   
		limit->lowerlimit=1; 
	 	limit->FLiimit=FALSE;
		break;
	 case Li_BLOCKLEVE:
		limit->toplimit= 3;   
		limit->lowerlimit=1;
	 	limit->FLiimit=FALSE;
		break;			
	case Li_LIGHT:
		limit->toplimit= 8;
		limit->lowerlimit=1; 
		limit->FLiimit=FALSE;
		break;
	 case Li_DIRECTLY:
		limit->toplimit= 100;
		limit->lowerlimit=1;
	 	limit->FLiimit=FALSE;

		break;
	 case Li_LENGTH:
		limit->toplimit= 100;
		limit->lowerlimit=1;
	 	limit->FLiimit=FALSE;

		break;
	 case Li_CONTRAST:
		limit->toplimit= 200;
		limit->lowerlimit=1;	
	 	limit->FLiimit=FALSE;

		break;
	 case Li_ROTATESPEED:
		limit->toplimit= 2000.0;
		limit->lowerlimit=1.0;	
	 	limit->FLiimit=FALSE;

		break;			
	 case Li_PRESSURE:
		limit->toplimit= 999.0;
		limit->lowerlimit=1.0;	
	  	limit->FLiimit=TRUE;
		break;					
	 case Li_LIQUID_1:
		limit->toplimit= 11.0;     //48
		limit->lowerlimit=3.0;	  //26	
		limit->FLiimit=FALSE;
		break;
	 case Li_LIQUID_2:
		limit->toplimit= 11.0;    //63
		limit->lowerlimit=3.0;	 //32  	
		limit->FLiimit=FALSE;
		break;
	 case Li_COEFFCIENTK:
		limit->toplimit= 20;
		limit->lowerlimit=0.0;	 
	 	limit->FLiimit=FALSE;
		break;	
	 case Li_COEFFICIENTB:
		limit->toplimit= 20;
		limit->lowerlimit=0.0;	  		 	 
		break;	
	 case Li_SERIALNUMBER:
		limit->toplimit= 99999999;
		limit->lowerlimit=0;
	   	limit->FLiimit=TRUE;
		break;
	 case Li_TIME:
		limit->toplimit= 99;
		limit->lowerlimit=0; 
	   	limit->FLiimit=TRUE;
		break;
	 case Li_TIMEDATA:
		limit->toplimit= 23;
		limit->lowerlimit=0; 
	   	limit->FLiimit=TRUE;
		break;	
	 case Li_MAXSPEED:            
		limit->toplimit= 2000.0;
		limit->lowerlimit=0.1;  
	   	limit->FLiimit=FALSE;
		break;	
	 case Li_BEDNUM:            
		limit->toplimit= 999;
		limit->lowerlimit=1;  
	   	limit->FLiimit=FALSE;
		break;					
	 case Li_ELSE:            
		limit->toplimit= 1500;
		limit->lowerlimit=0.1; 
	   	limit->FLiimit=TRUE;
		break;
	case Li_TESTMODE:
		limit->toplimit= 20000;
		limit->lowerlimit=0.1;
		limit->FLiimit=TRUE;
		break;
	 default:
		break;
	 }
}
#endif

void UpdateDripModeTheDisplay(int id,int* Drip ,double* Quantity, TIME* Time)
{
    double timeV_H=0.0;
    int miao=0;
	int* FlowRate;
	* FlowRate=DripMode.drip*DripMode.drips;
    if(id==CHANGE_DRIP)
    {
        //timeV_H = Time->hour + (Time->min/60.0) + (Time->sec/3600.0);
        if(*FlowRate <= 0.0)
        {
        	*FlowRate = 0.0;
            Time->hour= 0;
            Time->min =0;
            Time->sec= 0;
            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);
        }
        else
        {
        	if(*FlowRate >= SystemMaintain.MaxSpeed)
        	{
        		*FlowRate = SystemMaintain.MaxSpeed;
        	}
        	if(*Quantity <= 0.0)
        	{
				*Quantity = 0.0;
				Time->hour= 0;
	            Time->min =0;
	            Time->sec= 0;
	           // SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);        		
        	}
			else
			{
                timeV_H = ((*Quantity)/(*FlowRate))*3600;    
                if(timeV_H<=1&&timeV_H!=0)
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
                }
				// SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);				
			}
        }
    }
    else if(id==CHANGE_QUAN)
    {

		if(*Quantity <= 0.0)
        {
        	*Quantity = 0.0;
            Time->hour= 0;
            Time->min =0;
            Time->sec= 0;
            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);
        }
		else
		{
        	if(*FlowRate <= 0.0)
        	{
				*FlowRate = 0.0;
				Time->hour= 0;
	            Time->min =0;
	            Time->sec= 0;
	            //SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);        		
        	}	
			else
			{
                timeV_H = ((*Quantity)/(*FlowRate))*3600;    //预置量可能为0
                if(timeV_H<=1&&timeV_H!=0)
                {
                    Time->hour = 0;
                    Time->min = 0;
                    Time->sec = 1;
                }
                else
                {
                    miao = (int)(timeV_H+0.5);
                    Time->hour = miao/3600;
                    Time->min = (miao/60)%60;
                    Time->sec = miao%60;
                }
				//SetWindowCaption(mhWnd,languagedatatype.titlename.menutitle00);				
			}
		}
    }
}


float GetNowcumulant(void)
{
	return cumulantMode.Nowcumulant;
}
void SetNowcumulant(double nowanglenumber)
{
	cumulantMode.Nowcumulant=cumulantMode.Nowcumulant+nowanglenumber;
	if(cumulantMode.Nowcumulant >= 9999.99)
	{
		cumulantMode.Nowcumulant = 0.0;
	}
}

void ClearNowcumulant(void)
{
	cumulantMode.Nowcumulant = 0.0; 
}


/*计算剩余时间*/
TIME CalSurplusTime(double PresetValue,double Speed) 
{
	TIME time_T;
	double time_F;
	int Time_I;
	time_F=PresetValue/Speed;
	#if 0
	Time_I = time_F *3600;
	time_T.hour = Time_I / 3600;
	time_T.min = (Time_I / 60) % 60;
	time_T.sec = Time_I % 60;
	#else
	time_T.hour=time_F;     Time_I=time_F*60;
	time_T.min= Time_I%60;  Time_I=time_F*3600;
	time_T.sec= Time_I%60;
	if(time_T.hour <= 0)
	{
		time_T.hour = 0;
	}
	if(time_T.min <= 0)
	{
		time_T.min = 0;
	}
	if(time_T.sec <= 0)
	{
		time_T.sec = 0;
	}
	#endif

	return time_T;
}

/*计算剩余时间*/
TIME DripCalSurplusTime(double PresetValue,int Drip) 
{
	TIME time_T;
	double time_F;
	int Time_I;
	double Speed;
	Speed = (double)(DripMode.drip*DripMode.drips);
	time_F=PresetValue/Speed;
	#if 0
	Time_I = time_F *3600;
	time_T.hour = Time_I / 3600;
	time_T.min = (Time_I / 60) % 60;
	time_T.sec = Time_I % 60;
	#else
	time_T.hour=time_F;     Time_I=time_F*60;
	time_T.min= Time_I%60;  Time_I=time_F*3600;
	time_T.sec= Time_I%60;
	if(time_T.hour <= 0)
	{
		time_T.hour = 0;
	}
	if(time_T.min <= 0)
	{
		time_T.min = 0;
	}
	if(time_T.sec <= 0)
	{
		time_T.sec = 0;
	}
	#endif

	return time_T;
}


/*输液器接近完成时间*/
_Bool JudgedinfusionNeaeTimeAlarm(TIME* ResidueTime)
{
   int Time_S,NerTime_S;
   if(ParamSetting.NearDoneState){
	   Time_S=(ResidueTime->hour*3600)+(ResidueTime->min*60)+(ResidueTime->sec);
	   NerTime_S=ParamSetting.NearDoneTime*60;

	   if(Time_S<NerTime_S)
	   {
	  	  return TRUE;
	   }
   }
   return FALSE;
}


/*
***************************************************************************
* Function: // JudgedInfusionTubeFallOff_P
* Description: //根据下压力判断输液管是否脱落
* @param[in]   NowPrVal 下压力AD值
* @return	 下压力脱落标志
* Others: 
***************************************************************************
*/
_Bool JudgedInfusionTubeFallOff_P(  unsigned int NowPrVal)
{
	static unsigned int overun_num;
	static _Bool timecount_flag = FALSE;

	

	if(JudgedYesNoAlarm(ALARM_INFUSION_OFF))
	{
		overun_num = 0;
		timecount_flag = TubeFallTimeCountDown(FALSE);
		
	}
	else
	{
		timecount_flag = TubeFallTimeCountDown(TRUE);
		if((NowPrVal <= (SystemMaintain.AD0_Notube + 30) ) && (NowPrVal >= (SystemMaintain.AD0_Notube -50)))
		{	
			overun_num++;
		}
	}
	if(timecount_flag == TRUE)
	{
		if(overun_num >= 6)
		{
			overun_num = 0;
			timecount_flag = TubeFallTimeCountDown(FALSE);
			return TRUE;
		}
		else
		{
			overun_num = 0;
			timecount_flag = TubeFallTimeCountDown(FALSE);
			return FALSE;			
		}
	}
	else
	{
		
		 return FALSE;
	}

}



/*
***************************************************************************
* Function: // TubeFallTimeCountDown
* Description: //输液管脱落检测时间倒计时
* @param[in]   StartFlag 倒计时开始标志
* @return	  返回倒计时结束标志
* Others: 
***************************************************************************
*/
_Bool TubeFallTimeCountDown(_Bool StartFlag)
{
	static unsigned int tubefalltime = 8; //3s

	if(StartFlag == TRUE)
	{
		if(tubefalltime > 0)
		{
			tubefalltime--;
			if(tubefalltime <= 0)
			{
				tubefalltime = 0;
				return TRUE;
			}
		}
	}
	else if(StartFlag == FALSE)
	{
		tubefalltime = 8;
	}
	return FALSE;
}



//根据电机实际运行的总角度计算实际运行量
double CalCumulant(double NowAngleNumber,double speed) 
{
	double Cumulant=0.0;

	if(speed>=800.0)  //(800ml/h~1200ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("800\n");
	}
	else if(speed>=700.0) //(700ml/h~800ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("500\n");
	}
	else if(speed>=600.0) //(600ml/h~700ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("500\n");
	}
	else if(speed>=500.0) //(500ml/h~600ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("500\n");
	}
	else if(speed>=400.0) //(400ml/h~500ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("500\n");
	}
	else if(speed>=300.0) //(300ml/h~400ml/h)
	{
	
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("500\n");
	}
	else if(speed>=200.0) //(200ml/h~300ml/h)
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_HIGH_ML*1);
		//printf("200\n");
	}
	else if(speed>=50.0) //(50ml/h~200ml/h)
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_ML*1);
		//printf("50\n");
	}
	else if(speed>=25.0) //(25ml/h~50ml/h)
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_ML*1);
		//printf("25\n");
	}
	else if(speed>=5.0) //(5ml/h~25ml/h)
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_ML*1);
		//printf("5\n");
	}
	else if(speed>=0.1) //(0.1ml/h~5ml/h)
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_ML*1);
		//printf("0.1\n");
		//printf("SPeed=%d\n",SPeed);
	}
	else //防呆
	{
		Cumulant=(NowAngleNumber/360.0)/(CYLINDER_ML*1);
		//printf("else\n");
	}

	
	return Cumulant;
}


_Bool JudgeINjection(unsigned int Photo,double UTimeMS)
{   
	static int Utime100msNum=0;

	if(Photo)
	{
		Utime100msNum++;
	}
	else
	{
		Utime100msNum=0;
	}
	if(Utime100msNum>=UTimeMS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


_Bool CalAccumulativeBubble(unsigned int Photo,double AcBubTimeNumMs)
{
	//static int UtimeMsNum=0;
	int Flag=0;
	
	//if(Photo & TUBE_MOVE)
	if(Photo)
	{
		/*有气泡*/
		//UtimeMsNum +=100;  Flag=1;
		//UtimeMsNum++;
		airbubble_Data.airbubble_num++;
		Flag=1;
	}
	if((airbubble_Data.airbubble_num>=AcBubTimeNumMs)&&(Flag))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

_Bool JudgedDownBlockRelease_AD(int blocklevel,unsigned int  NowPrVal)
{  
	//blocklevel = getParamsettingBlockLevel();
	if(blocklevel == 1)
	{
		if((NowPrVal) < press_Data.Pressure_newAD40)
		{ 

			return TRUE;
		}
	}
	else if(blocklevel == 2)
	{
		if((NowPrVal) < press_Data.Pressure_newAD70)
		{  
			//printf("AD525=%d,nowAD=%d \n",press_Data.Pressure_newAD70,NowPrVal);
			return TRUE;
		}
	}
	else if(blocklevel == 3)
	{
		if((NowPrVal) < press_Data.Pressure_newAD120)
		{  
			return TRUE;
		}
	}
	return FALSE;
}



//判断时候发生下阻塞
_Bool JudgedInfusionDownBlock_AD(  unsigned int NowPrVal)
{
	static unsigned char i_40kpa=0;
	static unsigned char i_70kpa=0;
	static unsigned char i_120kpa=0;
	static _Bool timecount_flag = FALSE;

	int tempdata=ParamSetting.BlockLevel;
	//getParamsettingBlockLevel();
	

	if(JudgedYesNoAlarm(ALARM_UNDERBLOCKING))
	{
		i_40kpa = 0;
		i_70kpa = 0;
		i_120kpa = 0;
		timecount_flag = DownBlockTimeCountDown(FALSE);
	}
	else
	{
		timecount_flag = DownBlockTimeCountDown(TRUE);
		if(tempdata == 1)
		{
			if((NowPrVal)>press_Data.Pressure_newAD40)
			{  
				i_40kpa++;
			}
		}
		else if(tempdata == 2)
		{
			if((NowPrVal)>press_Data.Pressure_newAD70)
			{  
				i_70kpa++;
			}
		}
		else if(tempdata == 3)
		{
			if((NowPrVal)>press_Data.Pressure_newAD120)
			{  
				i_120kpa++;
			}
		}
	}
	if(timecount_flag == TRUE)
	{
		if(tempdata == 1)
		{
			if(i_40kpa >= 3)
			{
				i_40kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return TRUE;
			}
			else
			{
				i_40kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return FALSE;			
			}

		}
		else if(tempdata == 2)
		{
			if(i_70kpa >= 3)
			{
				i_70kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return TRUE;
			}
			else
			{
				i_70kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return FALSE;			
			}

		}
		else if(tempdata == 3)
		{
			if(i_120kpa >= 3)
			{
				i_120kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return TRUE;
			}
			else
			{
				i_120kpa = 0;
				timecount_flag = DownBlockTimeCountDown(FALSE);
				return FALSE;			
			}

		}
	}
	else
	{
		
		 return FALSE;
	}

}


/*
	functionname: returnParamsettingBlockLevel
	describe:     根据当前的压力等级返回1-3的数值
	Param1:		  当前的压力等级
	Param2:
	return: 
	author:		dong
*/
int getParamsettingBlockLevel()
{
	int tempdata=0;
	if( ParamSetting.BlockLevel >=1 && ParamSetting.BlockLevel<6 )
	{
		tempdata = 1;
	}
	else if(ParamSetting.BlockLevel >=6 && ParamSetting.BlockLevel<11)
	{
		tempdata = 2;
	}
	else if(ParamSetting.BlockLevel >=11 && ParamSetting.BlockLevel<15)
	{
		tempdata = 3;
	}
	else
	{
		tempdata = 1;
	}

	return tempdata;
}




_Bool DownBlockTimeCountDown(_Bool StartFlag)
{
	static unsigned int downblocktime = 10; //5s

	if(StartFlag == TRUE)
	{
		if(downblocktime > 0)
		{
			downblocktime--;
			if(downblocktime <= 0)
			{
				downblocktime = 0;
				return TRUE;
			}
		}
	}
	else if(StartFlag == FALSE)
	{
		downblocktime = 10;
	}
	return FALSE;
}


//更新压力传感器AD值
void update_pressure(void)
{
   sensorpack.DownPressure = Read_HX712_A()>>9;  //下压力
   sensorpack.UpPressure = Read_HX712_B()>>9;    //上压力
}


extern _Bool enterkey;

/* 输液器脱落检测 */
void infusion_apparatus_detection(void)
{
 //300ms的定时器
	calpressureADandValue(ParamSetting.BlockLevel);
	//判断输液器
	if(enterkey != true && !judgeIsRunScreen())
	{
		JudgeInstallTube();
	}	
}


//检测电机起始点校准标志
uint8_t detection_motor_start_point_flag = 0;

/* 检测电机起始点处理与压力值更新 */
void detection_motor_start_point_and_update_pressure(void)
{
    static uint32_t ms_count;
	//检测到取下输液夹
	if(detection_motor_start_point_flag == 1)
	{
		 /* 检测电机是否到达起始点 */	
      if(optocoupler_motor_arrive_motor_point == get_optocoupler_signal()&&MotorControl.status==MOTOR_RUN)
	  {
		 /* motor stop */
		 TMC2226_MotorStop();
		
		 detection_motor_start_point_flag = 0; 
		  
	   }else if(MotorControl.status==MOTOR_STOP){	 
		    /* motor run */
		 TMC2226_MotorRun(1,0,2000);	   
	  }	
   }

   //电机处于运行状态时 每一个叶片更新一次压力值
   if(MotorControl.status==MOTOR_RUN)   
   {
	 //检测到首个叶片和其他叶片  
	 if(optocoupler_motor_arrive_motor_point==get_optocoupler_signal()||optocoupler_motor_run==get_optocoupler_signal())
	 {
	   //更新压力值	    
	   update_pressure();
	 }  
   //电机处于停止状态时候0.5s时更新一次压力值 
   }else if(MotorControl.status==MOTOR_STOP||optocoupler_motor_stop==get_optocoupler_signal()){ 
	    ms_count++;
	    if(ms_count>=1000){ /* 0.5ms * 1000  = 0.5s */
	   
	    //更新压力值   
		update_pressure();   
		ms_count = 0;  
	   }
     
   }
}


//输液器安装
void JudgeInstallTube()
{
	int InstallFlag;
	if( (sensorpack.DownPressure >= (SystemMaintain.AD0_Notube+100)) &&sensorpack.RightKnobStatus == 1)		//判断压力变化和旋钮状态
	{
		InstallFlag=1;	/*关*/
	}
	else
	{
		InstallFlag=0;
	}
	/*切换到安装了输液管*/
	if(InstallFlag && (StaringOldPhoto==0))  
	{
		if(press_Data.Knob_Flag == 1)
		{
			press_Data.Knob_Flag = 0;
		}
		if(gt_disp_get_scr() != BrandChoice)
		{
			
			InfusionNow.ReminderFlag = 1;
			airbubble_Data.airbubble_num = 0;
			airbubble_Data.airbubble_time = 0;
			gt_disp_stack_load_scr_anim(GT_SCR_ID_87, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
		}
	}/*切换到未安装了输液管*/
	else if((InstallFlag==0) && StaringOldPhoto) 
	{
		if(gt_disp_get_scr() == BrandChoice && !my_judge_obj_exists(GT_SCR_ID_2))
		{
		  	
	      detection_motor_start_point_flag = 1;
			
		  gt_disp_stack_go_back(1);
		}
	}
	StaringOldPhoto=InstallFlag;
}



uint32_t SetProgressRunSpeed(double speed) 
{
	int SPeed_INT=speed;

	if(SPeed_INT<5){
		return 1100;
	}
	else if(SPeed_INT<10){
		return 1050;
	}
	else if(SPeed_INT<20){
		return 1000;
	}
	else if(SPeed_INT<50){
		return 950;
	}
	else if(SPeed_INT<100){
		return 900;
	}
	else if(SPeed_INT<200){
		return 850;
	}
	else if(SPeed_INT<300){
		return 800;
	}
	else if(SPeed_INT<400){
		return 750;
	}
	else if(SPeed_INT<500){
		return 700;
	}
	else if(SPeed_INT<600){
		return 650;
	}
	else if(SPeed_INT<700){
		return 600;
	}
	else if(SPeed_INT<800){
		return 550;
	}
	else if(SPeed_INT<1000){
		return 400;
	}	
	else if(SPeed_INT<1300){
		return 350;
	}
	else
	{ 
		return 100;
	}
	
}


/*
***************************************************************************
* Function: // BattetyStatusAlarm
* Description: //判断电池状态
* @param[in]   AFlag 电池状态
* @return	  none 
* Others: 
***************************************************************************
*/
void BattetyStatusAlarm(unsigned char AFlag)
{
	
	static uint8_t oldFlag = 0;
	
	if(AFlag!=oldFlag)
	{
		switch(oldFlag)
		{
			case 0:   
				break;
			case 1:  //充满
				break;
			case 2:  //充电
				break;
			case 3:  //电池脱落
				ClearAlarm(ALARM_NO_BATTETY);
				break;
			case 4:  //放电 ==   网电源脱落
				ClearAlarm(ALARM_NET_POWER_OFF);
				break;
			default:
		        break;	
		}					
		switch(AFlag)
		{
			case 0:   
				oldFlag=AFlag;
				break;
			case 1:  //充满
				oldFlag=AFlag;
				break;
			case 2:  //充电
				oldFlag=AFlag;				
				break;
			case 3:  //电池脱落
				AddAlarm(ALARM_NO_BATTETY);
				oldFlag=AFlag;
				break;
			case 4:  //放电 ==   网电源脱落
				AddAlarm(ALARM_NET_POWER_OFF);
				oldFlag=AFlag;
				break;
			default:
		        break;	
		}
	}
}

//电池耗尽报警
void BattetyLowAndDepleteAlarm(unsigned char NowBatt)
{
	static int LowFlag=1;
	if(NowBatt==1)
	{  		
		/*充满*/
		if(!judgeIsRunScreen()) //如果不再运行界面
		{
			if(JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE))
			{
				ClearAlarm(ALARM_BATTERY_DEPLETE);
				SetDEPLETEFlag(FALSE);
			}
		}
		if(JudgedYesNoAlarm(ALARM_BATTERY_LOW))
		{
			ClearAlarm(ALARM_BATTERY_LOW);
		}	
		LowFlag=1;
	}
	else if(NowBatt==2)
	{  	
		if(!judgeIsRunScreen())
		{
			/*充电*/
			if(JudgedYesNoAlarm(ALARM_BATTERY_DEPLETE))
			{
				ClearAlarm(ALARM_BATTERY_DEPLETE);
				SetDEPLETEFlag(FALSE);
			}
		}
		if(JudgedYesNoAlarm(ALARM_BATTERY_LOW))
		{
			ClearAlarm(ALARM_BATTERY_LOW);
		}	
		LowFlag=1;
	}
	else if(NowBatt==4)       /*放电*/
	{  
		if(sensorpack.voltagevalue <= 3)  //电池耗尽
		{
			
			SetDEPLETEFlag(TRUE);
			if(JudgedYesNoAlarm(ALARM_BATTERY_LOW))
			{
				ClearAlarm(ALARM_BATTERY_LOW);
			}
			if(MotorControl.status != MOTOR_STOP)
			{
				TMC2226_MotorStop();	 		
			}
			AddAlarm(ALARM_BATTERY_DEPLETE);
		}	
		if(sensorpack.voltagevalue <= 19)  //电池电量低
		{	
			if(LowFlag==1)
			{
				AddAlarm(ALARM_BATTERY_LOW);
				LowFlag=0;
			}
		}
	}
	else
	{
		LowFlag=1;
	}
}


/*
***************************************************************************
* Function: // JudgedInfusionUpBlock
* Description: //判断是否发生上阻塞
* @param[in]   NowPre3AD 上压力AD值
* @return	  上阻塞标志
* Others: 
***************************************************************************
*/

_Bool JudgedInfusionUpBlock(unsigned int NowPre3AD)
{
	static unsigned int overun_num;
	static _Bool timecount_flag = FALSE;
	

	if(JudgedYesNoAlarm(ALARM_UPPER_OCCLUSION))
	{
		overun_num = 0;
		timecount_flag = UpBlockTimeCountDown(FALSE);
	}
	else
	{
		//printf("ADU_Notube=%d ,nowAD3 =%d \n",SystemMaintain.ADU_Notube,NowPre3AD);
		timecount_flag = UpBlockTimeCountDown(TRUE);
		if((NowPre3AD <= (SystemMaintain.ADU_Notube)) && (NowPre3AD >= (SystemMaintain.ADU_Notube-50)))
		{	
			overun_num++;
		}
	}
	if(timecount_flag == TRUE)
	{
		if(overun_num >= 5)
		{
			overun_num = 0;
			timecount_flag = UpBlockTimeCountDown(FALSE);
			return TRUE;
		}
		else
		{
			overun_num = 0;
			timecount_flag = UpBlockTimeCountDown(FALSE);
			return FALSE;			
		}
	}
	else
	{
		
		 return FALSE;
	}

}


int LockTimeCountDown(_Bool DevBool,_Bool LockTime)
{
	if(!GetLockFlag()) /*没有上锁*/
	{	
		if(DevBool){
			LockTimeSec--;
			if(LockTimeSec<=0)
				{LockTimeSec=0;}    
		}else{
			LockTimeSec=LockTime*60;     
		}
	}else{
		LockTimeSec=LockTime*60;  
	}
	return LockTimeSec;
}




/*
***************************************************************************
* Function: // UpBlockTimeCountDown
* Description: //上阻塞检测时间倒计时
* @param[in]   StartFlag 倒计时开始标志
* @return	  返回倒计时结束标志
* Others: 
***************************************************************************
*/
_Bool UpBlockTimeCountDown(_Bool StartFlag)
{
	static unsigned int upblocktime = 6; //5s

	if(StartFlag == TRUE)
	{
		if(upblocktime > 0)
		{
			upblocktime--;
			if(upblocktime <= 0)
			{
				upblocktime = 0;
				return TRUE;
			}
		}
	}
	else if(StartFlag == FALSE)
	{
		upblocktime = 6;
	}
	return FALSE;
}



