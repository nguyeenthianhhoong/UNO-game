//#pragma warning (disable: 4996)
#include "structData.h"

LIST l; // danh sach de luu 108 quan bai
LIST l1, l2, l3, l4;// danh sach luu quan bai tren tay nguoi choi
STACK s; // luu quan bai da dao

void WAIT (int Seconds);
//doc file;
void docFile(FILE* fileIn, LIST* l);

// load danh sach nguoi dung tu file len danh sach lien ket
void loadTuFile(FILE* fileIn, LIST* l);

void Swap(int* number_1, int* number_2);

void ShuffleArray(int* arr, int n);

// ham trao bai roi nap no vao stack
void inPutStack(STACK* s, LIST l);

int CHECK(LIST xxx, int id, UNO* uno);

// ham nap bai khi bi phat
void phat(int n, LIST* tmp, STACK* s);

int getCardFromStack(int n, STACK* s);

void my_random(char* x);

char* my_itoa(int num, char* str);

void ITOA(LIST xxx, char* result);

//ham chia bai cho nguoi choi
void chiaBai(LIST* l1, LIST* l2, LIST* l3, LIST* l4, STACK* s, int m);

void ATOI(LIST l, LIST* xxx, char* str);

// ham kiem tra con bai co trong bo bai cua nguoi choi hay k
int quanBaiHopLe(LIST xxx, int id);
// ham cong don quan bai de phat
void soQuanBiPhat(int number, int* t);

//ham kiem tra quan bai hop le sau khi danh
int kt(UNO p, UNO r);

int doiMau(LIST xxx, char mau, NODE* r, int phat);
int doiMau2(LIST xxx, char mau, NODE* r);

void danhBaiChoMay(LIST* xxx, int* id, int* cml, char* mau, int* t);

LIST yyy;