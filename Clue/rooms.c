#include <time.h>
#include <stdio.h>                                                                                                                                                                                       
#include <stdlib.h>
#include "rooms.h"                                                                                                                                                                                                                                                                                                                                                                         
// #include "characters.h"                                                                                                                                                                                  
// #include "items.h"

struct Room *room(char* name, struct Item* itemList, struct Character *curCharacter, struct Room* current, struct Room* North, struct Room* South, struct Room* East, struct Room* West) {
    struct Room *rooms = (struct Room *) malloc(sizeof(struct Room));
    if (rooms == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    rooms->name = name;
    rooms->itemList = itemList;
    rooms->curCharacter = curCharacter;
    rooms->current = current;
    rooms->North = North;
    rooms->South = South;
    rooms->East = East;
    rooms->West = West;
    return rooms;

}

//Randomizes rooms each round                                                                                                                                                                               
void randomRooms(struct Room *grid[]) {
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        int random = rand() % 9;
        struct Room *temp = grid[i];
        grid[i] = grid[random];
        grid[random] = temp;
    }
}

//Creates the grid for the game                                                                                                                                                                     
void createRooms(struct Room *grid[]) {
    for (int i = 0; i < 9; i++) {
        grid[i]->North = (i - 3) >= 0 ? grid[i - 3] : NULL;
        grid[i]->West = (i % 3 != 0) ? grid[i - 1] : NULL;
        grid[i]->East = (i == 2 || i == 5 || i == 8) ? NULL: grid[i + 1];
        grid[i]->South = (8 - i > 2) ? grid[i + 3] : NULL;
    }
}

// function for the look command to look at surrounding rooms
void lookRooms(struct Room *curRoom) {
    printf("\nYou are currently in the %s room.\n", curRoom->name);
    if (curRoom->South != NULL) {
        printf("In the south is the %s room.\n", curRoom->South->name);
    } else {
        printf("There is no room in the south.\n");
    }
    if (curRoom->North != NULL) {
        printf("In the north is the %s room.\n", curRoom->North->name);
    } else {
        printf("There is no room in the north.\n");
    }
    if (curRoom->West != NULL) {
        printf("In the west is the %s room.\n", curRoom->West->name);
    } else {
        printf("There is no room in the west.\n");
    }
    if (curRoom->East != NULL) {
        printf("In the east is the %s room.\n", curRoom->East->name);
    } else {
        printf("There is no room in the east.\n");
    }
}

// function for look command to see the items in current room  
void lookItems(struct Room *curRoom) {
    struct Item *curItem = curRoom->itemList;
     if (curItem == NULL) {
        printf("\nThis room has no items.\n");
    } else { 
        printf("\nItems in room: \n");
        while (curItem != NULL) {
            printf("%s\n", curItem->name);
            curItem = curItem->next;
        }
    }
}

// function for look command to see the character in current room                                                                                                                                           
void lookCharacters(struct Room *curRoom) {
    struct Character *characters = curRoom->curCharacter;
    if (characters == NULL) {
        printf("\nThere are no characters in the room currently.\n");
    } else {
        printf("\nCharacters in the room: \n");
        while (characters != NULL) {
            printf("%s\n", characters->name);
            characters = characters->nextCharacter;
        }
    }
}
