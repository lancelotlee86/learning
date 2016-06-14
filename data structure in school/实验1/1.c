#include <stdio.h>

#define MAX_SIZE 100
#define ElemType char
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef struct {
	ElemType data[MAX_SIZE];
	int length;
}SqList;

Status Init_Sq_List(SqList *L) {
	L->length = 0;
	return OK;
}

int ListLength(SqList *L) {
	return L->length;
}

Status ListEmpty(SqList *L) {
	if(L->length == 0)
		return TRUE;
	return FALSE;
}

Status ClearList(SqList *L) {
    L->length=0;
    return OK;
}

Status GetElem(SqList *L, int i, ElemType *e) {
	if(L->length==0 || i<1 || i>L->length)	// make sure that 'i' is available
		return ERROR;
	*e = L->data[i-1];
	return OK;
}

Status GetElem2(SqList L,int i,ElemType *e) {
	if(L.length==0 || i<1 || i>L.length)	// make sure that 'i' is available
		return ERROR;
	*e = L.data[i-1];
	return OK;
}

Status ListInsert(SqList *L, int i, ElemType e) {
	if(i > L->length + 1 || i < 1)	// when i is larger than the next elem of last elem, or equel to 0 or smaller, return ERROR
		return ERROR;
	if(L->length == MAX_SIZE)	// the sequence list is full, return ERROR
		return ERROR;

	if(i <= L->length) {
		// i is not the next elem of the tail elem
		// so we need to move some elem to the next position
		for(int k = L->length - 1; k >= i - 1; k--) {
			L->data[k + 1] = L->data[k];
		}
	}
	L->data[i - 1] = e;
	L->length++;

	return OK;
}

int LocateElem(SqList *L, ElemType *e) {	// with my func, only can find the first elem matched
	for(int i = 0; i < L->length; i++) {
		if(L->data[i] == *e) {
			return i + 1;
		}
	}
	return 0;
}

Status ListDelete(SqList *L, int i, ElemType *e) {
	if(L->length == 0) {
		return ERROR;
	}
	if(i < 1 || i > L->length) {
		return ERROR;
	}
	*e = L->data[i - 1];
	if(i < L->length) {	// not the last elem of the list
		for(int k = i; k < L->length; k++) {
			L->data[k - 1] = L->data[k];
		}
	}
	L->length--;
	return OK;
}

Status ListPrintOut(SqList *L) {
	// why not printf("%s", L->data) ??????????????????
	printf("now the elems in the list are: ");
	for(int i = 0; i < L->length; i++) {
		printf("%c  ", L->data[i]);
	}
	printf("\n");
}

int main(void)
{
	printf("Initialize the sequence list...\n");
	SqList L;
	Init_Sq_List(&L);

	printf("Insert a, b, c, e into sequence list...\n");
	char data[4] = "abce";
	for(int i = 0; i < 4; i++) {
		ListInsert(&L, i + 1, data[i]);
	}
	ListPrintOut(&L);
	printf("the length of the list is: %d\n", ListLength(&L));

	char e;
	if(GetElem(&L, 3, &e)) {
		printf("the 3rd elem of the list is: %c\n", e);
	} else {
		printf("can not get elem\n");
		return 0;
	}

	char a = 'a';
	if(LocateElem(&L, &a)) {
		printf("the elem a is located at: %d\n", LocateElem(&L, &a));
	} else {
		printf("the elem you want is not in the list...\n");
	}

	printf("insert f into before the 4th\n");
	char f = 'f';
	ListInsert(&L, 4, f);

	ListPrintOut(&L);

	char deleted = ' ';
	ListDelete(&L, 3, &deleted);
	printf("delete the 3rd elem of the list: %c\n", deleted);

	ListPrintOut(&L);

	return 0;
}
