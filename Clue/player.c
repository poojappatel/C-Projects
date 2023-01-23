#include "player.h"
#include <stdio.h>                                                                                                                                                                                       
#include <stdlib.h>
#include <string.h>

struct Player *player(char *name, struct Room *playerRoom, struct Item *inventory) {
    struct Player *players = (struct Player*) malloc(sizeof(struct Player));
    if (players == NULL) {
                printf("malloc failed\n");
                return NULL;
        }
    players->name = name;
    players->playerRoom = playerRoom;
    players->inventory = inventory;
    return players;
}

void addItem(char *name, struct Player *avatar) {
    struct Item *prevNode = NULL;
    struct Item *tempPrevNodes = NULL;
    struct Item *curItem = malloc(sizeof (struct Item));
    curItem = avatar->playerRoom->itemList;

    if (avatar->playerRoom->itemList == NULL) {
        printf("There are no items in the room to take.");
    } else {
        while (curItem != NULL) {
            tempPrevNodes = prevNode;
            if (strcasecmp(name, curItem->name) == 0) {
                struct Item *tempItem = malloc(sizeof (struct Item));
                tempItem->name = curItem->name;
                tempItem->next = avatar->inventory;
                avatar->inventory = tempItem;
                if (curItem->next == NULL) {
                    avatar->playerRoom->itemList = prevNode;
                } else {
                    avatar->playerRoom->itemList = curItem->next;
                    while (prevNode != NULL) {
                        struct Item *temp = malloc(sizeof (struct Item));
                        temp->name = prevNode->name;
                        temp->next = avatar->playerRoom->itemList;
                        avatar->playerRoom->itemList = temp;
                        prevNode = prevNode->next;
                    }
                }
                break;
            } else {
                prevNode = malloc(sizeof(struct Item));
                prevNode->name = curItem->name;
                prevNode->next = tempPrevNodes;
                curItem = curItem->next;
            }
        }
    }
}

//Allows player to drop an item in a room                                                                                                                                                                   
void dropItem(char *name, struct Player *avatar) {
    struct Item *prevNode = NULL;
    struct Item *curItem = malloc(sizeof (struct Item));
    curItem = avatar->inventory;

    struct Item *tempPrevNodes = NULL;
    if (avatar->inventory == NULL) {
        printf("There are not items in your inventory to drop.");
    } else {
        while (curItem != NULL) {
            tempPrevNodes = prevNode;
            if (strcasecmp(name, curItem->name) == 0) {
                struct Item *tempItem = malloc(sizeof (struct Item));
                tempItem->name = curItem->name;
                tempItem->next = avatar->playerRoom->itemList;
                avatar->playerRoom->itemList = tempItem;
                if (curItem->next == NULL) {
                    avatar->inventory = prevNode;
                } else {
                    avatar->inventory = curItem->next;
                    while (prevNode != NULL) {
                        struct Item *temp = malloc(sizeof (struct Item));
                        temp->name = prevNode->name;
                        temp->next = avatar->inventory;
                        avatar->inventory = temp;
                        prevNode = prevNode->next;
                    }
                }
                break;
            } else {
                prevNode = malloc(sizeof(struct Item));
                prevNode->name = curItem->name;
                prevNode->next = tempPrevNodes;
                curItem = curItem->next;
            }
        }
    }
}

// function to move player                                                                                                                                                                                  
void movePlayer(struct Player *current, struct Room *nextRoom) {
  current->playerRoom = nextRoom;
}
