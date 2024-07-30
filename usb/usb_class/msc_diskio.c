/**
  **************************************************************************
  * @file     msc_diskio.c
  * @version  v2.0.9
  * @date     2022-06-28
  * @brief    usb mass storage disk function
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
#include "msc_diskio.h"
#include "msc_bot_scsi.h"
//#include "at32_sdio.h"
//#include "spi_flash.h"
#include "my_flash.h"
#include "bsp_qspi_flash.h"


static usb_sts_type flash_read(uint32_t address, uint32_t len, uint8_t *buf);
static usb_sts_type flash_write(uint32_t address, uint32_t len, uint8_t *buf);


/** @addtogroup AT32F435_periph_examples
  * @{
  */

/** @addtogroup 435_USB_device_msc
  * @{
  */
uint8_t scsi_inquiry[MSC_SUPPORT_MAX_LUN][SCSI_INQUIRY_DATA_LENGTH] =
{
  /* lun = 0 */
  {
    0x00,         /* peripheral device type (direct-access device) */
    0x80,         /* removable media bit */
    0x00,         /* ansi version, ecma version, iso version */
    0x01,         /* respond data format */
    SCSI_INQUIRY_DATA_LENGTH - 5, /* additional length */
    0x00, 0x00, 0x00, /* reserved */
    'Z', 'K', 'S', 'W', ' ', ' ', ' ', ' ', /* vendor information "AT32" */
    'D', 'i', 's', 'k', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* Product identification "Disk" */
    '2', '.', '0', '0'  /* product revision level */
  },
//  {
//    0x00,         /* peripheral device type (direct-access device) */
//    0x80,         /* removable media bit */
//    0x00,         /* ansi version, ecma version, iso version */
//    0x01,         /* respond data format */
//    SCSI_INQUIRY_DATA_LENGTH - 5, /* additional length */
//    0x00, 0x00, 0x00, /* reserved */
//    'A', 'T', '3', '2', ' ', ' ', ' ', ' ', /* vendor information "AT32" */
//    'D', 'i', 's', 'k', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* Product identification "Disk" */
//    '2', '.', '0', '0'  /* product revision level */
//  }
};

/**
  * @brief  get disk inquiry
  * @param  lun: logical units number
  * @retval inquiry string
  */
uint8_t *get_inquiry(uint8_t lun)
{
  if(lun < MSC_SUPPORT_MAX_LUN)
    return (uint8_t *)scsi_inquiry[lun];
  else
    return NULL;
}


/**
  * @brief  disk read
  * @param  lun: logical units number
  * @param  addr: logical address
  * @param  read_buf: pointer to read buffer
  * @param  len: read length
  * @retval status of usb_sts_type
  */
usb_sts_type msc_disk_read(uint8_t lun, uint32_t addr, uint8_t *read_buf, uint32_t len)
{
	usb_sts_type res;
	switch(lun)
	{
		case INTERNAL_FLASH_LUN:
			res=flash_read(addr,len ,read_buf);
		  
		break;
			
//		case SPI_FLASH_LUN:
//			spiflash_read(read_buf, (0x00600000+addr), len);
//			res=USB_OK;
//		break;
		
	}
	
	return res;
}


/**
  * @brief  disk write
  * @param  lun: logical units number
  * @param  addr: logical address
  * @param  buf: pointer to write buffer
  * @param  len: write length
  * @retval status of usb_sts_type
  */
usb_sts_type msc_disk_write(uint8_t lun, uint32_t addr, uint8_t *buf, uint32_t len)
{
	usb_sts_type res;
	
	switch(lun)
	{
		case INTERNAL_FLASH_LUN:
			flash_sector_erase(addr);
			res=flash_write(addr,len,buf);
		break;
		
//		case SPI_FLASH_LUN:
////			spiflash_sector_erase((0x00600000+addr));
//			spiflash_write(buf, (0x00600000+addr), len);
//			res=USB_OK;
//		break;
		
	
	}
	return res;
}

void getblksize(uint32_t *blk_nbr, uint32_t *blk_size)
{
	uint32_t sector_size = 2048;
//	uint32_t msc_flash_size;
//	uint32_t flash_s = *((uint32_t *)0x1FFFF7E0);
//	msc_flash_size = (flash_s << 10) - (USB_FLASH_ADDR_OFFSET - FLASH_BASE);
//	if(flash_s < 256)
//	{
//		sector_size = SECTOR_SIZE_1K;
//	}
//	else
//	{
//		sector_size = SECTOR_SIZE_2K;
//	}
	
	//0x08080000 512k-112k = 400kb
	
//	*blk_nbr = msc_flash_size / sector_size;
//	*blk_nbr = (msc_flash_size-0x1c000) / sector_size;   //512-112   = 400kb
	*blk_nbr  =  0x64000/sector_size; //理论应该为
	*blk_size =  sector_size;
	

}
/**
  * @brief  disk capacity
  * @param  lun: logical units number
  * @param  blk_nbr: pointer to number of block
  * @param  blk_size: pointer to block size
  * @retval status of usb_sts_type
  */
usb_sts_type msc_disk_capacity(uint8_t lun, uint32_t *blk_nbr, uint32_t *blk_size)
{	
	switch(lun)
	{
		case INTERNAL_FLASH_LUN:
			getblksize(blk_nbr,blk_size);
		break;
		
//		case SPI_FLASH_LUN:
//			*blk_nbr = 1*1024*1024 / 512; //1M
//			*blk_size = 512;
//		break;
		
		
		default:
		break;
	}
	return USB_OK;
}

usb_sts_type flash_read(uint32_t address, uint32_t len, uint8_t *buf)
{
	uint32_t i = 0;
	uint32_t flash_addr = address + USB_FLASH_ADDR_OFFSET;
	for(i = 0; i < len; i ++)
	{
		buf[i] = *((uint8_t *)flash_addr);
		flash_addr += 1;
	}
  
  return USB_OK; 
}


usb_sts_type flash_write(uint32_t address, uint32_t len, uint8_t *buf)
{
	uint32_t i = 0;
	uint32_t flash_addr = address + USB_FLASH_ADDR_OFFSET;
	uint32_t page_len = 2048, tolen = len;
	uint32_t erase_addr = flash_addr;
	flash_status_type status = FLASH_OPERATE_DONE;
	
	flash_unlock();
	while(tolen >= page_len)
	{
		flash_sector_erase(erase_addr);
		tolen -= page_len;
		erase_addr += page_len;
	}
	for(i = 0; i < len; i ++)
	{
		status=flash_byte_program(flash_addr+i, buf[i]);
		if(status != FLASH_OPERATE_DONE)
		{
			/* test spim fail */
			return USB_ERROR;;
		}
	}
	flash_lock();
  
  return USB_OK;
 
}






/**
  * @}
  */

/**
  * @}
  */
