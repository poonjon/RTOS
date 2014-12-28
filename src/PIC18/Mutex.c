#include "Mutex.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "PreemptiveOS.h"
#include <stdio.h>
#include "Interrupt.h"

// ignore scheduler for PC test
#if !(defined(__XC) || defined(__18CXX))
  #define timer0isr()
#else
  #include Clock.h
#endif // __18CXX

void initMutex(MutexData *mutex){
  
	mutex->count = 1;
	mutex->waitingQueue.head = NULL;
	mutex->waitingQueue.tail = NULL;
	readyQueue.tail = NULL;
	readyQueue.head = NULL;
	mutex->owner = NULL;
 
}

int acquireMutex(MutexData *mutex){
  disableGlobalInterrupt();
  if(mutex->count == 1 || mutex->owner == runningTCB){
    mutex->owner = runningTCB;
    mutex->count--;
    return 1;
  }
  else{
    addPriorityLinkedList(&(mutex->waitingQueue), runningTCB, comparePriority);
    readyQueueFlag = 1;
    timer0isr();
    readyQueueFlag = 0;
    return 0;
  }
 
  enableGlobalInterrupt();
}

void releaseMutex(MutexData *mutex){
  TCB *temp = NULL;
  disableGlobalInterrupt();
  
  if(mutex->owner == runningTCB){
    
    mutex->count++;  
    if(mutex->count < 1){}
    else{
      if(mutex->waitingQueue.head == NULL){
        mutex->owner = NULL;
      }
      else{
        temp = removeFromHeadPriorityLinkedList(&(mutex->waitingQueue));
        addPriorityLinkedList(&readyQueue, temp, comparePriority);
        mutex->owner = temp;
        mutex->count--;
      }
    }
  }
  enableGlobalInterrupt();
}

