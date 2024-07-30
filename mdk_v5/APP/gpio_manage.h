#ifndef __AT32F403A_GPIO_INIT_H
#define __AT32F403A_GPIO_INIT_H

#ifdef __cplusplus
extern "C" {
#endif







/* includes ------------------------------------------------------------------*/
#include "at32f403a_407.h"

/* exported functions ------------------------------------------------------- */
void led_gpio_init(void);
void key_gpio_init(void);
void led_control(int level);
void gpio_switch_init();


#ifdef __cplusplus
}
#endif

#endif 



