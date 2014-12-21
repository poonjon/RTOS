#include "TCB.h"
#include "PreemptiveOS.h"
#include "Mutex.h"
#include "PriorityLinked.h"
#include <malloc.h>

extern TCB *runningTCB;

mutexData* initMutex(){
  mutexData *mutex = malloc(sizeof(mutexData));
  
	mutex->state = UNLOCKED;
	mutex->count = 0;
	mutex->waitingQueue.head = NULL;
	mutex->waitingQueue.tail = NULL;
	mutex->owner = NULL;
  
	return mutex;
}

int acquireMutex(mutexData *data){
  
  if(data->state == UNLOCKED || data->owner == runningTCB){
    data->state = LOCKED;
    data->owner = runningTCB;
    data->count = 1;
    return 1;
  }


}
