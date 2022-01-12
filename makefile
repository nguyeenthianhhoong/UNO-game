CFLAGS = -c -Wall
CC = gcc 
# LIBS =  -lm
all: run

run: uno.o structData.o interface.o server.c client.c
	$(CC) uno.o structData.o server.c  -o server
	$(CC) uno.o structData.o interface.o client.c -o client `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -export-dynamic -lpthread

interface.o : interface.c
	$(CC) ${CFLAGS} interface.c `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -export-dynamic -lpthread

uno.o : uno.c
	${CC} ${CFLAGS} uno.c

structData.o : structData.c
	${CC} ${CFLAGS} structData.c

clean:
	rm -rf *.o *.~ tmp.jpg make