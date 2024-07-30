#ifndef LIBRARY_DRUG_H
#define LIBRARY_DRUG_H


#include "ui.h"


#define DrugTube_MaxNumber 40


extern char drugname[50];
extern char drugname1[50];
extern char drugname2[50];
extern char drugname3[50];
extern char drugname4[50];


/* 250 byte 最大药物数量40个 9k byte */
typedef struct 
{
    char        ch_name[50];                        //最多10个汉字
    char        en_name[50];                       //最多30个拼音
    char        es_name[50];
    char        ch2_name[50];
    char        pu_name[50];
}DrugNodeMessage;



typedef struct drug_node
{
    struct drug_node* nextnode;
    DrugNodeMessage message;
}DrugNode_t;



typedef struct drugList{
    int node_number;                    
    DrugNode_t * node;
}DrugList;



/************************function*************************/
void initDrugList(void);

void destroyDrugList(void);

_Bool addDrugNode(DrugNode_t* newnode,_Bool flag);

_Bool AddDrugNode(DrugNode_t* newnode,_Bool flag);

_Bool insertDrugNode(DrugNode_t* newnode,int pos);

_Bool removeDrugNodeById(char * str,_Bool flag);

_Bool updataDrugNameById(char * str,DrugNodeMessage message);

DrugNode_t* fineDrugNodeById(char * str);

int getNowDrugListNum(void);

char * getTheDrugNodeName(DrugNode_t * node);

DrugNode_t* fineDrugNodeByPosit(int id);



void fineDrugNode_four_ById(int id);

void createDrugLib(void);

DrugNode_t* getThefirstDrugNode(void);

void DrugNodelangue(char* medicine,DrugNode_t* node);

#endif