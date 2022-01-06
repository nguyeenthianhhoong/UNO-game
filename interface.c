#include "interface.h"

#define BUFF_SIZE 80

const int WINDOW_WIDTH = 1140;
const int WINDOW_HEIGHT = 700;
const float CARD_WIDTH = 55;
const float CARD_HEIGHT = 85;

const int PLAYER = 1;
const int ENEMY = 2;
const int OTHER = 3;

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

GtkWidget *playerNotificationBox;
GtkWidget *enemyNotificationBox;

GtkWidget *bgColorSquare; // background
GtkWidget *colorSquare;

GtkWidget *winDialog;
GtkWidget *loserDialog;

GtkWidget *boardWindow;
GtkWidget *boardWindowFixed;
GtkWidget *controllerBox;
GtkWidget *playerBox;
GtkWidget *enemyBox;
GtkWidget *iconON;
GtkWidget *iconOFF;
GtkWidget *chooseColorDialog;
pthread_t tid;

char buff[80];
int rcvBytes;
int sock_app;

UNO x_card = {0, 'x', -6};

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

int checkChooseColor = 0;
int notiCode;

//Check Input
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

// LOGIN SIGNIN

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
    // pthread_exit(NULL);
    gtk_main_quit();
}

void on_startGameBtn_clicked()
{
    gtk_widget_hide(mainMenuWindow);

    gtk_widget_show_all(boardWindow);

    main_play_game_with_bot();
}

//GAME BUTTON
//choose color - handle change_the_color_card
void after_chooseColor()
{
    checkChooseColor = 0;
    gtk_widget_hide(chooseColorDialog);
    gtk_window_set_accept_focus(GTK_WINDOW(boardWindow), TRUE);
    idUser = ENEMY;
    change_on_off_icon(ENEMY);
    draw_colorSquare();
    check_player_win();
}
void on_chooseRedBtn_clicked()
{
    mau = 'r';
    after_chooseColor();
}
void on_chooseGreenBtn_clicked()
{
    mau = 'g';
    after_chooseColor();
}
void on_chooseBlueBtn_clicked()
{
    mau = 'b';
    after_chooseColor();
}
void on_chooseYellowBtn_clicked()
{
    mau = 'y';
    after_chooseColor();
}

//after win|over game
void on_backToHomeBtn_clicked()
{
    gtk_widget_show(mainMenuWindow);
    gtk_widget_hide(winDialog);
    gtk_widget_hide(loserDialog);
    gtk_widget_hide(boardWindow);
}
void on_replayBtn_clicked()
{
    gtk_widget_hide(winDialog);
    gtk_widget_hide(loserDialog);
    main_play_game_with_bot();
}

//while playing games
void unoButtonClick(GtkWidget *button)
{
    if (idUser == PLAYER)
    {
        g_print("uno button click\n");
    }
}
void nextButtonClick(GtkWidget *button)
{
    if (drawCardCount == 1 && idUser == PLAYER)
    {
        drawCardCount = 0;
        idUser = ENEMY;
        change_on_off_icon(ENEMY);
    }
}
void drawCardButtonClick(GtkWidget *button)
{
    if (drawCardCount == 0 && idUser == PLAYER)
    {
        phat(1, &l1, &s);
        hand_size++;
        draw_hand(playerBox);

        NODE *p = find(l, up_card.id);
        UNO uno;
        if (CHECK(l1, up_card.id, &uno) != 1 && doiMau(l1, mau, p, t) != 1)
        {
            idUser = ENEMY;
            change_on_off_icon(ENEMY);
            return;
        }
        drawCardCount = 1;
    }
}

//handle game

