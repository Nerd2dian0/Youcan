/*LinkTable.c是接口的源代码*/
#include<stdio.h>
#include<stdlib.h>
#include "LinkTable.h"

/*链表节点类型*/
typedef struct LinkTableNode
{
   struct LinkTableNode * pNext;
}tLinkTableNode;

/*链表结构LinkTable Type*/
typedef struct LinkTable
{
    tLinkTableNode *pHead;/*说明带有头节点的链表*/
    tLinkTableNode *pTail;/*尾节点*/
    int SumOfNode;        /*说明一共有多少的节点*/
    pthread_mutex_t mutex;/*多线程，暂时不用管*/
}tLinkTable;

tLinkTable * CreateLinkTable()
{
  tLinkTable *pLinkTable = (tLinkTable*)malloc(sizeof(tLinkTable));
  if(pLinkTable == NULL)
  {
    return NULL;
  }
  pLinkTable->pHead = NULL;
  pLinkTable->pTail = NULL;
  pLinkTable->SumOfNode = 0;
  pthread_mutex_init(&(pLinkTable->mutex),NULL);
  return pLinkTable;
}

int DeleteLinkTable(tLinkTable *pLinkTable)
{
  if(pLinkTable==NULL)
  {
    return FAILURE;
  }
  while(pLinkTable->pHead != NULL)
  {
    tLinkTableNode *p =pLinkTable->pHead;
    pthread_mutex_lock(&(pLinkTable->mutex));
    pLinkTable->pHead = pLinkTable->pHead->pNext;
    pLinkTable->SumOfNode -= 1;
    pthread_mutex_unlock(&(pLinkTable->mutex));
    free(p);
  }
  /*以上的将遍历整个列表*/
  pLinkTable->pHead = NULL;
  pLinkTable->pTail = NULL;
  pLinkTable->SumOfNode = 0;
  pthread_mutex_destroy(&(pLinkTable->mutex));
  free(pLinkTable);
  return SUCCESS;
}

int AddLinkTableNode(tLinkTable *pLinkTable, tLinkTableNode *pNode)
{
    if (pLinkTable == NULL || pNode == NULL)
        return FAILURE;

    if (pLinkTable->pHead == NULL)
    {
        pLinkTable->pHead = pNode;
        pLinkTable->pTail = pNode;
        pLinkTable->SumOfNode = 1;
    }
    else
    {
        pLinkTable->pTail->pNext = pNode;
        pLinkTable->pTail = pNode;
        pLinkTable->SumOfNode++;
    }
    return SUCCESS;
}

int DeleteLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    /*错误处理*/
  if(pLinkTable->pHead == NULL || pNode == NULL)
  {
      return FAILURE;
  }
  pthread_mutex_lock(&(pLinkTable->mutex));
  if(pLinkTable->pHead == pNode)
  {
    pLinkTable->pHead = pLinkTable->pHead->pNext;
    pLinkTable->SumOfNode -= 1;
    if(pLinkTable->SumOfNode = 0)
    {
      pLinkTable->pTail = NULL;
    }
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return SUCCESS;
  }
  tLinkTableNode * pTempNode = pLinkTable->pHead;
  while(pTempNode != NULL)
  {
    if(pTempNode->pNext == pNode)
    {
      pTempNode->pNext = pTempNode->pNext->pNext;
      pLinkTable->SumOfNode -= 1;
      if(pLinkTable->SumOfNode = 0)
      {
        pLinkTable->pTail = NULL;
      }
      pthread_mutex_unlock(&(pLinkTable->mutex));
      return SUCCESS;
    }
    pTempNode = pTempNode->pNext;
  }
  pthread_mutex_unlock(&(pLinkTable->mutex));
  return FAILURE;
}

tLinkTableNode *SearchLinkTableNode(tLinkTable *pLinkTable,int Condition(tLinkTableNode * pNode, void * args),void *args)
{
    if(pLinkTable == NULL)
    {
        return NULL;
    }
    tLinkTableNode *tmp = pLinkTable->pHead;
    while(tmp != NULL)
    {
        if(Condition(tmp,args) == 1)
        {
            return tmp;
        }
        tmp = tmp->pNext;
    }
    return NULL;
}

tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable)
{
 if(pLinkTable == NULL)
 {
    return NULL;
 }
 return pLinkTable->pHead;
}

tLinkTableNode * GetNextLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
  if(pLinkTable == NULL || pNode == NULL)
  {
      return NULL;
  }
  tLinkTableNode * pTempNode = pLinkTable->pHead;
  while(pTempNode != NULL)
  {
    if(pTempNode == pNode)
    {
      return pTempNode->pNext;
    }
    pTempNode = pTempNode->pNext;
  }
  return NULL;
}
