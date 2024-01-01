typedef struct {
  PatronType *elements;
  int size;
  int nextId;
}PatronArrayType;

/*** Define the NodeType here ***/
typedef struct Node{
  ResvType *data;
  struct Node *prev;
  struct Node *next;
}NodeType;

/*** Define the ResvListType here ***/
typedef struct{
  NodeType *head;
  int nextId;
}ResvListType;

/*** Define the RestaurantType here ***/
typedef struct{
  char name[MAX_STR];
  ResvListType resvList;
  PatronArrayType patrons;
}RestaurantType;

void printMenu(int*);
void loadPatronData(RestaurantType*);
void loadResData(RestaurantType*);

void initPatronArray(PatronArrayType*);
void addPatron(PatronArrayType*, char*);
int findPatron(PatronArrayType*, int, PatronType**);
void printPatrons(PatronArrayType*);
void cleanupPatronArray(PatronArrayType*);

void initResvList(ResvListType*);
void initResvTime(ResvTimeType**, int yr, int mth, int day, int hr, int min);
void initResv(ResvType**, PatronType*, ResvTimeType*);
int lessThan(ResvTimeType*, ResvTimeType*);
void addResv(ResvListType*, ResvType*);
void printReservation(ResvType*);
void printReservations(ResvListType*);
void cleanupResvList(ResvListType*);

void initRestaurant(RestaurantType*, char*);
int validateResvTime(int, int, int, int, int);
void createResv(RestaurantType*, int, int, int, int, int, int);
void printResByPatron(RestaurantType*, int);
void cleanupRestaurant(RestaurantType*);