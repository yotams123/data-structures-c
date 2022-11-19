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
    Node *next = malloc(sizeof(Node));
    *next = GenList(length - 1);
    Node n = {rand() % UINT_MAX, next}; 
    return n;
}


void FreeList(Node *);
void FreeList(Node *head){
    if (head->next) FreeList(head->next);
    free(head);
}

int main(){
    // creating initial list of nodes: includes 50 nodes
    Node NodeA = GenList(50);
    
    clock_t begin = clock();
    puts("Before Merge Sort:");
    IterateNodes(&NodeA);

    puts("\nAfter Merge Sort:");
    Node *Head = MergeSort(&NodeA);
    IterateNodes(Head);
    puts("");
    Head = Reverse(Head);
    IterateNodes(Head);
    
    clock_t end = clock();
    double length = (end - begin)/ CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds\n", length);
    puts("\n======================================================");

    begin = clock();
    puts("Before Selection Sort: ");
    RandmonValues(Head);
    IterateNodes(Head);

    puts("\nAfter Selection Sort: ");
    Head = SelectionSort(Head);
    IterateNodes(Head);
    puts("");
    Head = Reverse(Head);
    IterateNodes(Head);

    end = clock();
    length = (end - begin)/CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds\n", length);
    puts("\n======================================================");


    begin = clock();
    puts("Before Bubble Sort: ");
    RandmonValues(Head);
    IterateNodes(Head);

    puts("\nAfter Bubble Sort: ");
    Head = BubbleSort(Head);
    IterateNodes(Head);
    puts("");
    Head = Reverse(Head);
    IterateNodes(Head);

    end = clock();
    length = (end - begin)/CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds\n", length);
    puts("\n======================================================");
    

    begin = clock();
    puts("Before QuickSort: ");
    RandmonValues(Head);
    IterateNodes(Head);

    puts("\nAfter QuickSort: ");
    Head = QuickSort(Head);
    IterateNodes(Head);
    puts("");
    Head = Reverse(Head);
    IterateNodes(Head);

    end = clock();
    length = (end - begin)/CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds", length);

    FreeList(&NodeA);
    return 0;
}



