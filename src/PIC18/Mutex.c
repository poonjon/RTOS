#include <malloc.h>
#include "Mutex.h"
#include "PriorityLinked.h"
#include "TCB.h"

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
