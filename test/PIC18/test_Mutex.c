#include "unity.h"
#include "Mutex.h"
#include <malloc.h>
#include "TCB.h"
#include "PriorityLinked.h"

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
