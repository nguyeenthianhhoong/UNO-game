#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

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

void Init(LIST* l);
NODE* getNode(UNO DATA);
void addTail(LIST* l, NODE* p);
void xoaDau(LIST* l);
void XoaCuoi(LIST* l);
void giaiPhong(LIST* l);
void Output(LIST l);
void show(LIST l1);
NODE* find(LIST l, int id);
void inPutL1(STACK* s, LIST* l1);
void deleteNode(LIST* l1, int id);
NODE* findL1(LIST l1, char x, int y);

void InitStack(STACK* s);
int isEmpty(STACK* s);
int push(STACK* s, NODE* p);
int push2(STACK* s, UNO uno);
UNO pop(STACK* s);
void outPut(STACK* s);

UNO timUno(LIST l, int id);