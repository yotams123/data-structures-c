#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sorting.h"

void IterateNodes(Node *head){
    while (head->next != NULL){
        printf("%u --> ", head->data);
        head = head->next;
    }
    printf("%u\n", head->data);
    return;
}

Node *Reverse(Node *Head){
    Node *curr = Head, *last = Head->next;
    
    if (!last) return Head; //one node in list

    while(last->next){  // getting the first node in reversed list in order to return it later
        curr = curr->next;
        last = last->next;
    }
    last->next = curr;

    while (curr != Head){
     curr = Head;
        while (curr->next->next->next != curr->next){ //eg. (curr=7   7-->8-->9-->8 will stop the loop
         curr = curr->next;
        }
     curr->next->next = curr;
    }
    curr->next = NULL; 
    return last;
}

Node *GenList(int);
Node *GenList(int length){
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n){
        puts("Failed to allocate memory on the heap");
        exit (-1);
    }

    n->data = rand() % UINT_MAX;
    if (length <= 1) {n->next = NULL;} else {n->next = GenList(length - 1);}
    return n;
}


void FreeList(Node *);
void FreeList(Node *head){
    if (head->next) FreeList(head->next);
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
    puts("\n==============================================================================================================================");
    return Head;
}

int main(int argc, char *argv[]){
    // creating initial list of nodes: includes 50 nodes
    
    if (argc != 2) {
        puts("Program must have one integer arg passed");
        exit(-1);
    }

    int arglen = strlen(argv[1]);
    int listlen = 0;
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



