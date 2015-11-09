#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0           // 用幻数让boolean更直观

typedef int ElementType;  // 通用单位数据
typedef struct LinkedNode{
    ElementType element;
    struct LinkedNode* next;
}LinkedNode;

LinkedNode* create();
LinkedNode* addTwoList(LinkedNode* head1,LinkedNode* head2);
int find(LinkedNode* head,ElementType x);
int findIndex(LinkedNode* head,ElementType x);
int length(LinkedNode* head);
void insert(LinkedNode* head,ElementType x);
void del(LinkedNode* head,ElementType x);
void printList(LinkedNode* head);
void reverse(LinkedNode* head);
void copy(LinkedNode* head1,LinkedNode* head2);
void makeCircle(LinkedNode* head);
void oneToTwo(LinkedNode* head,LinkedNode* head1,LinkedNode* head2);
ElementType* subEle(LinkedNode* head,int m,int n);

int main()
{
    FILE* fp = fopen("int.txt","r");
    LinkedNode* head = create();
    while(!feof(fp)){                 // 从文件中读取
        int i;
        fscanf(fp,"%d ",&i);
        insert(head,i);
    }
    LinkedNode* head1 = create();
    LinkedNode* head2 = create();
    reverse(head);
    printList(head);       // 基本测试
    oneToTwo(head,head1,head2);
    printList(head1);
    printList(head2);
    fclose(fp);
    return 0;
}

/*
 * 创建新的链表，返回头结点
 */
LinkedNode* create(){
    LinkedNode* head = (LinkedNode*)malloc(sizeof(LinkedNode));
    head->element = 0;
    head->next = NULL;
    return head;
}

/*
 *  在一个链表中查找数据x，返回boolean （支持环形链表）
 */
int find(LinkedNode* head,ElementType x){
    LinkedNode* p = head;
    while(p->next!=NULL && p->next!= head){
        p = p->next;
        if(p->element == x){
            return TRUE;
        }
    }
    return FALSE;
}

/*
 * 向链表中添加数据 x ，并且让头结点的数据 + 1（表示链表长度）
 */
void insert(LinkedNode* head,ElementType x){
    LinkedNode* p = head;
    LinkedNode* add_list = (LinkedNode*)malloc(sizeof(LinkedNode));
    add_list->element = x;
    add_list->next = NULL;
    while(p->next!=NULL){
        if(x < (p->next)->element){
            break;
        }
        p = p->next;
    }
    add_list->next = p->next;
    p->next = add_list;
    head->element++;
}

/*
 * 删除链表中数据x ，可进行多次删除
 */
void del(LinkedNode* head,ElementType x){
    LinkedNode* p = head;
    LinkedNode* delete_list = NULL;
    while(p->next!=NULL){
        if(x == (p->next)->element){
            delete_list = p->next;
            p->next = delete_list->next;
            free(delete_list);
            head->element--;
            continue;
        }
        p = p->next;
    }
}

/*
 * 头结点的数据表示链表长度，返回该数据
 */
int length(LinkedNode* head){
    return head->element;
}

/*
 * 输出该链表（可输出循环链表）
 */
void printList(LinkedNode* head){
    LinkedNode* p = head;
    while(p->next!=NULL && p->next!=head){
        p = p->next;
        printf("%d ",p->element);
    }
    printf("\n");
}

/*
 * 存储下一个节点和前一个节点，进行倒序
 */
void reverse(LinkedNode* head){
    LinkedNode* p = head->next;
    LinkedNode* future_list = NULL;
    LinkedNode* past_list = NULL;
    if(p == NULL || p->next == NULL){
        return;
    }
    while(p->next!=NULL){
        future_list = p->next;
        p->next = past_list;
        past_list = p;
        p = future_list;
    }
    p->next = past_list;
    head->next = p;
}

/*
 *  实现两个链表的复制
 */
void copy(LinkedNode* head1,LinkedNode* head2){
    LinkedNode* p = head1;
    while(p->next!=NULL){
        p = p->next;
        insert(head2,p->element);
    }
}

/*
 *  实现合并两个已排序的链表，返回新的合并后的链表
 */
LinkedNode* addTwoList(LinkedNode* head1,LinkedNode* head2){
    LinkedNode *head = create();
    copy(head1,head);
    LinkedNode *p2 = head2;
    while((p2 = p2->next)!=NULL){
        insert(head,p2->element);
    }
    return head;
}

/*
 *  令一个普通的单向链表变为循环链表
 */
void makeCircle(LinkedNode* head){
    LinkedNode* p = head;
    while(p->next!=NULL){
        p = p->next;
    }
    p->next = head;
}
/*
 *  在一个链表中查找数据x，返回index，若不存在返回-1,并添加该数据到尾部
 */
int findIndex(LinkedNode* head,ElementType x){
    LinkedNode* p = head;
    int index = 0;
    while(p->next!=NULL){
        p = p->next;
        index ++;
        if(p->element == x){
            return index;
        }
    }
    LinkedNode* add_list = (LinkedNode*)malloc(sizeof(LinkedNode));
    add_list->element = x;
    add_list->next = NULL;
    p->next = add_list;
    return -1;
}

/*
 * 将一个单向链表拆分为两个循环链表，第一个循环链表为原链表的奇数项，第二个循环链表为偶数项
 */
void oneToTwo(LinkedNode* head,LinkedNode* head1,LinkedNode* head2){
    if(!head1) {head1 = create();}
    if(!head2) {head2 = create();}
    LinkedNode *p = head;
    int mark = 0;
    while((p = p->next)!=NULL){
        if(++mark%2){
            insert(head1,p->element);
        }else{
            insert(head2,p->element);
        }
    }
    makeCircle(head1);
    head1->element = mark / 2 + 1;
    makeCircle(head2);
    head2->element = mark / 2;
}

/*
 *  实现类似substr()的功能
 */
ElementType* subEle(LinkedNode* head,int m,int n){
    ElementType* pe = (ElementType* )malloc((n-m)*sizeof(ElementType));
    LinkedNode* p = head;
    int i,j;
    for(i=0,j=0;p->next!=NULL;i++){
        p = p->next;
        if(i >= m && i < n){
            pe[j] = p->element;
            j++;
        }
    }
    return pe;
}
