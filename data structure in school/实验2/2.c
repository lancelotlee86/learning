#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define N 4 // 顺序栈的最大长度，本题中是车位数

typedef int Status;
typedef int ElemType; // 这里应该是 QElemType
typedef int SElemType;


//******************************************************
//*************** 顺序栈 *******************************
//*****************************************************

typedef struct {
    SElemType data[N];
    int top;   /* 用于栈顶指针 */
} SqStack;

Status InitStack(SqStack *S) {
    S->top = -1;
    return OK;
}

Status StackEmpty(SqStack *S) {
    if(S->top == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Status StackFull(SqStack *S) {
    if(S->top == N - 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Status StackLength(SqStack *S) {
    return S->top + 1;
}

void PrintOutStack(SqStack *S) {
    for(int i = 0; i <= S->top; i++) {
        printf("%d,  ", S->data[i]);
    }
}

Status StackPush(SqStack *S, SElemType *e) {
    if(S->top == N - 1) {
        // 栈满
        return ERROR;
    }
    S->top ++;
    S->data[S->top] = *e;
    return OK;
}

Status StackPop(SqStack *S, SElemType *e) {
    if(S->top == -1) {
        // 栈空
        return ERROR;
    }
    *e = S->data[S->top];
    S->top --;
    return OK;
}

// 返回等于元素 e 的元素的位置，data[0]为第一个元素
int FindSqStackElem(SqStack *S, SElemType *e) {
    if(S->top == -1) {
        // 栈空
        return ERROR;
    }
    int fakeTop = -1;
    for(int fakeTop = 0; fakeTop <= S->top; fakeTop++) {
        if(*e == S->data[fakeTop]) {
            return fakeTop + 1;
        }
    }
    return 0;
}

//******************************************************
//*************** 链队列 *********************************
//******************************************************
typedef struct QNode {
    ElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

/*
    生成的队列是这样的：
    一个头指针，指向头节点；
    头节点的data不存储数据，next指向下一个节点，也就是队列真正的第一个节点；
    尾指针，指向队列真正的最后一个节点
*/

Status InitQueue(LinkQueue *Q) {
    Q->front= Q->rear = (QueuePtr)malloc(sizeof(QNode));    // 让头尾指针都指向头节点；
    Q->front->next = NULL;
    return OK;
}

Status QueueEmpty(LinkQueue *Q) {
    // 如果队列链表为空，则返回 TRUE
    if(Q->front == Q->rear)
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(LinkQueue *Q, ElemType *e) {
    // 插入元素 e 到队列
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    s->data = *e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}

// 删除队首元素并将data赋值给 e
Status DeQueue(LinkQueue *Q, ElemType *e) {
    if(Q->front == Q->rear)
        return ERROR;   // 队列中没有元素了，头尾指针指向了同一个虚的头节点
    QueuePtr p = Q->front->next;    // p 现在是实际的第一个元��?
    *e = p->data;  // 第一个元素的data
    Q->front->next = p->next;   // 队列头节点的 next 域指向的元素应该被删除，所以将��? next 域指向原本第一个元素的下一个元��?
    if(Q->rear==p)		// 若队头就是队尾，则完成删除第一个元素后将rear指向头结��?
        Q->rear=Q->front;
    return OK;
}

int QueueLength(LinkQueue *Q) {
    QueuePtr p = Q->front->next;
    int count = 0;
    while (p != NULL) {
        count ++;
        p = p->next;
    }
    //printf("%d\n", count);
    return count;
}

Status QueuePrintOut(LinkQueue *Q) {
    QueuePtr p;
    p = Q->front->next;
    while(p != NULL) {
        printf("%d,  ", p->data);
        p = p->next;
    }
    printf("\n");
    //printf("%d\n", Q->front->next->data);
    //printf("%d\n", Q->front->next->next->data);
}

//*************************************************
//********************* 与停车场相关的操作 ************
//***************************************************

Status InParkingLot(SqStack *S0, SqStack *S1, LinkQueue *Q, ElemType *carNumber) {
    if(FindSqStackElem(S0, carNumber)) {
        printf("the car you typed is already in parking lot! try it again\n");
        return ERROR;
    }
    if(!StackFull(S0)) {
        // 停车场没有满，可以进入顺序栈 S0
        if(StackPush(S0, carNumber)) {
            return OK;
        } else {
            return ERROR;
        }
    } else{
        // 停车场满了，只能加入链队列 Q
        if(EnQueue(Q, carNumber)) {
            return OK;
        } else {
            return ERROR;
        }
    }
}

Status OutParkingLot(SqStack *S0, SqStack *S1, LinkQueue *Q, ElemType *carNumber) {
    // 检查顺序栈是否为空
    // 先检查车号为 carNumber 的车是否存在
    // 如存在则将该车之后的车一次放入顺序栈 S1 中
    // 接着将该车 pop
    // 然后将 S1 中的车再依次入栈 S0
    // 最后将链队列 Q 的队首元素入栈 S0
    if(StackEmpty(S0)) {
        printf("The parking lot is empty now!\n");
        return ERROR;
    }
    if(FindSqStackElem(S0, carNumber)) {
        // carNumber 车存在
        int sequence = -1;
        sequence = FindSqStackElem(S0, carNumber);
        if(sequence != S0->top + 1) {
            // 如果不在栈顶
            for(int fakeTop = S0->top; fakeTop >= sequence; fakeTop--) {
                // 将该车之后的车一次放入顺序栈 S1 中
                int car = 0;
                StackPop(S0, &car);
                StackPush(S1, &car);
            }
        }

        ElemType carPoped = -1;
        // 目标车辆出栈
        StackPop(S0, &carPoped);
        printf("The number %d car is driving out of parking lot...\n", carPoped);

        for(int i = 0; i <= StackLength(S1); i++) {
            // 然后将 S1 中的车再依次入栈 S0
            int car = 0;

            if(StackPop(S1, &car)) {
                // 如果 S1栈中有元素则压入 S0
                StackPush(S0, &car);
            }
        }
        if(QueueLength(Q) > 0) {
            int car = 0;
            DeQueue(Q, &car);
            StackPush(S0, &car);
        }
        return OK;
    } else {
        printf("Can't find the car you want to drive out.\n");
        return ERROR;
    }
}

void StatusOfParkingLot(SqStack *S0, SqStack *S1, LinkQueue *Q) {
    printf("The cars in S0: ");
    PrintOutStack(S0);
    printf("\n");

    printf("The cars in S1: ");
    PrintOutStack(S1);
    printf("\n");

    printf("The cars in Q: ");
    QueuePrintOut(Q);
    printf("\n");
}

int main(void) {

    // 初始化
    SqStack S0;
    InitStack(&S0);
    SqStack S1;
    InitStack(&S1);
    LinkQueue Q;
    InitQueue(&Q);

    printf("1. Drive into parking lot...\n");
    printf("2. Drive out of parking lot...\n");
    printf("3. Show the status of S0, S1 and Q...\n");
    printf("4. Exit now!\n");

    while(TRUE) {
        printf("Input the number of work you want do: ");
        int selected = 0;
        scanf("%d", &selected);
        switch (selected) {
            case 1:
                {
                    int carNumber = 0;
                    printf("Input the number of car driving in: ");
                    scanf("%d", &carNumber);    // 输入要入库的车号
                    InParkingLot(&S0, &S1, &Q, &carNumber);
                    break;
                }
            case 2:
                {
                    int carNumber = 0;
                    printf("Input the number of car driving out: ");
                    scanf("%d", &carNumber);    // 输入要出库的车号
                    OutParkingLot(&S0, &S1, &Q, &carNumber);
                    break;
                }
            case 3:
                StatusOfParkingLot(&S0, &S1, &Q);
                break;
            case 4:
                return 0;
        }
    }
    // 入库
    ElemType carNumber = 0;
    InParkingLot(&S0, &S1, &Q, &carNumber);
    carNumber ++;
    InParkingLot(&S0, &S1, &Q, &carNumber);
    carNumber ++;
    InParkingLot(&S0, &S1, &Q, &carNumber);
    printf("S0: ");
    PrintOutStack(&S0);
    printf("\n");
    printf("Q: ");
    QueuePrintOut(&Q);

    carNumber = 2;
    OutParkingLot(&S0, &S1, &Q, &carNumber);

    printf("S1: ");
    PrintOutStack(&S1);

    printf("\nS0: ");
    PrintOutStack(&S0);

/*
    //单元测试代码
    // 初始化
    SqStack S;
    InitStack(&S);

    // push 测试
    for(int e = 0; e < 4; e++) {
        StackPush(&S, &e);
    }

    // pop 测试
    int elem = -1;
    StackPop(&S, &elem);

    // printoutstack 测试
    printf("The elem in the stack is: ");
    PrintOutStack(&S);

    printf("\n");
    elem = 3;
    printf("%d\n", FindSqStackElem(&S, &elem));
*/
}
