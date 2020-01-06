#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct LinkedList{
    struct Node *head;
    int size;
};

/**
 * sets up a new linked list instance
 */
struct LinkedList *initialize(){
    //allocate size
    struct LinkedList *list = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    //initializes fields of list
    list->head = NULL;
    list->size = 0;
    return list;
}

/**struct LinkedList initialize2(){
    //allocate size
    struct LinkedList list;
    //&list = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    //initializes fields of list
    list.head = NULL;
    list.size = 0;
    return list;
}**/

/**
 * inserts a new value into linked list
 */
void add(struct LinkedList *list, int data){
    //create node
    struct Node *newnode = malloc(sizeof(struct Node));
    //give data
    newnode ->data = data;
    //replace head
    newnode->next = list->head;
    list->head = newnode;
    list->size ++;
}

/**
 * outputs the linked list to stdout
 * @return
 */
 void print(struct LinkedList *list){
     struct Node *cursor = list->head;
     printf("Printing list: \n");
     while(cursor){
         printf("%d ", cursor->data);
         cursor = cursor->next;
     }
     printf("\n");
 }

/**void print2(struct LinkedList list){
    struct Node *cursor = list.head;
    printf("Printing list: \n");
    while(cursor){
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
    printf("\n");
}**/

 /**returns and removes a value from list
  * notifies if invalid index
  * @return removed
  */
int delete(struct LinkedList *list, int position) {
     struct Node *cursor = list->head;
     struct Node *prior = NULL;
     int counter = 0;
     while (cursor) {
         if (counter == position) {
             if (prior == NULL) {
                 list->head = cursor->next;
                 list->size--;
                 free(cursor);
                 return 1;
             }
             prior->next = cursor->next;
             free(cursor);
             list->size--;
             return 1;
         }
         prior = cursor;
         cursor = cursor->next;
         counter++;
     }
     return 0;
 }

 //return one if successful and zero if failed
 //free memory space allocated
 //put delete in a while loop to delete all entries
 int lecture_delete(struct LinkedList *list, int data){
    struct Node *cursor = list->head;
    struct Node *prev = NULL;
    while(cursor != NULL){
        if(cursor->data == data){
            if (prev == NULL){
                list->head =cursor->next;
                list->size--;
                free(cursor);
                return 1;
            }
            prev->next = cursor->next;
            free(cursor);
            list->size--;
            return 1;
        }
        prev=cursor;
        cursor = cursor->next;
    }
    return 0;
}

 /**
  * changes node data here to specified new data
  * @return '1' if successful
  */
  int update(struct LinkedList *list, int position, int newdata){
        struct Node *cursor = list->head;
        int counter = 0;
        while(cursor){
            if (counter == position){
                cursor->data = newdata;
                return 1;
            }
            counter++;
        }
        //if unsuccessful
        return -1;
  }

  /**
   * counts amount of nodes with specified data
   * @param list
   * @param data
   * @return
   */
  int find(struct LinkedList *list, int data){
        int counter = 0;
        struct Node *cursor = list->head;
        while(cursor){
            if (cursor->data ==data){
                counter++;
            }
        }
        return counter;
  }

/**allows for recursive iteration
 * through the list without
 * inverting it
 * @param cursor
 */
  void assist(struct Node *cursor){
    //base
    if (!(cursor)){
        return;
    }
    //otherwise if you can continue iterating
    assist(cursor->next);

    //finally-head bc at end
    printf("%d ", cursor->data);
  }
  /**O(N) reverse printing list
   * recursive
   * @param list
   */
  void print_oldest_first(struct LinkedList *list){
      struct Node *cursor = list->head;
      assist(cursor->next);
      printf("%d , ", cursor->data);
  }

int main() {
    struct LinkedList *list = initialize();
    add(list, 10);
    add(list, 20);
    add(list, 30);

    print(list);
    printf("Inverted print-\n");
    print_oldest_first(list);

    delete(list, 0);
    printf("\nprinting list with first entry (30) removed\n" );
    print(list);

    delete(list, 1);
    printf("\nprinting list with 10 at 1 removed\n" );
    print(list);

    printf("\nList attempts to remove element at index 777\n");
    delete(list, 777);

    printf("\nsuccessfully updating entry 2 to value 777\n");
    update(list, 2, 23);
    print(list);
    printf("\nfailing to update entry at 777 to value 777\n");
    printf("%d", update(list, 777,777));

    printf("\nSuccessfully looking for double data=777\n");
    add(list, 777);
    int total = find(list, 42069);
    printf("%d", total);
    printf("\nUnsuccessfully looking for data=42\n");
     total = find(list, 42);
    printf("%d", total);
    return 0;
}