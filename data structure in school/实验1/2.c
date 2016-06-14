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
}Node;
typedef struct Node *LinkList;

Status InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    return OK;
}

Status ListPrintOUt(LinkList *L) {
    LinkList p = (*L)->next;
    while (p) {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status ListEmpty(LinkList *L) {
    // 如果链表为空，则返回 TRUE
    if((*L)->next)
        return FALSE;
    else
        return TRUE;
}

int ListLength(LinkList *L) {
    int i = 0;
    LinkList p = (*L)->next;
    while(p) {
        i++;
        p = p->next;
    }
    return i;
}

/*********************************************/
/* 返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
/*********************************************/
int LocateElem(LinkList *L, ElemType e) {
    LinkList p = (*L)->next;
    int i = 0;
    while (p) {
        i++;
        if(p->data == e)
            return i;
        p = p->next;
    }
    return 0;
}

/*******************************************/
/* 得到 L 中第 i 个元素的值，并赋给 e */
/****************************************/
Status GetElem(LinkList *L, int position, ElemType *e) {
    if(position <= 0 || position > ListLength(L)) {
        // 越界
        return ERROR;
    }
    LinkList p = (*L)->next;
    for(int i = 0; i < position - 1; i++) {
        p = p->next;
    }
    *e = p->data;
    return OK;
}

/***************************************/
/* 在L中第i个位置之前插入新的数据元素e */
/***************************************/
Status ListInsert(LinkList *L, int position, ElemType e) {
    if(position <= 0 || position > ListLength(L) + 1) {
        // 越界
        return ERROR;
    }
    LinkList p = *L;
    for(int i = 0; i < position-1; i++) {
        // 让 p 为第 i 个元素的指针
        p = p->next;
    }
    LinkList s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

/***********************************************/
/* 将元素 e 插入到链表 L 的合适位置，使其仍然保持从小到大的顺序 */
Status InsertListIncreaseOrder(LinkList *L, ElemType e) {
    if(LocateElem(L, e)) {
        // 如果 L 中已经存在 e，则返回 0
        return ERROR;
    }
    // 看看 e 是否比当前链表中的最后一个元素还要大
    // 如果大的话，就将该元素插入到链表的最后
    ElemType last_elem;
    GetElem(L, ListLength(L), &last_elem);
    if(e > last_elem) {
        ListInsert(L, ListLength(L)+1, e);
        return OK;
    }
    // 下面考虑的是一般情况
    LinkList p;
    p = (*L)->next;
    for(int i = 0; p!=NULL; i++) {
        // 当 e 小于 p 指向的元素，则将 e 元素插到 p 指针指向的元素之前
        if(e < p->data) {
            // 此时 p 指向刚好比 e 大的元素
            ListInsert(L, i+1, e);
            return OK;
        }
        p = p->next;
    }

    return ERROR;
}

Status UnionBtoA(LinkList *List_A, LinkList *List_B) {
    for(int i = 0; i < ListLength(List_B); i++) {
        ElemType e = 0;
        GetElem(List_B, i+1, &e);
        InsertListIncreaseOrder(List_A, e);
    }
}

int main(void) {
    printf("First, initialize the link lists A and B...\n");
    LinkList List_A;
    InitList(&List_A);
    LinkList List_B;
    InitList(&List_B);

    printf("Then, insert 1,6,8,21 into list A and 2,6,8,10 into B...\n");
    ListInsert(&List_A, 1, 1);
    ListInsert(&List_A, 2, 6);
    ListInsert(&List_A, 3, 8);
    ListInsert(&List_A, 4, 14);
    ListInsert(&List_B, 1, 2);
    ListInsert(&List_B, 2, 6);
    ListInsert(&List_B, 3, 8);
    ListInsert(&List_B, 4, 10);

    printf("Now, print out the List A and B...\n");
    printf("List A is: ");
    ListPrintOUt(&List_A);
    printf("List B is: ");
    ListPrintOUt(&List_B);

    printf("Last, merge list A into list B...\n");
    UnionBtoA(&List_B, &List_A);
    printf("And now the list B is: ");
    ListPrintOUt(&List_B);
    //printf("%d\n", ListLength(&List_B));

}
