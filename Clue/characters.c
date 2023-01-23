#include "characters.h"
#include <stdio.h>                                                                                                                                                                                       
#include <stdlib.h>

struct Character *character(char *name, struct Room *room, struct Character *nextCharacter) {
    struct Character *characters = (struct Character*) malloc(sizeof(struct Character));
    if (characters == NULL) {
                printf("malloc failed\n");
                return NULL;
        }
    characters->name = name;
    characters->room = room;
    characters->nextCharacter = nextCharacter;
    return characters;
}

// function to move characters                                                                                                                                                                              
void moveCharacter(struct Character *current, struct Room *curRoom) {
  //current->room = nextRoom;
  struct Character *characterList = curRoom->curCharacter;
  if (characterList == NULL) {
    curRoom->curCharacter = current;
  } else {
    while (characterList->nextCharacter != NULL) {
        characterList = characterList->nextCharacter;
    }
    characterList->nextCharacter = current;
  }
}
