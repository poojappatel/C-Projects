#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include "rooms.h"

struct Character {
    char *name;
    struct Room *room;
    struct Character *nextCharacter;
};

struct Character *character(char *name, struct Room *room, struct Character *nextCharacter);

void moveCharacter(struct Character *current, struct Room *curRoom);

#endif /* CHARACTERS_H_ */
