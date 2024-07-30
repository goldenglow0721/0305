#include "library_infusion.h"




static _Bool infusionNodeIsObtain(InfusionNode_t * node);

 struct infusionList* infusionlist;

char tubename[30];
char tubename1[30];
char tubename2[30];
char tubename3[30];
char tubename4[30];
char tubename5[30];
char tubename6[30];


/*        Labrary function     */

void initInfusionList()
{
    static InfusionList li;
    infusionlist = &li;
    //infusionlist = (InfusionList *)malloc(sizeof(InfusionList));
    infusionlist->node = NULL;
    infusionlist->node_number = 0;
}

void destroyInfusionList()
{
    infusionlist->node_number = 0;
    InfusionNode_t* node = infusionlist->node;
    InfusionNode_t* ntemp;

    while(node)
    {   
        //从头 往后释放
        ntemp = node;
        node = node->nextnode;
        free(ntemp);
    }
    infusionlist->node = NULL;
}

//尾插法 
_Bool addInfusionNode(InfusionNode_t* newnode,_Bool flag)
{

    if(infusionlist->node && newnode)
    {
        InfusionNode_t * n = infusionlist->node;  //取出第一个节点

        //在这里往后移动了不该移动的位置，如何避免？？？
        while(n->nextnode)//有下个节点
        {
            n = n->nextnode;
            
        }
        //到最终节点了
        n->nextnode = newnode; //放到最后
        ++infusionlist->node_number;
        if(flag)
        {
            ParamSetting.brandnumber = infusionlist->node_number;
            WriteParamSettingMessageToFlash();
            writeInfusionTubeListToFlash();
        }
        
        return true;

    }
    else if(!infusionlist->node && newnode) //如果是第一个节点
    {
        infusionlist->node = newnode;
        ++infusionlist->node_number;
        if(flag)
        {
            ParamSetting.brandnumber = infusionlist->node_number;
            WriteParamSettingMessageToFlash();
            writeInfusionTubeListToFlash();
        }
        return true;
    }
    return false;

}


_Bool AddInfusionNode(InfusionNode_t* newnode,_Bool flag)
{
    if(infusionlist->node && newnode)
    {
        InfusionNode_t * n = infusionlist->node;  //取出第一个节点

        //在这里往后移动了不该移动的位置，如何避免？？？
        while(n->nextnode)//有下个节点
        {
            n = n->nextnode;
        }
        //到最终节点了
        int node_count = getNowInfusionListNum();

        n->nextnode = newnode; //放到最后
        node_count++;

        infusionlist->node_number = node_count;   //节点总数加一
        if(flag)
        {
            ParamSetting.brandnumber = infusionlist->node_number;
            WriteParamSettingMessageToFlash();
            writeAddInfusionTubeListToFlash();
        }
        return true;
    }
    else if(!infusionlist->node && newnode) //如果是第一个节点
    {
        infusionlist->node = newnode;
        ++infusionlist->node_number;
        if(flag)
        {
            ParamSetting.brandnumber = infusionlist->node_number;
            WriteParamSettingMessageToFlash();
            writeAddInfusionTubeListToFlash();
        }
        return true;
    }
    return false;

}







#if 0
//在指定位置插入节点(可能不太需要)
_Bool insertInfusionNode(InfusionNode_t* newnode,int pos)
{
    //判断是否有这个位置
    if(infusionlist->node_number < pos)
    {
        return false;
    }

    int i=0;
    InfusionNode_t * n=infusionlist->node;
    while(n && i<pos)
    {
        i++;
        n = n->nextnode;
    }
    if(n)
    {
        newnode->lastnode = n;
        newnode->nextnode = n->nextnode;
        n->nextnode = newnode;

        infusionlist->node_number++;

        return true;
    }

    return false;

}
#endif
/*
	functionname: removeInfusionNodeByName
	describe:    通过传入的输液器品牌名删除节点  
	Param1:      传入的输液器品牌名
	Param2:
	return: 
	author:		dong
*/

