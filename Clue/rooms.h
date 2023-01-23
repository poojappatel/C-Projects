#ifndef ROOMS_H
#define ROOMS_H

#include "items.h"
#include "characters.h"                                                                                                                                                                                  

struct Room {
    char* name;
    struct Item* itemList;
    struct Character *curCharacter;
    struct Room* current;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;

    //  char *character[MAX_CHARACTER];                                                                                                                                                                     
};

//Constructor for room                                                                                                                                                                                      
struct Room *room(char* name, struct Item* itemList, struct Character *curCharacter, struct Room* current, struct Room* North, struct Room* South, struct Room* East, struct Room* West);

void createRooms(struct Room *grid[]);

void randomRooms(struct Room *grid[]);

void lookRooms(struct Room *curRoom);

void lookItems(struct Room *curRoom);

void lookCharacters(struct Room *curRoom);

#endif /* ROOMS_H_ */
