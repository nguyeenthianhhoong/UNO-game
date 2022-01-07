
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
	printf("CHECK\n");
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
	//strcpy(result, "");
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
		// printf("huhu");
		inPutL1(s, l1);
		// printf("huhu");
		inPutL1(s, l2);
		// printf("huhu");
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
// ham cho luot danh dau tien

//xử lý ko phụ thuộc
void luotDanhDau(LIST* xxx, int* id, int* cml, char* mau, int* t) {
	// UNO uno;
	NODE* p;//= find(*xxx, *id);
	// printf("\nDANH: ");
	// do {
	// 	scanf("%d%*c", id);
	// 	if (quanBaiHopLe(*xxx, *id) != 1) {
	// 		printf("\nquan bai khong hop le, moi danh lai.");
	// 	}
	// } while (quanBaiHopLe(*xxx, *id) != 1);
	p = find(*xxx, *id);
	// uno = p->data;
	// push2(s1, uno);
	soQuanBiPhat(p->data.number, t);
	if (p->data.number == -4) {
	// 	printf("\nCHON MAU: ");
	// 	scanf("%c%*c", mau);
	}
	deleteNode(xxx, *id);
	// printf("\nsau khi xoa id = %d", *id);
	// show(*xxx);
	// cap nhat lai chuoi result sau khi danh bai
	//ITOA(*xxx, result);
	*cml -= 1;
}


void luotDanhDauchoMay(LIST* xxx, int* id, int* cml, char* mau, int* t) {
	// UNO uno;

	NODE* p = xxx->pHead;
	// uno = p->data;
	// push2(s1, uno);
	// cap nhat so quan bai bi phat
	soQuanBiPhat(p->data.number, t);
	if (p->data.number == -4) {
		my_random(mau);
	}
	*id = p->data.id;
	deleteNode(xxx, *id);

	*cml -= 1;
}

//ham kiem tra quan bai hop le sau khi danh
int kt(NODE* p, NODE* r) {
	if (p->data.number == -5) {
		if (r->data.number == -5) {
			return 1;
		}
	}
	else if (p->data.number == -4) {
		if (r->data.color == 'k') {
			return 1;
		}
	}
	else if (p->data.number == -3) {
		if (r->data.number == -5 || r->data.number == -3) {
			return 1;
		}
	}
	else {
		if (r->data.color == p->data.color || r->data.number == p->data.number || r->data.color == 'k') {
			return 1;
		}
	}
	return 0;
}

// int doiMau(LIST xxx, char mau, NODE* r, int phat);
int doiMau2(LIST xxx, char mau, NODE* r);
// ham danh bai cho nguoi choi trong truong hop co quan bai hop le
void danhBai(LIST* xxx, int* id, int* cml, char* mau, int* t) {
	NODE* p;
	NODE* r;
	// UNO uno;
	//int ID;
	//ID = *id;
	p = find(l, *id);
	//phía trước có con chọn màu

	//ktra màu
	if (*mau != 'z') {
		do {
			printf("\nDANH: ");
			scanf("%d%*c", id);
			r = find(l, *id);
			//quan bai hop le -> so có ở trong list ko ???
			//doimau2 -> check thoa man
			if (quanBaiHopLe(*xxx, *id) != 1 || doiMau2(*xxx, *mau, r) != 1) {
				printf("quan bai khong hop le, moi danh lai.");
			}
		} while (quanBaiHopLe(*xxx, *id) != 1 || doiMau2(*xxx, *mau, r) != 1);
		*mau = 'z';
	}
	else {
		do {
			printf("\nDANH: ");
			scanf("%d%*c", id);
			r = find(l, *id);
			//kt kiểm tra cả màu hoặc số
			if (quanBaiHopLe(*xxx, *id) != 1 || kt(p, r) != 1) {
				printf("quan bai khong hop le, moi danh lai.");
			}
			//r = find(l, *id);
		} while (quanBaiHopLe(*xxx, *id) != 1 || kt(p, r) != 1);
	}
	//tìm uno để push vào s1
	p = find(l, *id);
	// uno = p->data;
	// push2(&s1, uno);
	// cap nhat so quan bai bi phat
	soQuanBiPhat(p->data.number, t);
	if (p->data.number == -4 || p->data.number == -5) {
		printf("\nCHON MAU: ");
		scanf("%c%*c", mau);
	}
	deleteNode(xxx, *id);
	printf("\nsau khi xoa id = %d", *id);
	// show(*xxx);
	*cml -= 1;
	// cap nhat lai chuoi result sau khi danh bai
	//ITOA(*xxx, result);
}

