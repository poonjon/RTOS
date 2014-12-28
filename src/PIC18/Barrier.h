#ifndef Barrier_H
#define Barrier_H
#include "Semaphore.h"
#include "TCB.h"

typedef struct BarrierData{
  int barrierLimit;
  
}BarrierData;

void setBarrierLimit(BarrierData *barrier, int limit);
void addTask(SemaphoreData *semaphore, TCB *task, BarrierData *barrier);
#endif // Barrier_H
