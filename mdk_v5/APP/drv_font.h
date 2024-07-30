#ifndef _drv_font_H_
#define _drv_font_H_



#include "at32f403a_407_board.h"
//#include "GT32L24F0210.h"



/******��ʼ���ֿ�**********/
void drv_font_init(void);


/*********��SPIʹ��**********/

void drv_font_enable(void);


/******************�ر�SPIʹ��*************/
					
void drv_font_disable(void);

/*********spi����һ���ֽ�**********/

uint8_t drv_font_send_byte(uint8_t dat);


/*******����******/
void gpio_font_config(void);



#endif
