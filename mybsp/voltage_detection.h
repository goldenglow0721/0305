#ifndef __VOLTAGE_DETECTION
#define __VOLTAGE_DETECTION

#include "stdint.h"

void chip_voltage_detection(void);

void chip_voltage_detection_dma_config(void);

double get_chip_voltage(void);



#endif /* __VOLTAGE_DETECTION  */
