#include "arr.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    clock_t begin = clock();

    item *arr[HT_BASE_SIZE];
    for (int i = 0; i<HT_BASE_SIZE; ++i){
        arr[i] = NULL;
    }

    char *name = malloc(30 *sizeof(char));
    char *bday = malloc(11 * sizeof(char));
    char *quote = malloc(100 * sizeof(char));

    strcpy(name, "Yotam Soudry");
    strcpy(bday, "9/2/2005");
    strcpy(quote, "Lightning bolts shoot from my fingertips!");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    printf("\n");

    strcpy(name, "Walter White");
    strcpy(bday, "7/9/1958");
    strcpy(quote, "I am the danger. I am the one who knocks");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    printf("\n");

    strcpy(name, "Saul Goodman");
    strcpy(bday, "12/11/1960");
    strcpy(quote, "I'm like a god in human clothing");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    puts("");

    strcpy(name, "Gustavo Fring");
    strcpy(bday, "6/9/1958");
    strcpy(quote, "I will kill your wife. I will kill your son. I will kill your infant daughter");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    puts("");

    strcpy(name, "Peter Griffin");
    strcpy(bday, "10/4/1975");
    strcpy(quote, "Holy crap Lois I'm India!");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    puts("");
    
    strcpy(name, "Walter White");
    remove_item(arr, name);
    print_item(arr, name);

    puts("");

    strcpy(name, "Dr. Michael Morbius");
    strcpy(bday, "1/4/2022");
    strcpy(quote, "I'm starting to get morby. You wouldn't like me when I'm morby");
    insert_item(arr, new_item(name, bday, quote));
    print_item(arr, name);

    clock_t end = clock();
    double time = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("Time Elapsed: %f\n", time);
    return 0;
}