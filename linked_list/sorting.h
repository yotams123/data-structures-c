#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct node Node;
typedef struct node{
    unsigned data;
    Node *next;
} Node;


void RandmonValues(Node *head){
    if (!head) return;
    head->data = rand() % UINT_MAX;
    RandmonValues(head->next);
}

static unsigned short CountNodes(Node *curr){

    if (curr){
        return CountNodes(curr->next) + 1;
    }
    return 0;
}



static Node *Merge(Node *, Node *);
Node *MergeSort(Node *ORIGINAL_HEAD){
    unsigned short length = CountNodes(ORIGINAL_HEAD);
    if (length == 1) return ORIGINAL_HEAD;
    if (length < 1) return NULL;

    unsigned short left_length = length / 2;
    unsigned short i = 1;
    Node *curr = ORIGINAL_HEAD;
    while(i < left_length){
        curr = curr->next;
        ++i;
    }
    Node *Right_head = curr->next;
    curr->next = NULL;
    Node *Sorted_left = MergeSort(ORIGINAL_HEAD);
    Node *Sorted_Right = MergeSort(Right_head);

    Node *New_Head = Merge(Sorted_left, Sorted_Right);
    return New_Head;
}

static Node *Merge(Node *Left_head, Node *Right_head){
    Node *left_curr = Left_head;
    Node *tmp;

    if (Right_head->data < Left_head->data){
        tmp = Right_head->next;
        Right_head->next = Left_head;
        Left_head = Right_head;
        Right_head = tmp;
        left_curr = Left_head;
    }

    while (left_curr->next != NULL && Right_head){
        if (left_curr->next->data > Right_head->data){
            tmp = Right_head->next;
            Right_head->next = left_curr->next;
            left_curr->next = Right_head;
            Right_head = tmp;
        }
        left_curr = left_curr->next;
    }

    if (Right_head){
        left_curr->next = Right_head;
    }
    
    return Left_head;
}



static Node *FindBeforeMin(Node *head){  // need to find the node before to exctract the minimum
    Node *curr = head;
    Node m = {0, head}; // m.data is irrelevant - not taken into account when looking for minimum
    Node *bmin = &m;

    while (curr->next){
        if (curr->next->data < bmin->next->data){
            bmin = curr;
        }
        curr = curr->next;
    }
    return bmin;
}

Node *SelectionSort(Node *head){
    if (!head) return NULL;

    Node *unsorted = head; // holds head of unsorted part

    Node *before_new_insert = FindBeforeMin(head);
    Node *new_head = before_new_insert->next;

    before_new_insert->next = before_new_insert->next->next;
    new_head->next = unsorted;
    Node *new_head_curr = new_head; // to hold the last node of the sorted part

    while (unsorted->next){
        before_new_insert = FindBeforeMin(unsorted);
        Node *new_insert = before_new_insert->next;
        new_head_curr->next = new_insert;

        if (new_insert == unsorted){
            unsorted = unsorted->next;
        } else {
            before_new_insert->next = before_new_insert->next->next;
            new_insert->next = unsorted;
        }
        new_head_curr = new_head_curr->next;
    }

    return new_head;    
}



Node *BubbleSort(Node *head){
    if (!head) return NULL;

    Node *new_head = head;
    Node *curr = new_head;
    bool sorted = true;

    do{
        sorted = true;
        if (curr->data > curr->next->data){ // checking head

            //swap nodes
            Node *tmp = curr->next;
            curr->next = curr->next->next;
            tmp->next = curr;
            new_head = tmp;
            
            curr = new_head;
            sorted = false;
        }

        while (curr->next->next){
            if (curr->next->data > curr->next->next->data){
                Node *tmp = curr->next;
                curr->next = tmp->next;
                tmp->next = curr->next->next;
                curr->next->next = tmp;

                sorted = false;
            }
            curr = curr->next;
        }
        curr = new_head;
    } while(!sorted);
    return new_head;
}


Node *QuickSort(Node *head){ // uses head as pivot
    if (!head) return NULL;
    if (!(head->next)) return head;
    
    Node *curr = head;

    Node *smaller = NULL; //list of nodes smaller than pivot
    Node *bigger = NULL; // list of nodes larger than pivot

    Node *tmp;
    while(curr && curr->next){
        if (curr->next->data < head->data){
            tmp = curr->next;
            curr->next = tmp->next;

            tmp->next = smaller;
            smaller = tmp;
        }
        else {
            if (!bigger) bigger = curr->next;
            curr = curr->next;
        }
    }
    
    head->next = NULL;

    if (smaller) smaller = QuickSort(smaller);
    if (bigger) bigger = QuickSort(bigger);

    head->next = bigger;

    if (!smaller) return head;
    
    curr = smaller;
    while (curr->next){
        curr = curr->next;
    }
    curr->next = head;

    return smaller;
}