#include "ui.h"
#include "library_history.h"

/** HistoryView */
gt_obj_st * HistoryView = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * lab16 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;


static const char title[5][1][50]={
	"历史记录",

	"History Record",

	"Registro de Historia",

	"歷史記錄",

	"Registro Histórico"
		
};

static int sg_maxpage;      //最大页数
static int sg_nowpage;		//当前页数
static int sg_surplus;		//剩余


static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}
static void showpage(unsigned int Surplus)  //用来帮助显示最后一页
{
	switch(Surplus)
	{
		case 5:
			gt_obj_set_visible(lab1,GT_INVISIBLE);
			gt_obj_set_visible(lab2,GT_INVISIBLE);
			gt_obj_set_visible(lab3,GT_INVISIBLE);
			gt_obj_set_visible(lab4,GT_INVISIBLE);
			gt_obj_set_visible(lab5,GT_INVISIBLE);
			gt_obj_set_visible(lab6,GT_INVISIBLE);
			gt_obj_set_visible(lab7,GT_INVISIBLE);
			gt_obj_set_visible(lab8,GT_INVISIBLE);
			gt_obj_set_visible(lab9,GT_INVISIBLE);
			gt_obj_set_visible(lab10,GT_INVISIBLE);
			gt_obj_set_visible(lab11,GT_INVISIBLE);
			gt_obj_set_visible(lab12,GT_INVISIBLE);
			gt_obj_set_visible(lab13,GT_INVISIBLE);
			gt_obj_set_visible(lab14,GT_INVISIBLE);
			gt_obj_set_visible(lab15,GT_INVISIBLE);
			break;
		case 1:
			gt_obj_set_visible(lab4,GT_INVISIBLE);
			gt_obj_set_visible(lab5,GT_INVISIBLE);
			gt_obj_set_visible(lab6,GT_INVISIBLE);
		case 2:
			gt_obj_set_visible(lab7,GT_INVISIBLE);
			gt_obj_set_visible(lab8,GT_INVISIBLE);
			gt_obj_set_visible(lab9,GT_INVISIBLE);
		case 3:
			gt_obj_set_visible(lab10,GT_INVISIBLE);
			gt_obj_set_visible(lab11,GT_INVISIBLE);
			gt_obj_set_visible(lab12,GT_INVISIBLE);
		case 4:
			gt_obj_set_visible(lab13,GT_INVISIBLE);
			gt_obj_set_visible(lab14,GT_INVISIBLE);
			gt_obj_set_visible(lab15,GT_INVISIBLE);
			break;
		case 0:
			gt_obj_set_visible(lab1,GT_VISIBLE);
			gt_obj_set_visible(lab2,GT_VISIBLE);
			gt_obj_set_visible(lab3,GT_VISIBLE);
			gt_obj_set_visible(lab4,GT_VISIBLE);
			gt_obj_set_visible(lab5,GT_VISIBLE);
			gt_obj_set_visible(lab6,GT_VISIBLE);
			gt_obj_set_visible(lab7,GT_VISIBLE);
			gt_obj_set_visible(lab8,GT_VISIBLE);
			gt_obj_set_visible(lab9,GT_VISIBLE);
			gt_obj_set_visible(lab10,GT_VISIBLE);
			gt_obj_set_visible(lab11,GT_VISIBLE);
			gt_obj_set_visible(lab12,GT_VISIBLE);
			gt_obj_set_visible(lab13,GT_VISIBLE);
			gt_obj_set_visible(lab14,GT_VISIBLE);
			gt_obj_set_visible(lab15,GT_VISIBLE);
			break;
	}
}


