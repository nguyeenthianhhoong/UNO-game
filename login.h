#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
// #include "test.h"
#include "uno.h"
#define BUFF_SIZE 80

const int WINDOW_WIDTH = 1140;
const int WINDOW_HEIGHT = 700;
const float CARD_WIDTH = 55;
const float CARD_HEIGHT = 85;

const int PLAYER = 1;
const int ENEMY = 2;
const int OTHER = 3;

int checkk = 0, check0 = 0;

GtkBuilder *builder;
GtkWidget *beginWindow;

GtkWidget *LoginWindow;
GtkWidget *usernameLoginEntry;
GtkWidget *passwordLoginEntry;
GtkWidget *errorLoginLabel;
GtkWidget *errorRegisLabel;

GtkWidget *RegisterWindow;
GtkWidget *usernameRegEntry;
GtkWidget *passwordRegEntry;
GtkWidget *passwordAgainRegEntry;

GtkWidget *mainMenuWindow;
GtkWidget *boardWindow;

char buff[80];
int rcvBytes;
int sock_app;

void trim(char s[])
{
    int i = strlen(s);
    while (s[0] == ' ')
    {
        for (int j = 0; j < i; j++)
            s[j] = s[j + 1];
        i--;
    }
    while (s[i - 1] == ' ' || s[i - 1] == '\n')
        i--;
    s[i] = '\0';
}

int checkSpace(char s[])
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
            return 1;
    }
    return 0;
}
UNO listCard[] = {{1, 'r', 0}, {2, 'r', 1}, {3, 'r', 2}, {4, 'r', 3}, {5, 'r', 4}, {6, 'r', 5}, {7, 'r', 6}, {8, 'r', 7}, {9, 'r', 8}, {10, 'r', 9}, {11, 'r', -1}, {12, 'r', -2}, {13, 'r', -3}, {14, 'k', -4}, {15, 'y', 0}, {16, 'y', 1}, {17, 'y', 2}, {18, 'y', 3}, {19, 'y', 4}, {20, 'y', 5}, {21, 'y', 6}, {22, 'y', 7}, {23, 'y', 8}, {24, 'y', 9}, {25, 'y', -1}, {26, 'y', -2}, {27, 'y', -3}, {28, 'k', -4}, {29, 'g', 0}, {30, 'g', 1}, {31, 'g', 2}, {32, 'g', 3}, {33, 'g', 4}, {34, 'g', 5}, {35, 'g', 6}, {36, 'g', 7}, {37, 'g', 8}, {38, 'g', 9}, {39, 'g', -1}, {40, 'g', -2}, {41, 'g', -3}, {42, 'k', -4}, {43, 'b', 0}, {44, 'b', 1}, {45, 'b', 2}, {46, 'b', 3}, {47, 'b', 4}, {48, 'b', 5}, {49, 'b', 6}, {50, 'b', 7}, {51, 'b', 8}, {52, 'b', 9}, {53, 'b', -1}, {54, 'b', -2}, {55, 'b', -3}, {56, 'k', -4}};
UNO x_card = {0, 'x', -6};
UNO add4card = {69, 'k', -5};
UNO add2card = {13, 'r', -3};

UNO up_card;
UNO hand[52];
int hand_size = 7;
int enemy_size = 7;

int t = 0;      // t luu tong so quan bai bi phat
char mau = 'z'; // luu mau khi 1 trong hai danh con doi mau va chon mau
int chonMau = 0;
int idUser = PLAYER;
int drawCardCount = 0;
// luu giu id nguoi danh, idUser = 1 la nguoi, idUser = 2 la may
// id la id cua quan bai

void deal_random_hand(int);
void card_clicked(GtkWidget *, gpointer);
int play(UNO *);
void draw_hand();
void draw_card(GtkWidget *, UNO *, int, float);
void draw_up_card(UNO *);
void remove_card(UNO *, int);
void clear_container(GtkWidget *);
void buildUIGameWindow();

void main_play_game_with_bot();

