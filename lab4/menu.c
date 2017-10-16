#include <stdio.h>
#include <stdlib.h>
#include "LinkTable.h"
int Help();
int Quit();

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

/* menu program */

/*data struct and its operations*/
typedef struct DataNode
{
    tLinkTableNode *pNext;
    char* cmd;
    char* desc;
    void   (*handler)();
}tDataNode;

/*find a cmd in the linkTable and return the data*/
tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode* pNode=(tDataNode*)GetLinkTableHead(head);
    while(pNode !=NULL)
    {
        if(!strcmp(pNode->cmd,cmd))
        {
            return pNode;
        }
        pNode=(tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode*)pNode);
    }
    return NULL;
}
/*show all cmd in listtable*/
int ShowAllCMD(tLinkTable* head)
{
    tDataNode *pNode=(tDataNode*)GetLinkTableHead(head);
    while(pNode !=NULL)
    {
        printf("%s - %s\n",pNode->cmd,pNode->desc);
        pNode =(tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode*)pNode);
    }
    return 0;
}

/*初始化*/
int InitMenuData(tLinkTable **ppLinkTable)
{
    *ppLinkTable=CreateLinkTable();/*创建一个链表*/
    tDataNode* pNode=(tDataNode*)malloc(sizeof(tDataNode));/*malloc一个节点*/
    pNode->cmd="help";
    pNode->desc="Menu List";
    pNode->handler=help;/*把这个节点的数据放入，以及这个数据的指针*/
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);/*把上面这个节点添加到这个链表中*/
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="info";
    pNode->desc="Show information";
    pNode->handler=info;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="echo";
    pNode->desc="Repeat your input";
    pNode->handler=echo;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="exit";
    pNode->desc="Exit this program";
    pNode->handler=Exit;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="time";
    pNode->desc="Show time now";
    pNode->handler=Time;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);

    return 0;
}

tLinkTable* head=NULL;
int main()
{
    char cmd[CMD_MAX_LEN];
    InitMenuData(&head);
    tLinkTableNode *command;
    printf("Program is running\n");
    while (1)
    {
        printf("Input a cmd >>");
        scanf("%s",cmd);
        tDataNode *p = FindCmd(head,cmd);
        if(p == NULL)
        {
            printf("Command Not found\n");
	    coutinue;
        } 
	printf("%s - s%\n", p->cmd, p->desc);
	if(p->handler != NULL)
        {
            p->handler();
        }
    }
}

int Help()
{
    ShowAllCmd(head);
    return 0; 
}
