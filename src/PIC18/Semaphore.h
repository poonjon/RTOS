#ifndef Semaphore_H
#define Semaphore_H
#include "PriorityLinked.h"

typedef struct{
  int counter;
  int maxCounter;
  PriorityLinkedList waitingQueue;
}Semaphore;

#endif // Semaphore_H