char *get_link_fileImage(int id, char *link)
{
    memset(link, 0, strlen(link));
    char tmpchar[30];
    int tmp = -1;
    if (id == 56 || id == 42 || id == 28)
    {
        tmp = 14;
    }
    else if (id == 82 || id == 95 || id == 108)
    {
        tmp = 69;
    }
    else if (id > 56 && id < 69)
    {
        tmp = id - 55;
    }
    else if (id > 69 && id < 82)
    {
        tmp = id - 54;
    }
    else if (id > 82 && id < 95)
    {
        tmp = id - 53;
    }
    else if (id > 95 && id < 108)
    {
        tmp = id - 52;
    }
    else
    {
        tmp = id;
    }
    my_itoa(tmp, tmpchar);

    strcpy(link, "cards/");
    strcat(link, tmpchar);
    strcat(link, ".png");
    return link;
}

GtkBuilder *builder;
GtkWidget *boardWindow;
GtkWidget *boardWindowFixed;
GtkWidget *controllerBox;
GtkWidget *playerBox;
GtkWidget *enemyBox;
GtkWidget *iconON;
GtkWidget *iconOFF;

int check_up_card(LIST *xxx, int *cml) //check phạt ko đỡ đk thì phạt luôn
{
    // printf("vao check\n");
    int ID = up_card.id;
    // printf("id: %d %d\n", ID, up_card.id);
    NODE *p = find(l, ID);
    UNO uno;
    if (CHECK(*xxx, ID, &uno) != 1 && doiMau(*xxx, mau, p) != 1)
    {
        printf("check 1\n");

        //************** bị phat
        if ((p->data.number == -3 || p->data.number == -5) && t != 0)
        {
            printf("check 2\n");
            printf("\n\nbi phat %d con bai", t);
            phat(t, xxx, &s);
            *cml += t;
            t = 0;
            draw_hand(playerBox);
            // cap nhat lai chuoi result sau khi bi phat bai
            //ITOA(yyy, result);
            if (p->data.number == -5)
            {
                chonMau = 2; // tin hieu cho biet máy dc chon mau cho luot choi ke
            }
            if (p->data.number == -3)
            {
                mau = p->data.color;
            }
        }
    }
}

void draw_enemyCards()
{
    clear_container(enemyBox);
    // draw all cards in the hand of enemy
    float sizeCard = 1;
    if (enemy_size <= 3)
    {
        gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 6, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), enemyBox, (WINDOW_WIDTH - CARD_WIDTH * 6) / 2, 30);
    }
    else if (enemy_size > 3 && enemy_size < 9)
    {
        gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 12, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), enemyBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 30);
    }
    else
    {
        gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 17, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), enemyBox, (WINDOW_WIDTH - CARD_WIDTH * 17) / 2, 30);
        if (enemy_size > 12)
        {
            sizeCard = 0.6;
            gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 17, CARD_HEIGHT * sizeCard);
        }
    }

    for (int i = 0; i < enemy_size; i++)
    {
        // draw the current card
        draw_card(enemyBox, &x_card, PLAYER, sizeCard);
    }

    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);
}

void drawCardButtonClick(GtkWidget *button)
{
    if (drawCardCount == 0)
    {
        phat(1, &l1, &s);
        hand_size++;
        draw_hand(playerBox);

        NODE *p = find(l, up_card.id);
        UNO uno;
        if (CHECK(l1, up_card.id, &uno) != 1 && doiMau(l1, mau, p) != 1)
        {
            idUser = 2;
            int id = up_card.id;

            mayDanh(&l2, &s1, &idUser, &id, &t, &enemy_size, &mau, &chonMau);
            up_card = timUno(l, id);
            draw_enemyCards();
            check_up_card(&l1, &hand_size);
            return;
        }
        drawCardCount++;
    }
}

GtkWidget *resize_image(GtkWidget *image, char *link, float x)
{
    char cmd[2048];
    FILE *f1;

    sprintf(cmd, "identify -format %%wx%%h \"%s\"\n", link);
    f1 = popen(cmd, "r");
    strcpy(cmd, "");
    fgets(cmd, 2048, f1);
    fclose(f1);

    float width = CARD_WIDTH * x;
    float height = CARD_HEIGHT * x;
    sprintf(cmd, "convert \"%s\" -resize %dx%d tmp.jpg\n", link, (int)width, (int)height);
    system(cmd);

    strcpy(link, "tmp.jpg");

    image = gtk_image_new_from_file(link);

    return image;
    system("rm tmp.jpg");
}

