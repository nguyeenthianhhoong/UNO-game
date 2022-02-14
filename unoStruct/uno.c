
#include "uno.h"
//doc file;
void WAIT (int Seconds){
  clock_t Timer;
  Timer = clock() + Seconds * CLOCKS_PER_SEC ;
  Seconds++;
  while (clock() < Timer) {}
}
void docFile(FILE* fileIn, LIST* l) {
	UNO uno;

	fscanf(fileIn, "%d", &uno.id);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%c", &uno.color);
	fseek(fileIn, 1, SEEK_CUR);
	fscanf(fileIn, "%d", &uno.number);
	NODE* p;
	p = getNode(uno);
	addTail(l, p);
}

// load danh sach nguoi dung tu file len danh sach lien ket
void loadTuFile(FILE* fileIn, LIST* l) {
	fileIn = fopen("../src/card.txt", "rt");
	if (!fileIn) {
		printf("\nkhong tim thay file card.txt");
		return;
	}
	while (!feof(fileIn)) {
		docFile(fileIn, l);
	}
	//XoaCuoi(l);
	fclose(fileIn);
}

void Swap(int* number_1, int* number_2)
{
	int temp = *number_1;
	*number_1 = *number_2;
	*number_2 = temp;
}

void ShuffleArray(int* arr, int n)
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

// ham trao bai roi nap no vao stack
void inPutStack(STACK* s, LIST l) {
	InitStack(s);
	int id[108] = { 1, 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41
	,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,
	63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,
	85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105
	,106,107,108 };

	ShuffleArray(id, 108);

	int i, j;
	for (i = 0; i < 108; i++) {
		j = id[i];
		UNO uno = timUno(l, j);
		NODE* p = getNode(uno);
		push(s, p);
	}
}

//kiểm tra quân bài phù hợp trong list bài của mik | đánh được là 1 | 0 ko được
int CHECK(LIST xxx, int id, UNO* uno) {
	// NODE* p = (NODE*)malloc(sizeof(NODE));
	NODE* p = find(l, id);
	char x;
	int y;
	x = p->data.color;
	y = p->data.number;
	for (p = xxx.pHead; p != NULL; p = p->pNext) {
		// truong hop con bai truoc la con cam hoac dao chieu
		if ((y == -1 || y == -2) && (p->data.color == x || p->data.number == y || p->data.color == 'k')) {
			*uno = p->data;
			return 1;
		}
		// con truoc la con +2
		else if (y == -3 && (p->data.number == y || p->data.number == -5)) {
			*uno = p->data;
			return 1;
		}
		// con truoc la con doi mau( phan else nay da bi thua)
		else if (y == -4 && (p->data.color == 'k')) {
			*uno = p->data;
			return 1;
		}
		// con truoc la con +4
		else if (y == -5 && (p->data.number == y)) {
			*uno = p->data;
			return 1;
		}// neu là con thông thường hoac truong hop y = 69
		else if (y >= 0 && (p->data.color == x || p->data.number == y || p->data.color == 'k')) {
			*uno = p->data;
			return 1;
		}
	}
	return 0;
}

// ham nap bai khi bi phat
int countLaBai=0;
void phat(int n, LIST* tmp, STACK* s) {
	for (int i = 1; i <= n; i++) {
		UNO uno;
		if(!isEmpty(s)){
			uno = pop(s);
		}else{
    		inPutStack(s, l);
			uno = pop(s);
		}
		countLaBai++;
		NODE* p = getNode(uno);
		addTail(tmp, p);
	}
}

int getCardFromStack(int n, STACK* s) {
	UNO uno;
	for (int i = 1; i <= n; i++) {
		if(!isEmpty(s)){
			uno = pop(s);
		}else{
    		inPutStack(s, l);
			uno = pop(s);
		}
		countLaBai++;
	}
	return uno.id;
}

void my_random(char* x) {
	char* str = "rgby";
	int y = 0 + rand() % (3 - 0 + 1);
	*x = str[y];
}

char* my_itoa(int num, char* str)
{
	if (str == NULL)
	{
		return NULL;
	}
	sprintf(str, "%d", num);
	return str;
}

