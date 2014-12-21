#include "unity.h"
#include "Barrier.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"

extern TCB *currentTCB;

void setUp(void){}
void tearDown(void){}

void test_addTask_should_add_1_task(){
  semaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  barrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.priority = 0};
  currentTCB = &task1;
  
  addTask(&semaphore, &task1, &barrier);
  
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.tail);
}

void test_addTask_should_add_2_tasks(){
  semaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  barrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  
  currentTCB = &task1;
  addTask(&semaphore, &task1, &barrier);
  
  currentTCB = &task2;
  addTask(&semaphore, &task2, &barrier);
  
  TEST_ASSERT_EQUAL(-2, semaphore.counter);
  TEST_ASSERT_EQUAL(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task2, semaphore.waitingQueue.tail);
}

void test_addTask_should_add_3_tasks_and_flush(){
  semaphoreData semaphore = {.counter = 0, .maxCounter = 0};
  barrierData barrier = {.barrierLimit = -3};
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  TCB task3 = {.priority = 0};
  
  currentTCB = &task1;
  addTask(&semaphore, &task1, &barrier);
  
  currentTCB = &task2;
  addTask(&semaphore, &task2, &barrier);
    
  currentTCB = &task3;
  addTask(&semaphore, &task3, &barrier);
  
  TEST_ASSERT_EQUAL(0, semaphore.counter);
  TEST_ASSERT_NULL(semaphore.waitingQueue.head);
  TEST_ASSERT_NULL(semaphore.waitingQueue.tail);
}






