This is my Harry Potter themed implementation of the adventure game Clue. The object of the game is to guess who injured a classmate of yours. This is a 
who dunnit, and you have to be the one to solve the mystery by going on an adventure throughout the castle and finding out what room this occured in, what 
person did it, and with what item. 

- To Compile
   - in terminal type gcc adventure.c -o adventure
   - then ./adventure to run
- Main code is within adventure.c
   - code for all user commands is in adventure.c
   - initalization of rooms, characters, player, and items
 - rooms.c
   - contains implementation of rooms grid and randomization of rooms
   - look command is coded in this file
 - items.c
   - function to print inventory as well
 - characters.c
   - function to move character is in this file
 - player.c
   - take and drop functions are in this file and function to move player