// ham kiem tra quan bai sau khi danh con doi mau
int doiMau2(LIST xxx, char mau, NODE* r) {
	for (NODE* p = xxx.pHead; p != NULL; p = p->pNext) {
		if ((p->data.color == mau || r->data.color == 'k' || r->data.number == -3) && mau != 'z') {
			r = p;
			//printf("\nmay vao day k");
			return 1;
		}
	}
	return 0;
}

int doiMau(LIST xxx, char mau, NODE* r, int phat) {
	for (NODE* p = xxx.pHead; p != NULL; p = p->pNext) {
		if ((p->data.color == mau || p->data.color == 'k' || p->data.number == -3) && mau != 'z' && phat == 0) {
			r = p;
			return 1;
		}
	}
	// printf("doimau\n");
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
		printf("findL1\n");
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
	printf("danhchomay\n");
}

//ham tim thu tu nguoi choi tiep theo
void XXX(int* idUser, int* chuyen, int id, int ID) {
	NODE* p = find(l, id);
	if (p->data.number == -2 && id != ID) {
		*chuyen *= -1;
	}

	if (*chuyen == 1) {
		if (p->data.number == -1 && id != ID) {
			if (*idUser == 1) {
				*idUser = 3;
			}
			else if (*idUser == 2) {
				*idUser = 4;
			}
			else if (*idUser == 3) {
				*idUser = 1;
			}
			else if (*idUser == 4) {
				*idUser = 2;
			}
		}
		else {
			if (*idUser == 1) {
				*idUser = 4;
			}
			else if (*idUser == 2) {
				*idUser = 1;
			}
			else if (*idUser == 3) {
				*idUser = 2;
			}
			else if (*idUser == 4) {
				*idUser = 3;
			}
		}
	}
	else {
		if (p->data.number == -1 && id != ID) {
			if (*idUser == 1) {
				*idUser = 3;
			}
			else if (*idUser == 2) {
				*idUser = 4;
			}
			else if (*idUser == 3) {
				*idUser = 1;
			}
			else if (*idUser == 4) {
				*idUser = 2;
			}
		}
		else {
			if (*idUser == 1) {
				*idUser = 2;
			}
			else if (*idUser == 2) {
				*idUser = 3;
			}
			else if (*idUser == 3) {
				*idUser = 4;
			}
			else if (*idUser == 4) {
				*idUser = 1;
			}
		}
	}
}

void khoiPhuc0(LIST* xxx, char* result) {
	ATOI(l, xxx, result);
}

void nguoiDanh(LIST* xxx, int* idUser, int* id, int* t, int* cml, char* mau, int* chonMau) {
	NODE* p = NULL;
	UNO uno;
	int ID = *id;

	show(*xxx);
	// if (*idUser != 0) {
		p = find(l, *id);
		printf("\nBAI VUA DANH: %d. %c-%d", p->data.id, p->data.color, p->data.number);
		if (*mau != 'z') {
			printf("\nmau hien tai: %c", *mau);
		}
	// }

//**************************************************************************

	if (*idUser == 0 || *chonMau == 1) {
		if (*chonMau == 1) {
			*chonMau = 0;
		}
		luotDanhDau(xxx, id, cml, mau, t);
	}
	else {
	//*********************** kiểm tra và đánh bài
	// kiểm tra đỡ bài
		if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p, *t) == 1) {
			if (*mau != 'z') {
				printf("\nmau hien tai: %c", *mau);
			}
			danhBai(xxx, id, cml, mau, t);
		}
		else {
			//nếu bị phạt -> phạt
	//************** bị phat
			if ((p->data.number == -3 || p->data.number == -5) && *t != 0) {
				printf("\n\nbi phat %d con bai", *t);
				phat(*t, xxx, &s);
				*cml += *t;
				*t = 0;
				// cap nhat lai chuoi result sau khi bi phat bai
				//ITOA(yyy, result);
				if (p->data.number == -5) {
					*chonMau = 2; // tin hieu cho biet may dc chon mau cho luot choi ke
				}
				if (p->data.number == -3) {
					*mau = p->data.color;
				}
			}
			//nếu ko có bài -> bốc
//******************************** ko co bai
		// 	else {
		// 		printf("\nnhan '1' de boc bai.");
		// 		scanf("%d", idUser);
		// 		phat(1, xxx, &s);
		// 		*cml += 1;
		// 		// cap nhat lai chuoi result sau khi boc bai
		// 		//ITOA(yyy, result);
		// 		show(*xxx);
		// //***********cần xử lý thêm next 
		// 		if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p) == 1) {
		// 			danhBai(xxx, id, cml, mau, t);
		// 			//*mau = 'z';
		// 		}
		// 	}
		}
	}

