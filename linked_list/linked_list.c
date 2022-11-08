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

int main(){

    // creating initial list of nodes: includes 50 nodes
    Node NodeJ5 = {rand() % UINT_MAX, NULL};
    Node NodeI5 = {rand() % UINT_MAX, &NodeJ5};
    Node NodeH5 = {rand() % UINT_MAX, &NodeI5};
    Node NodeG5 = {rand() % UINT_MAX, &NodeH5};
    Node NodeF5 = {rand() % UINT_MAX, &NodeG5};
    Node NodeE5 = {rand() % UINT_MAX, &NodeF5};
    Node NodeD5 = {rand() % UINT_MAX, &NodeE5};
    Node NodeC5 = {rand() % UINT_MAX, &NodeD5};
    Node NodeB5 = {rand() % UINT_MAX, &NodeC5};
    Node NodeA5 = {rand() % UINT_MAX, &NodeB5};
    Node NodeJ4 = {rand() % UINT_MAX, &NodeA5};
    Node NodeI4 = {rand() % UINT_MAX, &NodeJ4};
    Node NodeH4 = {rand() % UINT_MAX, &NodeI4};
    Node NodeG4 = {rand() % UINT_MAX, &NodeH4};
    Node NodeF4 = {rand() % UINT_MAX, &NodeG4};
    Node NodeE4 = {rand() % UINT_MAX, &NodeF4};
    Node NodeD4 = {rand() % UINT_MAX, &NodeE4};
    Node NodeC4 = {rand() % UINT_MAX, &NodeD4};
    Node NodeB4 = {rand() % UINT_MAX, &NodeC4};
    Node NodeA4 = {rand() % UINT_MAX, &NodeB4};
    Node NodeJ3 = {rand() % UINT_MAX, &NodeA4};
    Node NodeI3 = {rand() % UINT_MAX, &NodeJ3};
    Node NodeH3 = {rand() % UINT_MAX, &NodeI3};
    Node NodeG3 = {rand() % UINT_MAX, &NodeH3};
    Node NodeF3 = {rand() % UINT_MAX, &NodeG3};
    Node NodeE3 = {rand() % UINT_MAX, &NodeF3};
    Node NodeD3 = {rand() % UINT_MAX, &NodeE3};
    Node NodeC3 = {rand() % UINT_MAX, &NodeD3};
    Node NodeB3 = {rand() % UINT_MAX, &NodeC3};
    Node NodeA3 = {rand() % UINT_MAX, &NodeB3};
    Node NodeJ2 = {rand() % UINT_MAX, &NodeA3};
    Node NodeI2 = {rand() % UINT_MAX, &NodeJ2};
    Node NodeH2 = {rand() % UINT_MAX, &NodeI2};
    Node NodeG2 = {rand() % UINT_MAX, &NodeH2};
    Node NodeF2 = {rand() % UINT_MAX, &NodeG2};
    Node NodeE2 = {rand() % UINT_MAX, &NodeF2};
    Node NodeD2 = {rand() % UINT_MAX, &NodeE2};
    Node NodeC2 = {rand() % UINT_MAX, &NodeD2};
    Node NodeB2 = {rand() % UINT_MAX, &NodeC2};
    Node NodeA2 = {rand() % UINT_MAX, &NodeB2};
    Node NodeJ = {rand() % UINT_MAX, &NodeA2};
    Node NodeI = {rand() % UINT_MAX, &NodeJ};
    Node NodeH = {rand() % UINT_MAX, &NodeI};
    Node NodeG = {rand() % UINT_MAX, &NodeH};
    Node NodeF = {rand() % UINT_MAX, &NodeG};
    Node NodeE = {rand() % UINT_MAX, &NodeF};
    Node NodeD = {rand() % UINT_MAX, &NodeE};
    Node NodeC = {rand() % UINT_MAX, &NodeD};
    Node NodeB = {rand() % UINT_MAX, &NodeC};
    Node NodeA = {rand() % UINT_MAX, &NodeB};

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

    return 0;
}



