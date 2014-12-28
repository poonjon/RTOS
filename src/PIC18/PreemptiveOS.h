#ifndef PreemptiveOS_H
#define PreemptiveOS_H

#include "TCB.h"
#include "PriorityLinked.h"

extern TCB *runningTCB;
extern PriorityLinkedList readyQueue;
extern int readyQueueFlag;

void createTask(TCB TCBs[], int index, void(*task)());
void initPreemptiveMultitasking();
void taskOne();
void taskTwo();

#endif //PreemptiveOS_H