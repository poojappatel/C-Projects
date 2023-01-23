#ifndef ITEMS_H_
#define ITEMS_H_

struct Item {
    char *name;
    struct Item *next;
};

//Constructor for item                                                                                                                                                                                      
struct Item *item(char *name, struct Item *next);

void printInventory(struct Item *inventoryList);


#endif /* ITEMS_H_ */
