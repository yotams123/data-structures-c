#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define HT_BASE_SIZE 255 
#define PRIME 13
 
typedef struct i{
    char *name;
    char *bday;
    char *quote;
    struct i *next;
} item ;

item *new_item(char *name, char *bday, char *quote){
    item *i = (item *)malloc(sizeof(item));
    i->name = name;
    i->bday = bday;
    i->quote = quote;
    i->next = NULL;

    return i;
}


void insert_item(item **ht, item *i){
    unsigned short index;
    do {
        index = rand() % HT_BASE_SIZE;
    } while (ht[index]);
    ht[index] = i;
    printf("index: %d\n", index);
}

void remove_item(item **ht, char *name){
    item *i = NULL;
    for (short j = 0; j < HT_BASE_SIZE; j++){
        if(ht[j] && strcmp(ht[j]->name, name) == 0){
            i = ht[j];
            ht[j] = NULL;
            free(i);
            return;
        }
    }
    puts("Item with that name doesn't exist in table");
}

void print_item(item **ht, char *name){

    for (short j = 0; j<HT_BASE_SIZE; j++){
        if (ht[j] && strcmp(ht[j]->name, name) == 0){
            item *i = ht[j];
            printf("Name:\t%s\n", i->name);
            printf("Birthday:\t%s\n", i->bday);
            printf("Quote:\t%s\n", i->quote);
        return;
        }
    }
    puts("Item with that name does not exist in table");
}

void update_item(item **ht, item *i){
    for (short index = 0; index<HT_BASE_SIZE; index++){
        if (ht[index] && strcmp(ht[index]->name, i->name) == 0){
            i->next = ht[index]->next;
            ht[index] = i;
            return;
        }
    }
    puts("Item with that name does not exist in table");
    return;
}