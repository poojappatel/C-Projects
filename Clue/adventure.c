#include <stdio.h>                                                                                                                                                                                       
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "items.c"
#include "rooms.c"
#include "characters.c"
#include "player.c"

// function for the help command                                                                                                                                                                            
void printCommands() {
    printf("Here are a list of commands you can type throughout the game: \n");
    printf("help - lists the commands you can use\n");
    printf("list - shows you a list of items, rooms, and characters in the game\n");
    printf("look - allows you to see the room you are in, and the rooms in each direction\n");
    printf("go 'DIRECTION' - type go and a direction (north, west, south, or east) to move through rooms\n");
    printf("take 'itemname' - allows you to pick up an item only if item is in the room you are currently in\n");
    printf("drop 'itemname' - allows you to drop an item from your inventory in any room\n");
    printf("inventory - allows you to see what items are in your inventory\n");
    printf("clue 'charactername' - after you type clue, you have to type the character you think is correct\n");
    printf("give up - lets you see the correct answers and quit the game\n");
}

void again(char *userInput, int *clueCount, int *x) {
    printf("\nDo you want to play again? Enter yes or no: ");
    fgets(userInput, sizeof(userInput), stdin);
    if (strcasecmp(userInput, "yes\n") == 0) {
        *clueCount = 12;
    } else if (strcasecmp(userInput, "no\n") == 0) {
        *clueCount = 12;
        *x = 1;
    } else {
        printf("\nInvalid input. Try entering yes or no again.");
        again(userInput, clueCount, x);
    }
}

void userInputs(char *userInput) {
    if (userInput == NULL) {
        printf("Fail to read the input stream");
    } else {
        char *ptr = strchr(userInput, '\n');
        if (ptr) {
            *ptr  = '\0';
        }
    }
}