//**********************************	// kiem tra xem luot danh tiep theo thuoc ve ai
	p = find(l, *id);
	if (p->data.number == -1 && *id != ID) {
		*idUser = 1;
	}
	else {
		*idUser = 2;
	}

//*******************************	//xu ly uno
	if (*cml == 1) {
		printf("\nsap UNO, nhan 1 de xac nhan: ");
		scanf("%d", &ID);
		if (ID != 1) {
			printf("\nnhan sai hoac k nhan nen bi phat them 2 con.");
			phat(2, &yyy, &s);
			*cml += 2;
		}
	}
}

// void mayDanh(LIST* xxx, STACK* s1, int* idUser, int* id, int* t, int* cml, char* mau, int* chonMau) {
// 	NODE* p = find(l, *id);
// 	UNO uno;
// 	int ID = *id;
// 	printf("\n\n=== MAY DANH ===");
// 	show(*xxx);
// 	if (*chonMau == 2) {
// 		if (*chonMau == 2) {
// 			*chonMau = 0;
// 		}
// 		// WAIT(3);
// 		luotDanhDauchoMay(xxx, s1, id, cml, mau, t);
// 	}
// 	else {
// 		//printf("\nid = %d", *id);
// 		//printf("\nmau : %c", *mau);
// 		if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p) == 1) {
// 			printf("\nvao day hu");
// 		// WAIT(3);
// 			danhBaiChoMay(xxx, id, cml, mau, t);
// 		}
// 		else {
// 			if ((p->data.number == -3 || p->data.number == -5) && *t != 0) {
// 				printf("bi phat %d con bai", *t);
// 				phat(*t, xxx, &s);
// 				*cml += *t;
// 				*t = 0;

// 				if (p->data.number == -5) {
// 					*chonMau = 1;
// 				}
// 				if (p->data.number == -3) {
// 					*mau = p->data.color;
// 				}
// 			}
// 			else {
// 				printf("\nhe thong da tu dong boc bai.");
// 				phat(1, xxx, &s);
// 				*cml += 1;

// 				show(*xxx);
// 				if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p) == 1) {
// 		// WAIT(3);

// 					danhBaiChoMay(xxx, id, cml, mau, t);
// 					//*mau = 'z';
// 				}
				
// 			}
// 		}
// 	}
// 	// kiem tra xem luot danh tiep theo thuoc ve ai
// 	p = find(l, *id);
// 	if (p->data.number == -1 && *id != ID) {
// 		*idUser = 2;
// 		mayDanh(xxx, s1, idUser, id, t, cml, mau, chonMau);
// 	}
// 	else {
// 		*idUser = 1;
// 	}

// }

// void choiVoiMay(LIST* yyy, LIST* l1, LIST* l2, STACK* s1) {
// 	inPutL1(&s, l1);
// 	inPutL1(&s, l2);
// 	//chiaBai(&l1, &l2, &l3, &l4, &s, 2); 
// 	char result[256] = "";
// 	ITOA(*l1, result);
// 	printf("\nresult = %s", result);
// 	InitStack(s1);
// 	int cml1, cml2, t = 0, chonMau = 0;// t luu tong so quan bai bi phat
// 	char mau = 'z';// luu mau khi 1 trong hai danh con doi mau va chon mau
// 	cml1 = cml2 = 7;
// 	int idUser = 0, id = 0; // luu giu id nguoi danh, idUser = 1 la nguoi, idUser = 2 la may
// 	// id la id cua quan bai
// 	khoiPhuc0(yyy, result);
// 	show(*yyy);
// 	printf("\n=== NGUOI DANH ===");
// 	nguoiDanh(yyy, s1, &idUser, &id, &t, &cml1, &mau, &chonMau);

