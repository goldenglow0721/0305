#ifndef _BATTERY_MANAGE_H
#define _BATTERY_MANAGE_H


#define VoltageMonitor 1

#include "stdint.h"
#include "stdbool.h"

void gpio_bat_init(uint8_t val) ;


void Enter_PowerDown(void);

void BatteryManagement_PD(void);



void BatteryManagement(void);

void PowerDownFunction(void);

int getVoltageADCValue();

int process_adc_A_val(int val);

void gpio_bat_control(bool flag);
void BUZZER_control(bool flag);
#endif



























































