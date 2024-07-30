#include "ui.h"

gt_obj_st * BootUp = NULL;


static void back(gt_event_st * e) {

	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_BootUp()
{




    
    delay_ms(5000);
    back(NULL);
    return BootUp;
}