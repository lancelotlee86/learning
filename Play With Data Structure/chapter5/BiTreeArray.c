//
// Created by lancelot on 11/28/15.
//

#include <stdio.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;
typedef int TElemType;

typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct  // 这个是代表位置的，层和序号
{
    int level,order; /* 结点的层,本层序号(按满二叉树计算) */
} Position;

TElemType Nil = 0;

Status visit(TElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
Status InitBiTree(SqBiTree T)
{
    for( int i = 0; i < MAX_TREE_SIZE; i++)
    {
        T[i] = Nil;
    }
    return OK;
}

/* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T)
{
    /* 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T */
    for( int i = 0; i < 10; i++)
    {
        T[i] = i + 1;
    }
    /* 将空赋值给T的后面的结点 */
    for( int i = 10; i < MAX_TREE_SIZE; i++)
    {
        T[i] = Nil;
    }
}

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(SqBiTree T)
{
    if(T[0] == Nil)     /* 根结点为空,则树空 */
    {
        return TRUE;
    } else
    {
        return FALSE;
    }
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
//
int BiTreeDepth(SqBiTree T)
{
    for( int i = MAX_TREE_SIZE - 1; i >= 0; i--)
    {
        if(T[i] != Nil)     // 查找最后一个节点的序号
        {
            // 现在 i 为最后一个节点的下标
            i++;
            // 现在 i 为最后一个结点的序号
            for( int j = 1; j < MAX_TREE_SIZE; j++)
            {
                if(i > pow(2, j) - 1)   // 当不满足这个表达式时，j 刚好是深度的值
                {
                    continue;
                } else
                {
                    return j;
                }
            }
        }
    }
}


/* 初始条件: 二叉树T存在 */
/* 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 */
Status Root(SqBiTree T,TElemType *e)
{
    if(BiTreeEmpty(T))
    {
        return ERROR;
    } else
    {
        *e = T[0];
        return OK;
    }
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
TElemType Value(SqBiTree T,Position e)
{
    int seq = (int)(pow(2, e.level - 1) - 1 + e.order); // seq 是序数
    return T[seq - 1];  // 要返回 T[序数 -1]才行
}

/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
Status Assign(SqBiTree T,Position e,TElemType value)
{
    int seq = (int)(pow(2, e.level - 1) - 1 + e.order); // seq 是序数，不是下标

    if( value!=Nil && T[seq/2 - 1] == Nil) /* 给叶子赋非空值但双亲为空 */
    {
        return ERROR;
    } else if( value == Nil && (T[seq*2-1]!=Nil || T[seq*2+1-1]!=Nil))  /*  给双亲赋空值但有叶子（不空） */
        return ERROR;
    T[seq - 1] = value;
    return OK;
}

/* PreOrderTraverse()调用 */
void PreTraverse(SqBiTree T,int e)  // 参数 e 为序数，不是下标
{
    visit(T[e - 1]);
    if( T[e*2-1] != Nil)  // 左子树不为空
    {
        PreTraverse(T, e*2);
    }
    if( T[e*2] != Nil)  // 右子树不为空
    {
        PreTraverse(T, e*2 + 1);
    }
}

/* 初始条件: 二叉树存在 */
/* 操作结果: 先序遍历T。 */
Status PreOrderTraverse(SqBiTree T)
{
    if(!BiTreeEmpty(T))
    {
        PreTraverse(T, 1);
    }
    printf("\n");
    return OK;
}

int main(void)
{
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T,&e);
    if(i)
        printf("二叉树的根为：%d\n",e);
    else
        printf("树空，无根\n");
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);

    printf("修改结点的层号3本层序号2。");
    p.level=3;
    p.order=2;
    e=Value(T,p);
    printf("待修改结点的原值为%d请输入新值:50 ",e);
    e=50;
    Assign(T,p,e);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);

    ClearBiTree(T);
    printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T,&e);
    if(i)
        printf("二叉树的根为：%d\n",e);
    else
        printf("树空，无根\n");

    return 0;

}