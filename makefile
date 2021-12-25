CFLAGS = -c -Wall
CC = gcc 
# LIBS =  -lm
all: run

run: server.c client.c uno.o test.o
	$(CC) uno.o test.o server.c -o server
	$(CC) `pkg-config --cflags gtk+-3.0` uno.o test.o client.c -o client `pkg-config --libs gtk+-3.0` -export-dynamic



# run: uno.o test.o main.c
# 	${CC} test.o uno.o main.c -o main

uno.o : uno.c
	${CC} ${CFLAGS} uno.c

test.o : test.c
	${CC} ${CFLAGS} test.c

clean:
	rm -rf *.o *.~ | clear

# server.o: server.c uno.o test.o
# 	${CC} server.c uno.o test.c

# client.o: 
# 	gcc `pkg-config --cflags gtk+-3.0` -o client client.c `pkg-config --libs gtk+-3.0` -export-dynamic
# run: server.c client.c uno.c test.c
# 	$(CC) -o server server.c
# 	gcc `pkg-config --cflags gtk+-3.0` -o client client.c `pkg-config --libs gtk+-3.0` -export-dynamic

# main: test.o uno.o main.c
# 	${CC} test.o uno.o main.c -o main

