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
#include "../unoStruct/uno.h"
#define BUFF_SIZE 80


//Check Input
void trim(char s[]);
int checkSpace(char s[]);
int displayDisconnectToServer();
void on_closeDisconnectWindow_clicked();


//APP
int app(int argc, char **argv, int sockfd);

//BEGIN
void on_registerBtn_clicked();
void on_loginBtn_clicked();

// LOGIN
void on_LoginWindow_destroy();
void on_loginSubmitBtn_clicked();

// SIGNGIN
void on_RegisterWindow_destroy();
void on_registerSubmitBtn_clicked();

//MAIN MENU
void on_mainMenuWindow_destroy();
void on_startGameBtn_clicked();
void on_viewRankBtn_clicked();
void on_logoutBtn_clicked();

//PLAYMODE
void on_playerModeBtn_clicked();
void on_botModeBtn_clicked();

//RANK
int write_file_ranktxt();
void build_rankWindow();

//GAME BUTTON
void on_backToHomeBtn_clicked();
void on_replayBtn_clicked();
void unoButtonClick(GtkWidget *button);
void nextButtonClick(GtkWidget *button);
void drawCardButtonClick(GtkWidget *button);

//CHOOSE COLOR 
void on_chooseRedBtn_clicked();
void on_chooseGreenBtn_clicked();
void on_chooseBlueBtn_clicked();
void on_chooseYellowBtn_clicked();

//BOARD GAME

//card image and button image
char *get_link_fileImage(int id, char *link);
GtkWidget *resize_image(GtkWidget *image, char *link, float x);

//play with another player
void main_play_with_player();
//connect with another player
void on_backfromWaitPlayer_clicked();
int connect_with_another_player();
static gint check_connect_other_player(gpointer status);
void build_board_game_with_player();
//send | recv messege
void recv_msg_handler();
void send_msg_handler();

//play with bot
void main_play_game_with_bot();
//bot play
void bot_play();
void mayDanh(LIST *xxx, int *idUser, int *id, int *t, int *cml, char *mau, int *chonMau);

//handle game
int check_up_card(LIST *xxx, int *cml);
void card_clicked(GtkWidget *card_button, gpointer card_data);
int play(UNO *card);
void getNextPlayer();

//check UnoButton click and handle
static gboolean serial_data(gpointer user_data);
static void checkTimeOutUnoButton(gpointer user_data);

//check Win/Over
int check_player_win();
int check_bot_win();
//reset when end game
void reset_board_game();


//draw card and draw board game
void buildUIGameWindow();
void draw_hand(GtkWidget *container);
void draw_enemyCards();
void draw_card(GtkWidget *container, UNO *card, int status, float sizeCard);
void draw_colorSquare();
void clear_container(GtkWidget *container);

//notification
void change_on_off_icon(int mode);
void* DisplayNotification(void*);
void notificationThread(int mode, int user);

