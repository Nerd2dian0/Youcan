/*接口的使用说明*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"linktable.h"

#defiine debug

/*定义了Node节点，里面有pNext节点，以及data，data可以定义很多数据*/
typedef struct Node
{
  tLinkTableNode * pNext;
  int data;
}tNode;

tNode * Search(tLinkTable *pLinkTable);

int main()
{
  int i;
  tLinkTable * pLinkTable = CreateLinkTable();
  if (pLinkTable == NULL)
  {
    printf("CreateLinkTable Error!\n");
    exit(0);
  }
  
  /*在pNext节点后再创建新的节点，但并没有说明链表的具体内容*/
  for(i = 0; i<10; i++)
  {
      tNode* pNode =(tNode*)malloc(sizeof(tNode));/*生成新的节点pNode*/
      pNode->data = i;
      debug("AddLinkTableNode\n");
      AddLinkTableNode(pLinkTable,(tLinkTableNode *)pNode);/*将节点pNode强制转化，然后插入*/
  }
}

/*不知道链表内的数据，怎么实现查询？-- search one by one的方式查询*/
tNode * pTempNode = Search(pLinkTable);
printf("%d\n",pTempNode->data);
debug("DelLinkTableNode\n");
DelLinkTableNode(pLinkTable,(tLinkTableNode *)pTempNode);
free(pTempNode);/*del只是删除，并没有释放，free后释放*/
DeleteLinkTable(pLinkTable);/*删除整个链表*/

/*function of Search（）*/
tNode * Search(tLinkTable *pLinkTable)
{
  debug("Search GetLinkTableHead\n");
  tNode * pNode = (tNode*)GetLinkTableHead(pLinkTable);
  while(pNode !=NULL)
  {
    if(pNode->data == 5)
    {
      return pNode;
    }
    debug("GetNextLinkTableNode\n");
    pNode = (tNode*)GetNextLinkTableNode(pLinkTable,(tLinkTableNode *)pNode)
  }
  return NULL;
}
