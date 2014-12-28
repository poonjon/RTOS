#ifndef Mutex_H
#define Mutex_H
#include "TCB.h"
#include "PriorityLinked.h"

typedef struct MutexData MutexData;

struct MutexData{

	int count;
	TCB *owner; 
	PriorityLinkedList waitingQueue;
  
};

void initMutex(MutexData *mutex);
int acquireMutex(MutexData *mutex);
void releaseMutex(MutexData *mutex);

#endif // Mutex_H