#ifndef Mutex_H
#define Mutex_H
#include "TCB.h"
#include "PriorityLinked.h"

typedef enum {
  LOCKED,
  UNLOCKED
}State;
  
typedef struct mutexData mutexData;

struct mutexData{

	State state;
	int count;
	TCB *owner; 
	PriorityLinkedList waitingQueue;
  
};

mutexData* initMutex();
int acquireMutex(mutexData *data);
int releaseMutex(mutexData *data);

#endif // Mutex_H