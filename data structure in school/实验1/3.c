#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList;


int Joseph(LinkList *a, int topcount) {
    LinkList p;
    p = (*a);
    if(p->next == p) {
        printf("%d\n", p->data);
        return OK;
    }
    int newTopCount = 0;
    for(int i = 0; i < topcount-1; i++) {
        p = p->next;
        newTopCount = p->data;
    }
    printf("%d\n", newTopCount);
    p->data = p->next->data;
    p->next = p->next->next;
    Joseph(a, newTopCount);
    return newTopCount;
}

LinkList InitList(int people) {
    // 由于不要头节点，那么先初始化第一个节点，并赋值 1
    LinkList a = (LinkList)malloc(sizeof(Node));
    a->data = 1;
    a->next=a;
    // 声明一个指针，使其指向 a
    LinkList p = a;
    // 根据需要的人数，生成除了第一个的其他节点，并连起来
    for(int i = 0; i < people-1; i++) {
        LinkList b = (LinkList)malloc(sizeof(Node));
        p->next = b;
        p->next->data = i + 2;
        p = b;
    }
    // 最后将最后一个节点指向第一个节点
    p->next = a;

    return a;
}



int main(void) {
    //printf("First, initialize the linked list...\n");
    LinkList p;
    p = InitList(5);
    // 现在 p 指向了循环单链表中的第一个人
    int topcount = 3;
    Joseph(&p,topcount);


    return 0;
}
