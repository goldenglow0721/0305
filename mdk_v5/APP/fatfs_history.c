#include "fatfs_history.h"
#include "ff.h"
#include "stdio.h"
#include  <string.h>
#include "library_history.h"
#include "bsp_qspi_flash.h"

static FATFS fs;           // FatFs file system object
static FIL fil;            // File object
static FRESULT fr;         // To store the result of FatFs functions
static UINT bw, br;        // File read/write count
static char my_buffer[1024];  // File read/write buffer

/* 锟侥硷拷锟斤拷锟斤拷锟斤拷 MAX: 30  */
static char filepath[30];
/* 锟斤拷史锟侥硷拷锟斤拷锟斤拷息 */
#define  HISTORY_INFO_NAME    "history_info.txt"

#define  ON_FATFS_DEBUG   

/* 
  锟斤拷始锟斤拷锟侥硷拷系统
  
  @para1   drive: "0:"锟节诧拷flash / "1:"锟解部flash
  eg:      fatfs_init("1:") 锟解部flash
  @ret     fr
*/

uint32_t fatfs_init(const char* drive) {
    // Mount or format the drive

    fr = f_mount(&fs, drive, 1);
    if (fr == FR_NO_FILESYSTEM) {
        // No filesystem, need to format the drive
		 //printf("No filesystem found on %s, need to format the drive...\r\n", drive);

        fr = f_mkfs(drive, 0, 0, 4096);		
        if (fr != FR_OK) {
            //printf("Error formatting the drive %s: %d\r\n", drive, fr);
            return fr;
        }
        //printf("Drive %s formatted successfully.\r\n", drive);
    } else if (fr != FR_OK) {
        //printf("Failed to mount the filesystem on %s: %d\r\n", drive, fr);
        return fr;
    }
        //printf("Filesystem mounted successfully on %s.\r\n", drive);
	
   return 0;
}

/* 
 写锟斤拷史锟斤拷息 

 @para1   drive: "0:"锟节诧拷flash / "1:"锟解部flash
 @para2   write_info: 写锟斤拷锟斤拷锟斤拷
 eg:      write_history_info("1:","hello world!")
 eg: 	  write_history_info("1:",log)   log: char log[]
 @ret     fr
*/
uint32_t write_history_info(const char* drive,char* write_info)
{
	// Create or open a file
	
	sprintf(filepath, "%s%s", drive,HISTORY_INFO_NAME );
	// 锟斤拷锟侥硷拷锟斤拷锟斤拷锟侥硷拷指锟斤拷锟狡讹拷锟斤拷锟侥硷拷末尾锟斤拷锟斤拷锟斤拷追锟斤拷锟斤拷锟捷★拷锟斤拷锟斤拷募锟斤拷锟斤拷锟斤拷冢锟斤拷虼唇锟斤拷锟斤拷锟?
    fr = f_open(&fil, filepath, FA_OPEN_APPEND | FA_WRITE | FA_READ);

    if (fr != FR_OK) {
        //printf("Failed to open '%s': %d\r\n", filepath, fr);
        return fr;
    }

    // Write data to the file
    fr = f_write(&fil, write_info, strlen(write_info), &bw);
    if (fr != FR_OK) {
        //printf("Failed to write to '%s': %d\r\n", filepath, fr);
        f_close(&fil);
        return fr;
    }
    //printf("Written to '%s': %u bytes\r\n", filepath, bw);

    // Close the file to save the data
    f_close(&fil);

    // Open the file to read
    fr = f_open(&fil, filepath, FA_READ);
    if (fr != FR_OK) {
        //printf("Failed to open '%s' for reading: %d\r\n", filepath, fr);
        return fr;
    }

    // Read data from the file
    fr = f_read(&fil, my_buffer, sizeof(my_buffer), &br);
    if (fr != FR_OK) {
        //printf("Failed to read from '%s': %d\r\n", filepath, fr);
        f_close(&fil);
        return fr;
    }
    my_buffer[br] = 0; // Ensure string is null-terminated
    //printf("Read from '%s': %s\r\n", filepath, my_buffer);

    // Close the file
    f_close(&fil);
		
	return fr;

    // 卸锟斤拷锟侥硷拷系统
    f_mount(NULL, drive, 0);
}



