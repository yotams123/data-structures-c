#pragma once

#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30
#define BDAY_LENGTH 11
#define QUOTE_LENGTH 100
const char *seperator = ";";
//TODO: secure the inputs (buffer overflow, injection...)

int validate_input(char *input, const char *key, int maxlen, char *field){
    int i = 0;
    char k = key[0];
    if (input == NULL) {
        printf("Missing fields. Enter 'help' for info\n");
        return -1;
    }

    while (input[0] == ' ') input++;
    for (; i <= maxlen; i++){
        if (input[i] == k) {
            if (i == 0){
                printf("Invalid input. Enter 'help' for info\n");
                return -1;
            }
            return 0;
        }
        if (input[i] == '\0') {
            printf("Missing fields. Enter 'help' for info\n");
            return -1;
        }

        if (!((input[i] <= 'z' && input[i] >= 'a') || (input[i] <= 'Z' && input[i] >= 'A') || input[i] == ' ')){
            printf("Invalid character at position %d => %c\n", i, input[i]); // Making sure all chars are alphabetic and spaces
            return -1;
        }
        if (input[i] == ' '){
            if (input[i+1] == k || input[i+1] == ' ')
            {
                printf("Invalid character at position %d => space cannot be the last char in the string", i);
                printf("and cannot be followed by another space\n");
                return -1;
            }
        }
    }
    printf("Invalid input. %s must be %d chars long, followed by a '%c'\n", field, maxlen, k);
    return -1;
}

void shell_insert(char *input, item **ht){    
    if (validate_input(input, seperator, NAME_LENGTH, "name") == -1) return;
    char *name = strtok(input, seperator);

    char *bday = strtok(NULL, "");
    if (validate_input(bday, seperator, BDAY_LENGTH, "bday") == -1) return;
    bday = strtok(bday, seperator);

    char *quote = strtok(NULL, "");
    if (validate_input(quote, "\n", QUOTE_LENGTH, "quote") == -1) return;
    quote = strtok(NULL, "\n");

    insert_item(ht, name, bday, quote);
}

void shell_print(char *input, item **ht){
    char *name = input;
    print_item(ht, name);
}

void shell_remove(char *input, item **ht){
    char *name = input;
    remove_item(ht, name);
}

void shell_update(char *input, item **ht){
    if (validate_input(input, seperator, NAME_LENGTH, "name") == -1) return;
    char *name = strtok(input, seperator);

    char *bday = strtok(NULL, "");
    if (validate_input(bday, seperator, BDAY_LENGTH, "bday") == -1) return;
    bday = strtok(bday, seperator);

    char *quote = strtok(NULL, "");
    if (validate_input(quote, "\n", QUOTE_LENGTH, "quote") == -1) return;
    quote = strtok(NULL, "\n");

    update_item(ht, new_item(name, bday, quote));
}

int read_input(char *buff, int buffsize){
    int pos = 0;
    while (1){
        buff[pos] = getc(stdin);
        if (buff[pos] == '\n'){
            buff[pos] = '\0';  // End input on newline char
            return 0;
        }
        pos++;
        if (pos > buffsize){
            puts("Input too large. Enter 'help' for info");
            return -1;
        }
    }
}

void shell_print_hash(char *input){
    unsigned short i = hash_function(input, HT_BASE_SIZE);
    printf("%s:\t%d\n", input, i);
}

void shell_print_help(){
    printf("\n\tCreate new entry in the hash table:\n");
    printf("\t\tinsert <name (max %d chars)>; <bday (max %d chars)>; <quote (max %d chars)>\n\n", 
        NAME_LENGTH, BDAY_LENGTH, QUOTE_LENGTH);
    
    printf("\tRemove existing from the hash table:\n");
    printf("\t\tremove <name of person who's entry to remove>\n\n");
    
    printf("\tUpdate existing entry in the hash table:\n");
    printf("\t\tinsert <name (max %d chars)>; <bday (max %d chars)>; <quote (max %d chars)>\n\n", 
        NAME_LENGTH, BDAY_LENGTH, QUOTE_LENGTH);

    printf("\tPrint entry in the hash table:\n");
    printf("\t\tprint <name of person who's entry to print\n\n");

    printf("\tShow the hash value of a string:\n");
    printf("\t\thash <string to hash>\n\n");

    printf("\tClear the console:\n");
    printf("\t\t cls \t\t\t or \t\t\t clear \n\n");

    printf("\tExit the program:\n");
    printf("\t\t exit \t\t\t or \t\t\t quit \n");
}