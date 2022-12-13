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

int IsPalindrome(Node *head);
Node *PrintStats(const char *algorithm, Node *NodeA, Node *(*func)(Node *)){
    clock_t begin = clock();
    printf("Before %s:\n", algorithm);
    IterateNodes(NodeA);

    printf("\nAfter %s:\n", algorithm);
    NodeA = func(NodeA);
    IterateNodes(NodeA);
    puts("");
    NodeA = Reverse(NodeA);
    IterateNodes(NodeA);
    
    clock_t end = clock();
    double length = (end - begin)/ CLOCKS_PER_SEC;
    printf("Time to sort: %f seconds\n", length);
    printf((IsPalindrome(NodeA))? "List is a palindrome" : "List is not a palindrome"); 

    printf("\n\n%s\n\n\n", sep);
    return NodeA;
}

Node *CopyList(Node *head){
    if (!head) return NULL;   
 
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = head->data;
    new->next = CopyList(head->next);
    
    return new;
}

int IsPalindrome(Node *head){
    Node *tmp = CopyList(head);
    tmp = Reverse(tmp);
    Node *tmpcurr = tmp;
    
    while (tmpcurr != NULL){
         if (head->data != tmpcurr->data){
              FreeList(tmp);
	      return 0;
	 }
	 tmpcurr = tmpcurr->next;
	 head = head->next;
    }
    
    FreeList(tmp);
    return 1;    
}

int main(int argc, char *argv[]){
    
    if (argc != 2) {
        puts("Program must have one integer arg passed");
        exit(-1);
    }
    
    memset(sep, '=', SEPERATOR_SIZE - 1);

    unsigned short listlen;
    sscanf(argv[1], "%hu", &listlen);

    Node *NodeA = GenList(listlen);
   
    NodeA = PrintStats("Merge Sort", NodeA, MergeSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("Selection Sort", NodeA, SelectionSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("Bubble Sort", NodeA, BubbleSort);
    RandmonValues(NodeA);

    NodeA = PrintStats("QuickSort", NodeA, QuickSort);

    Node *CpyA = CopyList(NodeA);
    CpyA = Reverse(CpyA);
    Node *tmp = NodeA;  
    while (tmp->next) tmp = tmp->next; // getting last element
    tmp->next = CpyA;
   
    IterateNodes(NodeA);
    printf((IsPalindrome(NodeA))? "List is a palindrome\n" : "List is not a palindrome\n");    
    FreeList(CpyA);
    CpyA = NULL;

    FreeList(NodeA);
    NodeA = NULL;
    return 0;
}
