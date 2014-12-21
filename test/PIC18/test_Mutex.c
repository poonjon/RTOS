#include "unity.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "Mutex.h"
#include "PreemptiveOS.h"
#include <malloc.h>

extern TCB *runningTCB;

void setUp(void){}
void tearDown(void){}

void test_create_new_mutex(){
	mutexData *mutex;
  
  mutex = initMutex();
  TEST_ASSERT_NOT_NULL(mutex);
	TEST_ASSERT_EQUAL(0, mutex->count);
	TEST_ASSERT_NULL(mutex->waitingQueue.head);
	TEST_ASSERT_NULL(mutex->waitingQueue.tail);
	TEST_ASSERT_NULL(mutex->owner);
	TEST_ASSERT_EQUAL(UNLOCKED, mutex->state);
}

void test_acquireMutex_should_return_1_acquire_mutex(){
  mutexData *mutex;

  mutex = initMutex();
  acquireMutex(mutex);
  TEST_ASSERT_EQUAL(LOCKED, mutex->state);
  TEST_ASSERT_EQUAL(runningTCB, mutex->owner);
  TEST_ASSERT_EQUAL(1, mutex->count);
  
}