void unoButtonClick(GtkWidget *button)
{
    g_print("uno button click\n");
}

void nextButtonClick(GtkWidget *button)
{
    g_print("next button click\n");
    if (drawCardCount == 1 && idUser == PLAYER)
    {
        //xử lý next
        drawCardCount--;
        idUser = 2;
        int id = up_card.id;
        mayDanh(&l2, &s1, &idUser, &id, &t, &enemy_size, &mau, &chonMau);
        up_card = timUno(l, id);
        draw_enemyCards();
        check_up_card(&l1, &hand_size);
    }
}

int app(int argc, char **argv, int sockfd)
{
    gtk_init(&argc, &argv);
    sock_app = sockfd;

    builder = gtk_builder_new_from_file("UI.glade");
    beginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "beginWindow"));
    gtk_window_set_title(GTK_WINDOW(beginWindow), "Uno");

    LoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"));
    gtk_window_set_title(GTK_WINDOW(LoginWindow), "Đăng nhập");
    usernameLoginEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameLoginEntry"));
    passwordLoginEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLoginEntry"));
    errorLoginLabel = GTK_WIDGET(gtk_builder_get_object(builder, "errorLoginLabel"));

    RegisterWindow = GTK_WIDGET(gtk_builder_get_object(builder, "RegisterWindow"));
    gtk_window_set_title(GTK_WINDOW(RegisterWindow), "Đăng ký");
    usernameRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameRegEntry"));
    passwordRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordRegEntry"));
    passwordAgainRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordAgainRegEntry"));
    errorRegisLabel = GTK_WIDGET(gtk_builder_get_object(builder, "errorRegisLabel"));

    mainMenuWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainMenuWindow"));

    boardWindow = GTK_WIDGET(gtk_builder_get_object(builder, "boardWindow"));
    buildUIGameWindow();
    gtk_widget_hide(boardWindow);

    g_signal_connect(beginWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    gtk_widget_show(beginWindow);

    gtk_main();

    giaiPhong(&l1); // giải phóng bộ nhớ
    giaiPhong(&l2);
    return EXIT_SUCCESS;
}

void on_loginBtn_clicked()
{
    gtk_widget_show(LoginWindow);
    gtk_widget_hide(beginWindow);
    strcpy(buff, "1");
    send(sock_app, buff, strlen(buff), 0);
    rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
    buff[rcvBytes] = '\0';
}

void on_LoginWindow_destroy()
{
    gtk_widget_show(beginWindow);
    gtk_widget_hide(LoginWindow);
    gtk_editable_delete_text(GTK_EDITABLE(usernameLoginEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordLoginEntry), 0, -1);
    gtk_label_set_text(GTK_LABEL(errorLoginLabel), "");
}

void on_loginSubmitBtn_clicked()
{

    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(usernameLoginEntry)));
    trim(tmp);
    if (checkSpace(tmp) == 1)
    {
        //loi
        gtk_label_set_text(GTK_LABEL(errorLoginLabel), "username khong co dau cach!");
    }
    else
    {

        // printf("-%s-\n", tmp);
        strcpy(buff, tmp);
        sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordLoginEntry)));
        // printf("-%s-\n", tmp);
        // trim(tmp);
        if (checkSpace(tmp) == 1)
        {
            //loi
            gtk_label_set_text(GTK_LABEL(errorLoginLabel), "password khong co dau cach!");
        }
        else
        {
            strcat(buff, " ");
            strcat(buff, tmp);
            send(sock_app, buff, strlen(buff), 0);
            rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
            if (rcvBytes < 0)
            {
                perror("Error: ");
                return;
            }
            buff[rcvBytes] = '\0';
            if (strcmp(buff, "OK") == 0)
            {
                printf("\n-------------Let's play-------------\n");
                on_LoginWindow_destroy();
                //cua so main game
                gtk_widget_show(mainMenuWindow);
                gtk_widget_hide(beginWindow);
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(errorLoginLabel), buff);
                //continue;
            }
        }
    }
}

