#include "ui.h"
#include "infusion.h"



static const char title[5][1][50]={
	"输液器选择",

	"Select IV Set Brand",

	"Seleccionar IV Set Marca",

	"輸液器選擇",

	"Selecionar marca de equipo"
		
};

static int sg_maxpage;
static int sg_nowpage;
static int sg_surplus;

static int RecData = 0 ;
static char buffer[30];


/** BrandChoice2 */
gt_obj_st * BrandChoice2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * svg1 = NULL;
static gt_obj_st * svg2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * img1 = NULL;
int BrandSerialNumber;

static void showpage(unsigned int Surplus)  //用来帮助显示最后一页
{
	switch(Surplus)
	{
		case 1:
			gt_obj_set_visible(lab3,GT_INVISIBLE);
			gt_obj_set_visible(rect3,GT_INVISIBLE);
		case 2:
			gt_obj_set_visible(lab4,GT_INVISIBLE);
			gt_obj_set_visible(rect4,GT_INVISIBLE);
		case 3:
			gt_obj_set_visible(lab5,GT_INVISIBLE);
			gt_obj_set_visible(rect5,GT_INVISIBLE);
		case 4:
			gt_obj_set_visible(lab6,GT_INVISIBLE);
			gt_obj_set_visible(rect6,GT_INVISIBLE);
		case 5:
			gt_obj_set_visible(lab7,GT_INVISIBLE);
			gt_obj_set_visible(rect7,GT_INVISIBLE);
			break;
		case 0:
			gt_obj_set_visible(lab7,GT_VISIBLE);
			gt_obj_set_visible(lab6,GT_VISIBLE);
			gt_obj_set_visible(lab5,GT_VISIBLE);
			gt_obj_set_visible(lab4,GT_VISIBLE);
			gt_obj_set_visible(lab3,GT_VISIBLE);
			gt_obj_set_visible(lab2,GT_VISIBLE);
			gt_obj_set_visible(rect2,GT_VISIBLE);
			gt_obj_set_visible(rect3,GT_VISIBLE);
			gt_obj_set_visible(rect4,GT_VISIBLE);
			gt_obj_set_visible(rect5,GT_VISIBLE);
			gt_obj_set_visible(rect6,GT_VISIBLE);
			gt_obj_set_visible(rect7,GT_VISIBLE);
			break;
	}
}


