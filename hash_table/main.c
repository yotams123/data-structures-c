#include "hash_table.h"
#include "shell.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void){
    clock_t begin = clock();

    item *hash_table[HT_BASE_SIZE];
    for (int i = 0; i<HT_BASE_SIZE; ++i){
        hash_table[i] = NULL;
    }

    char *name = malloc(NAME_LENGTH *sizeof(char));
    char *bday = malloc(BDAY_LENGTH * sizeof(char));
    char *quote = malloc(QUOTE_LENGTH * sizeof(char));

    strcpy(name, "Yotam Soudry");
    strcpy(bday, "9/2/2005");
    strcpy(quote, "Lightning bolts shoot from my fingertips!");
    insert_item(hash_table, name, bday, quote);

    printf("\n");

    strcpy(name, "Walter White");
    strcpy(bday, "7/9/1958");
    strcpy(quote, "I am the danger. I am the one who knocks");
    insert_item(hash_table, name, bday, quote);

    printf("\n");

    strcpy(name, "Saul Goodman");
    strcpy(bday, "12/11/1960");
    strcpy(quote, "I'm like a god in human clothing");
    insert_item(hash_table, name, bday, quote);

    puts("");

    strcpy(name, "Gustavo Fring");
    strcpy(bday, "6/9/1958");
    strcpy(quote, "I will kill your wife. I will kill your son. I will kill your infant daughter");
    insert_item(hash_table, name, bday, quote);

    puts("");

    strcpy(name, "Peter Griffin");
    strcpy(bday, "10/4/1975");
    strcpy(quote, "Holy crap Lois I'm India!");
    insert_item(hash_table, name, bday, quote);

    puts("");

    strcpy(name, "Dr. Michael Morbius");
    strcpy(bday, "1/4/2022");
    strcpy(quote, "I'm starting to get morby. You wouldn't like me when I'm morby");
    insert_item(hash_table, name, bday, quote);

    clock_t end = clock();
    double time = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("Time Elapsed: %f\n", time);

    free(name);
    free(bday);
    free(quote);
    name = bday = quote = NULL;

    char *line;
    size_t buffsize = 155;
    size_t len;

    const char space[] = " ";
    
    system("cls");
    
    while (1 == 1){ 
        printf("ht> ");
        int code = read_input(line, buffsize); // success/error code after reading the input
        if (code == -1) continue;

        if (strcmp(line, "exit") == 0) break;
        if (strcmp(line, "cls") == 0 || strcmp(line, "clear") == 0){
            system("cls");
        }
        
        char *word = strtok(line, space);

        char *tmp = strtok(NULL, "\n");
        if (tmp) line = tmp; else continue; //checking that 'line' doesn't get a null value

        if (strcmp(word, "insert") == 0) {
            shell_insert(line, hash_table);
        } else if (strcmp(word, "remove") == 0) {
            shell_remove(line, hash_table);
        } else if (strcmp(word, "update") == 0){
            shell_update(line, hash_table);
        } else if (strcmp(word, "print") == 0) {
            shell_print(line, hash_table);
        } else if (strcmp(word, "hash") == 0) {
            shell_print_hash(line);
        }
    } 

    return 0;
}