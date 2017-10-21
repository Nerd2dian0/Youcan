/*定义一些接口*/
#ifndef _LINK_TABLE_H_
#define _LINK_TABLE_H_

#include <pthread.h>/*用到了多线程，暂时不用管*/

#define SUCCESS 0
#define FAILURE (-1)

/*定义的接口:*/
  /*创建一个LinkTable,返回链表的头结点,下面接口中的头结点都是为了确定是该链表而不是其他*/
tLinkTable * CreateLinkTable();
  /*delete a LinkTable，链表的生死相依原则*/
int DeleteLinkTable(tLinkTable *pLinkTable);
  /*add a LinkTableNode to LinkTable*/
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
  /*delete a LinkTableNode to LinkTable生死相依*/
int DeleteLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
/*查找一个cmd*/
tLinkListNode *SearchLinkListNode(tLinkList *pLinkList,int Condition(tLinkListNode * pNode, void * args),void *args);
  /*get LinkTableHead该接口是获得头结点*/
tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable);
  /* get next LinkTableNode根据一个节点执行这个节点的下一个节点，可以一直下去，实现用户的遍历*/
tLinkTableNode * GetNextLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);

#endif
/*结束了!_LINK_TABLE_H_*/
