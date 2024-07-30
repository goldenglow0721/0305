#ifndef _drv_font_H_
#define _drv_font_H_



#include "at32f403a_407_board.h"
//#include "GT32L24F0210.h"



/******初始化字库**********/
void drv_font_init(void);


/*********打开SPI使能**********/

void drv_font_enable(void);


/******************关闭SPI使能*************/
					
void drv_font_disable(void);

/*********spi发送一个字节**********/

uint8_t drv_font_send_byte(uint8_t dat);


/*******配置******/
void gpio_font_config(void);



#endif
