#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;  // make the program more useful
typedef struct LinkedNode{
    ElementType element;
    struct LinkedNode* next;
}LinkedNode;

void* pop(LinkedNode** ptop);
void* push(LinkedNode** ptop,ElementType element);

int main()
{
    char* old_str = "3*-y-a/y!2";   // ! instand of
    char* new_str = "3y-*ay2!/-";
    LinkedNode* top = NULL;
    while(*new_str){           // push once,then check all the possible pop
        push(&top,*old_str);
        old_str++;
        printf("X");
        while(top && top->element == *new_str){
            pop(&top);
            new_str++;
            printf("S");
        }
    }
    return 0;
}

/*
 *  pop an element,return the last top's element
 */
void* pop(LinkedNode** ptop){
    LinkedNode* top = *ptop;
    if(!top) return NULL;
    LinkedNode* last_top = top;
    top = top->next;
    free(last_top);
    return top;
}

/*
 * push a new element to the stack
 */
void* push(LinkedNode** ptop,ElementType element){
    LinkedNode* top = *ptop;
    LinkedNode* new_top = (LinkedNode*)malloc(sizeof(LinkedNode));
    new_top->element = element;
    new_top->next = top;
    return new_top;
}
