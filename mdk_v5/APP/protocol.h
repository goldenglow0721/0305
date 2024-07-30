#ifndef _PROTOCOL_H_
#define	_PROTOCOL_H_

#include "stdint.h"






typedef struct{

 uint32_t  s_calibcount;       
 uint32_t  scount;        
}Motor_CountNum;
extern Motor_CountNum motor_countnum;



typedef enum {Bubble_FALSE = 0, Bubble_TRUE = !Bubble_FALSE} NoBubble_State;



typedef struct{
 uint32_t  sonic_rx_num;  
 NoBubble_State  no_bubble_state;
}Airbubble;
extern Airbubble airbubble;






















































#endif

