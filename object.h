#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    NONE,
    LOGIN,
    SIGNUP,
    PLAY_WITH_BOT,
    ADD_ROOM,
    PLAY_WITH_PERSON,
    VIEW_RANK,
    LOGOUT
}Signal;

typedef struct {
    char username[30];
    char password[30];
}Login;

typedef struct {
    char username[30];
    char password[30];
    char confirm_password[30];
}Signup;

typedef struct {
    int id_player; //player win: 1; bot win: 0
}Play_With_Bot;

typedef struct {
    int id_room;
    int id_player; // 0:me  1:you
    int id_bai;
    char color;
    int bai_phat;
    int so_luong_bai;
}Play_With_Person;

typedef struct {
    Signal signal;
    Login login;
    Signup signup;
    Play_With_Bot play_with_bot;
    Play_With_Person play_with_person;
}Client;

typedef struct {
    int id_room;
    char messages[100];
    char list[50];
} send_room;


void free_obj(Client *c){
	free(c);
}
