#include "defs.h"

void initRestaurant(RestaurantType *r, char *n){
  strcpy(r->name, n);
  initResvList(&(r->resvList));
  initPatronArray(&(r->patrons));
}

int validateRevTime(int yr, int mth, int day, int hr, int min){
  if(yr<2023 || mth<1 || mth>12 || day<1 || day>31 || hr<0 || hr>23 || min<0 || min>59){
    return C_NOK;
  }
  return C_OK;
}

void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min){
  PatronType *p=NULL;
  
  int validTime = validateRevTime(yr, mth, day, hr, min);
  int validPatron = findPatron(&(r->patrons), pId, &p);
  
  if(validTime==C_NOK){
    printf("ERROR:  Date %d-%d-%d or time %d-%d is invalid\n",yr,mth,day,hr,min); 
  }
  
  if(validPatron==C_NOK){
    printf("ERROR:  Patron id %d was not found\n", pId);
  }
  
  if(validTime==C_OK && validPatron==C_OK){
    ResvTimeType *time;
    initResvTime(&time, yr, mth, day, hr, min);
  
    ResvType *rv;
    initResv(&rv, p, time);
  
    addResv(&(r->resvList), rv);
   
  }
  
  
}

void printResByPatron(RestaurantType *r, int id){
  
  PatronType *p=NULL;
  
  if(findPatron(&(r->patrons), id, &p)==C_OK){
    NodeType *currNode = r->resvList.head;
    printf("\nRESERVATIONS BY PATRON at %s\n",r->name);
    while(currNode!=NULL){
      if(currNode->data->patron->id == p->id){
        printReservation(currNode->data);
      }
      currNode = currNode->next;
    }
  }
  else{
    printf("ERROR: patron not found.\n");
  }
}

void cleanupRestaurant(RestaurantType *r){
  cleanupResvList(&(r->resvList));
  cleanupPatronArray(&(r->patrons));
}