#ifndef PreemptiveOS_H
#define PreemptiveOS_H

extern TCB *runningTCB;
extern PriorityLinkedList readyQueue;

void createTask(TCB TCBs[], int index, void(*task)());
void initPreemptiveMultitasking();
void taskOne();
void taskTwo();

#endif //PreemptiveOS_H