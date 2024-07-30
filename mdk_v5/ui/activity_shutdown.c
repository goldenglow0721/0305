#include "ui.h"


extern __IO uint8_t   DeviceFlag;

static const char title[5][2][50]={
	"关机",
	"待机",

	"Shutdown",
	"Standby",

	"Apagar",
	"En Espera",

	"關機",
	"待機",

	"Desligar",
	"Espera"

		
};

/** shutdown */
gt_obj_st * shutdown = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;

/** 返回 */
static void back(gt_event_st * e) {
	
	gt_disp_stack_go_back(1);
}


static void Confirm(gt_event_st * e){
   
   	#if 0
	gt_obj_st * temp = gt_disp_get_layer_top();
	printf("parent1 = %p\n",temp->parent);
	printf("type = %d\n",temp->class->type);
	_gt_obj_class_destroy_children(temp);
	printf("parent2 = %p\n",temp->parent);
	printf("type2 = %d\n",temp->class->type);

	// delay_sec(5);
	// not_first_start_write_history_info(EA_Shutdown,EA_Shutdown,NULL);
	// vtaskmanage(1);
	#endif
	// gt_obj_set_visible(img1,GT_INVISIBLE);
	// gt_obj_set_visible(img2,GT_INVISIBLE);
	// gt_obj_set_visible(img3,GT_INVISIBLE);
	// gt_obj_set_visible(img4,GT_VISIBLE);
	
	not_first_start_write_history_info(EA_Shutdown,EA_Shutdown,NULL);
	
	// vtaskmanage(1);
	
	gt_disp_stack_load_scr_anim(GT_SCR_ID_65, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}




static void StandbyBegin(gt_event_st * e){
   
	not_first_start_write_history_info(EA_Await,EA_Await,NULL);
	gt_disp_stack_load_scr_anim(GT_SCR_ID_84, GT_SCR_ANIM_TYPE_NONE, 500, 0, false);
}

gt_obj_st * gt_init_shutdown(void)
{
	shutdown =  gt_obj_create(NULL);
	my_set_obj_title(shutdown,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(shutdown, gt_color_hex(0x000000));
	 
	/** img1 */
	/** ReturnIcon */
	img1 = gt_img_create(shutdown);
	gt_obj_set_pos(img1, 1, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	img2 = gt_img_create(shutdown);
	gt_obj_set_pos(img2, 290, 120);
	gt_obj_set_size(img2, 120, 110);
	gt_img_set_src(img2, "f:img_120x110_guanji.png");
	gt_obj_add_event_cb(img2, Confirm, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	img3 = gt_img_create(shutdown);
	gt_obj_set_pos(img3, 90, 120);
	gt_obj_set_size(img3, 120, 110);
	gt_img_set_src(img3, "f:img_120x110_daiji.png");
	gt_obj_add_event_cb(img3, StandbyBegin, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	img4 = gt_img_create(shutdown);
	gt_obj_set_pos(img4, 70, 100);
	gt_obj_set_size(img4, 325, 160);
	gt_img_set_src(img4, "f:img_325x160_PowerOff.png");

	// gt_obj_set_visible(img1,GT_INVISIBLE);
	// gt_obj_set_visible(img2,GT_INVISIBLE);
	// gt_obj_set_visible(img3,GT_INVISIBLE);
	gt_obj_set_visible(img4,GT_INVISIBLE);

	return shutdown;
}

