static void Choice(gt_event_st * e) {
	uint8_t temp;  //表明被选择的是哪个品牌
	int id;
	gt_obj_st * target_scr;
	/*
		要再乘上页数 来具体表明是哪个输液器品牌
	*/ 
	temp= atoi(e->user_data);
	//还要读出品牌信息赋值给变量从而修改
	BrandSerialNumber = temp*sg_nowpage;
	InfusionNode_t* tempnode = fineInfusionNodeByPosit(temp*sg_nowpage);
	//取出内容
	infusion_data.Calibdata1 = tempnode->message.Calibdata1;
	infusion_data.Calibdata2 = tempnode->message.Calibdata2;
	infusion_data.Pressure_AD0 = tempnode->message.AD0;
	infusion_data.Pressure_AD40 = tempnode->message.AD40;
	infusion_data.Pressure_AD70 = tempnode->message.AD70;
	infusion_data.Pressure_AD120 = tempnode->message.AD120;
	infusion_data.Pressure_value40 = tempnode->message.P40;
	infusion_data.Pressure_value70 = tempnode->message.P70;
	infusion_data.Pressure_value120 = tempnode->message.P120;



	if(RecData == BrandCome1)
	{
		id = GT_SCR_ID_50;
	}
	else if(RecData == BrandCome2)
	{
		id = GT_SCR_ID_54;
	}
	else if(RecData == BrandCome3)
	{
		id = GT_SCR_ID_61;
	}
	else if(RecData == BrandCome4)
	{
		id = GT_SCR_ID_55;
	}
	else
	{
		;
	}
	
	gt_disp_stack_load_scr_anim(id, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void back(gt_event_st * e){
	gt_disp_stack_go_back(1);	
};


static void Up(gt_event_st* e){
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
	gt_label_set_text(lab8, buffer);

	fineInfusionNode_six_ById(sg_nowpage*6-6);
	//更新内容
	gt_label_set_text(lab2, tubename1);
	gt_label_set_text(lab3, tubename2);
	gt_label_set_text(lab4, tubename3);
	gt_label_set_text(lab5, tubename4);
	gt_label_set_text(lab6, tubename5);
	gt_label_set_text(lab7, tubename6);
}

static void Down(gt_event_st* e){
	char buff[30];
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
	sprintf(buff,"%d/%d",sg_nowpage,sg_maxpage);
	gt_label_set_text(lab8, buff);

	fineInfusionNode_six_ById(sg_nowpage*6-6);
	//更新内容
	gt_label_set_text(lab2, tubename1);
	gt_label_set_text(lab3, tubename2);
	gt_label_set_text(lab4, tubename3);
	gt_label_set_text(lab5, tubename4);
	gt_label_set_text(lab6, tubename5);
	gt_label_set_text(lab7, tubename6);
}

static void EventUpdata(gt_event_st * e)
{
	if(atoi(e->param) == 1)
	{
		RecData = 1;
	}
	else if(atoi(e->param) == 2)
	{
		RecData = 2;
	}
	else if(atoi(e->param) == 3)
	{
		RecData = 3;
	}
	else if(atoi(e->param) == 4)
	{
		RecData = 4;
	}
}


//需要接收是从哪里进来的
gt_obj_st * gt_init_BrandChoice2()
{
	int number=getNowInfusionListNum();

	if(number%6==0)   //确定sg_和surplus
	{
		if(number==0)
			sg_maxpage=1;
		else
			sg_maxpage=number/6;
	}
	else
		sg_maxpage=number/6+1;
											
	sg_surplus=number%6;


	sg_nowpage = 1;

	InfusionNode_t* tempnode = fineInfusionNodeByPosit(sg_nowpage*6-5);
	InfusionNodelangue(tubename1,tempnode);

	tempnode=fineInfusionNodeByPosit(sg_nowpage*6-4);
	InfusionNodelangue(tubename2,tempnode);

	tempnode=fineInfusionNodeByPosit(sg_nowpage*6-3);
	InfusionNodelangue(tubename3,tempnode);

	tempnode=fineInfusionNodeByPosit(sg_nowpage*6-2);
	InfusionNodelangue(tubename4,tempnode);

	tempnode=fineInfusionNodeByPosit(sg_nowpage*6-1);
	InfusionNodelangue(tubename5,tempnode);

	tempnode=fineInfusionNodeByPosit(sg_nowpage*6);
	InfusionNodelangue(tubename6,tempnode);

	BrandChoice2 =  gt_obj_create(NULL);
	my_set_obj_title(BrandChoice2,title[SystemSetting.langue][0]);
	gt_screen_set_bgcolor(BrandChoice2, gt_color_hex(0x000000));
	gt_obj_add_event_cb(BrandChoice2, EventUpdata, MY_EVENT_UPDATA, NULL);
	calibrate = false;

	RecData = brandchoice2_from;

	/** lab2 */
	lab2 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab2, 75, 65);
	gt_obj_set_size(lab2, 135, 60);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 20);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_family_fl(lab2, 50);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, tubename1);


	/** lab3 */
	lab3 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab3, 230, 65);
	gt_obj_set_size(lab3, 135, 60);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 20);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_family_fl(lab3, 50);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, tubename2);


	/** lab4 */
	lab4 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab4, 75, 145);
	gt_obj_set_size(lab4, 135, 60);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 20);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_family_fl(lab4, 50);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4,tubename3);


	/** lab5 */
	lab5 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab5, 230, 145);
	gt_obj_set_size(lab5, 135, 60);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 20);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_family_fl(lab5, 50);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, tubename4);


	/** lab6 */
	lab6 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab6, 75, 225);
	gt_obj_set_size(lab6, 135, 60);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 20);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_family_fl(lab6, 50);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, tubename5);


	/** lab7 */
	lab7 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab7, 230, 225);
	gt_obj_set_size(lab7, 135, 60);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 20);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_family_fl(lab7, 50);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, tubename6);


	/** rect2 */
	rect2 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect2, 75, 65);
	gt_obj_set_size(rect2, 135, 60);
	gt_obj_set_opa(rect2, GT_OPA_50);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x778899));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 4);
	gt_obj_add_event_cb(rect2, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "1");


	/** rect3 */
	rect3 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect3, 230, 65);
	gt_obj_set_size(rect3, 135, 60);
	gt_obj_set_opa(rect3, GT_OPA_50);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect3, gt_color_hex(0x778899));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 4);
	gt_obj_add_event_cb(rect3, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "2");


	/** rect4 */
	rect4 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect4, 75, 145);
	gt_obj_set_size(rect4, 135, 60);
	gt_obj_set_opa(rect4, GT_OPA_50);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect4, gt_color_hex(0x778899));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 4);
	gt_obj_add_event_cb(rect4, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "3");


	/** rect5 */
	rect5 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect5, 230, 145);
	gt_obj_set_size(rect5, 135, 60);
	gt_obj_set_opa(rect5, GT_OPA_50);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect5, gt_color_hex(0x778899));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 4);
	gt_obj_add_event_cb(rect5, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "4");


	/** rect6 */
	rect6 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect6, 75, 225);
	gt_obj_set_size(rect6, 135, 60);
	gt_obj_set_opa(rect6, GT_OPA_50);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect6, gt_color_hex(0x778899));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 4);
	gt_obj_add_event_cb(rect6, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "5");


	/** rect7 */
	rect7 = gt_rect_create(BrandChoice2);
	gt_obj_set_pos(rect7, 230, 225);
	gt_obj_set_size(rect7, 135, 60);
	gt_obj_set_opa(rect7, GT_OPA_50);
	gt_rect_set_radius(rect7, 0);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect7, gt_color_hex(0x778899));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 4);
	gt_obj_add_event_cb(rect7, Choice, GT_EVENT_TYPE_INPUT_RELEASED, "6");


	/** svg1 */
	svg1 = gt_img_create(BrandChoice2);
	gt_obj_set_pos(svg1, 405, 230);
	gt_obj_set_size(svg1, 50, 50);
	gt_img_set_src(svg1, "f:img_65x65_arrow_circle_down_22_14.png");
	gt_obj_add_event_cb(svg1, Down, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** svg2 */
	svg2 = gt_img_create(BrandChoice2);
	gt_obj_set_pos(svg2, 405, 70);
	gt_obj_set_size(svg2, 50, 50);
	gt_img_set_src(svg2, "f:img_65x65_arrow_circle_up_22_15.png");
	gt_obj_add_event_cb(svg1, Up, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab8 */
	lab8 = gt_label_create(BrandChoice2);
	gt_obj_set_pos(lab8, 394, 158);
	gt_obj_set_size(lab8, 80, 36);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_en(lab8, 33);
	gt_label_set_font_family_cn(lab8, 20);
	gt_label_set_font_family_fl(lab8, 50);
	gt_label_set_font_align(lab8, GT_ALIGN_CENTER_MID);
	sprintf(buffer,"1/%d",sg_maxpage);
	gt_label_set_text(lab8, buffer);

	if(sg_maxpage == 1)
	{
		showpage(sg_surplus);
	}
	else
	{
		showpage(0);
	}


	/** img1 */
	img1 = gt_img_create(BrandChoice2);
	gt_obj_set_pos(img1, 0, 260);
	gt_obj_set_size(img1, 60, 60);
	gt_img_set_src(img1, "f:img_60x60_12_enter_left.png");
	gt_obj_add_event_cb(img1, back, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	return BrandChoice2;
}

