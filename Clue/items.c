#include "items.h"
#include <stdio.h>                                                                                                                                                                                       
#include <stdlib.h>

struct Item *item(char *name, struct Item *next) {
    struct Item *newItem = (struct Item*) malloc(sizeof(next) + sizeof(name));
    if (newItem == NULL) {
                printf("malloc failed\n");
                return NULL;
        }
    newItem->name = name;
    newItem->next = next;
    return newItem;
}

//Function to print the player's current inventory                              
void printInventory(struct Item *inventoryList) {
     struct Item *curItem = inventoryList;
     if (curItem == NULL) {
         printf("You have no items currently.\n");
     }
     while (curItem != NULL) {
         printf("%s\n", curItem->name);
         curItem = curItem->next;
     }
 }
