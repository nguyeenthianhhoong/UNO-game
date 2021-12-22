#pragma warning(disable : 4996)
#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include <time.h>

FILE *fileIn;
FILE *fileOut;

//===============CAC CAU TRUC SE DUNG==================
// cau truc luu 108 la bai
typedef struct uno
{
	int id;		// tu 1 - 108
	char color; // r: do, y : vang, g: xanh la, b: xanh duong, k: khong mau
	int number; //
				// 0 - 9 la con bai thong thuong
				// -1 : cam 1
				// -2 : dao chieu
				// -3 : cong 2
				// -4 doi mau
				// -5 cong 4
} UNO;
typedef struct Node
{
	UNO data;
	struct Node *pNext;
} NODE;
typedef struct List
{
	NODE *pHead;
	NODE *pTail;
} LIST;
typedef struct stack
{
	NODE *top;
} STACK;

LIST l;	 // danh sach de luu 108 quan bai
LIST l1; // danh sach luu quan bai tren tay nguoi choi
STACK s;

//=========================================
void Init(LIST *l)
{
	l->pHead = l->pTail = NULL;
}

void InitStack(STACK *s)
{
	s->top = NULL;
}

//===================================
NODE *getNode(UNO DATA)
{
	NODE *p = (NODE *)malloc(sizeof(NODE)); //new NODE;// khoi tao
	if (p == NULL)
	{
		printf("\nkhong du bo nho de cap phat con tro.");
		return NULL;
	}
	p->data = DATA;	 // dua data vao trong node
	p->pNext = NULL; // khoi tao moi lien ket
	return p;		 // tra ve node p
}

//======================================
void addHead(LIST *l, NODE *p)
{
	// danh sach rong
	if (l->pHead == NULL)
	{
		l->pHead = l->pTail = p; // p vua la dau, vua la cuoi
	}
	else
	{
		p->pNext = l->pHead; // cho p tro toi dau danh sach
		l->pHead = p;		 // cap nhat lai dau danh sach
							 // them vao dau tk can them tro toi dau, dau cap nhat lai la no
	}
}
void addTail(LIST *l, NODE *p)
{
	if (l->pHead == NULL)
	{
		l->pHead = l->pTail = p;
	}
	else
	{
		l->pTail->pNext = p; // pTail tro Next toi p
		l->pTail = p;		 // cap nhat lai pTail
							 // them vao cuoi thi thang cuoi tro no, no cap nhat thanh cuoi
	}
}

// xoa nude dau
void xoaDau(LIST *l)
{
	if (l->pHead != NULL)
	{
		NODE *p = l->pHead;
		l->pHead = l->pHead->pNext;
		free(p);
	}
}

