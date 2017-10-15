/*LinkTable.c是接口的源代码*/
#include<stdio.h>
#include<stdlib.h>
#include "LinkTable.h"

tLinkTable * CreateLinkTable()
{
  tLinkTable *pLinkTable = (tLinkTable*)malloc(sizeof(tLinkTable))；
  pLinkTable->pHead = NULL;
  pLinkTable->pTail = NULL;
  pLinkTable->SumOfNode = 0;
  return pLinkTable;
}

int DeleteLinkTable(tLinkTable *pLinkTable)
{
  if(pLinkTable==NULL)
  {
    return 0;
  }
  
}
