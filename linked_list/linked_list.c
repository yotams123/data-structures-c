#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sorting.h"
#define SEPERATOR_SIZE 75
char sep[SEPERATOR_SIZE];

void IterateNodes(Node *head){
    if (!head) {
        puts("null");
        return;
    }

    while (head->next != NULL){
        printf("%u --> ", head->data);
        head = head->next;
    }
    printf("%u\n", head->data);
}

Node *Reverse(Node *Head){
	if (!Head) return NULL;
	if (!(Head->next)) return Head;
	
	Node *tail = Reverse(Head->next);
	Head->next->next = Head;
	Head->next = NULL;  // will be undone for all nodes but the first in the original list 
	
	return tail;
}

Node *GenList(int);
Node *GenList(int length){
    if (length <= 0) return NULL;

    Node *n = (Node *)malloc(sizeof(Node));
    if (!n){
        puts("Failed to allocate memory on the heap");
        
        exit (-1);
    }

    n->data = rand() % USHRT_MAX;
    n->next = GenList(length - 1);
    
    return n;
}


void FreeList(Node *);
void FreeList(Node *head){
    if (!head) return;
    FreeList(head->next);
    free(head);
}

Node *PrintStats(const char *algorithm, Node *NodeA, Node *(*func)(Node *)){
    clock_t begin = clock();
    printf("Before %s:\n", algorithm);
    IterateNodes(NodeA);

    printf("\nAfter %s:\n", algorithm);
    Node *Head = func(NodeA);
    IterateNodes(Head);
    puts("");
    Head = Reverse(Head);
    IterateNodes(Head);
    
    clock_t end = clock();
    double length = (end - begin)/ CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds\n", length);
    printf("%s\n", sep);
    return Head;
}

int main(int argc, char *argv[]){
    
    if (argc != 2) {
        puts("Program must have one integer arg passed");
        exit(-1);
    }
    
    memset(sep, (int)'=', SEPERATOR_SIZE - 1);
    int arglen = strlen(argv[1]);
    unsigned listlen = 0;
    for (size_t i = 0; i < arglen; i++){
        if (argv[1][i] < '0' || argv[1][i] > '9'){
            puts("Arg must be integer value");
            exit(-1);
        }
        listlen *= 10;
        listlen += argv[1][i] - '0';
    }
    Node *NodeA = GenList(listlen);
   
    NodeA = PrintStats("Merge Sort", NodeA, MergeSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("Selection Sort", NodeA, SelectionSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("Bubble Sort", NodeA, BubbleSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("QuickSort", NodeA, QuickSort);

    FreeList(NodeA);
    NodeA = NULL;
    return 0;
}



