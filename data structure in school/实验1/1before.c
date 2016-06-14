#include <stdio.h>
#include <malloc.h>

#define MAX_SIZE 100
#define ElemType int
#define OK 1

typedef int Status;

typedef struct {
	ElemType data[MAX_SIZE];
	int length;
}SqList;

Status Init_Sq_List(SqList *SqList) {
	list.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	list.length = 0;
	list.listsize = LIST_INIT_SIZE;
	return OK;
}

int ListLength(SqList &list) {
	return list.length;
}

// 在给定的线性表SqList的第i个元素前插入新元素newElem
Status ListInsert(SqList &list, int where, ElemType newElem) {
	ElemType *p;
	p = list.elem;
	*p = newElem;

	return OK;
}

int main(void)
{
	SqList list;

	// Init sequence list
	InitList_Sq(list);

	// print out the length of sequence
	printf("the length of the sequence list is %d", ListLength(list));


	// declare a new elem
	ElemType newElem = 1;
	ListInsert(list, 1, newElem);


	return 0;
}
