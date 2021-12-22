CC=gcc
all: run
run: server.c client.c
	$(CC) -o server server.c
	gcc `pkg-config --cflags gtk+-3.0` -o client client.c `pkg-config --libs gtk+-3.0` -export-dynamic