void on_registerBtn_clicked()
{
    gtk_widget_show(RegisterWindow);
    gtk_widget_hide(beginWindow);
    strcpy(buff, "2");
    send(sock_app, buff, strlen(buff), 0);
    rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
    buff[rcvBytes] = '\0';
}

void on_RegisterWindow_destroy()
{
    gtk_widget_show(beginWindow);
    gtk_widget_hide(RegisterWindow);
    gtk_editable_delete_text(GTK_EDITABLE(usernameRegEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordRegEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordAgainRegEntry), 0, -1);
    gtk_label_set_text(GTK_LABEL(errorRegisLabel), "");
}

void on_registerSubmitBtn_clicked()
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(usernameRegEntry)));
    trim(tmp);
    // printf("-%s-\n", tmp);
    if (checkSpace(tmp) == 1)
    {
        //loi
        gtk_label_set_text(GTK_LABEL(errorRegisLabel), "username khong co dau cach!");
    }
    else
    {

        strcpy(buff, tmp);
        strcat(buff, " ");
        sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordRegEntry)));
        if (checkSpace(tmp) == 1)
        {
            //loi
            gtk_label_set_text(GTK_LABEL(errorRegisLabel), "password khong co dau cach!");
        }
        else
        {

            // printf("-%s-\n", tmp);
            strcat(buff, tmp);
            strcat(buff, " ");
            sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordAgainRegEntry)));
            if (checkSpace(tmp) == 1)
            {
                //loi
                gtk_label_set_text(GTK_LABEL(errorRegisLabel), "password khong co dau cach!");
            }
            else
            {

                // printf("-%s-\n", tmp);
                strcat(buff, tmp);
                // printf("-%s-\n", buff);
                send(sock_app, buff, strlen(buff), 0);
                rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
                if (rcvBytes < 0)
                {
                    perror("Error: ");
                    return;
                }
                buff[rcvBytes] = '\0';
                if (strcmp(buff, "OK") == 0)
                {
                    printf("\nĐăng ký tài khoản thành công\n");
                    on_RegisterWindow_destroy();
                }
                gtk_label_set_text(GTK_LABEL(errorRegisLabel), buff);
            }
        }
    }
}

void on_mainMenuWindow_destroy()
{
    gtk_main_quit();
}

void on_startGameBtn_clicked()
{
    // gtk_widget_show(boardWindow);
    gtk_widget_show_all(boardWindow);
    gtk_widget_hide(mainMenuWindow);

    main_play_game_with_bot();
}

/**
 * Deal a random hand with the given length
 * @param length Number of cards in the hand
 */
void deal_random_hand(int length)
{
    // seed prng
    srand(time(NULL));

    // create a hand of size length
    for (int i = 0; i < length; i++)
    {
        // create a card with random values
        int r = 1 + rand() % (56);
        for (int j = 0; j < sizeof(listCard) / sizeof(UNO); j++)
        {
            if (listCard[j].id == r)
                hand[i] = listCard[j];
        }
    }

    // keep track of size of hand
    hand_size = length;

    // generate random up card

    int r = 1 + rand() % (56);
    for (int i = 0; i < sizeof(listCard) / sizeof(UNO); i++)
    {
        if (listCard[i].id == r)
        {
            up_card = listCard[i];
        }
    }
    draw_hand(playerBox);
}

/**
 * Draw the user's hand
 *
 */
