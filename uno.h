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

void my_random(char* x);

char* my_itoa(int num, char* str);

// void ITOA(LIST xxx, char* result);

//ham chia bai cho nguoi choi
void chiaBai(LIST* l1, LIST* l2, LIST* l3, LIST* l4, STACK* s, int m);

// void ATOI(LIST l, LIST* xxx, char* str);

// ham kiem tra con bai co trong bo bai cua nguoi choi hay k
int quanBaiHopLe(LIST xxx, int id);
// ham cong don quan bai de phat
void soQuanBiPhat(int number, int* t);
// ham cho luot danh dau tien
// void luotDanhDau(LIST* xxx, int* id, int* cml, char* mau, int* t);

// void luotDanhDauchoMay(LIST* xxx, int* id, int* cml, char* mau, int* t);

//ham kiem tra quan bai hop le sau khi danh
int kt(UNO p, UNO r);

int doiMau(LIST xxx, char mau, NODE* r, int phat);
int doiMau2(LIST xxx, char mau, NODE* r);
// ham danh bai cho nguoi choi trong truong hop co quan bai hop le
// void danhBai(LIST* xxx, int* id, int* cml, char* mau, int* t);

// ham kiem tra quan bai sau khi danh con doi mau
// int doiMau2(LIST xxx, char mau, NODE* r);

// int doiMau(LIST xxx, char mau, NODE* r);

void danhBaiChoMay(LIST* xxx, int* id, int* cml, char* mau, int* t);

//ham tim thu tu nguoi choi tiep theo
// void XXX(int* idUser, int* chuyen, int id, int ID);
LIST yyy;
// void khoiPhuc0(LIST* xxx, char* result);

// void nguoiDanh(LIST* xxx, int* idUser, int* id, int* t, int* cml, char* mau, int* chonMau) ;

// void mayDanh(LIST* xxx, int* idUser, int* id, int* t, int* cml, char* mau, int* chonMau);
// void choiVoiMay(LIST* yyy, LIST* l1, LIST* l2);
//=======================================================================================
//ham khoi phuc la bai
// LIST yyy2, yyy3, yyy4;
// void khoiPhuc(LIST* yyy, LIST* yyy2, LIST* yyy3, LIST* yyy4, char* result1, char* result2, char* result3, char* result4);
//ham choi nay danh cho choi 4 nguoi
// void Nguoi(LIST *xxx, int idUser, int* id, int* t, int* cml, char* mau, int* chonMau);
// void choi4Nguoi(LIST* yyy, LIST* yyy2, LIST* yyy3, LIST* yyy4, LIST* l1, LIST* l2, LIST* l3, LIST* l4) ;
