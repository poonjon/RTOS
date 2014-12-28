#include "PriorityLinked.h"
#include <stdio.h>
#include "TCB.h"

void createPriorityLinkedList(PriorityLinkedList *list){
  list->head = NULL;
  list->tail = NULL;
}

/**
  * compare listElement with insertElement
  * return 0: listElement > insertElement
  * return 1: listElement < insertElement
**/
int comparePriority(void *listElement, void *insertElement){
  if(((TCB *)listElement) != NULL && ((TCB *)insertElement) != NULL){
    if(((TCB *)listElement)->priority >= ((TCB *)insertElement)->priority){
      return 0;
    }
    else
      return 1;
  }
  else if(((TCB *)listElement) == NULL && ((TCB *)insertElement) != NULL){
    return 1;
  }
  
}

void *removeFromHeadPriorityLinkedList(PriorityLinkedList *list){
  TCB *removedElement;
  
  removedElement = list->head;
  if(list->head != NULL){
    list->head = list->head->next;
    removedElement->next = NULL;
  }
  if(list->head == NULL){
    list->tail = NULL;
  }
  return removedElement;
}

void addPriorityLinkedList(PriorityLinkedList *list, void *data, int compare(void *, void *)){
  TCB *newList;
  TCB *prevList;
  
  newList = list->head;
  prevList = list->head;
  
  if(list->head == NULL){
    list->head = data;
    list->tail = data;
  }
  else{    
    if(compare(newList, data) == 0){
      if(newList->next == NULL){
        newList->next = (TCB *)data;
        list->tail = newList->next;
      }
      else{
        while(compare(newList, data) == 0){
          
          if(newList->next == NULL){
            newList->next = (TCB *)data;
            list->tail = newList->next;
            break;
          }
          else if(compare(newList->next, data) == 1){
            ((TCB *)data)->next = prevList->next;
            prevList->next = (TCB *)data;           
            break;
          }
          prevList = newList;
          newList = newList->next;
        }
      }
    }
    else{
      if(newList->next == NULL){
        list->head = (TCB *)data;
      }
      ((TCB *)data)->next = newList;
      list->tail = newList;
    } 
  }
}


