#ifndef _AUDIO_MANAGE_H_
#define _AUDIO_MANAGE_H_


#include "infusion.h"







void audio_gpio_init(void);
void beep_init(uint8_t power_state);
void BeepStart(void);
void BeepStop(void);
void BeepWork(void);

void WT588F_Send_doubledata(unsigned int USER_DATA);
void WT588F_Send_Data(unsigned char DDATA);
void audio_gpio_init(void);






#endif