void ITOA(LIST xxx, char* result) {
	char str[4];
	strcpy(result, "");
	for (NODE* p = xxx.pHead; p != NULL; p = p->pNext) {
		my_itoa(p->data.id, str);
		strcat(result, str);
		strcat(result, " ");
	}
	int z = strlen(result);
	result[z-1] = '\0'; // z - 1
}

//ham chia bai cho nguoi choi
void chiaBai(LIST* l1, LIST* l2, LIST* l3, LIST* l4, STACK* s, int m) {
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
}

void ATOI(LIST l, LIST* xxx, char* str) {
	Init(xxx);
	int m;
	char* str2;
	int n = strlen(str);
	str2 = malloc(n + 1);// n + 1
	strcpy(str2, str);
	char tmp[10], tmp3[2] = "";
	strcpy(tmp, "");
	for (int i = 0; i <= strlen(str2); i++) {
		char c = str2[i];
		char tmp2[2] = { c , '\0' };
		strcpy(tmp3, tmp2);
		strcat(tmp, tmp3);
		if (c == ' ' || c == '\0') {
			m = atoi(tmp);
			strcpy(tmp, "");
			NODE* p = find(l, m);
			p = getNode(p->data);
			addTail(xxx, p);
		}
	}
}

// ham kiem tra con bai co trong bo bai cua nguoi choi hay k
int quanBaiHopLe(LIST xxx, int id) {
	for (NODE* p = xxx.pHead; p != NULL; p = p->pNext) {
		if (p->data.id == id) {
			return 1;
		}
	}
	return 0;
}
// ham cong don quan bai de phat
void soQuanBiPhat(int number, int* t) {
	if (number == -5) {
		*t += 4;
	}
	if (number == -3) {
		*t += 2;
	}
}

void luotDanhDauchoMay(LIST* xxx, int* id, int* cml, char* mau, int* t) {
	// UNO uno;

	NODE* p = xxx->pHead;
	// cap nhat so quan bai bi phat
	soQuanBiPhat(p->data.number, t);
	if (p->data.number == -4) {
		my_random(mau);
	}
	*id = p->data.id;
	deleteNode(xxx, *id);

	*cml -= 1;
}

int kt(UNO p, UNO r) {
	if (p.number == -5) {
		if (r.number == -5) {
			return 1;
		}
	}
	else if (p.number == -4) {
		if (r.color == 'k') {
			return 1;
		}
	}
	else if (p.number == -3) {
		if (r.number == -5 || r.number == -3) {
			return 1;
		}
	}
	else {
		if (r.color == p.color || r.number == p.number || r.color == 'k') {
			return 1;
		}
	}
	return 0;
}

int doiMau2(LIST xxx, char mau, NODE* r);

int doiMau(LIST xxx, char mau, NODE* r, int phat) {
	for (NODE* p = xxx.pHead; p != NULL; p = p->pNext) {
		if ((p->data.color == mau || p->data.color == 'k' || p->data.number == r->data.number) && mau != 'z' && phat == 0) {
			r = p;
			return 1;
		}
	}
	return 0;
}

void danhBaiChoMay(LIST* xxx, int* id, int* cml, char* mau, int* t) {
	NODE* p = NULL;
	UNO uno = timUno(l, *id);
	if (*mau != 'z') {
		for (p = xxx->pHead; p != NULL; p = p->pNext) {
			if (p->data.color == *mau || p->data.color == 'k' || p->data.number == uno.number) {
				*mau = 'z';
				break;
			}
		}
	}
	else {
		CHECK(*xxx, *id, &uno);
		p = findL1(*xxx, uno.color, uno.number);
	}

	uno = p->data;
	// cap nhat so quan bai bi phat
	soQuanBiPhat(p->data.number, t);
	
	if (p->data.number == -4 || p->data.number ==-5) {
		my_random(mau);
	}
	*id = p->data.id;
	
	*cml -= 1;
	deleteNode(xxx, *id);
}

void khoiPhuc0(LIST* xxx, char* result) {
	ATOI(l, xxx, result);
}

//=======================================================================================
//ham khoi phuc la bai
void khoiPhuc(LIST* yyy, LIST* yyy2, LIST* yyy3, LIST* yyy4, char* result1, char* result2, char* result3, char* result4) {
	ATOI(l, yyy, result1);
	ATOI(l, yyy2, result2);
	ATOI(l, yyy3, result3);
	ATOI(l, yyy4, result4);
}
