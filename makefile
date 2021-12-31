CFLAGS = -c -Wall
CC = gcc 
# LIBS =  -lm
all: run

run: server.c client.c uno.o structData.o
	$(CC) uno.o structData.o server.c -o server
	$(CC) `pkg-config --cflags gtk+-3.0` uno.o structData.o client.c -o client `pkg-config --libs gtk+-3.0` -export-dynamic

uno.o : uno.c
	${CC} ${CFLAGS} uno.c

structData.o : structData.c
	${CC} ${CFLAGS} structData.c

clean:
	rm -rf *.o *.~ tmp.jpg make