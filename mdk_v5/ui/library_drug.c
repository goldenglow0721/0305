
#include "library_drug.h"
#include "gt.h"
//用链表的形式做 (结构体)




static _Bool drugNodeIsObtain(DrugNode_t * node);

struct drugList* druglist;

char drugname[50];
char drugname1[50];
char drugname2[50];
char drugname3[50];
char drugname4[50];

/*        Labrary function     */

void initDrugList()
{
    static DrugList li;
    druglist = &li;
    druglist->node = NULL;
    druglist->node_number = 0;
}

void destroyDrugList()
{
    druglist->node_number = 0;
    DrugNode_t* node = druglist->node;
    DrugNode_t* ntemp;

    while(node)
    {   
        //从头 往后释放
        ntemp = node;
        node = node->nextnode;
        free(ntemp);
    }
    druglist->node = NULL;
}

//尾插法 readflash使用
_Bool addDrugNode(DrugNode_t* newnode,_Bool flag)
{    
    if(druglist->node && newnode)
    {
        DrugNode_t * n = druglist->node;  //取出第一个节点


        while(n->nextnode)//有下个节点
        {
            n = n->nextnode;
        }
        //到最终节点了
        n->nextnode = newnode; //放到最后
        ++druglist->node_number;  //节点总数加一
        if(flag)
        {
            
            ParamSetting.drugnumber = druglist->node_number;
            WriteParamSettingMessageToFlash();
            WriteDrugListToFlash();
        }
        return true;

    }
    else if(!(druglist->node && newnode)) //如果是第一个节点
    {
        druglist->node = newnode;
        ++druglist->node_number;
        if(flag)
        {
            
            ParamSetting.drugnumber = druglist->node_number;
            WriteParamSettingMessageToFlash();
            WriteDrugListToFlash();
        }
        return true;
    }
    return false;
}

_Bool AddDrugNode(DrugNode_t* newnode,_Bool flag)//添加药品
{	
	//获取节点数量
    if(druglist->node && newnode)
    {
        DrugNode_t * n = druglist->node;  //取出第一个节点
        while(n->nextnode)//有下个节点
        {
            n = n->nextnode;
        }
		int node_count = getNowDrugListNum();
        //到最终节点了
        n->nextnode = newnode; //放到最后
		node_count++;
		
        druglist->node_number = node_count;   //节点总数加一
		
		//printf("added DrugNode druglist->node_number is %d\r\n",druglist->node_number);
		
        if(flag)
        {
            // printf("add\n");
            ParamSetting.drugnumber = druglist->node_number;
            WriteParamSettingMessageToFlash();
            WriteAddDrugListToFlash();
        }
        return true;
    }
	
	
    else if(!(druglist->node && newnode)) //如果是第一个节点
    {
        druglist->node = newnode;
        ++druglist->node_number;
        if(flag)
        {
            //printf("add head\n");
            ParamSetting.drugnumber = druglist->node_number;
            WriteParamSettingMessageToFlash();
            WriteAddDrugListToFlash();
        }
        return true;
    }
    return false;
}


//通过传入的药物名删除节点 (此函数存在错误)
_Bool removeDrugNodeById(char * str,_Bool flag)
{
    DrugNode_t* node=druglist->node;
	DrugNode_t * pNtemp;
	
    if(!strcmp(getTheDrugNodeName(node),str)) //如果是第一个节点
    {
        druglist->node = node->nextnode;
        free(node);
        --druglist->node_number;
        if(flag){
			     ParamSetting.drugnumber = druglist->node_number;
                 WriteParamSettingMessageToFlash();
                 WriteDrugListToFlash();
			    }
        return true;
    }
    
    while(node->nextnode)
    {
        if(!strcmp(getTheDrugNodeName(node),str))
        {
            pNtemp=node->nextnode;
            node->nextnode = node->nextnode->nextnode;
            free(pNtemp);
            --druglist->node_number;
			if(flag){
					ParamSetting.drugnumber = druglist->node_number;
					WriteParamSettingMessageToFlash();
					WriteDrugListToFlash();
			}
           
            return true;
        }

        node=node->nextnode;
    }
    
    return false;
}



///* find Drug name remove */
//_Bool removeDrugNodeById(char *str)
//{
//    if (druglist == NULL || druglist->node == NULL) {
//        return false;
//    }

