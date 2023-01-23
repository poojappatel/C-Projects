#ifndef PLAYER_H_ 
#define PLAYER_H_ 

#include "rooms.h"
#include "items.h"

struct Player {
    char *name;
    struct Room *playerRoom;
    struct Item* inventory;
};

struct Player *player(char *name, struct Room *playerRoom, struct Item *inventory);

void addItem(char *name, struct Player *avatar);

void dropItem(char *name, struct Player *avatar);

void movePlayer(struct Player *current, struct Room *nextRoom);

#endif /* PLAYER_H_ */