//xoa cuoi
void XoaCuoi(LIST *l)
{
	NODE *g = l->pHead; // Node trÆ°á»›c
	NODE *p;
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
int isEmpty(STACK *s)
{
	if (s->top == NULL)
	{
		return 1;
	}
	return 0;
}

int push(STACK *s, NODE *p)
{
	if (p == NULL)
	{
		return 0;
	}
	//truong hop stack rong
	if (s->top == NULL)
	{
		s->top = p;
	}
	else
	{
		p->pNext = s->top;
		s->top = p;
	}
	return 1;
}

int push2(STACK *s, UNO uno)
{
	NODE *p = getNode(uno);
	if (s->top == NULL)
	{
		s->top = p;
	}
	else
	{
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

UNO pop(STACK *s) //Loai bo phan tu khoi Stack
{
	if (!isEmpty(s))
	{
		UNO x = s->top->data;	//luu lai gia tri
		s->top = s->top->pNext; //Xoa phan tu Top
		return x;
	}
}

// giai phong
void outPut(STACK *s)
{
	while (isEmpty(s) == 0)
	{
		UNO uno;
		uno = pop(s);
		//xuat(uno);
	}
}

//============================================
//
//doc file;
void docFile(FILE *fileIn, LIST *l)
{
	UNO uno;

	fscanf(fileIn, "%d", &uno.id);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%c", &uno.color);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%d", &uno.number);
	//printf("%d %c %d", uno.id, uno.color, uno.number);
	NODE *p;
	p = getNode(uno);
	addTail(l, p);
}

// load danh sach nguoi dung tu file len danh sach lien ket
void loadTuFile(FILE *fileIn, LIST *l)
{
	fileIn = fopen("input.txt", "rt");
	if (!fileIn)
	{
		printf("\nkhong tim thay file can doc.");
		return;
	}
	while (!feof(fileIn))
	{
		docFile(fileIn, l);
	}
	XoaCuoi(l);
	fclose(fileIn);
}

void giaiPhong(LIST *l)
{
	NODE *p;
	while (l->pHead != NULL)
	{
		p = l->pHead;				// cho con tro p tro toi nude dau
		l->pHead = l->pHead->pNext; // pHead dc tro sang node ben canh
		free(p);
	}
}

void Output(LIST l)
{
	for (NODE *p = l.pHead; p != NULL; p = p->pNext)
	{
		printf("%d %c %d", p->data.id, p->data.color, p->data.number);
		printf("\n");
	}
}

// ham in ra man hinh dan bai tren tay ng choi
void show(LIST l1)
{
	printf("\nbai cua ban:\n");
	for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
	{
		printf("%c-%d", p->data.color, p->data.number);
		printf("\n");
	}
}

// ham tim kiem 1 node trong dslk bang id
NODE *find(LIST l, int id)
{
	//UNO uno = NULL;
	int check = 0;
	NODE *q = NULL;
	//Output(l);
	for (NODE *p = l.pHead; p != NULL; p = p->pNext)
	{
		//Output(l);
		//printf("%d \n",p->data.id);
		if (p->data.id == id)
		{
			//uno = p->data;
			q = getNode(p->data);
			check = 1;
			break;
		}
	}
	if (check == 0)
	{
		printf("\np null");
	}
	//p = getNode(uno);
	return q;
}

void Swap(int *number_1, int *number_2)
{
	int temp = *number_1;
	*number_1 = *number_2;
	*number_2 = temp;
}

void ShuffleArray(int *arr, int n)
{
	srand(time(NULL));

	int minPosition;
	int maxPosition = n - 1;
	int swapPosition;

	int i = 0;
	while (i < n - 1)
	{
		minPosition = i + 1;
		swapPosition = rand() % (maxPosition - minPosition + 1) + minPosition;

		Swap(&arr[i], &arr[swapPosition]);
		i++;
	}
}

// ham tra ve 1 quan bai uno
UNO timUno(LIST l, int id)
{
	UNO uno;
	for (NODE *p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.id == id)
		{
			uno = p->data;
			break;
		}
	}
	return uno;
}

// ham trao bai roi nap no vao stack
void inPutStack(STACK *s, LIST l)
{
	InitStack(s);
	int id[108] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
				   63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
				   85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108};

	ShuffleArray(id, 108);

	//for (int i = 0; i < 108; i++){
	//	printf("%d ", id[i]);
	//}

	int i, j; /*
	for ( i = 0; i < 108; i++) {
		j = (i + 1) + rand() % (108 - (i + 1) + 1); // [a, b]
		int tmp = id[i];
		id[i] = id[j];
		id[j] = tmp;
	}*/

	// for (i = 0; i < 108; i++)
	// {
	// 	j = id[i];
	// 	NODE *p = find(l, j);
	// 	//UNO uno = timUno(l, j);
	// 	push(s, p);
	// }

	for (i = 0; i < 108; i++) {
		j = id[i];
		//printf("%d\n", j);
		//NODE* p = find(l, j);
		UNO uno = timUno(l, j);
		//printf("\nid = %d", uno.id);
		NODE* p = getNode(uno);
		push(s, p);

	}
}

// ham chia bai cho nguoi choi
void inPutL1(STACK *s, LIST *l1)
{
	Init(l1);
	for (int i = 0; i < 7; i++)
	{
		UNO uno = pop(s);
		NODE *p = getNode(uno);
		addTail(l1, p);
	}
}

void deleteNode(LIST *l1, int id)
{
	NODE *truoc = l1->pHead;
	for (NODE *p = l1->pHead->pNext; p != l1->pTail; p = p->pNext)
	{
		if (p->data.id == id)
		{
			truoc->pNext = p->pNext;
			free(p);
			break;
		}
		else
		{
			truoc = p;
		}
	}

	if (l1->pHead->data.id == id)
	{
		xoaDau(l1);
	}

	if (l1->pTail->data.id == id)
	{
		XoaCuoi(l1);
	}
}

// ham tim kiem trong dslk dua tren mau va gia tri.
NODE *findL1(LIST l1, char x, int y)
{
	NODE *p;
	for (p = l1.pHead; p != NULL; p = p->pNext)
	{
		if (p->data.color == x && p->data.number == y)
		{
			//q = p;
			break;
		}
	}
	return p;
}