// 	while (cml1 != 0 && cml2 != 0) {
// 		if (idUser == 1) {
// 			printf("\n=== NGUOI DANH ===");
// 			nguoiDanh(yyy, s1, &idUser, &id, &t, &cml1, &mau, &chonMau);
// 			printf("\nnguoi con lai %d con bai", cml1);
// 		}
// 		else {
// 			mayDanh(l2, s1, &idUser, &id, &t, &cml2, &mau, &chonMau);
// 			printf("\nmay con lai %d con bai", cml2);
// 		}
// 	}
// 	if (cml1 == 0) {
// 		printf("\nnguoi thang");

// 	}
// 	else {
// 		printf("\nmay thang");
// 	}

// 	giaiPhong(l1);
// 	giaiPhong(l2);
// 	giaiPhong(yyy);

// }

//=======================================================================================
//ham khoi phuc la bai
void khoiPhuc(LIST* yyy, LIST* yyy2, LIST* yyy3, LIST* yyy4, char* result1, char* result2, char* result3, char* result4) {
	ATOI(l, yyy, result1);
	ATOI(l, yyy2, result2);
	ATOI(l, yyy3, result3);
	ATOI(l, yyy4, result4);
}
//ham choi nay danh cho choi 4 nguoi
void Nguoi(LIST *xxx, int idUser, int* id, int* t, int* cml, char* mau, int* chonMau) {
	NODE* p = NULL;
	UNO uno;
	int sapUno;
	int ID = *id;
	show(*xxx);
	if (idUser != 0) {
		p = find(l, *id);
		printf("\nBAI VUA DANH: %d. %c-%d", p->data.id, p->data.color, p->data.number);
		if (*mau != 'z') {
			printf("\nmau hien tai: %c", *mau);
		}
	}
	if (idUser == 0 /* || *chonMau == 1*/) {
		//if (*chonMau == 1) {
		//	*chonMau = 0;
		//}
		luotDanhDau(xxx, id, cml, mau, t);
	}
	else {
		if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p, *t) == 1) {
			//if (*mau != 'z') {
			//	printf("\nmau hien tai: %c", *mau);
			//}
			danhBai(xxx, id, cml, mau, t);
		}
		else {
			if ((p->data.number == -3 || p->data.number == -5) && *t != 0) {
				printf("\n\nbi phat %d con bai", *t);
				phat(*t, xxx, &s);
				*cml += *t;
				*t = 0;
				// cap nhat lai chuoi result sau khi bi phat bai
				//ITOA(xxx, result);
				if (p->data.number == -5) {
					*chonMau = idUser; // tin hieu cho biet ai dc chon mau cho luot choi ke
				}
				if (p->data.number == -3) {
					*mau = p->data.color;
				}
			}
			else {
				printf("\nnhan '1' de boc bai: ");
				scanf("%d", &sapUno);
				phat(1, xxx, &s);
				*cml += 1;
				// cap nhat lai chuoi result sau khi boc bai
				//ITOA(xxx, result);
				show(*xxx);
				if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p, *t) == 1) {
					danhBai(xxx, id, cml, mau, t);
					//*mau = 'z';
				}
			}
		}
	}

	
	if (*cml == 1) {
		printf("\nsap UNO, nhan 1 de xac nhan: ");
		scanf("%d", &ID);
		if (ID != 1) {
			printf("\nnhan sai hoac k nhan nen bi phat them 2 con.");
			phat(2, xxx, &s);
			*cml += 2;
		}
	}
}


