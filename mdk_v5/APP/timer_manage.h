/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F403A_407_TIMER_H
#define __AT32F403A_407_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f403a_407.h"
#include "clock_manage.h"
/* exported functions ------------------------------------------------------- */
void tmr3_init(void);
void tmr4_init(void);
void tmr5_init(void);
void tmr12_init(enum CLOCK_WHICH clock_which );
void tmr13_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __AT32F403A_407_CLOCK_H */