uint32_t write_history_information(const char* drive, const void* write_info, size_t data_size)
{
    // Create or open a file
    char filepath[100]; // Ensure this buffer is large enough for the file path
    sprintf(filepath, "%s%s", drive, HISTORY_INFO_NAME);
    // 锟斤拷锟侥硷拷锟斤拷锟斤拷锟侥硷拷指锟斤拷锟狡讹拷锟斤拷锟侥硷拷末尾锟斤拷锟斤拷锟斤拷追锟斤拷锟斤拷锟捷★拷锟斤拷锟斤拷募锟斤拷锟斤拷锟斤拷冢锟斤拷虼唇锟斤拷锟斤拷锟?
    fr = f_open(&fil, filepath, FA_OPEN_APPEND | FA_WRITE | FA_READ);

    if (fr != FR_OK) {
        //printf("Failed to open '%s': %d\r\n", filepath, fr);
        return fr;
    }

    // Write data to the file
    fr = f_write(&fil, write_info, data_size, &bw);
    if (fr != FR_OK) {
        //printf("Failed to write to '%s': %d\r\n", filepath, fr);
        f_close(&fil);
        return fr;
    }
    //printf("Written to '%s': %u bytes\r\n", filepath, bw);

    // Close the file to save the data
    f_close(&fil);

    return fr;
}



/* 
  卸锟斤拷锟侥硷拷系统 
  @para1   drive: "0:"锟节诧拷flash / "1:"锟解部flash
  @ret     fr

*/
uint32_t unmount_fatfs(const char* drive)
{
	 fr = f_mount(NULL, drive, 0);
     return fr;
}


/* 锟侥硷拷系统锟斤拷锟斤拷*/
void fat_write_test(void)
{
	//锟斤拷始锟斤拷锟斤拷锟斤拷锟侥硷拷系统
	fatfs_init("1:");
	
	//锟斤拷锟斤拷写锟斤拷锟斤拷锟斤拷
	char test_info[20] = "test information";
	
	//锟斤拷锟斤拷
	char line_feed[2] = "\r\n";
	
	//锟较诧拷锟斤拷锟捷伙拷锟斤拷
	char buff[30];
	
	for(int i =1;i<=10;i++)
	{
		sprintf(buff,"%d:%s%s",i,test_info,line_feed);
		 
	    write_history_info("1:",buff);   
	}
    //卸锟斤拷锟侥硷拷系统    
    unmount_fatfs("1:");
}


extern const RecordEv recordEv[5][92];


///* 锟斤拷锟斤拷时写锟斤拷锟斤拷史锟斤拷录 */
//void first_start_write_history_info(void)
//{
//    rtc_time_get();
// 
//    HistoryNodeMessage message = {0};

//    strcpy(message.ch_name1,"锟斤拷锟斤拷");
//    strcpy(message.en_name1,"Start up");
//    strcpy(message.es_name1,"Encender");
//    strcpy(message.pu_name1,"Come?ar");
//    strcpy(message.ch2_name1,"锟絖锟紺");

//    strcpy(message.ch_name2,"锟斤拷锟斤拷");
//    strcpy(message.en_name2,"Start up");
//    strcpy(message.es_name2,"Encender");
//    strcpy(message.pu_name2,"Come?ar");
//    strcpy(message.ch2_name2,"锟絖锟紺");
//	
//	strcpy(message.Data," ");
////	 memset(message.Data, 0, sizeof(message.Data));

//     message.TIME_DATA.year = calendar.year;
//     message.TIME_DATA.mon  = calendar.mon;
//     message.TIME_DATA.day  = calendar.day;
//     message.TIME_DATA.hour = calendar.hour;
//     message.TIME_DATA.min  = calendar.min;
//     message.TIME_DATA.sec  = calendar.sec;
//	 
//	 printf("Date and Time: %04d-%02d-%02d %02d:%02d:%02d\n",
//           message.TIME_DATA.year,
//           message.TIME_DATA.mon,
//           message.TIME_DATA.day,
//           message.TIME_DATA.hour,
//           message.TIME_DATA.min,
//           message.TIME_DATA.sec);
//	
//	
//	 //锟斤拷锟斤拷锟斤拷写锟斤拷flash 锟斤拷锟斤拷锟斤拷锟斤拷史锟斤拷录值
////	 history_write_to_flash(&message);	
//}


