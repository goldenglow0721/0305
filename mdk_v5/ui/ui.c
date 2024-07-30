#include "ui.h"
#include "headbar_view.h"
#include "library_infusion.h"
#include "gt_scr_stack.h"
KeyBoardI keyboardi;
KeyBoardF keyboardf;
KeyBoardS keyboards;
KeyBoardT keyboardt;
Limit limit;


_Bool calibrate = false;  //用来区分精度校准的步骤
int   brandchoice2_from=0;  //用来记录从哪里进入的brandchoice2

//lvgl管理
void TMR5_GLOBAL_IRQHandler(void)
{

	if(tmr_flag_get(TMR5, TMR_OVF_FLAG) != RESET)
	{
		gt_tick_inc(1);
		tmr_flag_clear(TMR5, TMR_OVF_FLAG);
	}
}

void gt_ui_init(void) {
	gt_obj_st * target_scr =gt_init_Logo();
	gt_disp_load_scr_anim(target_scr, GT_SCR_ANIM_TYPE_NONE, 100, 0, true);
	
}


//1=visiable
void headvisiable(gt_visible_et temp)
{
	gt_disp_st * temp1 = gt_disp_get_default();
	gt_obj_child_set_prop(temp1->layer_top,GT_OBJ_PROP_TYPE_VISIBLE,temp);
	gt_disp_invalid_area(headrect);

	
}



//判断是否包含运行界面
_Bool judgeIsRunScreen()
{

	//判断当前的界面id值是否是run
	gt_scr_id_t id = my_get_now_scr_id();

	if(my_judge_obj_exists(GT_SCR_ID_97) || my_judge_obj_exists(GT_SCR_ID_96) || my_judge_obj_exists(GT_SCR_ID_98)  || my_judge_obj_exists(GT_SCR_ID_99))
	{
		return true;
	}
	else
	{
		return false;
	}
	 
	

}