/* 历史记录上翻页 */
static void Up(gt_event_st * e){
	char buffer[50];
	if(sg_nowpage>1)
	{
		sg_nowpage--;
		showpage(0);
	}
	else if(sg_nowpage==1) //上翻页溢出
	{
		showpage(sg_surplus);
		sg_nowpage=sg_maxpage;
	}
	else if(sg_nowpage==sg_maxpage)
	{
		sg_nowpage--;
		showpage(0);
	}
	printf("up sg_maxpage:%d  sg_nowpage:%d  sg_surplus:%d\r\n",sg_maxpage,sg_nowpage,sg_surplus);
	
	sprintf(buffer,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab16, buffer);

	get_history_info(sg_nowpage);	
	
	//更新内容
	gt_label_set_text(lab1, historytime1);
	gt_label_set_text(lab2, historyname1);
	sprintf(buffer,"%s%s",historyname6,historyData1);
	gt_label_set_text(lab3, buffer);
	gt_label_set_text(lab4, historytime2);
	gt_label_set_text(lab5, historyname2);
	sprintf(buffer,"%s%s",historyname7,historyData2);
	gt_label_set_text(lab6, buffer);
	gt_label_set_text(lab7, historytime3);
	gt_label_set_text(lab8, historyname3);
	sprintf(buffer,"%s%s",historyname8,historyData3);
	gt_label_set_text(lab9, buffer);
	gt_label_set_text(lab10, historytime4);
	gt_label_set_text(lab11, historyname4);
	sprintf(buffer,"%s%s",historyname9,historyData4);
	gt_label_set_text(lab12, buffer);
	gt_label_set_text(lab13, historytime5);
	gt_label_set_text(lab14, historyname5);
	sprintf(buffer,"%s%s",historyname10,historyData5);
	gt_label_set_text(lab15, buffer);
}

/* 历史记录下翻页 */
static void Down(gt_event_st * e){
	char buffer[50];
	


   if (sg_nowpage < sg_maxpage - 1) {    // 当前页小于倒数第二页
        sg_nowpage++;
        showpage(0);
    } else if (sg_nowpage == sg_maxpage - 1) {  // 当前页是倒数第二页
        sg_nowpage++;
        showpage(sg_surplus);
    } else if (sg_nowpage == sg_maxpage) {  // 当前页是最后一页
        sg_nowpage = 1;
        showpage(0);
    }

	printf("Down sg_maxpage:%d  sg_nowpage:%d  sg_surplus:%d\r\n",sg_maxpage,sg_nowpage,sg_surplus);

	sprintf(buffer,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab16, buffer);

	get_history_info(sg_nowpage);
	
	//更新内容
	gt_label_set_text(lab1, historytime1);
	gt_label_set_text(lab2, historyname1);
	sprintf(buffer,"%s%s",historyname6,historyData1);
	gt_label_set_text(lab3, buffer);

	gt_label_set_text(lab4, historytime2);
	gt_label_set_text(lab5, historyname2);
	sprintf(buffer,"%s%s",historyname7,historyData2);
	gt_label_set_text(lab6, buffer);

	gt_label_set_text(lab7, historytime3);
	gt_label_set_text(lab8, historyname3);
	sprintf(buffer,"%s%s",historyname8,historyData3);
	gt_label_set_text(lab9, buffer);

	gt_label_set_text(lab10, historytime4);
	gt_label_set_text(lab11, historyname4);
	sprintf(buffer,"%s%s",historyname9,historyData4);
	gt_label_set_text(lab12, buffer);
	
	gt_label_set_text(lab13, historytime5);
	gt_label_set_text(lab14, historyname5);
	sprintf(buffer,"%s%s",historyname10,historyData5);
	gt_label_set_text(lab15, buffer);
}

