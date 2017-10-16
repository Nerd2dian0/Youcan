/*LinkTable.c是接口的源代码*/
#include<stdio.h>
#include<stdlib.h>
#include "LinkTable.h"

tLinkTable * CreateLinkTable()
{
  if(pLinkTable == NULL)
  {
    return NULL;
  }
  tLinkTable *pLinkTable = (tLinkTable*)malloc(sizeof(tLinkTable))；
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
    free(p)
  }
  /*以上的将遍历整个列表*/
  pLinkTable->pHead = NULL;
  pLinkTable->pTail = NULL;
  pLinkTable->SumOfNode = 0;
  pthread_mutex_destroy(&(pLinkTable->mutex));
  free(pLinkTable);
  return SUCCESS;
}

int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
  /*错误处理*/
  if(pLinkTable->pHead == NULL || pNode == NULL)
  {
      return FAILURE;
  }
  pNode->pNext=NULL;/*把这个节点的Next置为NULL*/
  pthread_mutex_lock(&(pLinkTable->mutex));
  if(pLinkTable->pHead == NULL)
  {
    pLinkTable->pHead = pNode;/*此时该节点是头结点还是尾节点*/
  }
  if(pLinkTable->pTail == NULL)
  {
    pLinkTable->pTail == pNode;
  }
  else
  {
    pLinkTable->pTail->pNext = pNode;
    pLinkTable->pTail = pNode;
  }
  pLinkTable->SumOfNode += 1;
  pthread_mutex_unlock(&(pLinkTable->mutex));
  return SUCCESS；
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
