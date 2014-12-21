#include "unity.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "Mutex.h"
#include <malloc.h>

extern TCB *runningTCB;

void setUp(void){}
void tearDown(void){}

void test_create_new_mutex(){
	mutexData *mutex;
  
  mutex = initMutex();
  TEST_ASSERT_NOT_NULL(mutex);
	TEST_ASSERT_EQUAL(1, mutex->count);
	TEST_ASSERT_NULL(mutex->waitingQueue.head);
	TEST_ASSERT_NULL(mutex->waitingQueue.tail);
	TEST_ASSERT_NULL(mutex->owner);
}

void test_acquireMutex_should_return_1_acquire_mutex(){
  mutexData *mutex;
  int state;
  mutex = initMutex();
  state = acquireMutex(mutex);
  TEST_ASSERT_EQUAL(runningTCB, mutex->owner);
  TEST_ASSERT_EQUAL(0, mutex->count);
  TEST_ASSERT_EQUAL(1, state);
  
}

void test_acquireMutex_should_return_0_block(){
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  mutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task2;
  
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(0, state);
  
}

void test_acquireMutex_same_owner_should_return_1(){
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  mutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task1;
  
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(-1, mutex.count);
  TEST_ASSERT_EQUAL(1, state);
}

void test_releaseMutex_should_release_owner(){
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  mutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task1;
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_NULL(mutex.owner);
  TEST_ASSERT_EQUAL(1, mutex.count); 
}

void test_releaseMutex_neg1_should_save_owner(){
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  mutexData mutex = {.count = -1, .owner = &task1} ;
  runningTCB = &task1;
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count); 
}


