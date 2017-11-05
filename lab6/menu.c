//menu.c --命令的主要程序源代码

#include <stdio.h>
#include <stdlib.h>
#include "linkTable.h"
#include "menu.h"

tLinkTable* head=NULL;
int Help(int argc, char** argv);
int Quit(int argc, char** argv);

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
    int   (*handler)(int argc, char** argv);
}tDataNode;

/*find a cmd in the linkTable and return the data*/
int SearchCondition(tLinkTableNode * pNode, void * args)
{
    return (strcmp(((tDataNode*)pNode)->cmd,(char*)args)?0:1);
}

tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    return (tDataNode*)SearchLinkTableNode(head,SearchCondition,cmd);
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
/*int InitMenuData(tLinkTable **ppLinkTable)
{
    *ppLinkTable=CreateLinkTable();/*创建一个链表*/
    tDataNode* pNode=(tDataNode*)malloc(sizeof(tDataNode));/*malloc一个节点*/
    pNode->cmd="help";
    pNode->desc="Menu List";
    pNode->handler = Help; /*把这个节点的数据放入，以及这个数据的指针*/
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);/*把上面这个节点添加到这个链表中*/
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="info";
    pNode->desc="Show information";
    pNode->handler=NULL;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="echo";
    pNode->desc="Repeat your input";
    pNode->handler=NULL;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="quit";
    pNode->desc="Exit this program";
    pNode->handler=Quit;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);
    pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd="time";
    pNode->desc="Show time now";
    pNode->handler=NULL;
    AddLinkTableNode(*ppLinkTable,(tLinkTableNode *)pNode);

    return 0;
}*/

int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]))
{
    if(head == NULL)
    {
        head = CreateLinkTable();
        tDataNode *pNode = (tDataNode*) malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "List all command in this program";
        pNode->handler = help;
        AddLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    tDataNode* pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd=cmd;
    pNode->desc=desc;
    pNode->handler=handler;
    AddLinkTableNode(head,(tLinkTableNode *)pNode);
    return 0;
}

int ExecuteMenu()
{
    while(1)
    {
	int argc = 0;
	char *argv[CMD_MAX_ARGV_NUM];
        char cmd[CMD_MAX_LEN];
        char *pcmd = NULL;
        printf("Input a cmd number > ");
        /*scanf("%s", cmd);*/
        pcmd = fgets(cmd, CMD_MAX_LEN, stdin);
        if(pcmd == NULL)
        {
            continue;
        }
        /* convert cmd to argc/argv */
        pcmd = strtok(pcmd, " ");
        while(pcmd != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc] = pcmd;
            argc++;
            pcmd = strtok(NULL, " ");
        }
        if(argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0';
        }
        tDataNode *p = (tDataNode*)SearchLinkTableNode(head, SearchCondition, (void*)argv[0]);
        if(p == NULL)
        {
            printf("This is a wrong cmd!\n");
            continue;
        }
        if(p->handler != NULL)
        {
            p->handler(argc, argv);
        }
    }
    return 0;
}

int Help(int argc, char* argv[])
{
    ShowAllCMD(head);
    return 0; 
}
int Quit(int argc, char* argv[])
{
    exit(0);
}
