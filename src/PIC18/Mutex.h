#ifndef Mutex_H
#define Mutex_H
#include "TCB.h"
#include "PriorityLinked.h"

typedef struct mutexData mutexData;

struct mutexData{

	int count;
	TCB *owner; 
	PriorityLinkedList waitingQueue;
  
};

mutexData* initMutex();
int acquireMutex(mutexData *data);
void releaseMutex(mutexData *data);

#endif // Mutex_H