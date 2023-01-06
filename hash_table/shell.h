#pragma once
#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30
#define BDAY_LENGTH 11
#define QUOTE_LENGTH 100

static int IsNumeric(int x) { return (x >= '0' && x <= '9')? 1: 0; }
static int IsAlpha(int x) { return ((x >= 'A' && x <= 'Z') || ( x >= 'a' && x <= 'z') )? 1: 0; }

const char seperator[2] = ";";



int validate_input_name_quote(char *input, const char *key, int maxlen, char *field){
    int i = 0;
    char k = key[0];
    
    while (input[0] == ' ') input++;
    int length = strlen(input);
    
    for (; i <= maxlen; i++){
        if (input[i] == k || (i == length && strcmp(field, "quote") == 0) ) {
            if (i == 0){
                printf("Invalid input. Enter 'help' for info\n");
                return -1;
            }
            return 0;
        }

        if ( i == length && strcmp(field, "quote")) { // strcmp returns true when strings aren't equal
            printf("Missing fields. Enter 'help' for info\n");
            return -1;
        }

        if (!( IsAlpha(input[i]) || input[i] == ' ')){ 
            printf("Invalid character at position %d in %s => %c\n", i, field, input[i]); // Making sure all chars are alphabetic and spaces
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

int validate_input_bday(char *input){
    while (input[0] == ' ') input++;
   
    int slashes = 0;
    char *c = input;
    while (*c != seperator[0]){
	if (*c == '/') slashes++;
	c++; 
    }
    if (slashes != 2) {
	printf("Bday in invalid format. Enter 'help' for more info\n");
    	return -1;
    }

    int day, month, year;
    sscanf(input, "%d/%d/%d", &day, &month, &year);

    if (month > 12 || month < 1 || day > 31 || day < 1){  // if month and day not in range
    	printf("Day and month of birthday not valid\n");
        return -1;
    }

    // if day is the 31st, make sure that month has a 31st
    if (day == 31 && !(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)){
    	printf("Invalid birthday - no 31st of month %d\n", month);
        return -1;
    }   
    
    // no feburay 30th or 29th on non leap years
    if (month == 2){
    	if (day == 30 || (day == 29 && year % 4 != 0)) {
    	    printf("Invalid birthday - febuary is only 28 days long, 29 on leap years\n");
            return -1;
	}
    }

    return 0;
}

void shell_insert(char *input, item **ht){    
    if (validate_input_name_quote(input, seperator, NAME_LENGTH, "name") == -1) return;
    char *name = strtok(input, seperator);

    char *bday = strtok(NULL, "");
    if (validate_input_bday(bday) == -1) return;
    bday = strtok(bday, seperator);

    char *quote = strtok(NULL, "");
    if (validate_input_name_quote(quote, "\n", QUOTE_LENGTH, "quote") == -1) return;

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
    if (validate_input_name_quote(input, seperator, NAME_LENGTH, "name") == -1) return;
    char *name = strtok(input, seperator);

    char *bday = strtok(NULL, "");
    if (validate_input_bday(bday) == -1) return;
    bday = strtok(bday, seperator);

    char *quote = strtok(NULL, "");
    if (validate_input_name_quote(quote, "\n", QUOTE_LENGTH, "quote") == -1) return;

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
