#include "unity.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include <malloc.h>

extern TCB *currentTCB;

void setUp(void){}
void tearDown(void){}

void test_initSemaphore(){
	semaphoreData *semaphore;
  
  semaphore = initSemaphore(3);
  TEST_ASSERT_NOT_NULL(&semaphore);
	TEST_ASSERT_EQUAL(3, semaphore->counter);
	TEST_ASSERT_EQUAL(3, semaphore->maxCounter);
	TEST_ASSERT_NULL(semaphore->waitingQueue.head);
	TEST_ASSERT_NULL(semaphore->waitingQueue.tail);
}

void test_downSemaphore_should_decrease_counter_to_2(){
  semaphoreData semaphore = {.counter = 3, .maxCounter = 3};
  int state;
  
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(2, semaphore.counter);
  TEST_ASSERT_EQUAL(1, state);
  
}

void test_downSemaphore_should_decrease_counter_to_1(){
  semaphoreData semaphore = {.counter = 2, .maxCounter = 3};
  int state;
  
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(1, semaphore.counter);
  TEST_ASSERT_EQUAL(1, state);
  
}

void test_downSemaphore_should_decrease_counter_and_block(){
  semaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  int state;
  TCB task1 = {.priority = 0};
  currentTCB = &task1;
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(currentTCB, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(0, state);
  
}

void test_upSemaphore_should_add_counter(){
  semaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  
  TCB task1 = {.priority = 0};
  currentTCB = &task1;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(1, semaphore.counter);
  
}

void test_upSemaphore_should_not_add_counter(){
  semaphoreData semaphore = {.counter = 3, .maxCounter = 3};
  int state;
  TCB task1 = {.priority = 0};
  currentTCB = &task1;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(3, semaphore.counter);
}

void test_upSemaphore_should_add_counter_and_add_currentTCB(){
  semaphoreData semaphore = {.counter = -1, .maxCounter = 3};

  TCB task1 = {.priority = 0};
  currentTCB = NULL;
  semaphore.waitingQueue.head = &task1;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(0, semaphore.counter);
  TEST_ASSERT_EQUAL(&task1, currentTCB);
  TEST_ASSERT_NULL(semaphore.waitingQueue.head);
  TEST_ASSERT_NULL(semaphore.waitingQueue.tail);

}