//ham kiem tra xem tren bai cua nguoi choi co quan bai nao co the danh k
int check(LIST l1, char x, int y)
{
	for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
	{
		// truong hop con bai truoc la con cam
		if (y == -1 && (p->data.number == y || p->data.number == -4 || p->data.number == -5))
		{
			return 1;
		}
		// con truoc la con dao chieu
		else if (y == -2 && (p->data.number == y || p->data.number == -4 || p->data.number == -5))
		{
			return 1;
		}
		// con truoc la con +2
		else if (y == -3 && (p->data.number == y || p->data.number == -5))
		{
			return 1;
		}
		// con truoc la con doi mau
		else if (y == -4 && (p->data.number == y || p->data.number == -5))
		{
			return 1;
		}
		// con truoc la con +4
		else if (y == -5 && (p->data.number == y))
		{
			return 1;
		} // neu là con thông thường
		else if (p->data.color == x || p->data.number == y || p->data.color == 'k')
		{
			return 1;
		}
	}
	return 0;
}

//ham kiem tra cho truong hop danh quan dac biet
int check2(LIST l1, char tmp, int y)
{
	NODE *p;
	for (p = l1.pHead; p != NULL; p = p->pNext)
	{
		if (y = -4 && (p->data.color == tmp || p->data.color == 'k'))
		{
			return 1;
		}
		if (y = -5 && (p->data.color == tmp || (p->data.color == 'k' && y != -4)))
		{
			return 1;
		}
	}
	return 0;
}

// ham choi thu, tu choi voi chinh minh
void playGame(STACK *s, LIST *l1, LIST l)
{
	NODE *p;
	UNO uno;
	show(*l1);
	printf("\nban muon danh con nao!");
	printf("\nnhap mau truoc, so sau, vd: r 8\n");
	char x, tmp;
	int y, n;
	scanf("%c%d%*c", &x, &y);
	p = findL1(*l1, x, y);
	printf("%c-%d", p->data.color, p->data.number);
	deleteNode(l1, p->data.id);
	// rewind(stdin);
	while (l1->pHead != NULL)
	{
		show(*l1);
		if (x == 'k')
		{
			printf("\nchon mau: ");
			scanf("%c%*c", &tmp);
			// rewind(stdin);
			if (check2(*l1, tmp, y) == 1)
			{
				printf("\nmoi danh: ");
				scanf("%c%d%*c", &x, &y);

				// rewind(stdin);
				p = findL1(*l1, x, y);

				printf("\nbai vua danh: %c-%d", x, y);
				int z = p->data.id;
				deleteNode(l1, z);
			}
		}
		else if (x != 'k' && check(*l1, x, y) == 1)
		{
			printf("\nmoi danh: ");
			scanf("%c%d%*c", &x, &y);
			// rewind(stdin);
			p = findL1(*l1, x, y);
			printf("\nbai vua danh:%c-%d", x, y); // p->data.color, p->data.number
			int z = p->data.id;
			deleteNode(l1, z);
		}
		else
		{
			printf("\nkhong co quan bai thich hop, nhan 1 de boc them bai nhoa!!!");
			scanf("%d%*c", &n);
			if (s->top == NULL)
			{ // nap lai bai vao stack
				inPutStack(s, l);
				// loai bo nhung quan bai dang co tren tay nguoi choi
				//for (NODE* p = l1->pHead; p != NULL; p = p->pNext) {
				//	pop(s);
				//}
			}
			// rewind(stdin);
			if (n == 1)
			{
				uno = pop(s);
				NODE *p = getNode(uno);
				addTail(l1, p);
			}
		}

		if (l1->pHead->pNext == NULL)
		{
			printf("\nwoa sap uno roi, moi nhan '1' de thong bao!!!");
			scanf("%d%*c", &n);
		}
	}
	printf("\nwin");
}

// ham tong ket
void tongKet(LIST l, LIST l1, STACK s)
{
	// buoc 1: doc du lieu 108 con bai vo dslk
	Init(&l);
	loadTuFile(fileIn, &l); // do bai tu file vao dslk

	//printf("\nco chay k vay");
	//Output(l);

	// buoc 2: xao tron bo bai va do vao stack
	inPutStack(&s, l);

	//printf("\nco chay k vay ha 111");

	// buoc 3: chia bai cho nguoi choi
	inPutL1(&s, &l1);

	//printf("\nco chay k vay");

	// buoc 4: choi thoi
	playGame(&s, &l1, l);

	//printf("\nco chay k vay");
}

// int main()
// {
// 	//UNO* uno = NULL;

// 	tongKet(l, l1, s);

// 	// giai phong cac the loai
// 	outPut(&s);
// 	giaiPhong(&l1);
// 	giaiPhong(&l);
// 	//getch();
// 	return 0;
// }
