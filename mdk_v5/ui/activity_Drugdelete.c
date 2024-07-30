#include "ui.h"
#include "library_drug.h"

static const char title[5][4][50]={
	"删除药物名",
	"是否删除此药物名",
	"返回",
	"确认",

	"Delete Drug Name",
	"Delete the drug name or not?",
	"Return",
	"Confirm",

	"Eliminar Medicamento",
	"¿Eliminar el nombre del medicamento o no?",
	"Retorno",
	"Confirmar",

	"刪除藥物名",
	"是否刪除此藥物名",
	"返回",
	"確認",

	"Excluir nome do medicamento",
	"Excluir o nome do medicamento ou não?",
	"Retornar",
	"Confirmar"
		
};


/** DrugDelete */
gt_obj_st * DrugDelete = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * lab12 =NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * dialog3 = NULL;

static int sg_maxpage;
static int sg_nowpage;
static int sg_surplus;

uint8_t Drugtemp;


static void showpage(unsigned int Surplus)  //用来帮助显示最后一页
{
	switch(Surplus)
	{
		case 1:
			gt_obj_set_visible(lab4,GT_INVISIBLE);
			gt_obj_set_visible(rect3,GT_INVISIBLE);
		case 2:
			gt_obj_set_visible(lab5,GT_INVISIBLE);
			gt_obj_set_visible(rect4,GT_INVISIBLE);
		case 3:
			gt_obj_set_visible(lab6,GT_INVISIBLE);
			gt_obj_set_visible(rect5,GT_INVISIBLE);
			break;
		case 0:
			gt_obj_set_visible(lab3,GT_VISIBLE);
			gt_obj_set_visible(lab4,GT_VISIBLE);
			gt_obj_set_visible(lab5,GT_VISIBLE);
			gt_obj_set_visible(lab6,GT_VISIBLE);
			gt_obj_set_visible(rect2,GT_VISIBLE);
			gt_obj_set_visible(rect3,GT_VISIBLE);
			gt_obj_set_visible(rect4,GT_VISIBLE);
			gt_obj_set_visible(rect5,GT_VISIBLE);
			break;
	}
}

static void img1_0_cb(gt_event_st * e) {

	gt_disp_stack_go_back(1);
}


//确认删除
void Drugaffirm(gt_event_st * e) {
	
	char buffer[20];
	/*
		要再乘上页数 来具体表明是哪个药品名
	*/ 
	Drugtemp = atoi(e->user_data);	
		
	DrugNode_t* tempnode = fineDrugNodeByPosit(34+Drugtemp*sg_nowpage);
	
	//删除内容
	if(SystemSetting.langue == Chinese)
		removeDrugNodeById(tempnode->message.ch_name,false);
	else if(SystemSetting.langue == English)
		removeDrugNodeById(tempnode->message.en_name,false);
	else if(SystemSetting.langue == Spanish)
		removeDrugNodeById(tempnode->message.es_name,false);
	else if(SystemSetting.langue == Chinese2)
		removeDrugNodeById(tempnode->message.ch2_name,false);
	else if(SystemSetting.langue == Portuguese)
	    removeDrugNodeById(tempnode->message.pu_name,false);
	
	int number = getNowDrugListNum();
		
	number = number - 35;

	if(number%4==0)   //确定sg_和surplus
	{
		if(number==0)
			sg_maxpage=1;
		else
		sg_maxpage=number/4;
	}
	else
		sg_maxpage=number/4+1;
											
	sg_surplus=number%4;
	
	sprintf(buffer,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab2, buffer);

	if(sg_nowpage>1)
		showpage(0);
	else if(sg_nowpage==1)
		showpage(sg_surplus);
	else if(sg_nowpage==sg_maxpage)
		showpage(0);

	fineDrugNode_four_ById(sg_nowpage*4+32);
	//更新内容
	gt_label_set_text(lab3, drugname1);
	gt_label_set_text(lab4, drugname2);
	gt_label_set_text(lab5, drugname3);
	gt_label_set_text(lab6, drugname4);

	gt_event_send(dialog3,GT_EVENT_TYPE_NOTIFY_CLOSE,"1");
	if(number <= 0)
		img1_0_cb(NULL);
}





