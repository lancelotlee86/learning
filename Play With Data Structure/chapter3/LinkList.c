//
// Created by lancelot on 11/24/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

typedef int Status;
typedef int  ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node *LinkList;


/* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    if(!(*L))
    {
        return ERROR;
    }
    (*L)->next = NULL;  // 将头指针指向的设为NULL，也就是第一个元素为NULL
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L,int i,ElemType *e)
{
    LinkList p = L;
    for( int j = 0; j < i; j++)
    {
        if(!(p->next))
        {
            return ERROR;
        }
        p = p->next;
    }
    *e = p->data;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{
    if(L->next)
    {
        return FALSE;
    } else
    {
        return TRUE;
    }
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p = (*L)->next;    // p 指向第一个元素节点
    LinkList q;
    // 将着眼点放在 p 上
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;  // 将头节点指针域为NULL
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    LinkList p = L->next;
    int length = 0;
    while(p)
    {
        p = p->next;
        length ++;
    }
    return length;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L,ElemType e)
{
    LinkList p = L->next;
    int located = 0;
    while(p)
    {
        located ++;
        if(p->data == e)
        {
            return located;
        }
        p = p->next;
    }
    return ERROR;
}
/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L,int position,ElemType e)
{
    LinkList p = (*L);
    LinkList q;
    for(int i = 1; i < position; i++)
    {
        p = p->next;    // 循环结束时，p 指向第 i - 1 个元素节点
    }
    if(!p)
    {
        return ERROR;
    }
    q = p->next;    // q 指向第 i 个元素节点
    // 接下来要在第 i - 1 和第 i 个元素节点之间插入一个新的元素节点
    LinkList s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    p->next = s;
    s->next = q;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L,int position,ElemType *e)
{
    LinkList p = *L;    // 现在 p 指向第一个元素节点
    for( int i = 0; i < position - 1; i++)
    {
        p = p->next;
    }
    // 现在 p 指向第 (position - 1） 个元素节点
    if(!(p->next))  // 判断 p 的 next 有没有元素节点，没的话说明超出了范围
    {
        return ERROR;
    }
    LinkList q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    for(int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
    LinkList p,r;
    int i;
    srand(time(0));                      /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
    r=*L;                                /* r为指向尾部的结点 */
    for (i=0; i<n; i++)
    {
        p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
        p->data = rand()%100+1;           /*  随机生成100以内的数字 */
        r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
        r = p;                            /* 将当前的新结点定义为表尾终端结点 */
    }
    r->next = NULL;                       /* 表示当前链表结束 */
}

int main(void)
{
    LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));

    for(j=1;j<=5;j++)
        i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n", ListLength(L));
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);


    i=ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
        ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);

    printf("ListLength(L)=%d \n",ListLength(L));

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
    printf("ListLength(L)=%d \n",ListLength(L));

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);

    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j);
        if(k)
            printf("第%d个元素的值为%d\n",k,j);
        else
            printf("没有值为%d的元素\n",j);
    }


    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(&L,j,&e); /* 删除第j个数据 */
        if(i==ERROR)
            printf("删除第%d个数据失败\n",j);
        else
            printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L);

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L);


    i=ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建L的元素(头插法)：");
    ListTraverse(L);

    i=ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建L的元素(尾插法)：");
    ListTraverse(L);

}