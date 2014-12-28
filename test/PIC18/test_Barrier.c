#include "unity.h"
#include "Barrier.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "PreemptiveOS.h"
#include "p18f4520.h"
void setUp(void){}
void tearDown(void){}

void test_createBarrierData_should_set_limit(){
  BarrierData barrier;
  
  setBarrierLimit(&barrier, -3);
  
  TEST_ASSERT_EQUAL(-3, barrier.barrierLimit);

}

void test_addTask_should_add_1_task(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  BarrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.priority = 0};
  runningTCB = &task1;
  
  addTask(&semaphore, &task1, &barrier);
  
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.tail);
}

void test_addTask_should_add_2_tasks(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  BarrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  
  runningTCB = &task1;
  addTask(&semaphore, &task1, &barrier);
  
  runningTCB = &task2;
  addTask(&semaphore, &task2, &barrier);
  
  TEST_ASSERT_EQUAL(-2, semaphore.counter);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task2, semaphore.waitingQueue.tail);
}

void test_addTask_should_add_3_tasks_and_flush(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  BarrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.taskID = 1, .priority = 0};
  TCB task2 = {.taskID = 2, .priority = 0};
  TCB task3 = {.taskID = 3, .priority = 0};

  runningTCB = &task1;
  addTask(&semaphore, &task1, &barrier);
  
  runningTCB = &task2;
  addTask(&semaphore, &task2, &barrier);
    
  runningTCB = &task3;
  addTask(&semaphore, &task3, &barrier);
  
  TEST_ASSERT_EQUAL(0, semaphore.counter);
  TEST_ASSERT_NULL(semaphore.waitingQueue.head);
  TEST_ASSERT_NULL(semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(&task1, readyQueue.head);
  TEST_ASSERT_EQUAL(&task2, readyQueue.head->next);
  TEST_ASSERT_EQUAL(&task3, readyQueue.tail);
}