extern HistoryNodeMessage HistoryNodeMessage_buff[5];
gt_obj_st * gt_init_HistoryView(void)
{
	char buffer[50];
	
	printf("show history interface\r\n");
	
	flash_read(ParamSetting_Flash_ADDRESS_START,(uint16_t *)&ParamSetting,sizeof(Param_SettingType)/2);
	
	int number = ParamSetting.historynumber;
	printf("Number of historical records:%d\r\n",number);
	
	if(number%5==0)   //确定sg_和surplus
	{
		if(number==0)
			sg_maxpage=1;
		sg_maxpage=number/5;
	}
	else
		sg_maxpage=number/5+1;
											
	sg_surplus=number%5;
	
	sg_nowpage = 1;
	printf("sg_maxpage:%d  sg_nowpage:%d  sg_surplus:%d\r\n",sg_maxpage,sg_nowpage,sg_surplus);

	get_history_info(sg_nowpage);
	
	
	if(sg_maxpage==sg_nowpage==1)
	{
		 switch(sg_surplus)
	   { 
		case 1:

		     history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[0]);
			 break;
		case 2:

		     history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[0]);

		     history_info_langue(historytime2,historyname2,historyname7,historyData2,&HistoryNodeMessage_buff[1]);
			 break;
		case 3:

			 history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[0]);		

		     history_info_langue(historytime2,historyname2,historyname7,historyData2,&HistoryNodeMessage_buff[1]);
			
		     history_info_langue(historytime3,historyname3,historyname8,historyData3,&HistoryNodeMessage_buff[2]);
			break;
		case 4:

			 history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[0]);	

		     history_info_langue(historytime2,historyname2,historyname7,historyData2,&HistoryNodeMessage_buff[1]);
			
		     history_info_langue(historytime3,historyname3,historyname8,historyData3,&HistoryNodeMessage_buff[2]);

		     history_info_langue(historytime4,historyname4,historyname9,historyData4,&HistoryNodeMessage_buff[3]);
			break;

		case 0:

			 history_info_langue(historytime1,historyname1,historyname6,historyData1,&HistoryNodeMessage_buff[0]);	

		     history_info_langue(historytime2,historyname2,historyname7,historyData2,&HistoryNodeMessage_buff[1]);
			
		     history_info_langue(historytime3,historyname3,historyname8,historyData3,&HistoryNodeMessage_buff[2]);

		     history_info_langue(historytime4,historyname4,historyname9,historyData4,&HistoryNodeMessage_buff[3]);
			
		     history_info_langue(historytime5,historyname5,historyname10,historyData5,&HistoryNodeMessage_buff[4]);
			break;
	   }
	}
	
	HistoryView = gt_obj_create(NULL);
	gt_screen_set_bgcolor(HistoryView, gt_color_hex(0x000000));
	my_set_obj_title(HistoryView,title[SystemSetting.langue][0]);

	


	/** img1 */
	img1 = gt_img_create(HistoryView);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 75, 65);
	gt_img_set_src(img1, "f:img_75x65_12_enter_left.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg1 */
	svg1 = gt_img_create(HistoryView);
	gt_obj_set_pos(svg1, 415, 255);
	gt_obj_set_size(svg1, 65, 65);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_down_2_16.png");
	gt_obj_add_event_cb(svg1,Down,GT_EVENT_TYPE_INPUT_RELEASED,NULL);


	/** svg2 */
	svg2 = gt_img_create(HistoryView);
	gt_obj_set_pos(svg2, 245, 255);
	gt_obj_set_size(svg2, 65, 65);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_up_2_15.png");
	gt_obj_add_event_cb(svg2, Up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	

	lab1 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab1, 0, 57);
	gt_obj_set_size(lab1, 140, 35);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 9);
	gt_label_set_font_family_en(lab1, 30);
	gt_label_set_font_family_fl(lab1, 50);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, historytime1);

	lab2 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab2, 125, 57);
	gt_obj_set_size(lab2, 70, 35);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 9);
	gt_label_set_font_family_en(lab2, 30);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, historyname1);

	lab3 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab3, 190, 57);
	gt_obj_set_size(lab3, 240, 35);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 9);
	gt_label_set_font_family_en(lab3, 30);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT_MID);
	if(*historyData1){
		sprintf(buffer,"%s%s",historyname6,historyData1);
//		printf("%s",buffer);
		gt_label_set_text(lab3,buffer);
	}
	else
		gt_label_set_text(lab3,historyname6);
