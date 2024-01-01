#include "defs.h"

void initResvList(ResvListType *list){
  list->head = NULL;
  list->nextId = RES_IDS;
}

void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min){
  ResvTimeType *tmp;
  tmp = calloc(1, sizeof(ResvTimeType));
  tmp->year = yr;
  tmp->month = mth;
  tmp->day = day;
  tmp->hours = hr;
  tmp->minutes = min;
  *rt = tmp;
  
}

void initResv(ResvType **r, PatronType *p, ResvTimeType *rt){
  ResvType *tmp;
  tmp = calloc(1, sizeof(ResvType));
  tmp->id = 0;
  tmp->patron = p;
  tmp->resvTime = rt;
  *r = tmp;
}

int lessThan(ResvTimeType *r1, ResvTimeType *r2){
  if(r1->year<r2->year || ((r1->year==r2->year) && (r1->month<r2->month)) || ((r1->year==r2->year) && (r1->month==r2->month) && (r1->day<r2->day)) || ((r1->year==r2->year) && (r1->month==r2->month) && 
    (r1->day==r2->day) && (r1->hours<r2->hours)) || ((r1->year==r2->year) && (r1->month==r2->month) && (r1->day==r2->day) && (r1->hours==r2->hours) && (r1->minutes<r2->minutes))){
    return C_OK;
  }
  return C_NOK;
}

void addResv(ResvListType *list, ResvType *r){
  NodeType *newNode;
  NodeType *currNode;
  NodeType *prevNode;
  
  r->id = list->nextId;
  newNode = calloc(1, sizeof(NodeType));
  newNode->data = r;
  newNode->prev = NULL;
  newNode->next = NULL;
  
  currNode = list->head;
  prevNode = NULL;
  
  while(currNode!=NULL){
    if(lessThan(r->resvTime, currNode->data->resvTime)==C_OK){
      break;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }
  
  if(prevNode == NULL){
    list->head = newNode;
  }
  else{
    prevNode->next = newNode;
    newNode->prev = prevNode;
  }
  
  newNode->next = currNode;
  
  if(currNode!=NULL){
    currNode->prev = newNode;
  }
  
  list->nextId++;
}

void printReservation(ResvType *r){
  printf("%-2d :: %d-%02d-%02d @ %02d:%02d :: %s\n",r->id, r->resvTime->year, r->resvTime->month, r->resvTime->day, r->resvTime->hours, r->resvTime->minutes, r->patron->name);
}

void printReservations(ResvListType *list){
  NodeType *currNode = list->head;
  NodeType *prevNode = NULL;
  
  printf("\nFORWARDS:\n");
  while(currNode!=NULL){
    printReservation(currNode->data);
    prevNode = currNode;
    currNode = currNode->next;
  }
  
  printf("\nBACKWARDS:\n");
  currNode = prevNode;
  while(currNode!=NULL){
    printReservation(currNode->data);
    prevNode = currNode;
    currNode = currNode->prev;
  
  }

}

void cleanupResvList(ResvListType *list){
  NodeType *currNode = list->head;
  NodeType *nextNode;
  
  while(currNode!=NULL){
    nextNode = currNode->next;
    free(currNode->data->resvTime);
    free(currNode->data);
    free(currNode);
    currNode = nextNode; 
  }
}

