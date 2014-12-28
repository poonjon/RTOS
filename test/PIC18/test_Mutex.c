#include "unity.h"
#include "Mutex.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "PreemptiveOS.h"
#include "p18f4520.h"
void setUp(void){}
void tearDown(void){}

void test_create_new_mutex(){
	MutexData mutex;
  
  initMutex(&mutex);
  
  TEST_ASSERT_NOT_NULL(&mutex);
	TEST_ASSERT_EQUAL(1, mutex.count);
	TEST_ASSERT_NULL(mutex.waitingQueue.head);
	TEST_ASSERT_NULL(mutex.waitingQueue.tail);
	TEST_ASSERT_NULL(readyQueue.tail);
	TEST_ASSERT_NULL(readyQueue.head);
	TEST_ASSERT_NULL(mutex.owner);
}

void test_acquireMutex_should_return_1_acquire_mutex(){
  MutexData mutex;
  int state;
  initMutex(&mutex);
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(runningTCB, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(1, state);
}

void test_acquireMutex_should_return_0_block(){
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  MutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task2;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(&task2, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task2, mutex.waitingQueue.tail);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(0, state);
  
}

void test_acquireMutex_same_owner_should_return_1(){
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  MutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task1;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(-1, mutex.count);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL(1, state);
}

void test_acquireMutex_two_task_acquire_two_mutex(){
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  MutexData mutex = {.count = 1} ;
  MutexData mutex2 = {.count = 1} ;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  
  runningTCB = &task1;
  state = acquireMutex(&mutex);
  runningTCB = &task2;
  state = acquireMutex(&mutex2);
  
  TEST_ASSERT_EQUAL(&task2, mutex2.owner);
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(0, mutex2.count);
  TEST_ASSERT_EQUAL(1, state);
}

void test_releaseMutex_should_release_owner(){
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  MutexData mutex = {.count = 0, .owner = &task1};
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  mutex.waitingQueue.head = NULL;
  mutex.waitingQueue.tail = NULL;
  runningTCB = &task1;
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_NULL(mutex.owner);
  TEST_ASSERT_EQUAL_PTR(&task1, runningTCB);
  TEST_ASSERT_EQUAL(1, mutex.count); 
}

void test_releaseMutex_should_release_NULL(){
  TCB task1 = {.priority = 0};
  MutexData mutex = {.count = 0, .owner = &task1} ;
  runningTCB = &task1;
  mutex.waitingQueue.head = NULL;
  mutex.waitingQueue.tail = NULL;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL(1, mutex.count); 
}

void test_releaseMutex_neg1_should_save_owner(){
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  MutexData mutex = {.count = -1, .owner = &task1} ;
  runningTCB = &task1;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  mutex.waitingQueue.head = NULL;
  mutex.waitingQueue.tail = NULL;
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_EQUAL(0, mutex.count); 
}

void test_releaseMutex_should_release_mutex_until_NULL(){
  TCB task1 = {.priority = 0};
  MutexData mutex = {.count = -1, .owner = &task1} ;
  runningTCB = &task1;
  mutex.waitingQueue.head = NULL;
  mutex.waitingQueue.tail = NULL;
  readyQueue.tail = NULL;
  readyQueue.head = NULL;
  
  releaseMutex(&mutex);
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(1, mutex.count); 
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_NULL(mutex.owner);
}

void test_mutex_should_acquire_mutex_twice_and_release_twice(){
  MutexData mutex;
  int state;
  TCB task1 = {.priority = 0};
  
  initMutex(&mutex);
  
  runningTCB = &task1;
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(1, state);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);

  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(-1, mutex.count);
  TEST_ASSERT_EQUAL(1, state);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(0, mutex.count); 
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_EQUAL(&task1, mutex.owner);  
  
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(1, mutex.count); 
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_NULL(mutex.owner);
}

void test_mutex_should_acquire_mutex_block_task2_release_and_put_into_readyQueue(){
  MutexData mutex;
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  
  initMutex(&mutex);
  
  runningTCB = &task1;
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(1, state);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  
  runningTCB = &task2;
  state = acquireMutex(&mutex);
  
  TEST_ASSERT_EQUAL(&task1, mutex.owner);
  TEST_ASSERT_EQUAL(0, mutex.count);
  TEST_ASSERT_EQUAL(0, state);
  TEST_ASSERT_NULL(readyQueue.tail);
  TEST_ASSERT_NULL(readyQueue.head);
  TEST_ASSERT_EQUAL(&task2, mutex.waitingQueue.head);
  TEST_ASSERT_EQUAL(&task2, mutex.waitingQueue.tail);
  
  runningTCB = &task1;
  releaseMutex(&mutex);
  
  TEST_ASSERT_EQUAL(0, mutex.count); 
  TEST_ASSERT_EQUAL(&task2, readyQueue.tail);
  TEST_ASSERT_EQUAL(&task2, readyQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.head);
  TEST_ASSERT_NULL(mutex.waitingQueue.tail);
  TEST_ASSERT_EQUAL(&task2, mutex.owner);  
  
}
