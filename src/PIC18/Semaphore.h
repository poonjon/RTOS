#ifndef Semaphore_H
#define Semaphore_H
#include "PriorityLinked.h"

typedef struct semaphoreData{
  int counter;
  int maxCounter;
  PriorityLinkedList waitingQueue;
}semaphoreData;

semaphoreData* initSemaphore(int counter);
void upSemaphore(semaphoreData *semaphore);
int downSemaphore(semaphoreData *semaphore);

#endif // Semaphore_H
