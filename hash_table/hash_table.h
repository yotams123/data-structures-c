#pragma once

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>

#define HT_BASE_SIZE 255
#define PRIME 13
 
typedef struct i{
    char *name;
    char *bday;
    char *quote;
    struct i *next;
} item ;

unsigned short hash_function(char *name, int size){
    long hash = 0;
    unsigned short l = strlen(name);

    for (int i = 0; i<l; ++i){
        hash += (unsigned long long)(PRIME * i * name[i]);
        hash %= size;
    }
    return hash;
}


void print_item(item **, char *);

static item *new_item(char *name, char *bday, char *quote){
    item *i = (item *)malloc(sizeof(item));

    i->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(i->name, name);

    i->bday = (char *)malloc((strlen(bday) + 1) *sizeof(char));
    strcpy(i->bday, bday);

    i->quote = (char *)malloc((strlen(quote) + 1) * sizeof(char));
    strcpy(i->quote, quote);

    i->next = NULL;
    return i;
}

static void clear_item(item *i){
    //free(i->name);
    //free(i->bday);
    //free(i->quote);
    free(i);
}

void insert_item(item **ht, char *name, char *bday, char *quote){

    unsigned short index = hash_function(name, HT_BASE_SIZE);
    if (!ht[index]){
        ht[index] = new_item(name, bday, quote);
        puts("Succesfully inserted!");
        print_item(ht, ht[index]->name);
        return;
    }
    item *curr = ht[index];
    while(curr->next){
        curr = curr->next;
    }
    curr->next = new_item(name, bday, quote);
}

void remove_item(item **ht, char *name){
    unsigned short index = hash_function(name, HT_BASE_SIZE);
    item *i = NULL; //to free the item at the end

    if (strcmp(ht[index]->name, name) == 0){
        i = ht[index];
        ht[index] = ht[index]->next;
        clear_item(i);
        puts("Succesfully Removed");
        return;
    }
    
    item *curr = ht[index];
    while(curr->next && strcmp(curr->next->name, name) != 0){
        curr= curr->next;
    }
    if(curr->next){
        i = curr->next;
        curr->next = curr->next->next;
    }
    else{
        puts("Item was not in table");
    }
    clear_item(i);
    puts("Succesfully Removed");
}

void print_item(item **ht, char *name){

    unsigned short index = hash_function(name, HT_BASE_SIZE);
    if (ht[index] && strcmp(ht[index]->name, name) == 0){
        item *i = ht[index];
        printf("\tName:\t%s\n", i->name);
        printf("\tBirthday:\t%s\n", i->bday);
        printf("\tQuote:\t%s\n", i->quote);
        printf("\n");
        return;
    }
    item *curr = ht[index];
    while(curr && strcmp(curr->name, name) != 0){
        curr = curr->next;
    }
    if (curr){
        printf("Name:\t%s\n", curr->name);
        printf("Birthday:\t%s\n", curr->bday);
        printf("Quote:\t%s\n", curr->quote);
    } else {
        puts("Item with that name does not exist in table");
    }
}

void update_item(item **ht, item *i){
    short index = hash_function(i->name, HT_BASE_SIZE);
    if (strcmp(ht[index]->name, i->name) == 0){
        i->next = ht[index]->next;
        ht[index] = i;
        puts("Succesfully Updated!");
        return;
    }

    item *curr = ht[index];
    while(curr->next && strcmp(curr->next->name, i->name) != 0){
        curr = curr->next;
    }
    if (curr->next){
        i->next = curr->next->next;
        curr->next = i;
        puts("Successfully Updated!");
    } else {
        puts("Item with that name does not exist in table");
    }
    return;
}