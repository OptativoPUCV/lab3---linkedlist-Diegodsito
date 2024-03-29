#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * new = (List *)malloc(sizeof(List));
  if(new == NULL)exit(EXIT_FAILURE);
  new->head = NULL;
  new->tail = NULL;
  new->current = NULL;
     return new;
}

void * firstList(List * list) {
  if(list == NULL)return NULL;
  if(list->head == NULL)return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(list == NULL) return NULL;
  if(list->current == NULL) return NULL;
  if(list->current->next == NULL) return NULL;
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list == NULL) return NULL;
  while(list->current->next != NULL){
    list->current = list->current->next;
  }
  return list->current->data;
}

void * prevList(List * list) {
  if(list == NULL) return NULL;
  if(list->current == NULL) return NULL;
  if(list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * newNode = createNode(data);
  if(list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  }
  newNode->next = list->head;
  list->head->prev = newNode;
  list->head = newNode;
}

void pushBack(List * list, void * data) {
  Node * newNode = createNode(data);
  if(list->tail == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  }
  newNode->prev = list->tail;
  list->tail->next = newNode;
  list->tail = newNode;
}

void pushCurrent(List * list, void * data) {
  if(list->current == NULL) return;
  
  Node * newNode = createNode(data);
  newNode->next = list->current->next;
  newNode->prev = list->current;
  if(list->current->next == NULL) list->tail= newNode;
  list->current->next = newNode;
  if(list->current->next == NULL) list->tail = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list == NULL) return NULL;
  
  Node * aux = list->current;
  if(list->current == NULL) return NULL;
  
  if(list->current->prev == NULL){
    list->head = list->current->next;
    list->head->prev = NULL;
    list->current = list->head;
    return aux->data;
  }
  
  if(list->current->next == NULL){
    list->tail = list->current->prev;
    list->current = list->tail;
    list->current->next = NULL;
    return aux->data;
  }
  
  list->current = list->current->prev;
  list->current->next = list->current->next->next;
  
  
  return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}