#pragma warning(disable : 4996)
#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

LIST l; // danh sach de luu 108 quan bai
//LIST l1, l2, l3, l4;// danh sach luu quan bai tren tay nguoi choi
//STACK s; // luu quan bai da dao
//STACK s1;// luu quan bai da danh
void nguoi(LIST *l2, char *x, int *y, int chonMau, int *n, char *result);
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
	//XoaCuoi(l);
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

	for (i = 0; i < 108; i++)
	{
		j = id[i];
		//printf("%d\n", j);
		//NODE* p = find(l, j);
		UNO uno = timUno(l, j);
		//printf("\nid = %d", uno.id);
		NODE *p = getNode(uno);
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
	//XoaCuoi(l1);
}

void deleteNode(LIST *l1, int id)
{
	//printf("\n co vao day k");

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
	//show(*l1);
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

int CHECK(LIST l1, char x, int y, UNO *uno)
{
	for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
	{
		// truong hop con bai truoc la con cam hoac dao chieu
		if ((y == -1 || y == -2) && (p->data.color == x || p->data.number == y || p->data.color == 'k'))
		{
			*uno = p->data;
			return 1;
		}
		// con truoc la con dao chieu
		//else if (y == -2 && (p->data.number == y || p->data.color == 'k')) {
		//	return 1;
		//}
		// con truoc la con +2
		else if (y == -3 && (p->data.number == y || p->data.number == -5))
		{
			*uno = p->data;
			return 1;
		}
		// con truoc la con doi mau( phan else nay da bi thua)
		else if (y == -4 && (p->data.color == 'k'))
		{
			*uno = p->data;
			return 1;
		}
		// con truoc la con +4
		else if (y == -5 && (p->data.number == y))
		{
			*uno = p->data;
			return 1;
		} // neu là con thông thường hoac truong hop y = 69
		else if (y != -1 && y != -2 && y != -3 && y != -4 && y != -5 && p->data.color == x || p->data.number == y || p->data.color == 'k')
		{
			*uno = p->data;
			return 1;
		}
	}
	return 0;
}

//ham kiem tra xem tren bai cua nguoi choi co quan bai nao co the danh k
int check(LIST l1, char x, int y)
{
	for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
	{
		// truong hop con bai truoc la con cam hoac dao chieu
		if ((y == -1 || y == -2) && (p->data.color == x || p->data.number == y || p->data.color == 'k'))
		{
			return 1;
		}
		// con truoc la con dao chieu
		//else if (y == -2 && (p->data.number == y || p->data.color == 'k')) {
		//	return 1;
		//}
		// con truoc la con +2
		else if (y == -3 && (p->data.number == y || p->data.number == -5))
		{
			return 1;
		}
		// con truoc la con doi mau( phan else nay da bi thua)
		else if (y == -4 && (p->data.color == 'k'))
		{
			return 1;
		}
		// con truoc la con +4
		else if (y == -5 && (p->data.number == y))
		{
			return 1;
		} // neu là con thông thường hoac truong hop y = 69
		else if (y != -1 && y != -2 && y != -3 && y != -4 && y != -5 && p->data.color == x || p->data.number == y || p->data.color == 'k')
		{
			return 1;
		}
	}
	return 0;
}
/*
//ham kiem tra cho truong hop danh quan dac biet
int check2(LIST l1, char tmp, int y) {
	NODE* p;
	for (p = l1.pHead; p != NULL; p = p->pNext) {
		if (y = -4 && (p->data.color == tmp || p->data.color == 'k')) {
			return 1;
		}
		if (y = -5 && (p->data.color == tmp || (p->data.color == 'k' && y != -4))) {
			return 1;
		}
	}
	return 0;
}
*/

// kiem tra cho truong hop thang dang truoc danh con doi mau
/*int check5(LIST tmp, char x, int y) {
	for (NODE* p = tmp.pHead; p != NULL; p = p->pNext) {
		if ( y == -4 && (p->data.color == x || p->data.color == 'k')) {
			return 1;
		}
		if( y == -5 && p->data.number == -5){
			return 1;
		}
	}
	return 0;
}*/

/*
// ham choi thu, tu choi voi chinh minh
void playGame(STACK* s, STACK* s1, LIST* l1, LIST l) {
	InitStack(s1);
	NODE* p;
	UNO uno;
	show(*l1);
	printf("\nban muon danh con nao!");
	printf("\nnhap mau truoc, so sau, vd: r 8\n");
	char x, tmp;
	int y, n;
	scanf("%c%d%*c", &x, &y);
	p = findL1(*l1, x, y);
	printf("bai vua danh: %c-%d", p->data.color, p->data.number);
	push(s1, p);
	deleteNode(l1, p->data.id);
	//rewind(stdin);
	while (l1->pHead != NULL) {
		show(*l1);
		if (x == 'k') {
			printf("\nchon mau: ");
			scanf("%c%*c", &tmp);
			//rewind(stdin);
			if (check2(*l1, tmp, y) == 1) {
				printf("\nmoi danh: ");
				scanf("%c%d%*c", &x, &y);
				//rewind(stdin);
				p = findL1(*l1, x, y);
				printf("\nbai vua danh: %c-%d", x, y);
				int z = p->data.id;
				push(s1, p);
				deleteNode(l1, z);
			}
		}
		else if (x != 'k' && check(*l1, x, y) == 1) {
			printf("\nmoi danh: ");
			scanf("%c%d%*c", &x, &y);
			//rewind(stdin);
			p = findL1(*l1, x, y);
			printf("\nbai vua danh:%c-%d", x, y);  // p->data.color, p->data.number
			int z = p->data.id;
			push(s1, p);
			deleteNode(l1, z);
		}
		else {
			printf("\nkhong co quan bai thich hop, nhan 1 de boc them bai nhoa!!!");
			scanf("%d%*c", &n);
			if (s->top == NULL) {// nap lai bai vao stack
				printf("\thong bao het bai boc");
				for (NODE* p = s1->top; p != NULL; p = p->pNext) {
					push(s, p);
				}
			}
			//rewind(stdin);
			if (n == 1) {
				uno = pop(s);
				NODE* p = getNode(uno);
				addTail(l1, p);
			}
		}

		if (l1->pHead->pNext == NULL) {
			printf("\nwoa sap uno roi, moi nhan '1' de thong bao!!!");
			scanf("%d%*c", &n);

		}
	}
	printf("\nwin");
}

*/

// ham nap bai khi bi phat
void phat(int n, LIST* tmp, STACK* s) {
	for (int i = 1; i <= n; i++) {
		UNO uno = pop(s);
		NODE* p = getNode(uno);
		addTail(tmp, p);
	}
}


void my_random(char *x)
{
	char *str = "rgby";
	int y = 0 + rand() % (3 - 0 + 1);
	*x = str[y];
}

char *my_itoa(int num, char *str);

void trungGian22(LIST *xxx, STACK *s, STACK *s1, int checkk, char *x, int *y, int *t, int u, int *check0, int *cml, char *result)
{
	//int n = 100;
	int chonMau = 0;
	NODE *p;
	NODE *r;
	UNO uno;
	int n = -10;
	if (*y == -4)
	{
		if (u == 1)
		{
			chonMau = 1;
			printf("nguoi chon mau: ");
			nguoi(xxx, x, y, chonMau, &n, result);
			chonMau = 0;
			*y = 69;
		}
		else
		{
			printf("may chon mau: ");
			my_random(x);
			*y = 69;
		}
	}

	if (checkk == 1)
	{
		printf("\nnguoi danh: ");
	}
	else
	{
		printf("\nmay danh: ");
		show(*xxx);
	}
	if (CHECK(*xxx, *x, *y, &uno) == 1)
	{
		r = getNode(uno);
		//printf("\nhihi");
		//printf("\n%c-%d",r->data.color, r->data.number );
		//printf("\nhihi");

		//printf("\nhihi");
		if (checkk == 1)
		{
			nguoi(xxx, x, y, chonMau, &n, result);
		}
		else
		{
			//printf("\nhihi");
			*x = r->data.color;
			*y = r->data.number;
		}

		p = findL1(*xxx, *x, *y);
		printf("\nbai vua danh:%c-%d", p->data.color, p->data.number); // p->data.color, p->data.number
		int z = p->data.id;
		uno = p->data;
		push2(s1, uno);

		if (*y == -5)
		{
			*t += 4;
		}
		if (*y == -3)
		{
			*t += 2;
		}

		deleteNode(xxx, z);
		if (checkk == 1)
		{
			char str[4];
			strcpy(result, "");
			for (NODE *p = xxx->pHead; p != NULL; p = p->pNext)
			{
				my_itoa(p->data.id, str);
				strcat(result, str);
				strcat(result, " ");
			}
			int z = strlen(result);
			result[z - 1] = '\0';
		}
		*cml -= 1;
	}
	else
	{
		if (s->top == NULL)
		{ // nap lai bai vao stack
			printf("\thong bao het bai boc");
			InitStack(s);
			for (NODE *p = s1->top; p != NULL; p = p->pNext)
			{
				uno = p->data;
				push2(s, uno);
				//push(s, p);
			}
		}
		if (*y == -3 || *y == -5)
		{
			printf("\ndo bai cua ban k co con nao do duoc nen bi phat them %d con bai", *t);
			phat(*t, xxx, s);

			if (checkk == 1)
			{
				char str[4];
				strcpy(result, "");
				for (NODE *p = xxx->pHead; p != NULL; p = p->pNext)
				{
					my_itoa(p->data.id, str);
					strcat(result, str);
					strcat(result, " ");
				}
				int z = strlen(result);
				result[z - 1] = '\0';
			}

			*cml += *t;
			*t = 0;
			if (*y == -5)
			{
				if (checkk == 2)
				{
					chonMau = 1;
					printf("nguoi chon mau: ");
					nguoi(xxx, x, y, chonMau, &n, result);
					chonMau = 0;
					*y = 69;
				}
				else
				{
					printf("\nmay chon mau");
					my_random(x);
					*y = 69;
				}
			}
			if (*y == -3)
			{
				*y = 70;
			}
		}
		else
		{
			printf("\nkhong co quan bai thich hop, he thong da tu dong boc bai!!!");
			//scanf("%d%*c", &n);

			uno = pop(s);
			NODE *p = getNode(uno);
			addTail(xxx, p);
			*cml += 1;

			if (checkk == 1)
			{
				char str[4];
				strcpy(result, "");
				for (NODE *p = xxx->pHead; p != NULL; p = p->pNext)
				{
					my_itoa(p->data.id, str);
					strcat(result, str);
					strcat(result, " ");
				}
				int z = strlen(result);
				result[z - 1] = '\0';
			}

			if (CHECK(*xxx, *x, *y, &uno) == 1)
			{
				r = getNode(uno);
				show(*xxx);
				if (checkk == 1)
				{
					nguoi(xxx, x, y, chonMau, &n, result);
				}
				else
				{
					*x = r->data.color;
					*y = r->data.number;
				}

				p = findL1(*xxx, *x, *y);
				printf("\nbai vua danh:%c-%d", *x, *y);
				int z = p->data.id;

				uno = p->data;
				push2(s1, uno);
				if (*y == -5)
				{
					*t += 4;
				}
				if (*y == -3)
				{
					*t += 2;
				}

				deleteNode(xxx, z);
				if (checkk == 1)
				{
					char str[4];
					strcpy(result, "");
					for (NODE *p = xxx->pHead; p != NULL; p = p->pNext)
					{
						my_itoa(p->data.id, str);
						strcat(result, str);
						strcat(result, " ");
					}
					int z = strlen(result);
					result[z - 1] = '\0';
				}
				*cml -= 1;
				//show(*xxx);
			}
			else
			{
				if (*y == -2)
				{
					*y += 69;
				}
			}
		}
	}
	if (*cml != 0 && xxx->pHead->pNext == NULL)
	{
		if (checkk == 2)
		{
			printf("\nmay sap UNO, can than nha!");
		}
		else
		{
			chonMau = 2;
			nguoi(xxx, x, y, chonMau, &n, result);
			printf("\n n = %d", n);
			if (n != 2)
			{ // neu k nhan uno thi phat them 2 con bai
				printf("\ndo ban nhan sai nut nen bi phat them 2 con bai!");
				phat(2, xxx, s);

				if (checkk == 1)
				{
					char str[4];
					strcpy(result, "");
					for (NODE *p = xxx->pHead; p != NULL; p = p->pNext)
					{
						my_itoa(p->data.id, str);
						strcat(result, str);
						strcat(result, " ");
					}
					int z = strlen(result);
					result[z - 1] = '\0';
				}

				*cml += 2;
			}
		}
	}

	if (*cml == 0)
	{
		if (checkk == 1)
		{
			printf("\nnguoi thang");
		}
		else
		{
			printf("\nmay thang");
		}
		*check0 = 1;
	}
}

// ham trung gian
void trungGian(LIST *xxx, STACK *s, STACK *s1, int checkk, char *x, int *y, int *t, int u, int *check0, int *cml)
{

	NODE *p;
	UNO uno;
	int n = -10;
	if (*y == -4)
	{
		printf("\nmoi nguoi choi %d chon mau: ", u);
		scanf("%c%*c", x);
		*y = 69;
	}

	printf("\ntoi luot nguoi %d", checkk);
	show(*xxx);

	//printf("%c  %d", *x, *y);
	/*
	if ((*y == -4 || *y == -5) && check5(*xxx, *x, *y) == 1) {
			printf("\nmoi danh: ");
			scanf("%c%d%*c", x, y);
			//rewind(stdin);
			p = findL1(*xxx, *x, *y);
			printf("\nbai vua danh:%c-%d", *x, *y);  // p->data.color, p->data.number
			int z = p->data.id;
			printf("\n z = %d", z);
			uno = p->data;
			push2(s1, uno);
			if (*y == -5) {
				*t += 4;
			}
			if (*y == -3) {
				*t += 2;
			}
			
			deleteNode(xxx, z);
			//show(*xxx);
			
			
	}
	
	else*/
	if (check(*xxx, *x, *y) == 1)
	{
		//printf("\n lan 1");
		//show(xxx);
		printf("\nmoi danh: ");
		scanf("%c%d%*c", x, y);
		//rewind(stdin);
		p = findL1(*xxx, *x, *y);
		printf("\nbai vua danh:%c-%d", p->data.color, p->data.number); // p->data.color, p->data.number
		int z = p->data.id;
		//printf("\n z = %d", z);
		uno = p->data;
		push2(s1, uno);
		//printf("\n lan 2");
		//show(xxx);
		if (*y == -5)
		{
			*t += 4;
		}
		if (*y == -3)
		{
			*t += 2;
		}

		//show(xxx);
		//printf("\n lan 2");
		deleteNode(xxx, z);
		*cml -= 1;
		//show(*xxx);
	}
	else
	{
		if (s->top == NULL)
		{ // nap lai bai vao stack
			printf("\thong bao het bai boc");
			InitStack(s);
			for (NODE *p = s1->top; p != NULL; p = p->pNext)
			{
				uno = p->data;
				push2(s, uno);
				//push(s, p);
			}
		}
		if (*y == -3 || *y == -5)
		{
			printf("\ndo bai cua ban k co con nao do duoc nen bi phat them %d con bai", *t);
			phat(*t, xxx, s);
			*cml += *t;
			*t = 0;
			if (*y == -5)
			{
				printf("\nmoi nguoi choi %d chon mau: ", u);
				scanf("%c%*c", x);
				*y = 69;
			}
			if (*y == -3)
			{
				*y = 69;
			}
		}
		else
		{
			printf("\nkhong co quan bai thich hop, nhan 1 de boc them bai nhoa!!!");
			scanf("%d%*c", &n);

			//rewind(stdin);
			if (n == 1)
			{
				uno = pop(s);
				NODE *p = getNode(uno);
				addTail(xxx, p);
				*cml += 1;
			}
			show(*xxx);
			if (check(*xxx, *x, *y) == 1)
			{
				printf("\nmoi danh: ");
				scanf("%c%d%*c", x, y);
				//rewind(stdin);
				p = findL1(*xxx, *x, *y);
				printf("\nbai vua danh:%c-%d", *x, *y); // p->data.color, p->data.number
				int z = p->data.id;
				//printf("z = %d", z);
				uno = p->data;
				push2(s1, uno);
				if (*y == -5)
				{
					*t += 4;
				}
				if (*y == -3)
				{
					*t += 2;
				}

				deleteNode(xxx, z);
				*cml -= 1;
				//show(*xxx);
			}
			else
			{
				if (*y == -2)
				{
					*y += 69;
				}
			}
		}
	}
	if (*cml != 0 && xxx->pHead->pNext == NULL)
	{
		printf("\nwoa sap uno roi, moi nhan '2' de thong bao!!!");
		scanf("%d%*c", &n);
		if (n != 2)
		{ // neu k nhan uno thi phat them 2 con bai
			phat(2, xxx, s);
			*cml += 2;
		}
	}

	if (*cml == 0)
	{
		printf("\nnguoi choi %d da chien thang", checkk);
		*check0 = 1;
	}
}
//ham chia bai cho nguoi choi
void chiaBai(LIST *l1, LIST *l2, LIST *l3, LIST *l4, STACK *s, int *m)
{
	printf("\nnhap so nguoi choi: ");
	scanf("%d%*c", m);
	if (*m == 2)
	{
		inPutL1(s, l1);
		inPutL1(s, l2);
	}
	else if (*m == 3)
	{
		inPutL1(s, l1);
		inPutL1(s, l2);
		inPutL1(s, l3);
	}
	else
	{
		inPutL1(s, l1);
		inPutL1(s, l2);
		inPutL1(s, l3);
		inPutL1(s, l4);
	}
}

// ham choi cho n nguoi
void choiNhieuNguoi(LIST *l1, LIST *l2, LIST *l3, LIST *l4, STACK *s, STACK *s1)
{
	InitStack(s1);
	NODE *p;
	UNO uno;
	int u = 0;										  // luu vi tri nguoi choi truoc do
	int t = 0;										  // so quan bai cong don de them cho nguoi choi neu k đỡ được bài
	int n, m, checkk = 0, y, check0 = 0, chuyen = -1; // checkk luu thu tu nguoi choi
	// chuyen = -1: chay theo chieu kim dong ho, chuyen = 1: chay nguoc chieu
	char x, tmp; // x de luu mau, y luu so tren quan bai,
	/*
	printf("\nnhap so nguoi choi: ");
	scanf("%d%*c", &m);
	// phat bai
	if (m == 2) {
		inPutL1(s, l1);
		inPutL1(s, l2);
	}
	else if (m == 3) {
		inPutL1(s, l1);
		inPutL1(s, l2);
		inPutL1(s, l3);
	}
	else {
		inPutL1(s, l1);
		inPutL1(s, l2);
		inPutL1(s, l3);
		inPutL1(s, l4);
	}
	*/
	chiaBai(l1, l2, l3, l4, s, &m);
	int cml1, cml2, cml3, cml4;
	cml1 = cml2 = cml3 = cml4 = 7;
	while (check0 == 0)
	{
		if (checkk == 0)
		{
			checkk = 1;
			u = checkk;
			printf("\nnguoi choi 1, moi danh: ");
			show(*l1);
			scanf("%c%d%*c", &x, &y);
			printf("\nbai vua danh: %c-%d", x, y);
			p = findL1(*l1, x, y);
			uno = p->data;
			push2(s1, uno);
			if (y == -2)
			{
				chuyen *= -1;
			}
			if (chuyen == 1)
			{ // nguoc kim dong ho
				checkk = m;
			}
			else
			{
				if (y == -1 && m == 2)
				{
					checkk = 1;
				}
				else if (y == -1 && m > 2)
				{
					checkk = 3;
				}
				else
				{
					checkk = 2;
				}
			}
			if (y == -5)
			{
				t += 4;
			}
			if (y == -3)
			{
				t += 2;
			}

			deleteNode(l1, p->data.id);
			cml1 -= 1;
			//show(*l1);
		}
		else if (checkk == 1)
		{
			trungGian(l1, s, s1, checkk, &x, &y, &t, u, &check0, &cml1);
			if (check0 == 1)
			{
				break;
			}
			//p = findL1(*l1, x, y);
			//deleteNode(l1, p->data.id);
			//show(*l1);
			u = checkk;
			if (y == -2)
			{
				chuyen *= -1;
			}
			if (chuyen == 1)
			{
				if (y == -1 && m == 2)
				{
					checkk = 1;
				}
				else if (y == -1 && m > 2)
				{
					checkk = m - 1;
				}
				else
				{
					checkk = m;
				}
			}
			else
			{
				if (y == -1 && m == 2)
				{
					checkk = 1;
				}
				else if (y == -1 && m > 2)
				{
					checkk = 3;
				}
				else
				{
					checkk = 2;
				}
			}
			if (y == 67)
			{
				y -= 69;
			}
		}

		if (checkk == 2)
		{
			//show(*l2);
			trungGian(l2, s, s1, checkk, &x, &y, &t, u, &check0, &cml2);
			if (check0 == 1)
			{
				break;
			}
			//show(*l2);
			//p = findL1(*l2, x, y);
			//deleteNode(l2, p->data.id);
			//show(*l2);
			u = checkk;
			if (y == -2)
			{
				chuyen *= -1;
			}
			if (chuyen == 1)
			{
				if (y == -1)
				{
					checkk = m;
				}
				else
				{
					checkk = 1;
				}
			}
			else
			{
				if (y == -1 && m == 4)
				{
					checkk = 4;
				}
				else if ((y == -1 && m == 3))
				{
					checkk = 1;
				}
				else if (y == -1 && m == 2)
				{
					checkk = 2;
				}
				else if (m == 2)
				{
					checkk = 1;
				}
				else
				{
					checkk = 3;
				}
			}
			if (y == 67)
			{
				y -= 69;
			}
		}
		if (checkk == 3 && m > 2)
		{
			//printf("\n co cap nhat k: %c-%d", x, y);
			trungGian(l3, s, s1, checkk, &x, &y, &t, u, &check0, &cml3);
			if (check0 == 1)
			{
				break;
			}
			//p = findL1(*l3, x, y);
			//deleteNode(l3, p->data.id);
			//show(*l3);
			u = checkk;
			if (y == -2)
			{
				chuyen *= -1;
			}
			if (chuyen == 1)
			{
				if (y == -1)
				{
					checkk = 1;
				}
				else
				{
					checkk = 2;
				}
			}
			else
			{
				if (y == -1 && m == 4)
				{
					checkk = 1;
				}
				else if (y == -1 && m == 3)
				{
					checkk = 2;
				}
				else if (m == 3)
				{
					checkk = 1;
				}
				else
				{
					checkk = 4;
				}
			}
			if (y == 67)
			{
				y -= 69;
			}
		}
		if (checkk == 4 && m > 3)
		{
			trungGian(l4, s, s1, checkk, &x, &y, &t, u, &check0, &cml4);
			if (check0 == 1)
			{
				break;
			}
			//p = findL1(*l4, x, y);
			//deleteNode(l4, p->data.id);
			//show(*l4);
			u = checkk;
			if (y == -2)
			{
				chuyen *= -1;
			}
			if (chuyen == 1)
			{
				if (y == -1 && m == 4)
				{
					checkk = 2;
				}
				else
				{
					checkk = 3;
				}
			}
			else
			{
				if (y == -1 && m == 4)
				{
					checkk = 2;
				}
				else
				{
					checkk = 1;
				}
			}
			if (y == 67)
			{
				y -= 69;
			}
		}
	}

	//================giai phong bo nho=======================

	if (checkk == 1 && m == 2)
	{
		giaiPhong(l2);
	}
	if (checkk == 1 && m == 3)
	{
		giaiPhong(l2);
		giaiPhong(l3);
	}
	if (checkk == 1 && m == 4)
	{
		giaiPhong(l2);
		giaiPhong(l3);
		giaiPhong(l4);
	}

	if (checkk == 2 && m == 2)
	{
		giaiPhong(l1);
	}

	if (checkk == 2 && m == 3)
	{
		giaiPhong(l1);
		giaiPhong(l3);
	}
	if (checkk == 2 && m == 4)
	{
		giaiPhong(l1);
		giaiPhong(l3);
		giaiPhong(l4);
	}

	if (checkk == 3 && m == 3)
	{
		giaiPhong(l1);
		giaiPhong(l3);
	}
	if (checkk == 3 && m == 4)
	{
		giaiPhong(l2);
		giaiPhong(l1);
		giaiPhong(l4);
	}

	if (checkk == 4 && m == 4)
	{
		giaiPhong(l2);
		giaiPhong(l1);
		giaiPhong(l3);
	}
	//=========================================================
}

void ATOI(LIST l, LIST *xxx, char *str)
{
	Init(xxx);
	int m;
	char *str2;
	int n = strlen(str);
	str2 = malloc(n + 1);
	strcpy(str2, str);
	char tmp[10], tmp3[2] = "";
	strcpy(tmp, "");
	for (int i = 0; i <= strlen(str2); i++)
	{
		char c = str2[i];
		char tmp2[2] = {c, '\0'};
		strcpy(tmp3, tmp2);
		strcat(tmp, tmp3);
		if (c == ' ' || c == '\0')
		{
			m = atoi(tmp);
			strcpy(tmp, "");
			NODE *p = find(l, m);
			p = getNode(p->data);
			addTail(xxx, p);
		}
	}
}



char *my_itoa(int num, char *str)
{
	if (str == NULL)
	{
		return NULL;
	}
	sprintf(str, "%d", num);
	return str;
}

//==========19/12=======
//ham cua nguoi choi
void nguoi(LIST *xxx, char *x, int *y, int chonMau, int *n, char *result)
{
	//LIST yyy;
	//ATOI(l, &yyy, result);
	if (chonMau == 1)
	{
		scanf("%c%*c", x);
	}
	else if (chonMau == 2)
	{
		printf("\nwoa sap uno roi, moi nhan '2' de thong bao!!!");
		scanf("%d%*c", n);
	}
	else
	{
		if (*y == 69)
		{
			printf("\nda chon mau: %c", *x);
		}
		else
		{
			if (*y >= -5 && *y <= 9)
			{
				printf("\nbai vua danh: %c-%d", *x, *y);
			}
		}
		show(*xxx);
		printf("\ndanh: ");
		scanf("%c%d%*c", x, y);
	}
}
// hàm của máy
void may(STACK *s, STACK *s1, LIST* l1, LIST* l2){
	char str[4], result[256] = "";
	InitStack(s1);
	NODE* p;
	UNO uno;
	int u = 0; // luu vi tri nguoi choi truoc do
	int t = 0; // so quan bai cong don de them cho nguoi choi neu k đỡ được bài
	int n, m = 2, checkk = 0, y = 1000, check0 = 0, chuyen = -1; // checkk luu thu tu nguoi choi
	// chuyen = -1: chay theo chieu kim dong ho, chuyen = 1: chay nguoc chieu
	char x, tmp; // x de luu mau, y luu so tren quan bai,

	inPutL1(s, l1);// l2 la bai cua may
	printf("\n==========================");
	printf("\nbai cua nguoi choi");
	show(*l1);
	printf("\n==========================");
    for(NODE* p = l1->pHead; p != NULL; p = p->pNext){
		my_itoa(p->data.id, str);
		strcat(result, str);
		strcat(result, " ");
	}
	int z = strlen(result);
	result[z - 1] = '\0';

	inPutL1(s, l2);// l1 la bai cua nguoi choi
	int cml1 ,cml2;
	cml1 = cml2 = 7;
	while(check0 == 0){
		if (checkk == 0) {
		printf("\nnguoi danh: ");// gia su nguoi la 1, may la 2
	    nguoi(l1, &x, &y, 0, &n, result);
		printf("\nbai vua danh: %c-%d", x, y);
		p = findL1(*l1, x, y);
		uno = p->data;
		push2(s1, uno);
		    if (y == -2) {
			    chuyen *= -1;
			}
			if(chuyen == 1){ // nguoc kim dong ho
                checkk = m;
			}else{
                if (y == -1) {
					checkk = 1;
				}else{
					checkk = 2;
				}

			}
			if (y == -5) {
				t += 4;
			}
			if (y == -3) {
				t += 2;
			}

			//printf("\nden day chua, tai sao k xoa");
			//printf("\nid = %d",p->data.id );
			deleteNode(l1, p->data.id);

			strcpy(result, "");
			for(NODE* p = l1->pHead; p != NULL; p = p->pNext){
		    my_itoa(p->data.id, str);
		    strcat(result, str);
		    strcat(result, " ");
	        }
	        int z = strlen(result);
	        result[z - 1] = '\0';

			cml1 -= 1;
		}else if (checkk == 1){
			trungGian22(l1, s, s1, checkk, &x, &y, &t, u, &check0, &cml1,result );
			if(check0 == 1){
				break;
			}

			u = checkk;
			if (y == -2) {
				chuyen *= -1;
			}
			if(chuyen == 1){
				if (y == -1) {
				checkk = 1;
			    }
			    else {
				checkk = m;
			    }
			}else{
                if (y == -1) {
				checkk = 1;
			    }
			    else {
				checkk = 2;
			    }
			}
			if( y == 67){
				y -= 69;
			}
		}

	if (checkk == 2) {
			trungGian22(l2, s, s1, checkk, &x, &y, &t, u, &check0, &cml2, result);
			if(check0 == 1){
				break;
			}

			u = checkk;
			if (y == -2) {
				chuyen *= -1;
			}
			if(chuyen == 1){
				if (y == -1) {
					checkk = m;
				}
				else {
					checkk = 1;
				}
			}
			else {
				if (y == -1 && m == 2) {
					checkk = 2;
				}
				else {
					checkk = 1;
				}

			}
			if( y == 67){
				y -= 69;
			}

	}
  }

	giaiPhong(l1);
	giaiPhong(l2);

}

//======================

// ham tong ket
void tongKet(LIST *l, LIST *l1, LIST *l2, LIST *l3, LIST *l4, STACK *s, STACK *s1)
{
	// buoc 1: doc du lieu 108 con bai vo dslk
	//Init(l);
	//loadTuFile(fileIn, l); // do bai tu file vao dslk
	//printf("\nco chay k vay");
	//Output(l);

	// buoc 2: xao tron bo bai va do vao stack
	//inPutStack(s, *l);
	/*int i = 0;
	for(NODE* p = s->top; p != NULL; p = p->pNext){
		printf("\n%d", p->data.id);
        i++;
	}
	printf("\n toi day chua : %d", i);
    */

	//printf("\nco chay k vay ha 111");

	// buoc 3: chia bai cho nguoi choi

	//inPutL1(&s, &l1);

	//printf("\nco chay k vay");

	// buoc 4: choi thoi
	//playGame(&s,&s1, &l1, l);

	//choiNhieuNguoi(l1, l2, l3, l4, s, s1);

	//may(s, s1, l1, l2);

	//printf("\nco chay k vay");
}

// int main() {
// 	//LIST l; // danh sach de luu 108 quan bai
//     LIST l1, l2, l3, l4;// danh sach luu quan bai tren tay nguoi choi
//     STACK s; // luu quan bai da dao
//     STACK s1;// luu quan bai da danh
// 	//UNO* uno = NULL;

// 	tongKet(&l, &l1, &l2, &l3, &l4, &s, &s1);

// 	// giai phong cac the loai
// 	/*if(m == 3){
// 	giaiPhong(&l3);
// 	}
// 	if(m == 4){
// 	giaiPhong(&l4);
// 	}*/

// 	outPut(&s);
// 	outPut(&s1);

// 	giaiPhong(&l);

// 	printf("\nWIN\n");
// 	//getch();
// 	return 0;
// }

// dong 609 - 611