/* 锟角碉拷一锟斤拷锟斤拷锟斤拷时写锟斤拷锟斤拷锟斤拷 */
void not_first_start_write_history_info(int MoTion,int Describe,char* Data)
{ 
	//printf("not_first_start_write_history_info %s",Data);
	char buffer[50];
	
    rtc_time_get();
	
	HistoryNodeMessage message = {0};

	strcpy(message.ch_name1,recordEv[SystemSetting.langue][MoTion].EvChar);
    strcpy(message.en_name1,recordEv[SystemSetting.langue][MoTion].EvChar);
    strcpy(message.es_name1,recordEv[SystemSetting.langue][MoTion].EvChar);
    strcpy(message.pu_name1,recordEv[SystemSetting.langue][MoTion].EvChar);
    strcpy(message.ch2_name1,recordEv[SystemSetting.langue][MoTion].EvChar);

	strcpy(message.ch_name2,recordEv[SystemSetting.langue][Describe].EvChar);
    strcpy(message.en_name2,recordEv[SystemSetting.langue][Describe].EvChar);
    strcpy(message.es_name2,recordEv[SystemSetting.langue][Describe].EvChar);
    strcpy(message.pu_name2,recordEv[SystemSetting.langue][Describe].EvChar);
    strcpy(message.ch2_name2,recordEv[SystemSetting.langue][Describe].EvChar);

	if(Data)
	{
		sprintf(buffer,"%s",Data);
		strcpy(message.Data,buffer);
	}
	else 
	strcpy(message.Data," ");
	
	message.TIME_DATA.year = calendar.year;
    message.TIME_DATA.mon = calendar.mon;
    message.TIME_DATA.day = calendar.day;
    message.TIME_DATA.hour = calendar.hour;
    message.TIME_DATA.min = calendar.min;
    message.TIME_DATA.sec = calendar.sec;
 
	history_write_to_flash(&message);
	
    return;

}

/* 格式化文件系统并挂载 */
void formatting_fatfs_and_mount(const char* drive)
{
 /* 格式化文件系统并挂载 */
	 fr = f_mkfs(drive, 0, 0, 4096);	/* 格式化文件系统 */
	 if(fr != FR_OK){
	   printf("formatting err \r\n");
	 }else{
	   printf("formatting success \r\n");
	 }
	 
	 fr = f_mount(&fs, drive, 1);/* 挂载文件系统 */
	 
     if (fr == FR_NO_FILESYSTEM) {
        // No filesystem, need to format the drive
        printf("No filesystem found on %s, need to format the drive...\r\n", drive);
    } else if (fr != FR_OK) {
        printf("Failed to mount the filesystem on %s: %d\r\n", drive, fr);
        return;
    }
        printf("Filesystem mounted successfully on %s.\r\n", drive);
}



void write_to_fatfs(uint8_t * buffer)
{
	
	
	



}



void write_history(void)
{
	HistoryNodeMessage message;
	
	char buffer[150];
	uint32_t history_count;
	//创建历史记录缓存 将保存在外部flash的历史记录按指定格式写入文件系统内 
	
	//读取是否写满标志位
	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
	
	if(ParamSetting.history_full_flag)
	{	
	  history_count = History_max_num; 
		
	}else{
	  
	  history_count = ParamSetting.historynumber;
	}
	
	 //标志位满读取整个历史记录数据
	  for(int i=0;i<history_count;i++)	
	 {
		 spiflash_read((uint8_t *)&message,History_Flash_ADDRESS_Start+sizeof(HistoryNodeMessage)*i,sizeof(HistoryNodeMessage));
		 
		 sprintf(buffer,"%d/%d/%d %02d:%02d %s %s %s \r\n",
				 message.TIME_DATA.year,
				 message.TIME_DATA.mon,
				 message.TIME_DATA.day,
				 message.TIME_DATA.hour,
				 message.TIME_DATA.min,
				 message.en_name1,
				 message.en_name2,
				 message.Data
		        );
		 
         write_history_info("0:",buffer);  
	 }

    /* 设置卷标名称*/
//	f_setlabel("0:ZKSW_LOG");		 
}


/* 将历史记录写入flash */

void write_history_to_fatfs(void)
{
	/* 格式化内部flash并挂载文件系统 */
	formatting_fatfs_and_mount("0:"); 
			
	/* 将历史记录数据写入文件系统 */
	write_history();
	
   
}

//刷新缓冲区更新文件
void refresh_buffer(void)
{
	 f_sync(&fil);
}













