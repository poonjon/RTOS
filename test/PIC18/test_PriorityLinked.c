#include "unity.h"
#include "PriorityLinked.h"

void setUp(void){}
void tearDown(void){}

void test_craetePriorityLinkedList_should_create_linkedList(){
  PriorityLinkedList list;
  
  createPriorityLinkedList(&list);
  
  TEST_ASSERT_NULL(list.head);
  TEST_ASSERT_NOT_NULL(&list);
}

void test_compare_priority_list_element_smaller_shouled_return_1(void){
  int result;
  TCB list = {.priority = 1};
  TCB insert = {.priority = 2};
  
  result = comparePriority(&list, &insert);
  
  TEST_ASSERT_EQUAL(1, result);
}

void test_compare_priority_list_element_larger_should_return_0(void){
  int result;
  TCB list = {.priority = 2};
  TCB insert = {.priority = 1};
  
  result = comparePriority(&list, &insert);
  
  TEST_ASSERT_EQUAL(0, result);
}

void test_compare_priority_list_element_same_priority_should_return_0(void){
  int result;
  TCB list = {.priority = 1};
  TCB insert = {.priority = 1};
  
  result = comparePriority(&list, &insert);
  
  TEST_ASSERT_EQUAL(result, 0);
}

void test_removeFromHeadPriorityLinkedList_TCB1_should_be_removed_TCB2_should_be_head(){
  PriorityLinkedList list;
  TCB *removedElement;
  createPriorityLinkedList(&list);
  
  TCB TCB2 = {.next = NULL, .priority = 2};
  TCB TCB1 = {.next = &TCB2, .priority = 1};
  
  list.head = &TCB1;
  list.tail = &TCB2;
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  
  TEST_ASSERT_EQUAL(list.head, &TCB2);
  TEST_ASSERT_EQUAL(list.tail, &TCB2);
  TEST_ASSERT_EQUAL(removedElement, &TCB1);
  
  
}

void test_removeFromHeadPriorityLinkedList_TCB1_should_be_removed_head_should_be_null(){
  PriorityLinkedList list;
  TCB *removedElement;
  createPriorityLinkedList(&list);
  
  TCB TCB1 = {.next = NULL, .priority = 1};
  
  list.head = &TCB1;
  list.tail = &TCB1;
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  
  TEST_ASSERT_NULL(list.head);
  TEST_ASSERT_NULL(list.tail);
  TEST_ASSERT_EQUAL(removedElement, &TCB1);
  
}

void test_removeFromHeadPriorityLinkedList_TCB1_TCB2_should_be_removed_TCB3_should_be_head(){
  PriorityLinkedList list;
  TCB *removedElement;
  createPriorityLinkedList(&list);
  
  TCB TCB3 = {.next = NULL, .priority = 1};
  TCB TCB2 = {.next = &TCB3, .priority = 2};
  TCB TCB1 = {.next = &TCB2, .priority = 3};
  
  list.head = &TCB1;
  list.tail = &TCB3;
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB1, removedElement);
  TEST_ASSERT_EQUAL(&TCB2, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.head->next);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB2, removedElement);
  TEST_ASSERT_EQUAL(&TCB3, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  TEST_ASSERT_EQUAL(NULL, list.head->next);
  
}

void test_removeFromHeadPriorityLinkedList_TCB1_TCB2_TCB3_should_be_removed(){
  PriorityLinkedList list;
  TCB *removedElement;
  createPriorityLinkedList(&list);
  
  TCB TCB3 = {.next = NULL, .priority = 1};
  TCB TCB2 = {.next = &TCB3, .priority = 2};
  TCB TCB1 = {.next = &TCB2, .priority = 3};
  
  list.head = &TCB1;
  list.tail = &TCB3;
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB1, removedElement);
  TEST_ASSERT_EQUAL(&TCB2, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.head->next);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB2, removedElement);
  TEST_ASSERT_EQUAL(&TCB3, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  TEST_ASSERT_EQUAL(NULL, list.head->next);  

  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB3, removedElement);
  TEST_ASSERT_NULL(list.head);
  TEST_ASSERT_NULL(list.tail);
    
}

void test_addPriorityLinked_TCB1_into_empty_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  

  TCB TCB1 = {.next = NULL, .priority = 1};

  list.head = NULL;
  list.tail = NULL;

  addPriorityLinkedList(&list, &TCB1, comparePriority);

  TEST_ASSERT_NOT_NULL(list.head);
  TEST_ASSERT_NOT_NULL(list.tail);
  

}

void test_addPriorityLinked_lower_priority_TCB1_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);  
  
  TCB TCB1 = {.next = NULL, .priority = 1};
  TCB TCB2 = {.next = NULL, .priority = 20};

  list.head = &TCB2;
  list.tail = &TCB2;
  
  addPriorityLinkedList(&list, &TCB1, comparePriority);

  TEST_ASSERT_EQUAL(list.head, &TCB2);
  TEST_ASSERT_EQUAL(list.tail, &TCB1);
  TEST_ASSERT_EQUAL(TCB2.next, &TCB1);
  TEST_ASSERT_NULL(TCB1.next);
  
}

void test_addPriorityLinked_lower_priority_TCB3_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  
  TCB TCB3 = {.next = NULL, .priority = 20};
  TCB TCB2 = {.next = NULL, .priority = 20};
  TCB TCB1 = {.next = NULL, .priority = 20};

  list.head = &TCB1;
  list.tail = &TCB1;
  
  addPriorityLinkedList(&list, &TCB2, comparePriority);
  addPriorityLinkedList(&list, &TCB3, comparePriority);

  TEST_ASSERT_EQUAL(list.head, &TCB1);
  TEST_ASSERT_EQUAL(list.tail, &TCB3);
  TEST_ASSERT_EQUAL(TCB1.next, &TCB2);
  TEST_ASSERT_EQUAL(TCB2.next, &TCB3);
  TEST_ASSERT_NULL(TCB3.next);
  
}

