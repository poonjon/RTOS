#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include <malloc.h>

TCB *currentTCB;

semaphoreData* initSemaphore(int counter){
  semaphoreData *semaphore = malloc(sizeof(semaphoreData));
	semaphore->counter = counter;
	semaphore->maxCounter = counter;
	semaphore->waitingQueue.head = NULL;
	semaphore->waitingQueue.tail = NULL;
  
	return semaphore;
}

int downSemaphore(semaphoreData *semaphore){
  
  semaphore->counter--;
  if(semaphore->counter > 0){
    return 1;
  }
  else{
    addPriorityLinkedList(&(semaphore->waitingQueue), currentTCB, comparePriority) ;
    return 0;
  }
}

void upSemaphore(semaphoreData *semaphore){
  
  if(semaphore->counter < 0){
    currentTCB = removeFromHeadPriorityLinkedList(&(semaphore->waitingQueue));
  }
  
  if(semaphore->counter == semaphore->maxCounter){}
  else
    semaphore->counter++;
  
}