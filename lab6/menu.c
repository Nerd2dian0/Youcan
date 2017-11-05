//menu.c --命令的主要程序源代码

#include <stdio.h>
#include <stdlib.h>
#include "linkTable.h"
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
    int   (*handler)();
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
}
*/
//tLinkTable* head=NULL;
int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]))
{
    if(head == NULL)
    {
        head = CreateLinkList();
        tDataNode *pNode = (tDataNode*) malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "List all command in this program";
        pNode->handler = help;
        AddLinkListNode(head,(tLinkListNode *)pNode);
    }
    tDataNode* pNode=(tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd=cmd;
    pNode->desc=desc;
    pNode->handler=handler;
    AddLinkListNode(head,(tLinkListNode *)pNode);
    return 0;
}

int ExecuteMenu()
{
    int argc = 0;
    char cmd[CMD_MAX_LEN];
    char *argv[CMD_MAX_ARGV_NUM];
    char *command = NULL;
    MenuConfig("info","Show information\n\t'-Nerd2dian0' for author information\n\t'-version1.10' for version information",NULL);
    MenuConfig("echo","Repeat your input",NULL);
    MenuConfig("quit","Exit this program",Quit);
    MenuConfig("time","Show time now",NULL);
    printf("Program is running\n");
    while (1)
    {
        argc = 0;
        command = NULL;
        printf("Command>>");
        command=fgets(cmd,CMD_MAX_LEN,stdin);
        if (command == NULL)
        {
            continue;
        }
        command = strtok(command," ");
        while (command != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc] = command;
            argc++;
            command = strtok(NULL," ");
        }
        if(argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len -1) = '\0';
        }
        tDataNode *p = FindCmd(head,argv[0]);
        if(p == NULL)
        {
            printf("Command Not found\n");
        } else if(p->handler!= NULL)
        {
            p->handler(argc,argv);
        }
    }
}

int main()
{
    InitMenuData(&head);
    ExecuteMenu();

	printf("%s - %s\n", p->cmd, p->desc);
	if(p->handler != NULL)
        {
            p->handler();
        }
    }
}

int Help()
{
    ShowAllCMD(head);
    return 0; 
}
int Quit()
{
    exit(0);
}
