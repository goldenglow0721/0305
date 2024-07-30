#ifndef  __MY_FLASH
#define  __MY_FLASH


#include "stdint.h"

/* 

flash base adderss   0x0808 0000 

flash size 1024*512k  = 0x8 0000

*/

/* 文件系统起始地址 */
#define  FILE_SYS_BASE_ADDRESS  0x080A0000

/* 文件系统大小 */
#define  FILE_SYS_SIZE          0x80000


int8_t my_flash_read(uint8_t *pBuffer,uint32_t ReadAddr,  uint32_t NumByteToRead);
int8_t my_flash_write(uint8_t *p_buffer, uint32_t write_addr, uint32_t num_write);

int chip_flash_test(void);
void my_test_fatfs(const char* drive);

#endif


