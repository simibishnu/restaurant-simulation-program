#include <stdio.h>
#include <string.h>
#include "defs.h"

void initPatronArray(PatronArrayType *arr){
  arr->elements = calloc(MAX_CAP,sizeof(PatronType));
  arr->size = 0;
  arr->nextId = PATRON_IDS;
}

void addPatron(PatronArrayType *arr, char *n){
  
  if(arr->size >= MAX_CAP){
    PatronType *tmp;
    tmp = calloc((arr->size+1), sizeof(PatronType));
    
    for(int i=0; i<arr->size; ++i){
      tmp[i] = (arr->elements)[i];
    }
    cleanupPatronArray(arr);
    arr->elements = tmp;
  }
  
  PatronType newPatron;
  strcpy(newPatron.name,n);
  newPatron.id = arr->nextId;
  
  (arr->elements)[arr->size] = newPatron;
  arr->size++; 
  arr->nextId++;
}

int findPatron(PatronArrayType *arr, int id, PatronType **p){
  
  if(arr->size>0){
    for(int i=0; i<arr->size; ++i){
      if((arr->elements)[i].id == id){
        *p = &(arr->elements[i]);
      }
    }
  }
  
  if(*p == NULL){
    return C_NOK;
  }
 
  return C_OK;
}

void printPatrons(PatronArrayType *arr){
  for(int i=0; i<arr->size; ++i){
    printf("Patron #%d %s\n",(arr->elements[i]).id, (arr->elements)[i].name);
  }
}

void cleanupPatronArray(PatronArrayType *arr){
  free(arr->elements);
}