//    DrugNode_t* node = druglist->node;
//    DrugNode_t* prev = NULL;

//    // 为第一个节点
//    if (!strcmp(getTheDrugNodeName(node), str)) {
//        druglist->node = node->nextnode;
//        free(node);
//        --druglist->node_number;
//        ParamSetting.drugnumber = druglist->node_number;
//        WriteParamSettingMessageToFlash();
//        WriteDrugListToFlash();
//        return true;
//    }

//    // 遍历链表
//    while (node != NULL && node->nextnode != NULL) {
//        if (0 == strcmp(getTheDrugNodeName(node->nextnode), str)) {
//            DrugNode_t* pNtemp = node->nextnode;
//            node->nextnode = node->nextnode->nextnode;
//            free(pNtemp);
//            --druglist->node_number;
//            ParamSetting.drugnumber = druglist->node_number;
//			printf("ParamSetting.drugnumber is %d\r\n",ParamSetting.drugnumber);
//            WriteParamSettingMessageToFlash();
//            WriteDrugListToFlash();
//            return true;
//        }
//        node = node->nextnode;
//    }

//    return false;
//}





//通过id修改指定节点的值
_Bool updataDrugNameById(char * str,DrugNodeMessage message)
{
    DrugNode_t* node= fineDrugNodeById(str);
    if(node)
    {
        node->message = message;
        return true;
    }

    return false;
}

//通过id找到指定节点
DrugNode_t* fineDrugNodeById(char * str)
{
    DrugNode_t* node=druglist->node;
    while(node)
    {
        if(!strcmp(getTheDrugNodeName(node),str))
        {
            return node;
        }
        node = node->nextnode;

    }

    return NULL;
}

//获得药品库链表的第一个节点
DrugNode_t* getThefirstDrugNode()
{
    return druglist->node;
}

/*
	functionname: fineDrugNodeByPosit
	describe:    通过位置找到药物名节点 
	Param1:      位置
	Param2:      
	return: 
	author:		dong
*/
DrugNode_t* fineDrugNodeByPosit(int id)
{
    DrugNode_t* node = druglist->node;
    int posit = 1;
    while(node)
    {
        if(posit == id)
            return node;

        node = node->nextnode;
        posit++;
    }
    return NULL;               // 如果未找到匹配节点，则返回NULL
}

void DrugNodelangue(char* medicine,DrugNode_t* node)
{
    if(SystemSetting.langue==Chinese)
        strcpy(medicine,node->message.ch_name);          
    else if(SystemSetting.langue==English)
        strcpy(medicine,node->message.en_name);
    else if(SystemSetting.langue==Spanish)
        strcpy(medicine,node->message.es_name);
    else if(SystemSetting.langue==Chinese2)
        strcpy(medicine,node->message.ch2_name);
    else if(SystemSetting.langue==Portuguese) 
        strcpy(medicine,node->message.pu_name);
}

/*
	functionname: removeDrugNodeByName
	describe:    通过位置找到接下来的4的药物名 
	Param1:      传入的位置信息
	Param2:      
	return:      4个药物名
	author:		dong
*/
void fineDrugNode_four_ById(int id)
{
    int flag = 0;
    int point = 1;
    DrugNode_t* node = druglist->node;
    while(node)
    {
        if(point == id || flag)
        {
            if(flag  == 0)
            {           
                DrugNodelangue(drugname1,node); 
				printf("drugname1 is %s\r\n",drugname1);
				 flag++;
            }        
            else if(flag == 1)
            {               
                DrugNodelangue(drugname2,node); 
				printf("drugname2 is %s\r\n",drugname2);
				 flag++;
            }
            else if(flag == 2)
            {               
                DrugNodelangue(drugname3,node); 
				printf("drugname3 is %s\r\n",drugname3);
				 flag++;
            }
            else if(flag == 3)
            {             
                DrugNodelangue(drugname4,node); 
				printf("drugname4 is %s\r\n",drugname4);
				flag++;
                return ;
            }      
        }
        node = node->nextnode;
        point++;
    }
}




//获取当前的节点数
int getNowDrugListNum()
{
    return druglist->node_number;
}


//判断是否存在
static _Bool drugNodeIsObtain(DrugNode_t * node)
{
    DrugNode_t * tempnode = druglist->node;

    while(tempnode)
    {
        if(tempnode->message.en_name == node->message.en_name) //比对成功
        {
            return true;
        }
        tempnode = tempnode->nextnode;
    }

    return false;
}





