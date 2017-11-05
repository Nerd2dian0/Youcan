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
#define CMD_MAX_ARGV_NUM 128

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



int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]))
{
    if(head == NULL)
    {
        head = CreateLinkTable();
        tDataNode *pNode = (tDataNode*) malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "List all command in this program";
        pNode->handler = Help;
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