int main () {
    int x = 0;
    do {
        x = 0;
        
        // Initializing items by using the item struct                                                                                                                                                          
        struct Item *item1 = item("Sleeping Draught", NULL);
        struct Item *item2 = item("Vanishing Cabinet", NULL);
        struct Item *item3 = item("Portkey", NULL);
        struct Item *item4 = item("Nagini", NULL);
        struct Item *item5 = item("Petrificus Totalus", NULL);
        struct Item *item6 = item("Mandrake", NULL);

        //Creating array of items                                                                                                                                                                               
        struct Item *itemArray[6] = {item1, item2, item3, item4, item5, item6};

        // Initializing characters by using the character struct                                                                                                                                                
        struct Character *character1 = character("Draco", NULL, NULL);
        struct Character *character2 = character("Dolores Umbridge", NULL, NULL);
        struct Character *character3 = character("Lucius Malfoy", NULL, NULL);
        struct Character *character4 = character("Peter Pettigrew", NULL, NULL);
        struct Character *character5 = character("Bellatrix", NULL, NULL);
        struct Character *character6 = character("Voldemort", NULL, NULL);

        //Creating array of characters                                                                                                                                                                          
        struct Character *characterArray[6] = {character1, character2, character3, character4, character5, character6};


        // Initializing rooms by using the room struct                                                                                                                                                          
        struct Room *room1 = room("Great Hall", NULL, character3, NULL, NULL, NULL, NULL, NULL);
        struct Room *room2 = room("Dormitory", item5, NULL, NULL, NULL, NULL, NULL, NULL);
        struct Room *room3 = room("Potion's Class", item1, character4, NULL, NULL, NULL, NULL, NULL);
        struct Room *room4 = room("Quidditch Field", NULL, character1, NULL, NULL, NULL, NULL, NULL);
        struct Room *room5 = room("Owlery", item3, NULL, NULL, NULL, NULL, NULL, NULL);
        struct Room *room6 = room("Forbidden Forest", item4, character6, NULL, NULL, NULL, NULL, NULL);
        struct Room *room7 = room("Room of Requirement", item2, character5, NULL, NULL, NULL, NULL, NULL);
        struct Room *room8 = room("Defense Against Dark Arts Room", NULL, character2, NULL, NULL, NULL, NULL, NULL);
        struct Room *room9 = room("Library", item6, NULL, NULL, NULL, NULL, NULL, NULL);

        //Creating array of rooms                                                                                                                                                                               
        struct Room* roomArray[9] = {room1, room2, room3, room4, room5, room6, room7, room8, room9};

        
        // Initalizing player                                                                                                                                                                                   
        struct Player *avatar = player("Harry", NULL, NULL);

        //Randomizaing and creating the rooms                                                                                                                                                                   
        randomRooms(roomArray);
        createRooms(roomArray);

        //Starting position of player                                                                                                                                                                           
        avatar->playerRoom = roomArray[4];

        //Randomized answers for the games each round                                                                                                                                                           
        struct Room* answerRooms = roomArray[rand() % 9];
        struct Character* answerCharacter = characterArray[rand() % 6];
        struct Item* answerItems = itemArray[rand() % 6];

        int clueCount = 1;
        char userInput[100];
        char characterWord[100];
        char itemWord[100];
        bool win = false;

        //Created these for debugging                                                                                                                                                                           
        // printf("Correct Room: %s", answerRooms->name);                                                                                                                                                     
        // printf("Correct Character: %s", answerCharacter->name);                                                                                                                                            
        // printf("Correct Items: %s", answerItems->name);                                                                                                                                                    

        printf("Welcome to Hogwarts! You are on an adventure around Hogwarts Castle to find the person who injured a classmate of yours. You have to find who did it, with what item they injured the student, and in which room this took place in. Have fun!\n");

        while (clueCount <= 11) {

            if (win == false && clueCount == 10) {
                printf("No more guesses left! You lost!\n");
                printf("Correct Room: %s\n", answerRooms->name);
                printf("Correct Character: %s\n", answerCharacter->name);
                printf("Correct Item: %s\n", answerItems->name);

                again(userInput, &clueCount, &x);
                break;

            }

            printf("\nEnter a command: ");

            fgets(userInput, sizeof(userInput), stdin);
            userInputs(userInput);

            //help command                                                                                                                                                                                      
            if (strcasecmp(userInput, "help") == 0) {
                printCommands();
                //list command                                                                                                                                                                                  
            } else if (strcasecmp(userInput, "list") == 0) {
                printf("Rooms: Great Hall, Dormitory, Potion's Class, Quidditch Field, Owlery, Forbidden Forest, Room of Requirement, Defense Against Dark Arts Room, Library\n");
                printf("Characters: Draco, Dolores Umbridge, Lucius Malfoy, Peter Pettigrew, Bellatrix, Voldemort\n");
                printf("Items: Sleeping Draught, Vanishing Cabinet, Portkey, Nagini, Petrificus Totalus, Mandrake\n");
                //inventory command                                                                                                                                                                             
            } else if (strcasecmp(userInput, "inventory") == 0) {
                printInventory(avatar->inventory);
                //look command                                                                                                                                                                                  
            } else if (strcasecmp(userInput, "look") == 0) {
                lookRooms(avatar->playerRoom);
                lookItems(avatar->playerRoom);
                lookCharacters(avatar->playerRoom);
                //take and drop command                                                                                                                                                                         
            } else if (strcasecmp(userInput, "take sleeping draught") == 0) {
                addItem("Sleeping Draught", avatar);
            } else if (strcasecmp(userInput, "take vanishing cabinet") == 0) {
                addItem("Vanishing Cabinet", avatar);
            } else if (strcasecmp(userInput, "take portkey") == 0) {
                addItem("Portkey", avatar);
            } else if (strcasecmp(userInput, "take nagini") == 0) {
                addItem("Nagini", avatar);
            } else if (strcasecmp(userInput, "take petrificus totalus") == 0) {
                addItem("Petrificus Totalus", avatar);
            } else if (strcasecmp(userInput, "take mandrake") == 0) {
                addItem("Mandrake", avatar);
            } else if (strcasecmp(userInput, "drop sleeping draught") == 0) {
                dropItem("Sleeping Draught", avatar);
            } else if (strcasecmp(userInput, "drop vanishing cabinet") == 0) {
                dropItem("Vanishing Cabinet", avatar);
            } else if (strcasecmp(userInput, "drop portkey") == 0) {
                dropItem("Portkey", avatar);
            } else if (strcasecmp(userInput, "drop nagini") == 0) {
                dropItem("Nagini", avatar);
            } else if (strcasecmp(userInput, "drop petrificus totalus") == 0) {
                dropItem("Petrificus Totalus", avatar);
            } else if (strcasecmp(userInput, "drop mandrake") == 0) {
                dropItem("Mandrake", avatar);
                //go command                                                                                                                                                                                    
            } else if (strcasecmp(userInput, "go north") == 0) {
                if (avatar->playerRoom->North != NULL) {
                    movePlayer(avatar, avatar->playerRoom->North);
                } else {
                    printf("There is no room here. Try another direction.");
                }
            } else if (strcasecmp(userInput, "go south") == 0) {
                if (avatar->playerRoom->South != NULL) {
                    movePlayer(avatar, avatar->playerRoom->South);
                } else {
                    printf("There is no room here. Try another direction.");
                }
            } else if (strcasecmp(userInput, "go west") == 0) {
                if (avatar->playerRoom->West != NULL) {
                    movePlayer(avatar, avatar->playerRoom->West);
                } else {
                    printf("There is no room here. Try another direction.");
                }
            } else if (strcasecmp(userInput, "go east") == 0) {
                if (avatar->playerRoom->East != NULL) {
                    movePlayer(avatar, avatar->playerRoom->East);
                } else {
                    printf("There is no room here. Try another direction.");
                }
                //clue command                                                                                                                                                                                  
            } else if (strcasecmp(userInput, "clue") == 0) {
                printf("Room Guess: %s\n", avatar->playerRoom->name);
                printf("Please enter a character name: ");
                fgets(characterWord, sizeof(characterWord), stdin);
                userInputs(characterWord);
                if (true) {
                    for (int i = 0; i < 6; i++) {
                        if (strcasecmp(characterArray[i]->name, characterWord) == 0) {
                            //moveCharacter(characterArray[i], avatar->playerRoom);
                            printf("Character Guess: %s\n", characterArray[i]->name);
                            break;
                        } else if (i == 5 && strcasecmp(characterArray[i]->name, characterWord) != 0) {
                            printf("Invalid character. Try again.\n");
                            break;
                        }
                    }
                }
                printf("Enter an item name: ");
                fgets(itemWord, sizeof(itemWord), stdin);
                userInputs(itemWord);
                if (true) {
                    for (int i = 0; i < 6; i++) {
                        if (strcasecmp(itemArray[i]->name, itemWord) == 0) {
                            if (avatar->inventory != NULL && strcasecmp(itemArray[i]->name, avatar->inventory->name) == 0) {
                                printf("Item Guess: %s\n", avatar->inventory->name);
                                break;
                            } else if (avatar->playerRoom->itemList != NULL && strcasecmp(itemArray[i]->name, avatar->playerRoom->itemList->name) == 0) {
                                printf("Item Guess: %s\n", avatar->playerRoom->itemList->name);
                                break;
                            }
                        } else if (i == 5 && strcasecmp(itemArray[i]->name, itemWord) != 0) {
                            printf("Item is either not in the room or not in your invetory or invalid input. \nTry again after you are near an item or have an item in you inventory.\n");
                            break;
                        }
                    }
                }
                if ((strcasecmp(answerRooms->name, avatar->playerRoom->name) == 0) && (strcasecmp(characterWord, answerCharacter->name) == 0) && (strcasecmp(itemWord, answerItems->name) == 0)) {
                    clueCount++;
                    win = true;
                    printf("Congratulations! You solved the mystery!");
                    again(userInput, &clueCount, &x);
                    break;
                } else {
                    if ((strcasecmp(answerRooms->name, avatar->playerRoom->name) != 0)) {
                        printf("Incorrect Room.\n");
                    }
                    if (strcasecmp(characterWord, answerCharacter->name) != 0) {
                        printf("Incorrect Character.\n");
                    }
                    if (strcasecmp(itemWord, answerItems->name)!= 0) {
                        printf("Incorrect Item.\n");
                    }
                    printf("Keep searching.");
                    clueCount++;
                }
            //quit command                                                                                                                                                                              
            } else if (strcasecmp(userInput, "quit") == 0) {
                printf("\nCorrect Room: %s\n", answerRooms->name);
                printf("Correct Character: %s\n", answerCharacter->name);
                printf("Correct Item: %s\n", answerItems->name);
                x = 1;
                break;
            } else {
                printf("Command is invalid, try again.\n");
            }
        }
        
        //freeing items                                                                                                                                                                                         
        free(room1); 
        free(room2); 
        free(room3); 
        free(room4); 
        free(room5); 
        free(room6); 
        free(room7); 
        free(room8); 
        free(room9);
        free(item1); 
        free(item2); 
        free(item3); 
        free(item4); 
        free(item5); 
        free(item6);
        free(character1); 
        free(character2); 
        free(character3); 
        free(character4); 
        free(character5); 
        free(character6);
        free(avatar);

    } while (x !=  1);

    return 0;
}