void main_play_game_with_bot()
{
    Init(&l);
    loadTuFile(fileIn, &l); // do bai tu file vao dslk
    inPutStack(&s, l);
    //**********************************************************************************
    hand_size = 7;
    idUser = PLAYER;
    inPutL1(&s, &l1);
    draw_hand(playerBox);

    enemy_size = 7;
    inPutL1(&s, &l2);
    draw_enemyCards();

    up_card = pop(&s);

    //******vào lượt người chơi:

    //xử lý +2 | +4 | mất lượt | chuyển màu | xoay vòng
    if (up_card.number == -3)
    {
        t = 2;
    }
    else if (up_card.number == -5)
    {
        t = 4;
        mau = 'r';
    }
    else if (up_card.number == -4)
    {
        mau = 'r';
    }
    else if (up_card.number == -1 || up_card.number == -2)
    {
        idUser = ENEMY;
    }

    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);
    draw_colorSquare();

    if (check_up_card(&l1, &hand_size) != 1)
    {
        idUser = ENEMY;
        bot_play();
    }
}

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

//draw game
void buildUIGameWindow()
{
    boardWindow = GTK_WIDGET(gtk_builder_get_object(builder, "boardWindow"));

    g_signal_connect(boardWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // gtk_builder_connect_signals(builder, NULL);

    //add container
    boardWindowFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(boardWindow), boardWindowFixed);

    //add background of window
    GdkPixbuf *backgrndPixbuf;
    GtkWidget *backgrndImage;
    GError *error = NULL;
    backgrndPixbuf = gdk_pixbuf_new_from_file("images/background/bgB.png", &error);
    backgrndPixbuf = gdk_pixbuf_scale_simple(backgrndPixbuf, 1140, 700, GDK_INTERP_BILINEAR);
    backgrndImage = gtk_image_new_from_pixbuf(backgrndPixbuf);
    gtk_container_add(GTK_CONTAINER(boardWindowFixed), backgrndImage);

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
    char link[100];
    strcpy(link, "images/button/pile.png");
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
    g_signal_connect(drawCardButton, "event-after", G_CALLBACK(bot_play), NULL);
    //2.5 add colorSquare
    strcpy(link, "images/color/white.png");
    bgColorSquare = gtk_image_new_from_file(link);
    bgColorSquare = resize_image(bgColorSquare, link, 1);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), bgColorSquare, startWidth + CARD_WIDTH * 5, heightControllerBox + 5);
    strcpy(link, "images/color/r.png");
    colorSquare = gtk_image_new_from_file(link);
    // colorSquare = resize_image(colorSquare, link, 1);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), colorSquare, startWidth + CARD_WIDTH * 5 + 5, heightControllerBox + 10);
    //3.add next button
    strcpy(link, "images/button/next.png");
    GtkWidget *nextImage = gtk_image_new_from_file(link);
    nextImage = resize_image(nextImage, link, 0.8);
    // gtk_widget_set_size_request(nextImage, CARD_WIDTH, CARD_HEIGHT);
    GtkWidget *nextButton = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(nextButton), TRUE);
    gtk_button_set_image(GTK_BUTTON(nextButton), nextImage);
    //add to box
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), nextButton, startWidth + CARD_WIDTH * 5, heightControllerBox + 67); //45
    g_signal_connect(nextButton, "clicked", G_CALLBACK(nextButtonClick), NULL);
    g_signal_connect(nextButton, "event-after", G_CALLBACK(bot_play), NULL);
    //4.add uno button
    strcpy(link, "images/button/uno.png");
    GtkWidget *unoImage = gtk_image_new_from_file(link);
    unoImage = resize_image(unoImage, link, 0.8);
    // gtk_widget_set_size_request(unoImage, CARD_WIDTH, CARD_HEIGHT);
    GtkWidget *unoButton = gtk_button_new();
    //add image to button
    gtk_button_set_always_show_image(GTK_BUTTON(unoButton), TRUE);
    gtk_button_set_image(GTK_BUTTON(unoButton), unoImage);
    //add to box
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), unoButton, startWidth + CARD_WIDTH * 5, heightControllerBox + 125); //115
    g_signal_connect(unoButton, "clicked", G_CALLBACK(unoButtonClick), NULL);
    //****************************************************************************************
    // iconON = gtk_image_new_from_icon_name("dialog-ok", GTK_ICON_SIZE_DND);
    strcpy(link, "images/messages/isPlay.png");
    iconON = gtk_image_new_from_file(link);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), iconON, 40, 610);

    // iconOFF = gtk_image_new_from_icon_name("dialog-close", GTK_ICON_SIZE_DND);
    strcpy(link, "images/messages/isPause.png");
    iconOFF = gtk_image_new_from_file(link);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), iconOFF, 40, 60);
    //*****************************************************************************************
    enemyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(enemyBox, CARD_WIDTH * 12, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), enemyBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 30);

    playerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_size_request(playerBox, CARD_WIDTH * 12, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), playerBox, (WINDOW_WIDTH - CARD_WIDTH * 12) / 2, 582);

    //******************************************************************
    playerNotificationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_size_request(playerNotificationBox, CARD_WIDTH * 6, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), playerNotificationBox, startWidth, heightControllerBox + CARD_HEIGHT * 2.5);

    //******************************************************************
    enemyNotificationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_size_request(enemyNotificationBox, CARD_WIDTH * 6, CARD_HEIGHT);
    gtk_fixed_put(GTK_FIXED(boardWindowFixed), enemyNotificationBox, startWidth, heightControllerBox - CARD_HEIGHT * 1.25);
}

