#pragma warning (disable: 4996)
#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// #include <gtk/gtk.h>
// #include "login.h"
FILE* fileIn;
FILE* fileOut;

//===============CAC CAU TRUC SE DUNG==================
// cau truc luu 108 la bai
typedef struct uno {
	int id; // tu 1 - 108
	char color; // r: do, y : vang, g: xanh la, b: xanh duong, k: khong mau
	int number; // 
	// 0 - 9 la con bai thong thuong
	// -1 : cam 1 
	// -2 : dao chieu
	// -3 : cong 2
	// -4 doi mau
	// -5 cong 4
}UNO;
typedef struct Node {
	UNO data;
	struct Node* pNext;
}NODE;
typedef struct List {
	NODE* pHead;
	NODE* pTail;
}LIST;
typedef struct stack {
	NODE* top;
}STACK;

LIST l; // danh sach de luu 108 quan bai
//LIST l1, l2, l3, l4;// danh sach luu quan bai tren tay nguoi choi
STACK s; // luu quan bai da dao
STACK s1;// luu quan bai da danh

void Init(LIST* l) {
	l->pHead = l->pTail = NULL;
}

void InitStack(STACK* s) {
	s->top = NULL;
}

//===================================
NODE* getNode(UNO DATA) {
	NODE* p = (NODE*)malloc(sizeof(NODE));//new NODE;// khoi tao
	if (p == NULL) {
		printf("\nkhong du bo nho de cap phat con tro.");
		return NULL;
	}
	p->data = DATA; // dua data vao trong node
	p->pNext = NULL; // khoi tao moi lien ket
	return p; // tra ve node p
}



//======================================
void addHead(LIST* l, NODE* p) {
	// danh sach rong
	if (l->pHead == NULL) {
		l->pHead = l->pTail = p;// p vua la dau, vua la cuoi
	}
	else {
		p->pNext = l->pHead; // cho p tro toi dau danh sach
		l->pHead = p; // cap nhat lai dau danh sach
// them vao dau tk can them tro toi dau, dau cap nhat lai la no
	}
}
void addTail(LIST* l, NODE* p) {
	if (l->pHead == NULL) {
		l->pHead = l->pTail = p;
	}
	else {
		l->pTail->pNext = p;// pTail tro Next toi p
		l->pTail = p;// cap nhat lai pTail
// them vao cuoi thi thang cuoi tro no, no cap nhat thanh cuoi
	}
}

// xoa nude dau
void xoaDau(LIST* l) {
	if (l->pHead != NULL) {
		NODE* p = l->pHead;
		l->pHead = l->pHead->pNext;
		free(p);
	}
}

//xoa cuoi
void XoaCuoi(LIST* l)
{
	NODE* g = l->pHead; // Node trÆ°á»›c
	NODE* p;
	for (p = l->pHead; p != NULL; p = p->pNext)
	{
		if (p == l->pTail)
		{
			g->pNext = NULL;
			l->pTail = g;
			free(p);
			return;
		}
		g = p;
	}
}

//============PHAN HAM CUA STACK===================
int isEmpty(STACK* s) {
	if (s->top == NULL) {
		return 1;
	}
	return 0;
}

int push(STACK* s, NODE* p) {
	if (p == NULL) {
		return 0;
	}
	//truong hop stack rong
	if (s->top == NULL) {
		s->top = p;
	}
	else {
		p->pNext = s->top;
		s->top = p;
	}
	return 1;
}

int push2(STACK* s, UNO uno) {
	NODE* p = getNode(uno);
	if (s->top == NULL) {
		s->top = p;
	}
	else {
		p->pNext = s->top;
		s->top = p;
	}
	return 1;
}

// xoa dinh stack, thanh cong tra ve 1, nguoc lai 0
//int Pop(STACK* s, UNO* DATA) {
//	DATA = s->top;
//	NODE* p = s->top;
//	////s->top = p->pNext;  // s->top = s->top->pNext;
//	free(p);
//	return 1;
//}

UNO pop(STACK* s) //Loai bo phan tu khoi Stack
{
	if (!isEmpty(s))
	{
		UNO x = s->top->data; //luu lai gia tri
		s->top = s->top->pNext; //Xoa phan tu Top
		return x;
	}
}

// giai phong
void outPut(STACK* s) {
	while (isEmpty(s) == 0) {
		UNO uno;
		uno = pop(s);
		//xuat(uno);
	}
}

//============================================ 
// 
//doc file;
void docFile(FILE* fileIn, LIST* l) {
	UNO uno;

	fscanf(fileIn, "%d", &uno.id);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%c", &uno.color);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%d", &uno.number);
	//printf("%d %c %d", uno.id, uno.color, uno.number);
	NODE* p;
	p = getNode(uno);
	addTail(l, p);
}

// load danh sach nguoi dung tu file len danh sach lien ket
void loadTuFile(FILE* fileIn, LIST* l) {
	fileIn = fopen("input.txt", "rt");
	if (!fileIn) {
		printf("\nkhong tim thay file can doc.");
		return;
	}
	while (!feof(fileIn)) {
		docFile(fileIn, l);
	}
	//XoaCuoi(l);
	fclose(fileIn);
}

void giaiPhong(LIST* l) {
	NODE* p;
	while (l->pHead != NULL) {
		p = l->pHead;// cho con tro p tro toi nude dau
		l->pHead = l->pHead->pNext;// pHead dc tro sang node ben canh
		free(p);
	}
}

void Output(LIST l) {
	for (NODE* p = l.pHead; p != NULL; p = p->pNext) {
		printf("%d %c %d", p->data.id, p->data.color, p->data.number);
		printf("\n");
	}
}

// ham tim kiem 1 node trong dslk bang id
NODE* find(LIST l, int id) {
	//UNO uno = NULL;
	int check = 0;
	NODE* q = NULL;
	//Output(l);
	for (NODE* p = l.pHead; p != NULL; p = p->pNext) {
		//Output(l);
		//printf("%d \n",p->data.id);
		if (p->data.id == id) {
			//uno = p->data;
			q = getNode(p->data);
			check = 1;
			break;
		}
	}
	if (check == 0) {
		printf("\np null");
	}
	//p = getNode(uno);
	return q;
}

void Swap(int* number_1, int* number_2)
{
	int temp = *number_1;
	*number_1 = *number_2;
	*number_2 = temp;
}