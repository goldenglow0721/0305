#ifndef LIBRARY_INFUSION_H
#define LIBRARY_INFUSION_H




#include "ui.h"


#define InfusionTube_MaxNumber 40


extern char tubename[30];
extern char tubename1[30];
extern char tubename2[30];
extern char tubename3[30];
extern char tubename4[30];
extern char tubename5[30];
extern char tubename6[30];


/* 150+ 40+ 16  = 206 */
typedef struct 
{
    char        ch_name[30];                        //最多10个汉字
    char        en_name[30];                       //最多30个拼音
    char        es_name[30];
    char        ch2_name[30];
    char        pu_name[30];

    double      Calibdata1;
	double      Calibdata2;
    int         AD0;
	int         AD40;
	int         AD70;
	int         AD120;
	double      P40;
	double      P70;
	double      P120;
	
}InfusionNodeMessage;



typedef struct infusion_node
{
    struct infusion_node* nextnode;
    InfusionNodeMessage message;
}InfusionNode_t;



typedef struct infusionList{
    int node_number;                    
    InfusionNode_t * node;
}InfusionList;

/************************function*************************/
void initInfusionList(void);

void destroyInfusionList(void);

_Bool addInfusionNode(InfusionNode_t* newnode,_Bool flag);

_Bool AddInfusionNode(InfusionNode_t* newnode,_Bool flag);

_Bool insertInfusionNode(InfusionNode_t* newnode,int pos);

_Bool removeInfusionNodeByName(char * str,_Bool flag);

_Bool updataInfusionNameByName(char * str,InfusionNodeMessage message);

InfusionNode_t* fineInfusionNodeByName(char * str);

int getNowInfusionListNum(void);

void createInfusionLib(void);

void fineInfusionNode_six_ById(int id);
InfusionNode_t* getThefirstInfusionNode(void);

char * getTheTubeNodeName(InfusionNode_t * node);

InfusionNode_t* fineInfusionNodeByPosit(int id);

void InfusionNodelangue(char* Infusionname,InfusionNode_t* node);

#endif