void draw_hand(GtkWidget *container)
{
    clear_container(container);
    float sizeCard = 1;
    // draw the up card
    if (hand_size <= 3)
    {
        gtk_widget_set_size_request(playerBox, CARD_WIDTH * 6, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), playerBox, (WINDOW_WIDTH - CARD_WIDTH * 6) / 2, 582);
    }
    else if (hand_size > 3 && hand_size < 9)
    {
        gtk_widget_set_size_request(playerBox, CARD_WIDTH * 12, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), playerBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 582);
    }
    else
    {
        gtk_widget_set_size_request(playerBox, CARD_WIDTH * 17, CARD_HEIGHT);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), playerBox, 100, 582);
        if (hand_size > 12)
        {
            sizeCard = 0.6;
            gtk_widget_set_size_request(playerBox, CARD_WIDTH * 17, CARD_HEIGHT * sizeCard);
        }
    }
    // draw all cards in the hand
    // for (int i = 0; i < hand_size; i++)
    // {
    //     // draw the current card
    //     draw_card(container, &hand[i], PLAYER, sizeCard);
    // }

    for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
    {
        // printf("%d-%c-%d", p->data.id, p->data.color, p->data.number);
        // printf("\n");
        draw_card(container, &(p->data), PLAYER, sizeCard);
    }

    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);
}

/**
 * Draw a single card
 *
 * @param card Card to draw
 * @param x x-position of card
 * @param y y-position of card
 *status == 1 -> can click -> check value
 */
void draw_card(GtkWidget *container, UNO *card, int status, float sizeCard)
{
    //add array button card game
    char link[30];
    GtkWidget *image = gtk_image_new_from_file(get_link_fileImage(card->id, link));
    if (sizeCard != 1)
    {
        image = resize_image(image, get_link_fileImage(card->id, link), sizeCard);
    }
    GtkWidget *button = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(button), TRUE);
    gtk_button_set_image(GTK_BUTTON(button), image);
    // draw card
    gtk_box_pack_start(GTK_BOX(container), button, TRUE, FALSE, 0);

    if (status == PLAYER)
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(card_clicked), card);

    gtk_widget_show(button);
}

/**
 * Event handler for a card being clicked
 */
void card_clicked(GtkWidget *card_button, gpointer card_data)
{
    // cast generic gpointer to a card
    UNO *card = (UNO *)card_data;
    // play the card
    if (idUser == 1)
    {
        if(play(card)==1){
            if (up_card.number == -1)
            {
                idUser = 1;
            }
            else
            {
                // WAIT(2);
                idUser = 2;
                int id = up_card.id;
                mayDanh(&l2, &s1, &idUser, &id, &t, &enemy_size, &mau, &chonMau);
                up_card = timUno(l, id);
                draw_enemyCards();
                check_up_card(&l1, &hand_size);
            }
        }
    }
}

/**
 * Play the given card
 * @param card Card to play
 * @return False if card cannot be played, true otherwise
 */
int play(UNO *card)
{
    // // if either value or color matches, then move is valid
    // if (card->color == up_card.color || card->color == 'k' || card->number == up_card.number)
    // {
    //     // change the up card
    //     up_card = *card;

    //     // // clear game so we can remove the card that was played
    //     // clear_container(boardWindowFixed);

    //     // // draw the new game state
    //     remove_card(card, PLAYER);
    //     draw_hand(playerBox);
    //     return 1;
    // }

    // // illegal move
    // return 0;
    // void danhBai(LIST* xxx) {
    NODE *p;
    NODE *r;
    UNO uno;
    int ID = card->id;
    p = find(l, up_card.id);

    r = find(l, card->id);
    //phía trước có con chọn màu

    //ktra màu
    // if (mau != 'z') {
    //     do {
    //         printf("\nDANH: ");
    //         // scanf("%d%*c", id);
    //         r = find(l, ID);
    //         //quan bai hop le -> so có ở trong list ko ???
    //         //doimau2 -> check thoa man
    //         if (quanBaiHopLe(l1, *id) != 1 || doiMau2(l1, mau, r) != 1) {
    //             printf("quan bai khong hop le, moi danh lai.");
    //         }
    //     } while (quanBaiHopLe(l1, *id) != 1 || doiMau2(l1, mau, r) != 1);
    //     mau = 'z';
    // }
    // else {
    // do {
    if (mau != 'z')
    {
        if ((r->data.color != mau) && (r->data.color != 'k'))
        {
            return 0;
        }
        mau = 'z';
    }
    else
    {
        if (kt(p, r) != 1)
        {
            // printf("quan bai khong hop le, moi danh lai.");
            return 0;
        }
    }

    //kt kiểm tra cả màu hoặc số
    up_card = *card;
    //tìm uno để push vào s1
    p = find(l, ID);
    uno = p->data;
    push2(&s1, uno);
    // cap nhat so quan bai bi phat
    soQuanBiPhat(p->data.number, &t);
    if (p->data.number == -4 || p->data.number == -5)
    {
        printf("\nCHON MAU: ");
        scanf("%c%*c", &mau);
    }
    deleteNode(&l1, ID);
    printf("\nsau khi xoa id = %d", ID);
    show(l1);
    hand_size -= 1;
    // // draw the new game state
    // remove_card(card, PLAYER);
    draw_hand(playerBox);
    //r = find(l, *id);
    // } while (quanBaiHopLe(l1, ID) != 1 || kt(p, r) != 1);
    // }

    // cap nhat lai chuoi result sau khi danh bai
    //ITOA(*xxx, result);
    drawCardCount = 0;
    // p = find(l, card->id);
    // if (p->data.number == -1 && card->id != up_card.id) {
    // 	idUser = 1;
    // }
    // p = find(l, card->id);
    return 1;
}

