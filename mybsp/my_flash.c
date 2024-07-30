#include "my_flash.h"
#include "at32f403a_407.h"
#include "stdio.h"
#include "infusion.h"
#include "ff.h"
#include <stdlib.h>


 

int8_t my_flash_read(uint8_t *pBuffer,uint32_t ReadAddr,  uint32_t NumByteToRead)
{
    // Iterate over the number of bytes to read
    for(uint32_t i = 0; i < NumByteToRead; i++)
    {
        // Read a single byte from the flash memory and increment the address
        pBuffer[i] = *(uint8_t*)ReadAddr;
        ReadAddr++;
    }	
	 return 0;  // �ɹ�
}



int8_t my_flash_write_nocheck(uint32_t write_addr, uint8_t *p_buffer, uint32_t num_write)
{
  uint16_t i;
  flash_status_type status = FLASH_OPERATE_DONE; 
  for(i = 0; i < num_write; i++)
  {
    status = flash_byte_program(write_addr, p_buffer[i]);
    if(status != FLASH_OPERATE_DONE)
      return ERROR;
    write_addr += 1;
  }
  return 0;
}


#define SECTOR_SIZE 2048
uint8_t my_flash_buf[SECTOR_SIZE];

int8_t my_flash_write(uint8_t *p_buffer, uint32_t write_addr, uint32_t num_write)
{
  uint32_t offset_addr;
  uint32_t sector_position;
  uint32_t sector_offset;   // ���ֽڼ���ƫ��
  uint32_t sector_remain;   // ���ֽڼ���ʣ����
  uint32_t i;
  flash_status_type status = FLASH_OPERATE_DONE;
  
  flash_unlock();
  offset_addr = write_addr - FLASH_BASE;
  sector_position = offset_addr / SECTOR_SIZE;
  sector_offset = offset_addr % SECTOR_SIZE;
  sector_remain = SECTOR_SIZE - sector_offset;
  if(num_write <= sector_remain)
    sector_remain = num_write;

  while(1)
  {
    my_flash_read(my_flash_buf,sector_position * SECTOR_SIZE + FLASH_BASE,  SECTOR_SIZE);
    for(i = 0; i < sector_remain; i++)
    {
      if(my_flash_buf[sector_offset + i] != 0xFF)  // �޸ļ������Ϊ8λ
        break;
    }
    if(i < sector_remain)
    {
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
        my_flash_buf[i + sector_offset] = p_buffer[i];
      }
      if(my_flash_write_nocheck(sector_position * SECTOR_SIZE + FLASH_BASE, my_flash_buf, SECTOR_SIZE) != SUCCESS)
        return ERROR;
    }
    else
    {
      if(my_flash_write_nocheck(write_addr, p_buffer, sector_remain) != SUCCESS)
        return ERROR;
    }
    if(num_write == sector_remain)
      break;
    else
    {
      sector_position++;
      sector_offset = 0;
      p_buffer += sector_remain;
      write_addr += sector_remain;
      num_write -= sector_remain;
      if(num_write > SECTOR_SIZE)
        sector_remain = SECTOR_SIZE;
      else
        sector_remain = num_write;
    }
  }
  flash_lock();
  
  return 0;
}





//FATFS fs;           // FatFs file system object
//FIL fil;            // File object
//FRESULT fr;         // to store the result of FatFs functions
//UINT bw, br;        // File read/write count
//char my_buffer[1024];  // File read/write buffer

//void my_test_fatfs(const char* drive) {
//    // Mount or format the drive
//    fr = f_mount(&fs, "1:", 1);
//    if (fr == FR_NO_FILESYSTEM) {
//        // No filesystem, need to format the drive
//        printf("No filesystem found, need to format the drive...\n");
//        fr = f_mkfs("1:", 0, 0, 4096);
//        if (fr != FR_OK) {
//            printf("Error formatting the drive: %d\n", fr);
//            return;
//        }
//        printf("Drive formatted successfully.\n");
//    } else if (fr != FR_OK) {
//        printf("Failed to mount the filesystem: %d\n", fr);
//        return;
//    }
//    printf("Filesystem mounted successfully.\n");

//    // Create a new file, or open it if it already exists
//    fr = f_open(&fil, "1:test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
//    if (fr != FR_OK) {
//        printf("Failed to open 'test.txt': %d\n", fr);
//        return;
//    }

//    // Write data to the file
//    fr = f_write(&fil, "Hello, world!", 13, &bw);
//    if (fr != FR_OK) {
//        printf("Failed to write to 'test.txt': %d\n", fr);
//        f_close(&fil);
//        return;
//    }
//    printf("Written to 'test.txt': %u bytes\n", bw);

//    // Close the file to save the data
//    f_close(&fil);

//    // Open the file to read
//    fr = f_open(&fil, "1:test.txt", FA_READ);
//    if (fr != FR_OK) {
//        printf("Failed to open 'test.txt' for reading: %d\n", fr);
//        return;
//    }

//    // Read data from the file
//    fr = f_read(&fil, my_buffer, sizeof(my_buffer), &br);
//    if (fr != FR_OK) {
//        printf("Failed to read from 'test.txt': %d\n", fr);
//        f_close(&fil);
//        return;
//    }
//    my_buffer[br] = 0; // Ensure string is null-terminated