static void Up(gt_event_st * e){
	char buffer[30];
	if(sg_nowpage>1)
	{
		sg_nowpage--;
		showpage(0);
	}
	else if(sg_nowpage==1)
	{
		showpage(sg_surplus);
		 sg_nowpage=sg_maxpage;
	}
	else if(sg_nowpage==sg_maxpage)
	{
		 sg_nowpage--;
		showpage(0);
	}
	sprintf(buffer,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab2, buffer);

	fineDrugNode_four_ById(sg_nowpage*4+32);
	//更新内容
	gt_label_set_text(lab3, drugname1);
	gt_label_set_text(lab4, drugname2);
	gt_label_set_text(lab5, drugname3);
	gt_label_set_text(lab6, drugname4);

}

static void back(gt_event_st * e) {
	gt_event_send(dialog3,GT_EVENT_TYPE_NOTIFY_CLOSE,"1");
}


static void Down(gt_event_st * e){
	char buffer[30];
	if(sg_nowpage<sg_maxpage-1)  //这个用来控制最后一页显示
	{
		sg_nowpage++;
		showpage(0);
	}
	else if(sg_nowpage==sg_maxpage-1)
	{
		showpage(sg_surplus);
		sg_nowpage++;
	}
	else if(sg_nowpage==sg_maxpage&&sg_nowpage!=1)
	{
		sg_nowpage=1;
		showpage(0);
	}
	else if(sg_nowpage==sg_maxpage&&sg_nowpage==1)
	{
		sg_nowpage=1;
		showpage(sg_surplus);
	}
	sprintf(buffer,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab2, buffer);
	fineDrugNode_four_ById(sg_nowpage*4+32);
	//更新内容
	gt_label_set_text(lab3, drugname1);
	gt_label_set_text(lab4, drugname2);
	gt_label_set_text(lab5, drugname3);
	gt_label_set_text(lab6, drugname4);

}


gt_obj_st * _dialog3_init(gt_event_st * e) {
		

	/** dialog3 */
	dialog3 = gt_dialog_create(false);
	gt_obj_set_pos(dialog3, 120, 90);
	gt_obj_set_size(dialog3, 240, 130);
	gt_dialog_set_bgcolor(dialog3, gt_color_hex(0xffffff));
	gt_dialog_set_border_color(dialog3, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog3, 3);
	gt_dialog_set_border_radius(dialog3, 0);
	//gt_dialog_set_outside_auto_hide(dialog3,true);


	/** btn3 */
	btn3 = gt_btn_create(dialog3);
	gt_obj_set_pos(btn3, 135, 160);
	gt_obj_set_size(btn3, 90, 50);
	gt_btn_set_font_color(btn3, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn3, 24);
	gt_btn_set_font_family_cn(btn3, 20);
	gt_btn_set_font_family_en(btn3, 33);
	gt_btn_set_font_family_fl(btn3, 50);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, title[SystemSetting.langue][2]);
	gt_btn_set_color_background(btn3, gt_color_hex(0x0097e6));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0xc0c0c0));
	gt_btn_set_radius(btn3, 4);
	gt_obj_add_event_cb(btn3, back, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** btn4 */
	btn4 = gt_btn_create(dialog3);
	gt_obj_set_pos(btn4, 255, 160);
	gt_obj_set_size(btn4, 90, 50);
	gt_btn_set_font_color(btn4, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn4, 24);
	gt_btn_set_font_family_cn(btn4, 20);
	gt_btn_set_font_family_en(btn4, 33);
	gt_btn_set_font_family_fl(btn4, 50);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn4, title[SystemSetting.langue][3]);
	gt_btn_set_color_background(btn4, gt_color_hex(0x0097e6));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0xc0c0c0));
	gt_btn_set_radius(btn4, 4);
	gt_obj_add_event_cb(btn4, Drugaffirm, GT_EVENT_TYPE_INPUT_PRESSED, e->user_data);


	/** lab12 */
	lab12 = gt_label_create(dialog3);
	gt_obj_set_pos(lab12, 120, 115);
	gt_obj_set_size(lab12, 240, 35);
	gt_label_set_font_color(lab12, gt_color_hex(0x000000));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_cn(lab12, 20);
	gt_label_set_font_family_en(lab12, 33);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab12, title[SystemSetting.langue][1]);

	

	gt_dialog_show(dialog3);
	
	return dialog3;
}