void choi4Nguoi(LIST* yyy, LIST* yyy2, LIST* yyy3, LIST* yyy4, LIST* l1, LIST* l2, LIST* l3, LIST* l4) {
	chiaBai(l1, l2, l3, l4, &s, 4);
	char result1[256] = "", result2[256] = "", result3[256] = "", result4[256] = "";
	ITOA(*l1, result1);
	ITOA(*l2, result2);
	ITOA(*l3, result3);
	ITOA(*l4, result4);
	// InitStack(s1);
	int u = 0; // luu vi tri nguoi choi truoc do
	int cml1, cml2, cml3, cml4, t = 0, chonMau = 0;// t luu tong so quan bai bi phat
	char mau = 'z';// luu mau khi 1 trong hai danh con doi mau va chon mau
	cml1 = cml2 = cml3 = cml4 = 7;
	int idUser = 0, id = 0, chuyen = -1, ID = 0; // luu giu thu tu nguoi danh
	//chuyen = -1 thi chay theo chieu kim dong ho, chuyen = 1 danh nguoc kim dong ho
	//dau tien thi nguoi choi 1 se duoc danh bai dau tien
	khoiPhuc(yyy, yyy2, yyy3, yyy4, result1, result2, result3, result4);
	printf("\ntoi luot nguoi choi 1.");
	Nguoi(yyy, idUser, &id, &t, &cml1, &mau, &chonMau);
	u = idUser = 1;
	XXX(&idUser, &chuyen, id, ID);
	printf("\nnguoi 1 con lai %d con bai", cml1);
	ID = id;

	while (cml1 != 0 && cml2 != 0 && cml3 != 0 && cml4 != 0) {
		if (idUser == 1) {
			printf("\ntoi luot nguoi choi 1.");
			//show(*yyy);
			Nguoi(yyy, idUser, &id, &t, &cml1, &mau, &chonMau);
			if (chonMau != 0) {
				printf("\nnguoi choi %d chon mau: ", u);
				scanf("%c%*c", &mau);
				chonMau = 0;
			}
			//cap nhat u
			u = idUser;
			// kiem tra xem luot danh tiep theo thuoc ve ai
			XXX(&idUser, &chuyen, id, ID);
			printf("\nnguoi 1 con lai %d con bai", cml1);
			ID = id;
		}
		else if (idUser == 2) {
			printf("\ntoi luot nguoi choi 2.");
			Nguoi(yyy2, idUser, &id, &t, &cml2, &mau, &chonMau);
			if (chonMau != 0) {
				printf("\nnguoi choi %d chon mau: ", u);
				scanf("%c%*c", &mau);
				chonMau = 0;
			}
			//cap nhat u
			u = idUser;
			// kiem tra xem luot danh tiep theo thuoc ve ai
			XXX(&idUser, &chuyen, id, ID);
			printf("\nnguoi 2 con lai %d con bai", cml2);
			ID = id;
		}
		else if (idUser == 3) {
			printf("\ntoi luot nguoi choi 3.");
			Nguoi(yyy3, idUser, &id, &t, &cml3, &mau, &chonMau);
			if (chonMau != 0) {
				printf("\nnguoi choi %d chon mau: ", u);
				scanf("%c%*c", &mau);
				chonMau = 0;
			}
			//cap nhat u
			u = idUser;
			// kiem tra xem luot danh tiep theo thuoc ve ai
			XXX(&idUser, &chuyen, id, ID);
			printf("\nnguoi 3 con lai %d con bai", cml3);
			ID = id;
		}
		else {
			printf("\ntoi luot nguoi choi 4.");
			Nguoi(yyy4, idUser, &id, &t, &cml4, &mau, &chonMau);
			if (chonMau != 0) {
				printf("\nnguoi choi %d chon mau: ", u);
				scanf("%c%*c", &mau);
				chonMau = 0;
			}
			//cap nhat u
			u = idUser;
			// kiem tra xem luot danh tiep theo thuoc ve ai
			XXX(&idUser, &chuyen, id, ID);
			printf("\nnguoi 4 con lai %d con bai", cml4);
			ID = id;
		}
	}

	if (cml1 == 0) {
		printf("\nnguoi choi 1 thang.");
	}
	else if (cml2 == 0) {
		printf("\nnguoi choi 2 thang.");
	}
	else if (cml3 == 0) {
		printf("\nnguoi choi 3 thang.");
	}
	else {
		printf("\nnguoi choi 4 thang.");
	}

	giaiPhong(l1);
	giaiPhong(l2);
	giaiPhong(l3);
	giaiPhong(l4);

	giaiPhong(yyy);
	giaiPhong(yyy2);
	giaiPhong(yyy3);
	giaiPhong(yyy4);
}