CFLAGS = -c -Wall
CC = gcc 
SRC=../unoStruct
all: run

run: uno.o structData.o server.c
	$(CC) uno.o structData.o server.c -o server

uno.o : $(SRC)/uno.c
	${CC} ${CFLAGS} $(SRC)/uno.c

structData.o : $(SRC)/structData.c
	${CC} ${CFLAGS} $(SRC)/structData.c

clean:
	rm -rf *.o *.~ ../src/rank.txt