/**
 * Draw the user's hand
 *
 */
void draw_hand(GtkWidget *container)
{
    clear_container(container);
    float sizeCard = 1;

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
    for (NODE *p = l1.pHead; p != NULL; p = p->pNext)
    {
        draw_card(container, &(p->data), PLAYER, sizeCard);
    }
    // draw the up card
    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);
    draw_colorSquare();
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
        draw_card(enemyBox, &x_card, ENEMY, sizeCard);
    }

    clear_container(controllerBox);
    draw_card(controllerBox, &up_card, OTHER, 2);
    draw_colorSquare();
    check_bot_win();
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
    // system("rm tmp.jpg");
    return image;
}

void reset_board_game()
{
    mau = 'z';
    hand_size = 0;
    enemy_size = 0;
    outPut(&s);
    giaiPhong(&l1);
    giaiPhong(&l2);
    // pthread_cancel(tid);
    // pthread_exit(NULL);
}

void check_player_win()
{
    if (hand_size == 0)
    {
        printf("player Win\n");
        gtk_widget_show(winDialog);
        gtk_window_set_accept_focus(GTK_WINDOW(boardWindow), FALSE);
        idUser = PLAYER;
        reset_board_game();
    }
}

void check_bot_win()
{
    if (enemy_size == 0)
    {
        printf("bot Win\n");
        gtk_widget_show(loserDialog);
        gtk_window_set_accept_focus(GTK_WINDOW(boardWindow), FALSE);
        idUser = ENEMY;
        reset_board_game();
    }
}

int check_up_card(LIST *xxx, int *cml) //check phạt ko đỡ đk thì phạt luôn
{
    change_on_off_icon(PLAYER);

    NODE *p = find(l, up_card.id);
    UNO uno;
    if (CHECK(*xxx, up_card.id, &uno) != 1 && doiMau(*xxx, mau, p, t) != 1)
    {
        //************** bị phat
        if ((p->data.number == -3 || p->data.number == -5) && t != 0)
        {
            printf("\n\nbi phat %d con bai\n", t);
            phat(t, xxx, &s);
            *cml += t;
            t = 0;
            draw_hand(playerBox);

            if (p->data.number == -3)
            {
                mau = p->data.color;
            }
            free(p);
            return 0;
        }
    }
    free(p);
    return 1;
}