/**
 * Remove all children from the given container
 *
 */
void clear_container(GtkWidget *container)
{
    // get all children in the container
    GList *children = gtk_container_get_children(GTK_CONTAINER(container));

    // iterate over children of container
    for (GList *i = children; i != NULL; i = g_list_next(i))
        // gtk_widget_destroy(GTK_WIDGET(i->data));
        gtk_container_remove(GTK_CONTAINER(container), GTK_WIDGET(i->data));

    // free list
    g_list_free(children);
}

/**
 * Remove the given card from the hand
 * @param card Card to remove 
 */
void remove_card(UNO *card, int mode)
{
    int removed = 0;

    // iterate over hand, looking for card
    for (int i = 0; i < hand_size; i++)
    {
        // if card has already been removed, then sift element back one
        if (removed)
            hand[i - 1] = hand[i];

        // if card matches, then begin sifting cards backward
        if (hand[i].number == card->number && hand[i].color == card->color)
            removed = 1;
    }

    // since we've removed a card
    hand_size--;
}

void buildUIGameWindow()
{

    //add widget from file glade
    // builder = gtk_builder_new_from_file("login.glade");
    boardWindow = GTK_WIDGET(gtk_builder_get_object(builder, "boardWindow"));

    g_signal_connect(boardWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    //add container
    boardWindowFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(boardWindow), boardWindowFixed);

    //add background of window
    GdkPixbuf *backgrndPixbuf;
    GtkWidget *backgrndImage;
    GError *error = NULL;
    backgrndPixbuf = gdk_pixbuf_new_from_file("images/background.png", &error);
    backgrndPixbuf = gdk_pixbuf_scale_simple(backgrndPixbuf, 1140, 700, GDK_INTERP_BILINEAR);
    backgrndImage = gtk_image_new_from_pixbuf(backgrndPixbuf);
    gtk_container_add(GTK_CONTAINER(boardWindowFixed), backgrndImage);

    int box_width = CARD_WIDTH * 2 * 5;
    int box_height = CARD_HEIGHT * 2;
    //*****************************************************************************************************
    //ADD CONTROLLER: up card | draw button | next button | uno button
    int startWidth = (WINDOW_WIDTH - CARD_WIDTH * 8) / 2 + 50;
    int heightControllerBox = (WINDOW_HEIGHT - CARD_HEIGHT * 2) / 2 - 15;
    //1.. up card
    controllerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), controllerBox, startWidth, heightControllerBox);
    // draw_up_card(&x_card);
    draw_card(controllerBox, &x_card, OTHER, 2);
    //2.add draw card button
    char link[] = "images/pile.png";
    GtkWidget *drawCardImage = gtk_image_new_from_file(link);
    drawCardImage = resize_image(drawCardImage, link, 2);
    // gtk_widget_set_size_request(drawCardImage, CARD_WIDTH*2, CARD_HEIGHT*2);
    GtkWidget *drawCardButton = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(drawCardButton), TRUE);
    gtk_button_set_image(GTK_BUTTON(drawCardButton), drawCardImage);
    //add to box
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), drawCardButton, startWidth + CARD_WIDTH * 2.5, heightControllerBox);
    g_signal_connect(drawCardButton, "clicked", G_CALLBACK(drawCardButtonClick), NULL); //when clicked, draw a card and pass the player's box

    //3.add next button
    strcpy(link, "images/next.png");
    GtkWidget *nextImage = gtk_image_new_from_file(link);
    nextImage = resize_image(nextImage, link, 1);
    // gtk_widget_set_size_request(nextImage, CARD_WIDTH, CARD_HEIGHT);
    GtkWidget *nextButton = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(nextButton), TRUE);
    gtk_button_set_image(GTK_BUTTON(nextButton), nextImage);
    //add to box
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), nextButton, startWidth + CARD_WIDTH * 5, heightControllerBox + 20);
    g_signal_connect(nextButton, "clicked", G_CALLBACK(nextButtonClick), NULL);

    //4.add uno button
    strcpy(link, "images/uno.png");
    GtkWidget *unoImage = gtk_image_new_from_file(link);
    unoImage = resize_image(unoImage, link, 1);
    // gtk_widget_set_size_request(unoImage, CARD_WIDTH, CARD_HEIGHT);
    GtkWidget *unoButton = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(unoButton), TRUE);
    gtk_button_set_image(GTK_BUTTON(unoButton), unoImage);
    //add to box
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), unoButton, startWidth + CARD_WIDTH * 5, heightControllerBox + 100);
    g_signal_connect(unoButton, "clicked", G_CALLBACK(unoButtonClick), NULL);
    //****************************************************************************************
    iconON = gtk_image_new_from_icon_name("dialog-ok", GTK_ICON_SIZE_DND);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), iconON, 40, 610);

    iconOFF = gtk_image_new_from_icon_name("dialog-close", GTK_ICON_SIZE_DND);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), iconOFF, 40, 60);
    //*****************************************************************************************
    enemyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 12, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), enemyBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 30);

    // 4 box vao 4 vi tri.
    playerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_size_request(playerBox, CARD_WIDTH * 12, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), playerBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 582);
}