void test_addPriorityLinked_higher_priority_TCB1_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  
  TCB TCB1 = {.next = NULL, .priority = 40};
  TCB TCB2 = {.next = NULL, .priority = 20};

  list.head = &TCB2;
  list.tail = &TCB2;

  addPriorityLinkedList(&list, &TCB1, comparePriority);
  TEST_ASSERT_EQUAL(&TCB1, list.head);
  TEST_ASSERT_EQUAL(&TCB2, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_NULL(TCB2.next);
  
}

void test_addPriorityLinked_inbetween_priority_TCB1_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  
  TCB TCB3 = {.next = NULL, .priority = 20};
  TCB TCB2 = {.next = &TCB3, .priority = 50};
  TCB TCB1 = {.next = NULL, .priority = 40};

  list.head = &TCB2;
  list.tail = &TCB3;

  addPriorityLinkedList(&list, &TCB1, comparePriority);
  TEST_ASSERT_EQUAL(&TCB2, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  TEST_ASSERT_EQUAL( &TCB1, TCB2.next);
  TEST_ASSERT_EQUAL(&TCB3, TCB1.next);
  TEST_ASSERT_NULL(TCB3.next);
  
}

void test_addPriorityLinked_add_same_priority_TCB3_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  
  TCB TCB3 = {.next = NULL, .priority = 0};
  TCB TCB2 = {.next = NULL, .priority = 0};
  TCB TCB1 = {.next = &TCB2, .priority = 0};

  list.head = &TCB1;
  list.tail = &TCB2;

  addPriorityLinkedList(&list, &TCB3, comparePriority);
  TEST_ASSERT_EQUAL(&TCB1, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_EQUAL(&TCB3, TCB2.next);
  TEST_ASSERT_NULL(TCB3.next);
  
}

void test_addPriorityLinked_add_4_same_priority_into_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  
  TCB TCB4 = {.next = NULL, .priority = 0};
  TCB TCB3 = {.next = NULL, .priority = 0};
  TCB TCB2 = {.next = NULL, .priority = 0};
  TCB TCB1 = {.next = NULL, .priority = 0};

  list.head = &TCB1;
  list.tail = &TCB1;

  addPriorityLinkedList(&list, &TCB2, comparePriority);
  addPriorityLinkedList(&list, &TCB3, comparePriority);
  addPriorityLinkedList(&list, &TCB4, comparePriority);
  TEST_ASSERT_EQUAL(&TCB1, list.head);
  TEST_ASSERT_EQUAL(&TCB4, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_EQUAL(&TCB3, TCB2.next);
  TEST_ASSERT_EQUAL(&TCB4, TCB3.next);
  TEST_ASSERT_NULL(TCB4.next);
  
}

void test_addPriorityLinked_add_3_same_priority_into_list_and_removeFromHeadPriorityLinkedList_remove_3_from_list(){
  PriorityLinkedList list;
  createPriorityLinkedList(&list);
  TCB *removedElement;
  
  TCB TCB4 = {.next = NULL, .priority = 0};
  TCB TCB3 = {.next = NULL, .priority = 0};
  TCB TCB2 = {.next = NULL, .priority = 0};
  TCB TCB1 = {.next = NULL, .priority = 0};

  list.head = &TCB1;
  list.tail = &TCB1;

  addPriorityLinkedList(&list, &TCB2, comparePriority);
  TEST_ASSERT_EQUAL(&TCB2, list.head->next);
  TEST_ASSERT_EQUAL(&TCB1, list.head);
  TEST_ASSERT_EQUAL(&TCB2, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_NULL(TCB2.next);
  
  addPriorityLinkedList(&list, &TCB3, comparePriority);
  TEST_ASSERT_EQUAL(&TCB3, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_EQUAL(&TCB3, TCB2.next);
  TEST_ASSERT_NULL(TCB3.next);
  
  addPriorityLinkedList(&list, &TCB4, comparePriority);
  TEST_ASSERT_EQUAL(&TCB4, list.tail);
  TEST_ASSERT_EQUAL(&TCB2, TCB1.next);
  TEST_ASSERT_EQUAL(&TCB3, TCB2.next);
  TEST_ASSERT_EQUAL(&TCB4, TCB3.next);
  TEST_ASSERT_NULL(TCB4.next);
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB1, removedElement);
  TEST_ASSERT_EQUAL(&TCB2, list.head);
  TEST_ASSERT_EQUAL(&TCB3, list.head->next);
  TEST_ASSERT_EQUAL(&TCB4, list.tail);
  TEST_ASSERT_EQUAL(&TCB3, TCB2.next);
  TEST_ASSERT_EQUAL(&TCB4, TCB3.next);
  TEST_ASSERT_NULL(TCB4.next);
  TEST_ASSERT_NULL(TCB1.next);
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB2, removedElement);
  TEST_ASSERT_EQUAL(&TCB3, list.head);
  TEST_ASSERT_EQUAL(&TCB4, list.tail);
  TEST_ASSERT_EQUAL(&TCB4, list.head->next);  
  TEST_ASSERT_EQUAL(&TCB4, TCB3.next);
  TEST_ASSERT_NULL(TCB4.next);
  
  removedElement = removeFromHeadPriorityLinkedList(&list);
  TEST_ASSERT_EQUAL(&TCB3, removedElement);
  TEST_ASSERT_EQUAL(&TCB4, list.head);
  TEST_ASSERT_EQUAL(&TCB4, list.tail);
  TEST_ASSERT_NULL(TCB4.next);
}






