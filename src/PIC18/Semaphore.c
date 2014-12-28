#include "Semaphore.h"
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

void initSemaphore(SemaphoreData *semaphore, int counter){
  
	semaphore->counter = counter;
	semaphore->maxCounter = counter;
	semaphore->waitingQueue.head = NULL;
	semaphore->waitingQueue.tail = NULL;
	readyQueue.head = NULL;
	readyQueue.tail = NULL;
  
	
}

void initBinarySemaphore(SemaphoreData *semaphore){
  
	semaphore->counter = 1;
	semaphore->maxCounter = 1;
	semaphore->waitingQueue.head = NULL;
	semaphore->waitingQueue.tail = NULL;
  readyQueue.head = NULL;
	readyQueue.tail = NULL;
}

int downSemaphore(SemaphoreData *semaphore){
  disableGlobalInterrupt();
  semaphore->counter--;
  if(semaphore->counter > 0){
    return 1;
  }
  else{
    addPriorityLinkedList(&(semaphore->waitingQueue), runningTCB, comparePriority);
    readyQueueFlag = 1;
    timer0isr();
    readyQueueFlag = 0;
    return 0;
  }
  enableGlobalInterrupt();
}

void upSemaphore(SemaphoreData *semaphore){
  TCB *temp = NULL;
  disableGlobalInterrupt();
  if(semaphore->counter < 0 || semaphore->waitingQueue.head != NULL){
    temp = removeFromHeadPriorityLinkedList(&semaphore->waitingQueue);
    addPriorityLinkedList(&readyQueue, temp, comparePriority);
  }
  
  if(semaphore->counter == semaphore->maxCounter){}
  else
    semaphore->counter++;
  
  enableGlobalInterrupt();
}


