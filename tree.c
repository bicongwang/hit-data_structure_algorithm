#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;  // make the program more useful
typedef struct TreeNode{   // the struct for a tree node
    ElementType element;
    struct TreeNode* lc;
    struct TreeNode* rc;
}TreeNode;
typedef struct LinkedNode{ // the struct for a linkednode.In this program,it is used for a queue.
    TreeNode* element;
    struct LinkedNode* next;
}LinkedNode;

TreeNode* createTreeNode(ElementType element);
TreeNode* find(TreeNode* root,ElementType element);
LinkedNode* createLinkedNode(TreeNode* element);
LinkedNode* enqueue(LinkedNode* back,TreeNode* element);
LinkedNode* dequeue(LinkedNode* front);
void preTraverse(TreeNode* root);
void inTraverse(TreeNode* root);
void postTraverse(TreeNode* root);
void levelTraverse(TreeNode* root);
void addTreeNode(ElementType element,TreeNode* parent,char mark);
void addTreeNodeByUser(TreeNode* root,ElementType element,ElementType parent_element,char mark);
void testTraverse(TreeNode* root);

int main()
{
    ElementType curr_ele,parent_ele;
    TreeNode* root = NULL;
    char mark;
    while(1){
        scanf("%c%c%c",&curr_ele,&parent_ele,&mark);
        getchar();
        // fflush(stdout);
        // printf("%c %c %c\n",curr_ele,parent_ele,mark);
        if(curr_ele == '#'){                               // '#' is like a NULL or None.
            break;
        }else if(parent_ele == '#'){
            root = createTreeNode(curr_ele);
        }else{
            addTreeNodeByUser(root,curr_ele,parent_ele,mark);
        }
    }
    testTraverse(root);
    return 0;
}

// create a new tree node,usually used when creating a new root.
TreeNode* createTreeNode(ElementType element){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->element = element;
    node->lc = NULL;
    node->rc = NULL;
    return node;
}

// create a new linked node. In this program,it is used for a queue.
LinkedNode* createLinkedNode(TreeNode* element){
    LinkedNode* p = (LinkedNode*)malloc(sizeof(LinkedNode));
    p->element = element;
    p->next = NULL;
    return p;
}

// find a element in a tree.
TreeNode* find(TreeNode* root,ElementType element){
    if(!root){
        return NULL;
    }
    TreeNode* find_node = NULL;
    if(root->element == element){
        return root;
    }else if((find_node = find(root->lc,element))){
        return find_node;
    }else if((find_node = find(root->rc,element))){
        return find_node;
    }else{
        return NULL;
    }
}

// use the current element,parent point and whether the current node is leftChild or rightChild to add a new node.
void addTreeNode(ElementType element,TreeNode* parent,char mark){
    TreeNode* child = createTreeNode(element);
    switch(mark){
        case 'L':
            parent->lc = child;
            break;
        case 'R':
            parent->rc = child;
            break;
        }
}

// a simple method to add a new node.
void addTreeNodeByUser(TreeNode* root,ElementType element,ElementType parent_element,char mark){
    TreeNode* parent = find(root,parent_element);
    if(!parent){
        return;
    }
    addTreeNode(element,parent,mark);
}

// data && leftTree && rightTree
void preTraverse(TreeNode* root){
    if(!root){
        return;
    }
    printf("%c",root->element);
    preTraverse(root->lc);
    preTraverse(root->rc);
}

// leftTree && data && rightTree
void inTraverse(TreeNode* root){
    if(!root){
        return;
    }
    inTraverse(root->lc);
    printf("%c",root->element);
    inTraverse(root->rc);
}

// leftTree && rightTree && data
void postTraverse(TreeNode* root){
    if(!root){
        return;
    }
    postTraverse(root->lc);
    postTraverse(root->rc);
    printf("%c",root->element);
}

// traverse a tree by level.
void levelTraverse(TreeNode* root){
    if(!root){
        return;
    }
    LinkedNode* front = NULL;
    LinkedNode* back = NULL;

    front = back = createLinkedNode(root);
    while(front){
        TreeNode* node = front->element;
        if(node->lc){
            back = enqueue(back,node->lc);
        }
        if(node->rc){
            back = enqueue(back,node->rc);
        }
        printf("%c",node->element);
        front = dequeue(front);
    }
}

// test all the 4 traverses
void testTraverse(TreeNode* root){
	printf("Traverse data && leftTree && rightTree:\n");
    preTraverse(root);
    printf("\nTraverse leftTree && data && rightTree:\n");
    inTraverse(root);
    printf("\nTraverse leftTree && rightTree && data:\n");
    postTraverse(root);
    printf("\nTraverse by level: \n");
    levelTraverse(root);
    printf("\n");
}

// make a data enter a queue
LinkedNode* enqueue(LinkedNode* back,TreeNode* element){
    LinkedNode* new_back = createLinkedNode(element);
    back->next = new_back;
    return new_back;
}

// make a data out
LinkedNode* dequeue(LinkedNode* front){
    LinkedNode* old_front = front;
    front = front->next;
    free(old_front);
    return front;
}