void mayDanh(LIST *xxx, int *idUser, int *id, int *t, int *cml, char *mau, int *chonMau)
{
    int checkPlayCard = 0;
    NODE *p = find(l, *id);
    UNO uno;
    int ID = *id;
    printf("\n\n=== MAY DANH ===");
    show(*xxx);
    if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p, *t) == 1)
    {
        printf("-danhbai1-\n");
        danhBaiChoMay(xxx, id, cml, mau, t);
        up_card = timUno(l, *id);
        checkPlayCard = 1;
    }
    else
    {
        if ((up_card.number == -3 || up_card.number == -5) && *t != 0)
        {
            printf("bi phat %d con bai", *t);
            phat(*t, xxx, &s);
            *cml += *t;
            *t = 0;

            if (up_card.number == -3)
            {
                *mau = up_card.color;
            }
        }
        else
        {
            printf("\nhe thong da tu dong boc bai.");
            phat(1, xxx, &s);
            *cml += 1;

            show(*xxx);
            if (CHECK(*xxx, *id, &uno) == 1 || doiMau(*xxx, *mau, p, *t) == 1)
            {
                printf("-danhbai2-\n");
                danhBaiChoMay(xxx, id, cml, mau, t);
                up_card = timUno(l, *id);
                checkPlayCard = 1;
            }
        }
    }
    printf("done\n");
    // kiem tra xem luot danh tiep theo thuoc ve ai
    if (up_card.number == -1 && *id != ID)
    {
        *idUser = ENEMY;
        // notificationThread(1, PLAYER);
    }
    else if (up_card.number == -2 && *id != ID)
    {
        *idUser = ENEMY;
        // notificationThread(2, PLAYER);
    }
    else
    {
        if (up_card.number == -5 && checkPlayCard == 1)
        {
            // notificationThread(5, PLAYER);
        }
        else if (up_card.number == -3 && checkPlayCard == 1)
        {
            // notificationThread(3, PLAYER);
        }
        *idUser = 1;
    }
    free(p);
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

    chooseColorDialog = GTK_WIDGET(gtk_builder_get_object(builder, "chooseColorDialog"));

    winDialog = GTK_WIDGET(gtk_builder_get_object(builder, "winDialog"));
    loserDialog = GTK_WIDGET(gtk_builder_get_object(builder, "loserDialog"));

    g_signal_connect(beginWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    gtk_widget_show(beginWindow);

    gtk_main();

    giaiPhong(&l1); // giải phóng bộ nhớ
    giaiPhong(&l2);
    giaiPhong(&l);
    outPut(&s);
    // pthread_exit(NULL);
    // return 0;
    return EXIT_SUCCESS;
}

/**
 * Event handler for a card being clicked
 */
void card_clicked(GtkWidget *card_button, gpointer card_data)
{
    int pre_id = up_card.id;
    // cast generic gpointer to a card
    UNO *card = (UNO *)card_data;
    // play the card
    if (idUser == 1)
    {
        if (play(card) == 1)
        {
            if (up_card.number == -1 && up_card.id != pre_id)
            {
                idUser = PLAYER;
                // notificationThread(1, ENEMY);
            }
            else if (up_card.number == -2 && up_card.id != pre_id)
            {
                idUser = PLAYER;
                // notificationThread(2, ENEMY);
            }
            else
            {
                idUser = ENEMY;
                if (checkChooseColor != 1)
                    change_on_off_icon(ENEMY);
            }
        }
    }
}

