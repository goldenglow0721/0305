#ifndef __FATFS_HISTORT
#define __FATFS_HISTORT

#include "stdint.h"
#include <string.h>
#include  "infusion.h"
#include "library_history.h"

/* 中文 历史记录定义 */
typedef struct 
{
    char        ch_name1[50];                        
    char        ch_name2[50];                        

}ch_history_information;

/* 英文 历史记录定义 */
typedef struct 
{                     
    char        en_name1[50];                                          
    char        en_name2[50];                       
}en_history_information;

typedef struct 
{                    
    char        es_name1[50];                   
    char        es_name2[50];

}es_history_information;

/* 繁体 历史记录定义 */
typedef struct 
{
    char        ch2_name1[50];
    char        ch2_name2[50];
}ch2_history_information;


typedef struct 
{ 
    char        pu_name1[50];
    char        pu_name2[50];
}pu_history_information;

/* 54字节 */
typedef struct 
{ 
    char        Data[30];
    TIME        TIME_DATA;
}history_tim_information;

typedef enum hsitory_language{
    Export_history_EN =1,
	Export_history_ZH
}hsitory_language;


uint32_t fatfs_init(const char* drive);
uint32_t write_history_info(const char* drive,char* write_info);
uint32_t unmount_fatfs(const char* drive);

uint32_t write_history_information(const char* drive, const void* write_info, size_t data_size);

void fat_write_test(void);


void first_start_write_history_info(void);
void not_first_start_write_history_info(int MoTion,int Describe,char* Data);

void my_test_fatfs(const char* drive);

void write_history_to_fatfs(void);

void refresh_buffer(void);

#endif  /* __FATFS_HISTORT */