//		printf("%s",historyname6);

	lab4 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab4, 0, 99);
	gt_obj_set_size(lab4, 140, 35);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 9);
	gt_label_set_font_family_en(lab4, 30);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4,historytime2);

	lab5 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab5, 125, 99);
	gt_obj_set_size(lab5, 70, 35);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 16);
	gt_label_set_font_family_cn(lab5, 9);
	gt_label_set_font_family_en(lab5, 30);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, historyname2);

	lab6 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab6, 190, 99);
	gt_obj_set_size(lab6, 240, 35);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 16);
	gt_label_set_font_family_cn(lab6, 9);
	gt_label_set_font_family_en(lab6, 30);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	if(*historyData2){
		sprintf(buffer,"%s%s",historyname7,historyData2);
		gt_label_set_text(lab6,buffer);
	}
	else 
		gt_label_set_text(lab6,historyname7);
	

	lab7 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab7, 0, 141);
	gt_obj_set_size(lab7, 140, 35);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 16);
	gt_label_set_font_family_cn(lab7, 9);
	gt_label_set_font_family_en(lab7, 30);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, historytime3);

	lab8 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab8, 125, 141);
	gt_obj_set_size(lab8, 70, 35);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 16);
	gt_label_set_font_family_cn(lab8, 9);
	gt_label_set_font_family_en(lab8, 30);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab8, historyname3);

	lab9 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab9, 190, 141);
	gt_obj_set_size(lab9, 240, 35);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 16);
	gt_label_set_font_family_cn(lab9, 9);
	gt_label_set_font_family_en(lab9, 30);
	gt_label_set_font_family_fl(lab9, 50);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT_MID);
	if(*historyData3){
		sprintf(buffer,"%s%s",historyname8,historyData3);
		gt_label_set_text(lab9,buffer);
	}
	else 
		gt_label_set_text(lab9,historyname8);
	

	lab10 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab10, 0, 183);
	gt_obj_set_size(lab10, 140, 35);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 16);
	gt_label_set_font_family_cn(lab10, 9);
	gt_label_set_font_family_en(lab10, 30);
	gt_label_set_font_family_fl(lab10, 50);
	gt_label_set_font_align(lab10, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab10,historytime4);

	lab11 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab11, 125, 183);
	gt_obj_set_size(lab11, 70, 35);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 16);
	gt_label_set_font_family_cn(lab11, 9);
	gt_label_set_font_family_en(lab11, 30);
	gt_label_set_font_family_fl(lab11, 50);
	gt_label_set_font_align(lab11, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab11, historyname4);

	lab12 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab12, 190, 183);
	gt_obj_set_size(lab12, 240, 35);
	gt_label_set_font_color(lab12, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab12, 16);
	gt_label_set_font_family_cn(lab12, 9);
	gt_label_set_font_family_en(lab12, 30);
	gt_label_set_font_family_fl(lab12, 50);
	gt_label_set_font_align(lab12, GT_ALIGN_LEFT_MID);
	if(*historyData4){
		sprintf(buffer,"%s%s",historyname9,historyData4);
		gt_label_set_text(lab12,buffer);
	}
	else
		gt_label_set_text(lab12,historyname9);


	lab13 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab13, 0, 225);
	gt_obj_set_size(lab13, 140, 35);
	gt_label_set_font_color(lab13, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab13, 16);
	gt_label_set_font_family_cn(lab13, 9);
	gt_label_set_font_family_en(lab13, 30);
	gt_label_set_font_family_fl(lab13, 50);
	gt_label_set_font_align(lab13, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab13,historytime5);

	lab14 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab14, 125, 225);
	gt_obj_set_size(lab14, 70, 35);
	gt_label_set_font_color(lab14, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab14, 16);
	gt_label_set_font_family_cn(lab14, 9);
	gt_label_set_font_family_en(lab14, 30);
	gt_label_set_font_family_fl(lab14, 50);
	gt_label_set_font_align(lab14, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab14, historyname5);

	lab15 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab15, 190, 225);
	gt_obj_set_size(lab15, 240, 35);
	gt_label_set_font_color(lab15, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab15, 16);
	gt_label_set_font_family_cn(lab15, 9);
	gt_label_set_font_family_en(lab15, 30);
	gt_label_set_font_family_fl(lab15, 50);
	gt_label_set_font_align(lab15, GT_ALIGN_LEFT_MID);
	if(*historyData5){
		sprintf(buffer,"%s%s",historyname10,historyData5);
		gt_label_set_text(lab15,buffer);
	}else
		gt_label_set_text(lab15,historyname10);


	lab16 = gt_label_create(HistoryView);
	gt_obj_set_pos(lab16, 340, 270);
	gt_obj_set_size(lab16, 60, 35);
	gt_label_set_font_color(lab16, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab16, 16);
	gt_label_set_font_family_en(lab16, 30);
	gt_label_set_font_family_cn(lab16, 9);
	gt_label_set_font_family_fl(lab16, 50);
	gt_label_set_font_align(lab16, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"1/%d",sg_maxpage);
	gt_label_set_text(lab16, buffer);

	if(sg_maxpage == 1)
		showpage(sg_surplus);
	else if(number == 0)
		showpage(5);
	else
		showpage(0);

	return HistoryView;
}

