#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;  // make the program more useful
typedef struct LinkedNode{
    ElementType element;
    struct LinkedNode* next;
}LinkedNode;

LinkedNode* pop(LinkedNode* top);
LinkedNode* push(LinkedNode* top,ElementType element);

int main()
{
    char* old_str = "3*-y-a/y!2";   // ! instand of
    char* new_str = "3y-*ay2!/-";
    LinkedNode* top = NULL;
    while(*new_str){           // push once,then check all the possible pop
        top = push(top,*old_str);
        old_str++;
        printf("X");
        while(top && top->element == *new_str){
            top = pop(top);
            new_str++;
            printf("S");
        }
    }
    return 0;
}

/*
 *  pop an element,return the last top's element
 */
LinkedNode* pop(LinkedNode* top){
    if(!top) return NULL;
    LinkedNode* last_top = top;
    top = top->next;
    free(last_top);
    return top;
}

/*
 * push a new element to the stack
 */
LinkedNode* push(LinkedNode* top,ElementType element){
    LinkedNode* new_top = (LinkedNode*)malloc(sizeof(LinkedNode));
    new_top->element = element;
    new_top->next = top;
    return new_top;
}
