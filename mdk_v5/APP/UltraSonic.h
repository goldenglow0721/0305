#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "at32f403a_407.h"
#include "at32f403a_407_board.h"
#include "protocol.h"

void gpio_UltraSonic_init(void);
void sonic_tx_pwm_init(void);
void sonic_rx_receiver_init(void);
void sonic_tx_capture_init(void);
void sonic_tmr_init(void);
void airbubble_default_para_init(Airbubble *Airbubble_struct);
void ultrasonic_init(void);
























#endif
