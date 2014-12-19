#ifndef PriorityLinked_H
#define PriorityLinked_H
#include "TCB.h"

typedef struct PriorityLinkedList PriorityLinkedList;
struct PriorityLinkedList{
  TCB *head;
  TCB *tail;
};

PriorityLinkedList *createPriorityLinkedList();
int comparePriority(void *listElement, void *insertElement);
void *removeFromHeadPriorityLinkedList(PriorityLinkedList *list);
void addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *));
void *removePriorityLinkedList(PriorityLinkedList *list, void *data, int compare);

#endif // PriorityLinked_H
