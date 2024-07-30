/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "at32f403a_407_flash.h"
#include "my_flash.h"
#include "infusion.h"
/* Definitions of physical drive number for each drive */
#define DEV_SPI		1	
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

 	


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;


	return 0;	
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

    return 0;

}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;
	

	flash_read(FILE_SYS_BASE_ADDRESS + sector*1024, buff, count*1024);
	

    return 0;

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;	
	
	// translate the arguments here	
	
	flash_sector_erase(FILE_SYS_BASE_ADDRESS+sector*2048);

	flash_write(FILE_SYS_BASE_ADDRESS+sector*1024,(uint16_t*)buff,count*1024);
	
	return 0;

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
		DRESULT res;
	int result;
	
	switch (pdrv) {
	case 0 :

		// Process of the command for the RAM drive
		switch(cmd)
		{
			case CTRL_SYNC:
				res = RES_OK; 
			break;
			
			case GET_SECTOR_SIZE:
				*(DWORD*)buff = 2048;    //������С
				res = RES_OK;
			break;	
			
			case GET_BLOCK_SIZE:
				*(WORD*)buff = 1;   
				res = RES_OK;
			break;	
			
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = 128;  //��������
				res = RES_OK;
			break;
			
			default:
				res = RES_PARERR;
			break;
		}

		return res;
	}

	return RES_PARERR;
}

