//
// Created by lancelot on 11/27/15.
//

#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

typedef struct
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
}SqDoubleStack;

/*  构造一个空栈S */
Status InitStack(SqDoubleStack *S)
{
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

/* 把S置为空栈 */
Status ClearStack(SqDoubleStack *S)
{
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(SqDoubleStack S)
{
    if(S.top1 == -1 && S.top2 == MAXSIZE)
    {
        return TRUE;
    } else
    {
        return FALSE;
    }
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqDoubleStack S)
{
    return (S.top1 + 1) + (MAXSIZE - S.top2);
}

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack *S,SElemType e,int stackNumber)
{
    if(S->top1 + 1 == S->top2)  // 栈满
    {
        return ERROR;
    }
    if(stackNumber == 1)
    {
        S->top1 ++;
        S->data[S->top1] = e;
    } else if(stackNumber == 2)
    {
        S->top2 --;
        S->data[S->top2] = e;
    } else
    {
        return ERROR;
    }
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{
    if(stackNumber == 1)
    {
        if(S->top1 == -1)    // 栈 1 为空
        {
            return ERROR;
        }
        *e = S->data[S->top1];
        S->top1 --;
    } else if( stackNumber == 2)
    {
        if(S->top2 == MAXSIZE)
        {
            return ERROR;
        }
        *e = S->data[S->top2];
        S->top2 ++;
    }
}

Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

Status StackTraverse(SqDoubleStack S)
{
    if(S.top1 + 1 == S.top2)
    {
        return ERROR;
    }
    for( int i = 0; i <= S.top1; i++)
    {
        visit(S.data[i]);
    }
    for( int i = MAXSIZE - 1; i >= S.top2; i--)
    {
        visit(S.data[i]);
    }
    return OK;
}

int main(void)
{
    int j;
    SqDoubleStack s;
    int e;
    if(InitStack(&s)==OK)
    {
        for(j=1;j<=5;j++)
            Push(&s,j,1);
        for(j=MAXSIZE;j>=MAXSIZE-2;j--)
            Push(&s,j,2);
    }

    printf("栈中元素依次为：");
    StackTraverse(s);

    printf("当前栈中元素有：%d \n",StackLength(s));

    Pop(&s,&e,2);
    printf("弹出的栈顶元素 e=%d\n",e);
    printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));

    for(j=6;j<=MAXSIZE-2;j++)
        Push(&s,j,1);

    printf("栈中元素依次为：");
    StackTraverse(s);

    printf("栈满否：%d(1:否 0:满)\n",Push(&s,100,1));


    ClearStack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));

    return 0;
}