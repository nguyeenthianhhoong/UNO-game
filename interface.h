#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "uno.h"
// #include "object.h"
#define BUFF_SIZE 80


//Check Input
void trim(char s[]);
int checkSpace(char s[]);

// LOGIN SIGNGIN
void on_loginBtn_clicked();
void on_LoginWindow_destroy();
void on_loginSubmitBtn_clicked();
void on_registerBtn_clicked();
void on_RegisterWindow_destroy();
void on_registerSubmitBtn_clicked();
void on_mainMenuWindow_destroy();
void on_startGameBtn_clicked();
void on_viewRankBtn_clicked();
void on_logoutBtn_clicked();

//GAME BUTTON
void on_chooseRedBtn_clicked();
void on_chooseGreenBtn_clicked();
void on_chooseBlueBtn_clicked();
void on_chooseYellowBtn_clicked();
void on_backToHomeBtn_clicked();
void on_replayBtn_clicked();
void unoButtonClick(GtkWidget *button);
void nextButtonClick(GtkWidget *button);
void drawCardButtonClick(GtkWidget *button);

//handle game
void main_play_game_with_bot();
char *get_link_fileImage(int id, char *link);
void reset_board_game();
int check_player_win();
int check_bot_win();
int check_up_card(LIST *xxx, int *cml); //check phạt ko đỡ đk thì phạt luôn
void mayDanh(LIST *xxx, int *idUser, int *id, int *t, int *cml, char *mau, int *chonMau);
int app(int argc, char **argv, int sockfd);
void card_clicked(GtkWidget *card_button, gpointer card_data);
void getNextPlayer();
void bot_play();
int play(UNO *card);
static gboolean serial_data(gpointer user_data);
static void checkTimeOutUnoButton(gpointer user_data);

void main_play_with_player();
int connect_with_another_player();
static gint check_connect_other_player(gpointer status);
void recv_msg_handler();
void send_msg_handler();
void build_board_game_with_player();
void on_backfromWaitPlayer_clicked();

//draw game
void buildUIGameWindow();
void draw_hand(GtkWidget *container);
void draw_enemyCards();
static gint check_connect_other_player(gpointer status);
static void drawHandCardsFromRecv(gpointer user_data);
GtkWidget *resize_image(GtkWidget *image, char *link, float x);
void draw_card(GtkWidget *container, UNO *card, int status, float sizeCard);
void draw_colorSquare();
void change_on_off_icon(int mode);
void* DisplayNotification(void*);
void notificationThread(int mode, int user);
void clear_container(GtkWidget *container);

void build_rankWindow();