//


_Bool removeInfusionNodeByName(char * str,_Bool flag)
{
    InfusionNode_t* node=infusionlist->node;

    if(!strcmp(getTheTubeNodeName(node),str)) //如果是第一个节点
    {
        infusionlist->node = node->nextnode;
        free(node);
        --infusionlist->node_number;
		if(flag){
				ParamSetting.brandnumber = infusionlist->node_number;
				WriteParamSettingMessageToFlash();
				writeInfusionTubeListToFlash();
				}
       
        return true;
    }
    InfusionNode_t * pNtemp;
    while(node->nextnode)
    {
        if(!strcmp(getTheTubeNodeName(node->nextnode),str))
        {
            pNtemp=node->nextnode;
            node->nextnode = node->nextnode->nextnode;
            free(pNtemp);
            --infusionlist->node_number;
			
			if(flag){
					 ParamSetting.brandnumber = infusionlist->node_number;
					 WriteParamSettingMessageToFlash();
					 writeInfusionTubeListToFlash();			
			        }         
            return true;
        }
        node=node->nextnode;
    }

    return false;
}

/*
	functionname: removeInfusionNodeByName
	describe:    修改输液器品牌数据  
	Param1:      传入的输液器品牌名
	Param2:      修改后的信息
	return: 
	author:		dong
*/
_Bool updataInfusionNameByName(char * str,InfusionNodeMessage message)
{
    InfusionNode_t* node= fineInfusionNodeByName(str);
    if(node)
    {
        node->message = message;
        return true;
    }

    return false;
}


/*
	functionname: removeInfusionNodeByName
	describe:    通过输液器品牌名找到节点 
	Param1:      传入的输液器品牌名
	Param2:      
	return: 
	author:		dong
*/
InfusionNode_t* fineInfusionNodeByName(char * str)
{
    InfusionNode_t* node = infusionlist->node;
    while(node)
    {
        if(!strcmp(getTheTubeNodeName(node),str))
        {
           
            return node;
        }
        node = node->nextnode;

    }
    
    return NULL;
}



/*
	functionname: getThefirstInfusionNode
	describe:    获得输液器品牌链表的第一个节点 
	Param1:      
	Param2:      
	return: 
	author:		dong
*/
InfusionNode_t* getThefirstInfusionNode()
{
    return infusionlist->node;
}


/*
	functionname: fineInfusionNodeByPosit
	describe:    通过位置找到输液器节点 
	Param1:      位置
	Param2:      
	return: 
	author:		dong
*/
InfusionNode_t* fineInfusionNodeByPosit(int id)
{
    InfusionNode_t* node = infusionlist->node;
    int posit = 1;
    while(node)
    {
        if(posit == id)
         return node;

        node = node->nextnode;
        posit++;
    }
}

void InfusionNodelangue(char* Infusionname,InfusionNode_t* node)
{
    if(SystemSetting.langue==Chinese)
	    strcpy(Infusionname,node->message.ch_name);
    else if(SystemSetting.langue==English)
        strcpy(Infusionname,node->message.en_name);
    else if(SystemSetting.langue==Spanish)
        strcpy(Infusionname,node->message.es_name);
    else if(SystemSetting.langue==Chinese2)
        strcpy(Infusionname,node->message.ch2_name);
    else if(SystemSetting.langue==Portuguese)
        strcpy(Infusionname,node->message.pu_name);
}

/*
	functionname: removeInfusionNodeByName
	describe:    通过位置找到接下来的6的输液器品牌 
	Param1:      传入的位置信息
	Param2:      
	return:      6个品牌名
	author:		dong
*/
void fineInfusionNode_six_ById(int id)
{
    int flag = 0;
    int point=0;
    InfusionNode_t* node = infusionlist->node;
    while(node)
    {      
        if(point == id || flag)
        {
            if(flag == 0)
            {
	            InfusionNodelangue(tubename1,node);
                flag++;
            }
            else if(flag == 1)
            {
                InfusionNodelangue(tubename2,node);
                flag++;
            }
            else if(flag == 2)
            {
                InfusionNodelangue(tubename3,node);
                flag++;
            }
            else if(flag == 3)
            {
                InfusionNodelangue(tubename4,node);
                flag++;
            }
            else if(flag == 4)
            {
                InfusionNodelangue(tubename5,node);
                flag++;
            }
            else if(flag == 5)
            {               
                InfusionNodelangue(tubename6,node);
                flag++;
                return ;
            }  
        }
        node = node->nextnode;
        point++;
        
    }
}




