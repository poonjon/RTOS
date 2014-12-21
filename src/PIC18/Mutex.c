#include "TCB.h"
#include "Mutex.h"
#include "PriorityLinked.h"
#include <malloc.h>

TCB *runningTCB;

mutexData* initMutex(){
  mutexData *mutex = malloc(sizeof(mutexData));
	mutex->count = 1;
	mutex->waitingQueue.head = NULL;
	mutex->waitingQueue.tail = NULL;
	mutex->owner = NULL;
  
	return mutex;
}

int acquireMutex(mutexData *data){
  
  if(data->count == 1 || data->owner == runningTCB){
    data->owner = runningTCB;
    data->count--;
    return 1;
  }
  else{
    addPriorityLinkedList(&(data->waitingQueue), runningTCB, comparePriority);
    return 0;
  }
 
}

void releaseMutex(mutexData *data){
  
  data->count++;
  if(data->count < 1){}
  else{
    if(data->waitingQueue.head == NULL){
      runningTCB = NULL;
    }
    else{
      runningTCB = removeFromHeadPriorityLinkedList(&(data->waitingQueue));
      data->owner = runningTCB;
      data->count--;
    }
  }
}