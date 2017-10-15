/*接口的使用声明*/
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
  assert(pLinkTable != NULL)
}
