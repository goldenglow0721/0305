/************************************************
  
  

        对话框文件。 含有确定按键和返回键



**************************************************/

#include "ui.h"

static const char title[5][2][50]={
	"是否删除此输液器品牌",
	"是否删除此药物名",


	"Delete IV Set Brand or not?",
	"Delete the drug name or not?",


	"Eliminar IV Set marca o no?",
	"¿Eliminar el nombre del medicamento o no?",


	"是否刪除此輸液器品牌",
	"是否刪除此藥物名",
	

	"Excluir marcaequipo ou não?",
	"Excluir o nome do medicamento ou não?"
	
		
};

gt_obj_st * dialog2 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * lab =NULL;

gt_dialog_param_st param;

static void back(gt_event_st * e) {

    gt_event_send(dialog2,GT_EVENT_TYPE_NOTIFY_CLOSE,"1");
}

static void affirm(char * str,gt_event_st * e) {
	
	printf(" affirm \r\n ");
    
    if(strcmp(param.content,"是否删除此药物名"))    //删除药品过来的
	{
	    Drugaffirm(e->user_data); 
	    printf("drugs num is:%d\r\n",getNowDrugListNum());  //进不去
	}
    	
    else if(strcmp(param.content,"是否删除此输液器品牌"))     //删除输液器品牌过来的
        Brandaffirm(e->user_data);
		
    //打印药物库节点数量   
}

gt_obj_st * dialog2_create(char * str,gt_event_st * e) {
	
	/** dialog2 */
	gt_dialog_param_st param;
	param.cancel_cb = back;
	param.cancel_cb_user_data = NULL;
	param.confirm_cb = affirm;
	param.confirm_cb_user_data = e->user_data;
	param.title = NULL;
	param.content = str;
	
	dialog2 = gt_dialog_create_issue(false,&param);
	gt_obj_set_pos(dialog2, 120, 90);
	gt_obj_set_size(dialog2, 240, 130);
	gt_dialog_set_bgcolor(dialog2, gt_color_hex(0xffffff));
	gt_dialog_set_border_color(dialog2, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog2, 3);
	gt_dialog_set_border_radius(dialog2, 0);
	gt_dialog_set_content_font_size(dialog2, 24);
	gt_dialog_set_content_font_family_cn(dialog2, 20);
	gt_dialog_set_content_font_family_en(dialog2, 33);
	gt_dialog_set_content_font_family_fl(dialog2, 50);
	gt_dialog_set_outside_auto_hide(dialog2, false);
	gt_dialog_set_anim_time(dialog2,50);
	gt_dialog_show(dialog2);



    #if 0
	dialog2 = gt_dialog_create(false);
	gt_obj_set_pos(dialog2, 120, 90);
	gt_obj_set_size(dialog2, 240, 130);
	gt_dialog_set_bgcolor(dialog2, gt_color_hex(0xffffff));
	gt_dialog_set_border_color(dialog2, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog2, 3);
	gt_dialog_set_border_radius(dialog2, 0);
	//gt_dialog_set_outside_auto_hide(dialog2,true);

    
	param->cancel_cb = back;
	param->cancel_cb_user_data = NULL;
	param->confirm_cb = affirm;
	param->confirm_cb_user_data =  e->user_data;
	param->title = NULL;
	param->content = str;
	gt_dialog_create_issue(false,param);


	/** btn */
	btn1 = gt_btn_create(dialog2);
	gt_obj_set_pos(btn1, 190, 160);
	gt_obj_set_size(btn1, 100, 50);
	gt_btn_set_font_color(btn1, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1,18);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn1, "确认");
	gt_btn_set_color_background(btn1, gt_color_hex(0x0097e6));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0xc0c0c0));
	gt_btn_set_radius(btn1, 4);
    
	    gt_obj_add_event_cb(btn1, affirm, GT_EVENT_TYPE_INPUT_PRESSED, "1");

    /** btn */
	btn2 = gt_btn_create(dialog2);
	gt_obj_set_pos(btn2, 190, 160);
	gt_obj_set_size(btn2, 100, 50);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2,18);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "返回");
	gt_btn_set_color_background(btn2, gt_color_hex(0x0097e6));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0xc0c0c0));
	gt_btn_set_radius(btn2, 4);
	gt_obj_add_event_cb(btn2, back, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** lab */
	lab = gt_label_create(dialog2);
	gt_obj_set_pos(lab, 120, 115);
	gt_obj_set_size(lab, 240, 35);
	gt_label_set_font_color(lab, gt_color_hex(0x000000));
	gt_label_set_font_size(lab, 24);
	gt_label_set_font_family_en(lab, 33);
	gt_label_set_font_family_cn(lab, 18);
	gt_label_set_font_family_fl(lab, 50);
	gt_label_set_font_align(lab, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab, str);
    
	gt_dialog_show(dialog2);
    #endif

	return dialog2;
}









