CFLAGS = -c -Wall
CC = gcc 
SRC=../unoStruct
all: run

run: uno.o structData.o interface.o client.c
	$(CC) uno.o structData.o interface.o client.c -o client `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -export-dynamic -lpthread -lX11

interface.o : interface.c
	$(CC) ${CFLAGS} interface.c `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -export-dynamic -lpthread -lX11

uno.o : $(SRC)/uno.c
	${CC} ${CFLAGS} $(SRC)/uno.c

structData.o : $(SRC)/structData.c
	${CC} ${CFLAGS} $(SRC)/structData.c

clean:
	rm -rf *.o *.~ tmp.jpg rankRecv.txt
