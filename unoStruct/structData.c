#include "structData.h"

//=========================================
void Init(LIST* l) {
	l->pHead = l->pTail = NULL;
}

void InitStack(STACK* s) {
	s->top = NULL;
}

//===================================
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

// xoa node dau
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

void giaiPhong(LIST* l) {
	NODE* p;
	while (l->pHead != NULL) {
		p = l->pHead;// cho con tro p tro toi node dau
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

// ham in ra man hinh dan bai tren tay ng choi
void show(LIST l1) {
	printf("\n===BO BAI===\n");
	for (NODE* p = l1.pHead; p != NULL; p = p->pNext) {
		printf("%d. %c-%d", p->data.id, p->data.color, p->data.number);
		printf("\n");
	}
	printf("\n============");
}

// ham tim kiem 1 node trong dslk bang id
NODE* find(LIST l, int id) {
	int check = 0;
	NODE* q = NULL;
	for (NODE* p = l.pHead; p != NULL; p = p->pNext) {
		if (p->data.id == id) {
			q = getNode(p->data);
			check = 1;
			break;
		}
	}
	if (check == 0) {
		printf("\np null");
	}
	return q;
}

// ham chia bai cho nguoi choi
void inPutL1(STACK* s, LIST* l1) {
	Init(l1);
	for (int i = 0; i < 7; i++) {
		UNO uno = pop(s);
		NODE* p = getNode(uno);
		addTail(l1, p);
	}
}

void deleteNode(LIST* l1, int id) {
	if (l1->pHead->data.id == id)
	{
		xoaDau(l1);
		return;
	}

	if (l1->pTail->data.id == id)
	{
		XoaCuoi(l1);
		return;
	}
	NODE* truoc = l1->pHead;
	for (NODE* p = l1->pHead->pNext; p != l1->pTail; p = p->pNext) {
		if (p->data.id == id) {
			truoc->pNext = p->pNext;
			free(p);
			break;
		}
		else {
			truoc = p;
		}
	}

}

// ham tim kiem trong dslk dua tren mau va gia tri.
NODE* findL1(LIST l1, char x, int y) {
	NODE* p;
	for (p = l1.pHead; p != NULL; p = p->pNext) {
		if (p->data.color == x && p->data.number == y) {
			break;
		}
	}
	return p;
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
	NODE* q = (NODE*)malloc(sizeof(NODE));
	q = p;
	//truong hop stack rong
	if (s->top == NULL) {
		s->top = q;
	}
	else {
		q->pNext = s->top;
		s->top = q;
	}
	return 1;
}

int push2(STACK* s, UNO uno) {
	NODE* p = (NODE*)malloc(sizeof(NODE));
	p = getNode(uno);
	if (s->top == NULL) {
		s->top = p;
	}
	else {
		p->pNext = s->top;
		s->top = p;
	}
	return 1;
}

UNO pop(STACK* s) //Loai bo phan tu khoi Stack
{
    UNO x;
	NODE* p = (NODE*)malloc(sizeof(NODE));
	if (!isEmpty(s))
	{
		x = s->top->data; //luu lai gia tri
		p = s->top;
		s->top = s->top->pNext; //Xoa phan tu Top
		free(p);
	}
    return x;
}

// giai phong
void outPut(STACK* s) {
	while (isEmpty(s) == 0) {
		pop(s);
	}
}
//==========================================================

// ham tra ve 1 quan bai uno
UNO timUno(LIST l, int id) {
	UNO uno;
	for (NODE* p = l.pHead; p != NULL; p = p->pNext) {
		if (p->data.id == id) {
			uno = p->data;
			break;
		}
	}
	return uno;
}