void main_play_game_with_bot()
{
    Init(&l);
    loadTuFile(fileIn, &l); // do bai tu file vao dslk
    inPutStack(&s, l);
    //**********************************************************************************
    hand_size = 7;
    inPutL1(&s, &l1);
    draw_hand(playerBox);

    enemy_size = 7;
    inPutL1(&s, &l2);
    draw_enemyCards();

    InitStack(&s1);

    up_card = pop(&s);
    int id = up_card.id;
    push2(&s1, up_card);
    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);

    //******vào lượt người chơi:

    // check_up_card(next_user_id);//cho người và máy
    //xử lý +2 | +4 | mất lượt | chuyển màu | xoay vòng
    check_up_card(&l1, &hand_size);

    // char result[256] = "";
    // ITOA(l1, result);
    // printf("\nresult = %s", result);

    // khoiPhuc0(&yyy, result);
    // show(l1);
    // printf("\n=== NGUOI DANH ===");
    // nguoiDanh(&l1, &s1, &idUser, &id, &t, &hand_size, &mau, &chonMau);

    // while (hand_size != 0 && enemy_size != 0) {
    // 	if (idUser == 1) {
    // 		printf("\n=== NGUOI DANH ===");
    // 		nguoiDanh(&l1, &s1, &idUser, &id, &t, &hand_size, &mau, &chonMau);
    // 		printf("\nnguoi con lai %d con bai", hand_size);
    // 	}
    // 	else {
    // 		mayDanh(&l2, &s1, &idUser, &id, &t, &enemy_size, &mau, &chonMau);
    // 		printf("\nmay con lai %d con bai", enemy_size);
    // 	}
    // }
    // if (hand_size == 0) {
    // 	printf("\nnguoi thang");

    // }
    // else {
    // 	printf("\nmay thang");
    // }

    // giaiPhong(&l1);
    // giaiPhong(&l2);
    // giaiPhong(&yyy);

    //******************************************************************************************

    // choiVoiMay(&yyy, &l1, &l2, &s1);
}