#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

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


int main(void) {
    LinkQueue Q;
    InitQueue(&Q);
    ElemType number = 0;
    printf("Welcome to the hosipital queue system...\n");
    printf("1. In Queue...\n");
    printf("2. See the doctor...\n");
    printf("3. Show the queue...\n");
    printf("4. No need the queue, see the doctor one by one...\n");
    printf("5. Go back home!\n");

    while(TRUE) {
        printf("Input the number of works you want do: ");
        int selected = 0;
        scanf("%d", &selected);
        switch (selected) {
            case 1:
                printf("Input the number of this patient: ");
                ElemType number = 0;
                scanf("%d", &number);
                if(EnQueue(&Q, &number)) {
                    printf("Done!\n");
                } else {
                    printf("Please try it again\n");
                }
                break;
            case 2:
                if(DeQueue(&Q, &number)) {
                    printf("Now is turn to the number %d patient to see the doctor\n", number);
                } else {
                    printf("Please try it again\n");
                }
                break;
            case 3:
                printf("All of the patient in the queue:\n");
                QueuePrintOut(&Q);
                break;
            case 4:
                printf("See the doctor in this order:\n");
                QueuePrintOut(&Q);
                return 0;
            case 5:
                printf("Exit now!\n");
                return 0;
        }
        //system("cls");
    }
}
