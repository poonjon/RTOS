#ifndef Barrier_H
#define Barrier_H
#include "Semaphore.h"
#include "TCB.h"

typedef struct barrierData{
  int barrierLimit;
  
}barrierData;


void addTask(semaphoreData *semaphore, TCB *task, barrierData *numOfTasks);
#endif // Barrier_H