/*    persion function  */

void createDrugLib()
{
    initDrugList(); //初始化链表
    
    //添加药物名字等
    DrugNode_t *newnode1 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode2 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode3 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
	
    DrugNode_t *newnode4 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode5 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    
    DrugNode_t *newnode6 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode7 =(DrugNode_t *)malloc(sizeof(DrugNode_t));

    DrugNode_t *newnode8 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode9 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode10 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
   
    DrugNode_t *newnode11 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode12 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode13 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode14 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode15 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode16 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode17 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode18 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode19 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode20 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode21 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode22 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode23 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode24 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode25 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode26 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode27 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    
    DrugNode_t *newnode28 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode29 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode30 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode31 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode32 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode33 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode34 =(DrugNode_t *)malloc(sizeof(DrugNode_t));
    DrugNode_t *newnode35 =(DrugNode_t *)malloc(sizeof(DrugNode_t));


    DrugNodeMessage message;

    strcpy(message.ch_name,"未选药");
    strcpy(message.en_name,"No medicine selected");
    strcpy(message.es_name,"Ningún medicamento seleccionado");
    strcpy(message.pu_name,"Nenhum medicamento selecionado");
    strcpy(message.ch2_name,"未選藥");

    newnode1->message = message;
    newnode1->nextnode = NULL;
    addDrugNode(newnode1,false);

    strcpy(message.ch_name,"0.9%%氯化钠");
    strcpy(message.en_name,"0.9%%sodium chloride");
    strcpy(message.es_name,"0.9%% Cloruro de sodio ");
    strcpy(message.pu_name,"0.9%%de cloreto de sódio");
    strcpy(message.ch2_name,"0.9%%氯化鈉");

    newnode2->message = message;
    newnode2->nextnode = NULL;
    addDrugNode(newnode2,false);

    strcpy(message.ch_name,"硫酸镁");
    strcpy(message.en_name,"Magnesium sulfate");
    strcpy(message.es_name,"Sulfato de magnesio");
    strcpy(message.pu_name,"Sulfato de magnésio");
    strcpy(message.ch2_name,"硫酸鎂");

    newnode3->message = message;
    newnode3->nextnode = NULL;
    addDrugNode(newnode3,false);

    strcpy(message.ch_name,"5%%葡萄糖");
    strcpy(message.en_name,"5%% Glucose");
    strcpy(message.es_name,"5%% Glucosa");
    strcpy(message.pu_name,"5%% de glicose");
    strcpy(message.ch2_name,"5%%葡萄糖");
   
    newnode4->message = message;
    newnode4->nextnode = NULL;
    addDrugNode(newnode4,false);

    strcpy(message.ch_name,"盐酸多巴胺");
    strcpy(message.en_name,"Dopamine hydrochloride");
    strcpy(message.es_name,"Clorhidrato de dopamina");
    strcpy(message.pu_name,"Cloridrato de dopamina");
    strcpy(message.ch2_name,"鹽酸多巴胺");
    
    newnode5->message = message;
    newnode5->nextnode = NULL;
    addDrugNode(newnode5,false);

    strcpy(message.ch_name,"注射用生长抑素");
    strcpy(message.en_name,"Somatostatin for Injection");
    strcpy(message.es_name,"Somatostatina para inyección");
    strcpy(message.pu_name,"Somatostatina para injeção");
    strcpy(message.ch2_name,"注射用生長抑素");
    
    newnode6->message = message;
    newnode6->nextnode = NULL;
    addDrugNode(newnode6,false);

    strcpy(message.ch_name,"去甲肾上腺素");
    strcpy(message.en_name,"Norepinephrine");
    strcpy(message.es_name,"Norepinefrina");
    strcpy(message.pu_name,"Norepinefrina");
    strcpy(message.ch2_name,"去甲腎上腺素");
    
    newnode7->message = message;
    newnode7->nextnode = NULL;
    addDrugNode(newnode7,false);

    strcpy(message.ch_name,"西地兰");
    strcpy(message.en_name,"Cediland");
    strcpy(message.es_name,"Cedilandia");
    strcpy(message.pu_name,"Cediland");
    strcpy(message.ch2_name,"西地蘭");
    
    newnode8->message = message;
    newnode8->nextnode = NULL;
    addDrugNode(newnode8,false);

    strcpy(message.ch_name,"盐酸多巴酚丁胺");
    strcpy(message.en_name,"Dobutamine Hydrochloride");
    strcpy(message.es_name,"Clorhidrato de dobutamina");
    strcpy(message.pu_name,"Cloridrato de Dobutamina");
    strcpy(message.ch2_name,"鹽酸多巴酚丁胺");
    
    newnode9->message = message;
    newnode9->nextnode = NULL;
    addDrugNode(newnode9,false);

    strcpy(message.ch_name,"10%%浓氯化钠");
    strcpy(message.en_name,"10%% concentrated sodium chloride");
    strcpy(message.es_name,"Cloruro de sodio concentrado al 10%%");
    strcpy(message.pu_name,"Cloreto de sódio concentrado a 10%%");
    strcpy(message.ch2_name,"10%%濃氯化鈉");
    
    newnode10->message = message;
    newnode10->nextnode = NULL;
    addDrugNode(newnode10,false);
 
    strcpy(message.ch_name,"米力农");
    strcpy(message.en_name,"Milrinone");
    strcpy(message.es_name,"Milrinona");
    strcpy(message.pu_name,"Milrinona");
    strcpy(message.ch2_name,"米力農");
    
    newnode11->message = message;
    newnode11->nextnode = NULL;
    addDrugNode(newnode11,false);

    strcpy(message.ch_name,"10%%葡萄糖");
    strcpy(message.en_name,"10%% glucose");
    strcpy(message.es_name,"10%% de glucosa");
    strcpy(message.pu_name,"10%% de glicose");
    strcpy(message.ch2_name,"10%%葡萄糖");
    
    newnode12->message = message;
    newnode12->nextnode = NULL;
    addDrugNode(newnode12,false);

    strcpy(message.ch_name,"肝素钠");
    strcpy(message.en_name,"Heparin Sodium");
    strcpy(message.es_name,"Heparina Sódica");
    strcpy(message.pu_name,"Heparina Sódica");
    strcpy(message.ch2_name,"肝素鈉");
    
    newnode13->message = message;
    newnode13->nextnode = NULL;
    addDrugNode(newnode13,false);

    strcpy(message.ch_name,"灭菌注射用水");
    strcpy(message.en_name,"Sterile water for injection");
    strcpy(message.es_name,"Agua estéril para inyección");
    strcpy(message.pu_name,"Água estéril para injeção");
    strcpy(message.ch2_name,"滅菌注射用水");
    
    newnode14->message = message;
    newnode14->nextnode = NULL;
    addDrugNode(newnode14,false);

    strcpy(message.ch_name,"注射用硝普钠");
    strcpy(message.en_name,"Sodium nitroprusside for injection");
    strcpy(message.es_name,"Nitrógeno de sodio para inyección");
    strcpy(message.pu_name,"Nitroprussiato de sódio para injeção");
    strcpy(message.ch2_name,"注射用硝普鈉");
    
    newnode15->message = message;
    newnode15->nextnode = NULL;
    addDrugNode(newnode15,false);

    strcpy(message.ch_name,"盐酸肾上腺素");
    strcpy(message.en_name,"Epinephrine hydrochloride");
    strcpy(message.es_name,"Clorhidrato de epinefrina");
    strcpy(message.pu_name,"Cloridrato de epinefrina");
    strcpy(message.ch2_name,"鹽酸腎上腺素");
    
    newnode16->message = message;
    newnode16->nextnode = NULL;
    addDrugNode(newnode16,false);

    strcpy(message.ch_name,"呋塞米");
    strcpy(message.en_name,"Furosemide");
    strcpy(message.es_name,"Furosemida");
    strcpy(message.pu_name,"Furosemida");
    strcpy(message.ch2_name,"呋塞米");
    
    newnode17->message = message;
    newnode17->nextnode = NULL;
    addDrugNode(newnode17,false);

    strcpy(message.ch_name,"盐酸利多卡因");
    strcpy(message.en_name,"Lidocaine Hydrochloride");
    strcpy(message.es_name,"Clorhidrato de lidocaína");
    strcpy(message.pu_name,"Cloridrato de Lidocaína");
    strcpy(message.ch2_name,"鹽酸利多卡因");
    
    newnode18->message = message;
    newnode18->nextnode = NULL;
    addDrugNode(newnode18,false);

    strcpy(message.ch_name,"垂体后叶");
    strcpy(message.en_name,"Posterior pituitary");
    strcpy(message.es_name,"Pituitaria posterior");
    strcpy(message.pu_name,"Pituitária posterior");
    strcpy(message.ch2_name,"垂體後葉");
    
    newnode19->message = message;
    newnode19->nextnode = NULL;
    addDrugNode(newnode19,false);

    strcpy(message.ch_name,"盐酸右美托咪定");
    strcpy(message.en_name,"Dexmedetomidine Hydrochloride");
    strcpy(message.es_name,"Clorhidrato de dexmedetomidina");
    strcpy(message.pu_name,"Cloridrato de Dexmedetomidina");
    strcpy(message.ch2_name,"鹽酸右美托咪定");
    
    newnode20->message = message;
    newnode20->nextnode = NULL;
    addDrugNode(newnode20,false);

    strcpy(message.ch_name,"盐酸艾司洛尔");
    strcpy(message.en_name,"Esmolol Hydrochloride");
    strcpy(message.es_name,"Clorhidrato de esmolol");
    strcpy(message.pu_name,"Cloridrato de Esmolol");
    strcpy(message.ch2_name,"鹽酸艾司洛爾");
    
    newnode21->message = message;
    newnode21->nextnode = NULL;
    addDrugNode(newnode21,false);

    strcpy(message.ch_name,"奥硝唑氯化钠");
    strcpy(message.en_name,"Ornidazole Sodium Chloride");
    strcpy(message.es_name,"Cloruro de sodio ornidazol");
    strcpy(message.pu_name,"Cloreto de sódio de ornidazol");
    strcpy(message.ch2_name,"奧硝唑氯化鈉");
    
    newnode22->message = message;
    newnode22->nextnode = NULL;
    addDrugNode(newnode22,false);

    strcpy(message.ch_name,"碳酸氢钠");
    strcpy(message.en_name,"Sodium bicarbonate");
    strcpy(message.es_name,"Bicarbonato de sodio");
    strcpy(message.pu_name,"Bicarbonato de Sódio");
    strcpy(message.ch2_name,"碳酸氫鈉");
    
    newnode23->message = message;
    newnode23->nextnode = NULL;
    addDrugNode(newnode23,false);

    strcpy(message.ch_name,"帕拉米韦氯化钠");
    strcpy(message.en_name,"Peramivir sodium chloride");
    strcpy(message.es_name,"Cloruro de sodio peramivir");
    strcpy(message.pu_name,"Cloreto de sódio de peramivir");
    strcpy(message.ch2_name,"帕拉米韋氯化鈉");
    
    newnode24->message = message;
    newnode24->nextnode = NULL;
    addDrugNode(newnode24,false);

    strcpy(message.ch_name,"葡萄糖氯化钠");
    strcpy(message.en_name,"Glucose Sodium Chloride");
    strcpy(message.es_name,"Cloruro de sodio glucosa");
    strcpy(message.pu_name,"Cloreto de Sódio Glicose");
    strcpy(message.ch2_name,"葡萄糖氯化鈉");
    
    newnode25->message = message;
    newnode25->nextnode = NULL;
    addDrugNode(newnode25,false);

    strcpy(message.ch_name,"利奈唑胺葡萄糖");
    strcpy(message.en_name,"Linezolid Glucose");
    strcpy(message.es_name,"Linezolida Glucosa");
    strcpy(message.pu_name,"Glicose Linezolida");
    strcpy(message.ch2_name,"利奈唑胺葡萄糖");
    
    newnode26->message = message;
    newnode26->nextnode = NULL;
    addDrugNode(newnode26,false);

    strcpy(message.ch_name,"50%%葡萄糖");
    strcpy(message.en_name,"50%% glucose");
    strcpy(message.es_name,"50%% de glucosa");
    strcpy(message.pu_name,"50%% de glicose");
    strcpy(message.ch2_name,"50%%葡萄糖");
    
    newnode27->message = message;
    newnode27->nextnode = NULL;
    addDrugNode(newnode27,false);

    strcpy(message.ch_name,"甲硝唑氯化钠");
    strcpy(message.en_name,"Metronidazole Sodium Chloride");
    strcpy(message.es_name,"Cloruro de sodio de metronidazol");
    strcpy(message.pu_name,"Cloreto de Sódio Metronidazol");
    strcpy(message.ch2_name,"甲硝唑氯化鈉");
    
    newnode28->message = message;
    newnode28->nextnode = NULL;
    addDrugNode(newnode28,false);

    strcpy(message.ch_name,"左氧氟沙星氯化钠");
    strcpy(message.en_name,"Levofloxacin Sodium Chloride");
    strcpy(message.es_name,"Cloruro de sodio de levofloxacina");
    strcpy(message.pu_name,"Cloreto de sódio de levofloxacina");
    strcpy(message.ch2_name,"左氧氟沙星氯化鈉");
    
    newnode29->message = message;
    newnode29->nextnode = NULL;
    addDrugNode(newnode29,false);

    strcpy(message.ch_name,"咪达唑仑");
    strcpy(message.en_name,"Midazolam");
    strcpy(message.es_name,"Midazolam");
    strcpy(message.pu_name,"Midazolam");
    strcpy(message.ch2_name,"咪達唑侖");
    
    newnode30->message = message;
    newnode30->nextnode = NULL;
    addDrugNode(newnode30,false);

    strcpy(message.ch_name,"丙泊酚");
    strcpy(message.en_name,"Propofol");
    strcpy(message.es_name,"Propofol");
    strcpy(message.pu_name,"Propofol");
    strcpy(message.ch2_name,"丙泊酚");
    
    newnode31->message = message;
    newnode31->nextnode = NULL;
    addDrugNode(newnode31,false);

    strcpy(message.ch_name,"右美托咪定");
    strcpy(message.en_name,"Dexmedetomidine");
    strcpy(message.es_name,"Dexmedetomidina");
    strcpy(message.pu_name,"Dexmedetomidina");
    strcpy(message.ch2_name,"右美托咪定");
    
    newnode32->message = message;
    newnode32->nextnode = NULL;
    addDrugNode(newnode32,false);

    strcpy(message.ch_name,"依托咪酯");
    strcpy(message.en_name,"Etomidate");
    strcpy(message.es_name,"Etomidato");
    strcpy(message.pu_name,"Etomidato");
    strcpy(message.ch2_name,"依託咪酯");
    
    newnode33->message = message;
    newnode33->nextnode = NULL;
    addDrugNode(newnode33,false);

    strcpy(message.ch_name,"地西泮");
    strcpy(message.en_name,"Diazepam");
    strcpy(message.es_name,"Diazepam");
    strcpy(message.pu_name,"Diazepam");
    strcpy(message.ch2_name,"地西泮");
    
    newnode34->message = message;
    newnode34->nextnode = NULL;
    addDrugNode(newnode34,false);

    strcpy(message.ch_name,"瑞马唑仑");
    strcpy(message.en_name,"Remimazolam");
    strcpy(message.es_name,"Remimazolam");
    strcpy(message.pu_name,"Remimazolam");
    strcpy(message.ch2_name,"瑞馬唑侖");
    
    newnode35->message = message;
    newnode35->nextnode = NULL;
    addDrugNode(newnode35,true);   //每插入一次节点就会对flash操作
	 
	printf("write DrugNode_t success\r\n");
		
}





/*
	functionname: 		getTheDrugNodeName
	describe:      		获取输液器品牌名称
	Param1:				输液器品牌的节点
	Param2:				null
	return: 			输液器品牌名(字符串)
	author:				dong
*/
char * getTheDrugNodeName(DrugNode_t * node)
{
    if(SystemSetting.langue==Chinese)
    {
		return node->message.ch_name;
	}
    else if(SystemSetting.langue == English)
	{
		return node->message.en_name;
	}
	else if(SystemSetting.langue == Spanish)
	{
		return node->message.es_name;
	}
	else if(SystemSetting.langue == Chinese2)
	{
		return node->message.ch2_name;
	}
	else if(SystemSetting.langue == Portuguese)
	{
		return node->message.pu_name;
	}
	else
	{
		return NULL;
	}
}



//保存药品到flash
void save_drug_to_flash(void)
{
    //获取节点数
	ParamSetting.drugnumber = druglist->node_number;
    WriteParamSettingMessageToFlash();
    WriteDrugListToFlash();
}




