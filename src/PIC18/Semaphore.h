#ifndef Semaphore_H
#define Semaphore_H
#include "PriorityLinked.h"

typedef struct SemaphoreData{
  int counter;
  int maxCounter;
  PriorityLinkedList waitingQueue;
}SemaphoreData;

void initBinarySemaphore(SemaphoreData *semaphore);
void initSemaphore(SemaphoreData *semaphore, int counter);
void upSemaphore(SemaphoreData *semaphore);
int downSemaphore(SemaphoreData *semaphore);

#endif // Semaphore_H
