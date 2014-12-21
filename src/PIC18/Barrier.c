#include <stdio.h>
#include "Barrier.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"

extern TCB *currentTCB;

void addTask(semaphoreData *semaphore, TCB *task, barrierData *barrier){
  
  if(barrier->barrierLimit != semaphore->counter){
    downSemaphore(semaphore);
  }
  
  if(barrier->barrierLimit == semaphore->counter){
    while(semaphore->counter != semaphore->maxCounter){
      upSemaphore(semaphore);
    }
  }
}