//获取当前的节点数
int getNowInfusionListNum()
{
    return infusionlist->node_number;
}


//判断是否存在
static _Bool infusionNodeIsObtain(InfusionNode_t * node)
{
    InfusionNode_t * tempnode = infusionlist->node;

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



/*                      persion function                              */

void createInfusionLib()
{
    initInfusionList(); //初始化链表

    //添加输液器名字
    InfusionNode_t *newnode1 =(InfusionNode_t *)malloc(sizeof(InfusionNode_t));
    InfusionNode_t *newnode2 =(InfusionNode_t *)malloc(sizeof(InfusionNode_t));
    InfusionNode_t *newnode3 =(InfusionNode_t *)malloc(sizeof(InfusionNode_t));
   // InfusionNode_t newnode3;
    InfusionNodeMessage message;

    strcpy(message.ch_name,"安得");
    strcpy(message.en_name,"ANDE");
    strcpy(message.es_name,"ANDE");
    strcpy(message.pu_name,"ANDE");
    strcpy(message.ch2_name,"ANDE");

    newnode1->message = message;
    newnode1->nextnode = NULL;
    newnode1->message.AD0 =18530;
    newnode1->message.AD40=18826;
    newnode1->message.AD70= 19166;
    newnode1->message.AD120=19592;
    newnode1->message.P40 = 40;
    newnode1->message.P70 = 70;
    newnode1->message.P120 = 120;
    newnode1->message.Calibdata1=7.48;
    newnode1->message.Calibdata2=7.21;
    addInfusionNode(newnode1,false);
    
    strcpy(message.ch_name,"洁瑞");
    strcpy(message.en_name,"WEGO");
    strcpy(message.es_name,"WEGO");
    strcpy(message.pu_name,"WEGO");
    strcpy(message.ch2_name,"WEGO");
    newnode2->message = message;
    newnode2->nextnode = NULL;
    newnode2->message.AD0 =18530;
    newnode2->message.AD40=18826;
    newnode2->message.AD70= 19166;
    newnode2->message.AD120=19592;
    newnode2->message.P40 = 40;
    newnode2->message.P70 = 70;
    newnode2->message.P120 = 120;
    newnode2->message.Calibdata1=7.48;
    newnode2->message.Calibdata2=7.21;
    addInfusionNode(newnode2,false);

    strcpy(message.ch_name,"宏达");
    strcpy(message.en_name,"HONGDA");
    strcpy(message.es_name,"HONGDA");
    strcpy(message.pu_name,"HONGDA");
    strcpy(message.ch2_name,"HONGDA");
    newnode3->message = message;
    newnode3->nextnode = NULL;
    newnode3->message.AD0 =18530;
    newnode3->message.AD40=18826;
    newnode3->message.AD70= 19166;
    newnode3->message.AD120=19592;
    newnode3->message.P40 = 40;
    newnode3->message.P70 = 70;
    newnode3->message.P120 = 120; 
    newnode3->message.Calibdata1=7.48;
    newnode3->message.Calibdata2=7.21;
    addInfusionNode(newnode3,TRUE);	
}




/*
	functionname: 		getTheTubeNodeName
	describe:      		获取输液器品牌名称
	Param1:				输液器品牌的节点
	Param2:				null
	return: 			输液器品牌名(字符串)
	author:				dong
*/
char * getTheTubeNodeName(InfusionNode_t * node)
{
	if(SystemSetting.langue == Chinese)
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





