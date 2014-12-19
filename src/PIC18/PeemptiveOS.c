#include "TCB.h"
#include "PriorityLinked.h"
#include "PreemptiveOS.h"
#include "Types.h"
#include "TCB.h"
#include <stdio.h>

TCB *runningTCB;
TCB allTCBs[3];
uint8 stacks[2][80];
PriorityLinkedList readyQueue;

void createTask(TCB TCBs[], int index, void(*task)()){
  TCBs[index].next = NULL;
  TCBs[index].priority = 0;
  TCBs[index].task = (uint16)task;
  TCBs[index].stackPointer = (uint16)&stacks[index-1]+34;
  stacks[index - 1][4] = (uint16)&stacks[index - 1] + 34;
  TCBs[index].taskID = index;
  addPriorityLinkedList(&readyQueue, &allTCBs[index], comparePriority);

}

void initPreemptiveMultitasking(){
  readyQueue.head = NULL;
  readyQueue.tail = NULL;
  runningTCB = &allTCBs[0];
  runningTCB->next - NULL;
  createTask(allTCBs, 1, &taskOne);
  createTask(allTCBs, 2, &taskTwo);
}

void taskOne(){
    int i = 0;
    while(i != 100000){
        i++;
    }

}

void taskTwo(){
    int j = 0;
    while(j != 100000){
        j++;
    }

}