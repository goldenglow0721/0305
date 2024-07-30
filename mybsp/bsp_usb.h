#ifndef __USB_H
#define __USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "at32f403a_407.h" 
#include "at32f403a_407_usb.h" 
#include "stdio.h"



void usb_msc_cdc_config(void);

void usb_cdc_test(void);
void usb_cbc_send_data_test(void);
void usb_print(const char *format, ...);
void usb_dis_connect(void);
	
void usb_hardware_connect_init(void);
void usb_config_process(void);

#ifdef __cplusplus
}
#endif

#endif

