#include "unity.h"
#include "Semaphore.h"
#include "TCB.h"
#include "PriorityLinked.h"
#include "PreemptiveOS.h"
#include "p18f4520.h"
void setUp(void){}
void tearDown(void){}

void test_initSemaphore(){
	SemaphoreData semaphore;
  
  initSemaphore(&semaphore, 3);
  TEST_ASSERT_NOT_NULL(&semaphore);
	TEST_ASSERT_EQUAL(3, semaphore.counter);
	TEST_ASSERT_EQUAL(3, semaphore.maxCounter);
	TEST_ASSERT_NULL(semaphore.waitingQueue.head);
	TEST_ASSERT_NULL(semaphore.waitingQueue.tail);
}

void test_downSemaphore_should_decrease_counter_to_2(){
  SemaphoreData semaphore = {.counter = 3, .maxCounter = 3};
  int state;
  
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(2, semaphore.counter);
  TEST_ASSERT_EQUAL(1, state);
  
}

void test_downSemaphore_should_decrease_counter_to_1(){
  SemaphoreData semaphore = {.counter = 2, .maxCounter = 3};
  int state;
  
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(1, semaphore.counter);
  TEST_ASSERT_EQUAL(1, state);
  
}

void test_downSemaphore_should_decrease_counter_and_block(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  int state;
  TCB task1 = {.priority = 0};
  runningTCB = &task1;
  state = downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(runningTCB, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL(0, state);
  
}

void test_downSemaphore_should_decrease_counter_and_block_again(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  int state;
  TCB task1 = {.priority = 0};
  TCB task2 = {.priority = 0};
  TCB task3 = {.priority = 0};
  
  runningTCB = &task1;
  state = downSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(&task1, semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(0, state);
  
  runningTCB = &task2;
  state = downSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(-2, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task2, semaphore.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head->next->next);
  TEST_ASSERT_EQUAL_PTR(&task2, semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(0, state);
  TEST_ASSERT_EQUAL(&task2, task1.next);
  TEST_ASSERT_NULL(task2.next);
  
  runningTCB = &task3;
  state = downSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(-3, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task2, semaphore.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.head->next->next);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head->next->next->next);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(0, state);
  TEST_ASSERT_EQUAL(&task2, task1.next);
  TEST_ASSERT_EQUAL(&task3, task2.next);
  TEST_ASSERT_NULL(task3.next);
}

void test_upSemaphore_should_add_counter(){
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  
  TCB task1 = {.priority = 0};
  runningTCB = &task1;
  semaphore.waitingQueue.head = NULL;
  semaphore.waitingQueue.tail = NULL;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(1, semaphore.counter);
  TEST_ASSERT_NULL(readyQueue.head);
  
}

void test_upSemaphore_should_add_counter_and_move_task_to_readyQueue(){
  SemaphoreData semaphore = {.counter = -1, .maxCounter = 3};
  TCB task1 = {.priority = 0, .next = NULL};
  TCB tcb;
  runningTCB = &tcb;
  semaphore.waitingQueue.head = &task1;
  semaphore.waitingQueue.tail = &task1;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(0, semaphore.counter);
  TEST_ASSERT_NULL(semaphore.waitingQueue.head);
  TEST_ASSERT_NULL(semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(&task1, readyQueue.head);
  TEST_ASSERT_EQUAL(&task1, readyQueue.tail);

}

void test_upSemaphore_should_not_add_counter(){
  SemaphoreData semaphore = {.counter = 3, .maxCounter = 3};
  int state;
  TCB task1 = {.priority = 0};
  runningTCB = &task1;
  
  upSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(3, semaphore.counter);
}

void test_upSemaphore_should_remove_3_elements_from_waiting_queue_and_put_them_in_ready_queue(){
  TCB task3 = {.priority = 0, .next = NULL};
  TCB task2 = {.priority = 0, .next = NULL};
  TCB task1 = {.priority = 0, .next = NULL};
  TCB savior;
  SemaphoreData semaphore = {.counter = 0, .maxCounter = 3};
  semaphore.waitingQueue.head = NULL;
  semaphore.waitingQueue.tail = NULL;
  readyQueue.head = NULL;
  readyQueue.tail = NULL;
  
  runningTCB = &task1;
  downSemaphore(&semaphore);
  runningTCB = &task2;
  downSemaphore(&semaphore);
  runningTCB = &task3;
  downSemaphore(&semaphore);
  
  TEST_ASSERT_EQUAL(-3, semaphore.counter);
  TEST_ASSERT_EQUAL_PTR(&task1, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task2, semaphore.waitingQueue.head->next);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL(&task2, task1.next);
  TEST_ASSERT_EQUAL(&task3, task2.next);
  TEST_ASSERT_NULL(task3.next);
  
  runningTCB = &savior;
  
  upSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(-2, semaphore.counter);
  //waiting queue
  TEST_ASSERT_EQUAL_PTR(&task2, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.tail);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.head->next);
  //ready queue
  TEST_ASSERT_EQUAL(&task1, readyQueue.head);
  TEST_ASSERT_EQUAL(&task1, readyQueue.tail);
  TEST_ASSERT_EQUAL(&task3, task2.next);
  TEST_ASSERT_NULL(task3.next);
  
  upSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(-1, semaphore.counter);
  //waiting queue
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(&task3, semaphore.waitingQueue.tail);
  TEST_ASSERT_NULL(semaphore.waitingQueue.head->next);
  TEST_ASSERT_EQUAL(&task2, task1.next);
  TEST_ASSERT_NULL(task2.next);
  //ready queue
  TEST_ASSERT_EQUAL(&task1, readyQueue.head);
  TEST_ASSERT_EQUAL(&task2, readyQueue.tail);
  TEST_ASSERT_EQUAL(&task2, readyQueue.head->next);
  TEST_ASSERT_NULL(task3.next);
  
  upSemaphore(&semaphore);
  TEST_ASSERT_EQUAL(0, semaphore.counter);
  //waiting queue
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.head);
  TEST_ASSERT_EQUAL_PTR(NULL, semaphore.waitingQueue.tail);
  //ready queue
  TEST_ASSERT_EQUAL(&task1, readyQueue.head);
  TEST_ASSERT_EQUAL(&task3, readyQueue.tail);
  TEST_ASSERT_EQUAL(&task2, readyQueue.head->next);
  TEST_ASSERT_EQUAL(&task2, task1.next);
  TEST_ASSERT_EQUAL(&task3, task2.next);
  TEST_ASSERT_NULL(task3.next);
}



