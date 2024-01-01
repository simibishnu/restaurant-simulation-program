#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{
  RestaurantType r;
  int choice;
  
  initRestaurant(&r, "The Restaurant");
  loadPatronData(&r);
  loadResData(&r);
  
  while(1){
    printMenu(&choice);
    
    if(choice==1){
      printf("\nREGISTERED PATRONS at %s\n",r.name);
      printPatrons(&(r.patrons));
    }
    else if(choice==2){
      printf("\nRESERVATIONS at %s\n",r.name);
      printReservations(&(r.resvList));
    }
    else if(choice==3){
      int pId;
      printf("Enter patron id: ");
      scanf("%d",&pId);
      printf("\n");
      printResByPatron(&r,pId); 
    
    }
    else{
      break;
    }
  }
  
  
  cleanupRestaurant(&r);
  
  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print patrons\n");
  printf("  (2) Print reservations\n");
  printf("  (3) Print reservations by patron\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}
