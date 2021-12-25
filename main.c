#include "uno.h"
int main() {

	Init(&l);
	loadTuFile(fileIn, &l); // do bai tu file vao dslk
	//Output(l);
	inPutStack(&s, l);
	/*while (isEmpty(&s) == 0) {
		UNO uno;
		uno = pop(&s);
		printf("%d %c %d", uno.id, uno.color, uno.number);
		printf("\n");
	}*/

	int a;

	printf("\n1. Danh voi may.");
	printf("\n2. Danh 4 nguoi.");
	printf("\nchon: ");
    scanf("%d%*c", &a);
	//printf("%d", a);

	//char result[256] = "";
    if(a == 1){
		//l1 la bo bai cua nguoi choi, l2 la cua may
	
		//printf("\nresult = %s", result);
		choiVoiMay(&yyy, &l1, &l2, &s1);
	}else{
		choi4Nguoi(&yyy, &yyy2, &yyy3, &yyy4, &l1, &l2, &l3, &l4, &s1);
	}

	outPut(&s);
	outPut(&s1);
	giaiPhong(&l);

	printf("\nWIN\n");
	return 0;
}