//    printf("Read from 'test.txt': %s\n", my_buffer);

//    // Close the file
//    f_close(&fil);

//    // Optionally, unmount the filesystem
//    f_mount(NULL, "1:", 0);
//}


FATFS fs;           // FatFs file system object
FIL fil;            // File object
FRESULT fr;         // To store the result of FatFs functions
UINT bw, br;        // File read/write count
char my_buffer[1024];  // File read/write buffer


void test_formatting(const char* drive){
	fr = f_mkfs(drive, 0, 0, 4096);
	if(fr == 0){
	  printf(" test formatting success\r\n ");
	}else{
	
	  printf(" test formatting failed\r\n ");
	}
}

/* ���øú������ܻᵼ��openʧ�� ���ڶ��߳�Ӱ�� */
void my_test_fatfs(const char* drive) {
    // Mount or format the drive

    fr = f_mount(&fs, drive, 1);
    if (fr == FR_NO_FILESYSTEM) {
        // No filesystem, need to format the drive
        printf("No filesystem found on %s, need to format the drive...\r\n", drive);
        fr = f_mkfs(drive, 0, 0, 4096);		
        if (fr != FR_OK) {
            printf("Error formatting the drive %s: %d\r\n", drive, fr);
            return;
        }
        printf("Drive %s formatted successfully.\r\n", drive);
    } else if (fr != FR_OK) {
        printf("Failed to mount the filesystem on %s: %d\r\n", drive, fr);
        return;
    }
        printf("Filesystem mounted successfully on %s.\r\n", drive);

    // Create or open a file
    char filepath[30];
    sprintf(filepath, "%stest.txt", drive);
    fr = f_open(&fil, filepath, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
    if (fr != FR_OK) {
        printf("Failed to open '%s': %d\r\n", filepath, fr);
        return;
    }

    // Write data to the file
    fr = f_write(&fil, "Hello, world!", 13, &bw);
    if (fr != FR_OK) {
        printf("Failed to write to '%s': %d\r\n", filepath, fr);
        f_close(&fil);
        return;
    }
    printf("Written to '%s': %u bytes\r\n", filepath, bw);

    // Close the file to save the data
    f_close(&fil);

    // Open the file to read
    fr = f_open(&fil, filepath, FA_READ);
    if (fr != FR_OK) {
        printf("Failed to open '%s' for reading: %d\r\n", filepath, fr);
        return;
    }

    // Read data from the file
    fr = f_read(&fil, my_buffer, sizeof(my_buffer), &br);
    if (fr != FR_OK) {
        printf("Failed to read from '%s': %d\r\n", filepath, fr);
        f_close(&fil);
        return;
    }
    my_buffer[br] = 0; // Ensure string is null-terminated
    printf("Read from '%s': %s\r\n", filepath, my_buffer);

    // Close the file
    f_close(&fil);

    // Optionally, unmount the filesystem
    f_mount(NULL, drive, 0);
}






// ����Ļ���ַ����Ҫ����ʵ��Ӳ������
#define CHIP_FLASH_BASE_ADDRESS 0x080C8000



int chip_flash_test(void)
{
    uint8_t test_data[4] = {0xAA, 0xBB, 0xCC, 0xDD};  // ��������
    uint8_t read_buffer[4];  // ��ȡ������
    uint32_t sector_size = 2048;  // ÿ��������СΪ2K�ֽ�
    uint32_t num_sectors = 50;  // 100K / 2K = 50����
    uint32_t addr;
    int8_t write_status, read_status;

    // ���ȱ�������������д������
    for (uint32_t i = 0; i < num_sectors; i++) {
        addr = CHIP_FLASH_BASE_ADDRESS + i * sector_size;  // ����������ʼ��ַ

        // д��ÿ��������ǰ4�ֽ�
        write_status = my_flash_write(test_data, addr, 4);
        if (write_status != 0) {
            printf("Failed to write to sector %u at address 0x%08X\n", i, addr);
            return -1;  // д��ʧ�ܣ����ش���
        }
    }

    // �ٴα���������������ȡ��֤����
    for (uint32_t i = 0; i < num_sectors; i++) {
        addr = CHIP_FLASH_BASE_ADDRESS + i * sector_size;  // ����������ʼ��ַ

        // ��ȡ����֤ÿ��������ǰ4�ֽ�
        read_status = my_flash_read(read_buffer, addr, 4);
        if (read_status != 0) {
            printf("Failed to read from sector %u at address 0x%08X\n", i, addr);
            return -2;  // ��ȡʧ�ܣ����ش���
        }

        // ��֤�����Ƿ���ȷ
        if (read_buffer[0] != test_data[0] || read_buffer[1] != test_data[1] ||
            read_buffer[2] != test_data[2] || read_buffer[3] != test_data[3]) {
            printf("Data verification failed at sector %u\n", i);
            return -3;  // ������֤ʧ�ܣ����ش���
        }
    }

    printf("Flash read/write test passed successfully.\r\n");
    return 0;  // ����ͨ��
}


