#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

Node GenList(int);
Node GenList(int length){
    if (length == 0){
        Node n = {rand() % UINT_MAX, NULL};
        return n;
    }
    Node *next = (Node *)malloc(sizeof(Node));
    *next = GenList(length - 1);
    Node n = {rand() % UINT_MAX, next}; 
    return n;
}


void FreeList(Node *);
void FreeList(Node *head){
    if (head->next) FreeList(head->next);
    free(head);
}

void PrintStats(const char *algorithm, Node *NodeA, Node *(*func)(Node *)){
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
}


int main(){
    // creating initial list of nodes: includes 50 nodes
    Node NodeA = GenList(50);
    
    PrintStats("Merge Sort", &NodeA, MergeSort);
    RandmonValues(&NodeA);

    PrintStats("Selection Sort", &NodeA, SelectionSort);
    RandmonValues(&NodeA);

    PrintStats("Bubble Sort", &NodeA, BubbleSort);
    RandmonValues(&NodeA);

    PrintStats("QuickSort", &NodeA, QuickSort);

    FreeList(NodeA.next);
    NodeA.next = NULL;
    return 0;
}



