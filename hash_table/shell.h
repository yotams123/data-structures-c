#pragma once

#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30
#define BDAY_LENGTH 11
#define QUOTE_LENGTH 100
//TODO: secure the inputs (buffer overflow, injection...)

const char semicolon[] = ";";
const char newline[] = "\n";

void shell_insert(char *input, item **ht){
    char *name = strtok(input, semicolon);
    if(strlen(name) > NAME_LENGTH - 1){
        puts("Name too long, failed to insert");
        return;
    }

    char *bday = strtok(NULL, semicolon);
    if (strlen(bday) > BDAY_LENGTH - 1){
        puts("Bday too long, failed to insert");
        return;
    }

    char *quote = strtok(NULL, newline);
    if (strlen(quote) > QUOTE_LENGTH - 1){
        puts("Quote too long, failed to insert");
        return;
    }

    insert_item(ht, name, bday, quote);
}

void shell_print(char *input, item **ht){
    char *name = strtok(input, newline);
    print_item(ht, name);
}

void shell_remove(char *input, item **ht){
    char *name = strtok(input, newline);
    remove_item(ht, name);
}

void shell_update(char *input, item **ht){
    char *name = strtok(input, semicolon);
    if(strlen(name) > NAME_LENGTH - 1){
        puts("Name too long, failed to insert");
        return;
    }

    char *bday = strtok(NULL, semicolon);
    if (strlen(bday) > BDAY_LENGTH - 1){
        puts("Bday too long, failed to insert");
        return;
    }

    char *quote = strtok(NULL, newline);
    if (strlen(quote) > QUOTE_LENGTH - 1){
        puts("Quote too long, failed to insert");
        return;
    }
    
    update_item(ht, new_item(name, bday, quote));
}

int read_input(char *buff, int buffsize){
    int pos = 0;
    while (1){
        buff[pos] = getc(stdin);
        if (buff[pos] == '\n' || buff[pos] == EOF || buff[pos] == '\0'){
            buff[pos] = '\0';
            return 0;
        }
        pos++;
        if (pos > buffsize){
            puts("Input too large");
            return -1;
        }
    }
}

void shell_print_hash(char *name){
    unsigned short i = hash_function(name, HT_BASE_SIZE);
    printf("%s:\t%d\n", name, i);
}