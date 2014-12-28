#include <stdio.h>
#include "Barrier.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "Interrupt.h"

// ignore scheduler for PC test
#if !(defined(__XC) || defined(__18CXX))
  #define timer0isr()
#else
  #include Clock.h
#endif // __18CXX

void setBarrierLimit(BarrierData *barrier, int limit){
   barrier->barrierLimit = limit;
}

void addTask(SemaphoreData *semaphore, TCB *task, BarrierData *barrier){
  
  disableGlobalInterrupt(); 

  if(barrier->barrierLimit != semaphore->counter){
    downSemaphore(semaphore);
    disableGlobalInterrupt(); 
  }
  
  if(barrier->barrierLimit == semaphore->counter){
    while(semaphore->counter != semaphore->maxCounter){
      upSemaphore(semaphore);
      disableGlobalInterrupt(); 
    }
  }
  
  enableGlobalInterrupt();
  
}