void bot_play()
{
    if (checkChooseColor != 1 && (hand_size != 0 && enemy_size != 0))
    {
        if (idUser == ENEMY)
        {
            int id = up_card.id;
            mayDanh(&l2, &idUser, &id, &t, &enemy_size, &mau, &chonMau); //xxxsss
            printf("\n%c ---- %c-%d\n", mau, up_card.color, up_card.number);
            up_card = timUno(l, id);
            draw_enemyCards();

            if (check_up_card(&l1, &hand_size) != 1)
            {
                idUser = ENEMY;
                bot_play();
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
    NODE *p;
    NODE *r;
    int ID = card->id;
    p = find(l, up_card.id);

    r = find(l, card->id);

    if (mau != 'z')
    {
        if ((r->data.color != mau) && (r->data.color != 'k') && (r->data.number != up_card.number))
        {
            free(p);
            free(r);
            return 0;
        }
    }
    else
    {
        if (kt(p, r) != 1)
        {
            free(p);
            free(r);
            return 0;
        }
    }

    if (mau != 'z')
    {
        mau = 'z';
    }

    //kt kiểm tra cả màu hoặc số
    up_card = *card;
    //tìm uno để push vào s1
    p = find(l, ID);
    // cap nhat so quan bai bi phat
    soQuanBiPhat(p->data.number, &t);
    deleteNode(&l1, ID);
    hand_size -= 1;
    // draw the new game state
    draw_hand(playerBox);

    drawCardCount = 0;
    if (p->data.number == -4 || p->data.number == -5)
    {
        gtk_widget_show(chooseColorDialog);
        gtk_window_set_accept_focus(GTK_WINDOW(boardWindow), FALSE);
        checkChooseColor = 1;
        if (p->data.number == -5)
        {
            // notificationThread(5, ENEMY);
        }
    }
    else
    {
        if (p->data.number == -3)
        {
            // notificationThread(3, ENEMY);
        }
        check_player_win();
    }
    free(p);
    free(r);
    return 1;
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

    if (status == PLAYER)
    {
        g_signal_connect(button, "clicked", G_CALLBACK(card_clicked), card);
        g_signal_connect(button, "event-after", G_CALLBACK(bot_play), NULL);
    }
    // draw card
    gtk_box_pack_start(GTK_BOX(container), button, TRUE, FALSE, 0);

    gtk_widget_show(button);
}

void draw_colorSquare()
{
    char link[50];
    memset(link, 0, strlen(link));
    strcpy(link, "images/color/");

    int checkNoColor = 0;

    if (mau != 'z')
    {
        link[strlen(link)] = mau;
    }
    else
    {
        link[strlen(link)] = up_card.color;
        if (up_card.color == 'k')
            checkNoColor = 1;
    }

    if (checkNoColor != 1)
    {
        strcat(link, ".png");
        gtk_image_set_from_file(GTK_IMAGE(colorSquare), link);
    }
}

void change_on_off_icon(int mode)
{
    if (mode == ENEMY)
    {
        printf("luot doi thu\n");
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), iconON, 40, 60);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), iconOFF, 40, 610);
    }
    else if (mode == PLAYER)
    {
        printf("luot player\n");
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), iconON, 40, 610);
        gtk_fixed_move(GTK_FIXED(boardWindowFixed), iconOFF, 40, 60);
    }
}

void *DisplayNotification(void *noti)
{ // code == mode*10 + user
    printf("thong bao\n");
    int mode = notiCode / 10;
    int user = notiCode % 10;
    char link[100];
    switch (mode)
    {
    case 1:
        strcpy(link, "images/messages/1.png");
        break;
    case 2:
        if (user == PLAYER)
            strcpy(link, "images/messages/22.png");
        else
            strcpy(link, "images/messages/21.png");
        break;
    case 3:
        strcpy(link, "images/messages/3.png");
        break;
    case 5:
        strcpy(link, "images/messages/5.png");
        break;
    default:
        break;
    }
    GtkWidget *notificationImage;
    notificationImage = gtk_image_new_from_file(link);

    if (user == PLAYER)
    {
        gtk_box_pack_start(GTK_BOX(playerNotificationBox), notificationImage, TRUE, FALSE, 0);
        gtk_widget_show(notificationImage);
        sleep(2);
        gtk_container_remove(GTK_CONTAINER(playerNotificationBox), GTK_WIDGET(notificationImage));
    }
    else
    {
        gtk_box_pack_start(GTK_BOX(enemyNotificationBox), notificationImage, TRUE, FALSE, 0);
        gtk_widget_show(notificationImage);
        sleep(2);
        gtk_container_remove(GTK_CONTAINER(enemyNotificationBox), GTK_WIDGET(notificationImage));
    }
    return NULL;
}

void notificationThread(int mode, int user)
{
    notiCode = mode * 10 + user;
    pthread_create(&tid, NULL, DisplayNotification, (void *)&notiCode);
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
        gtk_widget_destroy(GTK_WIDGET(i->data));
    // gtk_container_remove(GTK_CONTAINER(container), GTK_WIDGET(i->data));

    // free list
    g_list_free(children);
}

//***********