gt_obj_st * gt_init_DrugDelete(void)
{
	int number=getNowDrugListNum();
	number=number-35;
	char buffer[50];

	if(number%4==0)   //确定sg_和surplus
	{
		if(number==0)
			sg_maxpage=1;
		sg_maxpage=number/4;
	}
	else
		sg_maxpage=number/4+1;
											
	sg_surplus=number%4;


	sg_nowpage = 1;

	
	DrugNode_t* tempnode = fineDrugNodeByPosit(36);
	DrugNodelangue(drugname1,tempnode); 

	tempnode=fineDrugNodeByPosit(37);
	DrugNodelangue(drugname2,tempnode); 

	tempnode=fineDrugNodeByPosit(38);
	DrugNodelangue(drugname3,tempnode); 

	tempnode=fineDrugNodeByPosit(39);
	DrugNodelangue(drugname4,tempnode); 

	DrugDelete = gt_obj_create(NULL);
	gt_screen_set_bgcolor(DrugDelete, gt_color_hex(0x000000));
	my_set_obj_title(DrugDelete,title[SystemSetting.langue][0]);

	/** img1 */
	img1 = gt_img_create(DrugDelete);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(DrugDelete);
	gt_obj_set_pos(svg1, 415, 65);
	gt_obj_set_size(svg1, 65, 65);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg1,Up,GT_EVENT_TYPE_INPUT_RELEASED,NULL);

	/** svg2 */
	svg2 = gt_img_create(DrugDelete);
	gt_obj_set_pos(svg2, 415, 220);
	gt_obj_set_size(svg2, 65, 65);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg2, Down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab3 */
	lab3 = gt_label_create(DrugDelete);
	gt_obj_set_pos(lab3, 90, 65);
	gt_obj_set_size(lab3, 300, 50);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, drugname1);


	/** lab4 */
	lab4 = gt_label_create(DrugDelete);
	gt_obj_set_pos(lab4, 90, 125);
	gt_obj_set_size(lab4, 300, 50);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, drugname2);


	/** lab5 */
	lab5 = gt_label_create(DrugDelete);
	gt_obj_set_pos(lab5, 90, 185);
	gt_obj_set_size(lab5, 300, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, drugname3);


	/** lab6 */
	lab6 = gt_label_create(DrugDelete);
	gt_obj_set_pos(lab6, 90, 245);
	gt_obj_set_size(lab6, 300, 50);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, drugname4);


	/** rect2 */
	rect2 = gt_rect_create(DrugDelete);
	gt_obj_set_pos(rect2, 90, 65);
	gt_obj_set_size(rect2, 300, 50);
	gt_obj_set_opa(rect2, GT_OPA_41);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, _dialog3_init, GT_EVENT_TYPE_INPUT_RELEASED, "1");

	/** rect3 */
	rect3 = gt_rect_create(DrugDelete);
	gt_obj_set_pos(rect3, 90, 125);
	gt_obj_set_size(rect3, 300, 50);
	gt_obj_set_opa(rect3, GT_OPA_38);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, _dialog3_init, GT_EVENT_TYPE_INPUT_RELEASED, "2");


	/** rect4 */
	rect4 = gt_rect_create(DrugDelete);
	gt_obj_set_pos(rect4, 90, 185);
	gt_obj_set_size(rect4, 300, 50);
	gt_obj_set_opa(rect4, GT_OPA_41);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, _dialog3_init, GT_EVENT_TYPE_INPUT_RELEASED, "3");


	/** rect5 */
	rect5 = gt_rect_create(DrugDelete);
	gt_obj_set_pos(rect5, 90, 245);
	gt_obj_set_size(rect5, 300, 50);
	gt_obj_set_opa(rect5, GT_OPA_37);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, _dialog3_init, GT_EVENT_TYPE_INPUT_RELEASED, "4");

	/** lab2 */
	lab2 = gt_label_create(DrugDelete);
	gt_obj_set_pos(lab2, 420, 146);
	gt_obj_set_size(lab2, 55, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"1/%d",sg_maxpage);
	gt_label_set_text(lab2, buffer);

	if(sg_maxpage == 1)
	{
		showpage(sg_surplus);
	}
	else
	{
		showpage(0);
	}

	return DrugDelete;
}

