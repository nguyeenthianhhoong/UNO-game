#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
//#include <pthread.h>
#include "../unoStruct/uno.h"
#include "../unoStruct/object.h"
#define BUFF_SIZE 100
#define SIZE 1024
#define BACKLOG 10 //number of pending connections in queue

typedef room room;

typedef struct node_room
{
    room room;
    struct node_room *next;
} node_room;

typedef struct node_room node_room;
node_room *root_r, *cur_r;

node_room *makeNewNode_room(room r)
{
    node_room *new = (node_room *)malloc(sizeof(node_room));
    new->room = r;
    new->next = NULL;
    return new;
}

void addRoom(room r)
{ //at end
    node_room *new = makeNewNode_room(r);
    if (root_r == NULL)
    {
        root_r = new;
    }
    else
    {
        cur_r = root_r;
        while (cur_r->next != NULL)
        {
            cur_r = cur_r->next;
        }
        cur_r->next = new;
    }
}

node_room *check_full_room()
{
    node_room *tmp = root_r;
    while (tmp != NULL)
    {
        if (tmp->room.sockfd1.sock != -1 && tmp->room.sockfd2.sock == -1)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

node_room *checkRoomID(int id)
{
    node_room *tmp = root_r;
    while (tmp != NULL)
    {
        if (tmp->room.id == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void destroy_waiting_room()
{
    node_room *tmp = root_r;
    while (tmp != NULL)
    {
        if (tmp->room.sockfd1.sock != -1 && tmp->room.sockfd2.sock == -1)
        {
            free(tmp);
        }
        tmp = tmp->next;
    }
}

void destroy_room(int id)
{
    node_room *tmp = root_r;
    while (tmp != NULL)
    {
        if (tmp->room.id == id)
        {
            free(tmp);
            return;
        }
        tmp = tmp->next;
    }
}

void displayRoom()
{
    node_room *tmp = root_r;
    while (tmp != NULL)
    {
        tmp = tmp->next;
    }
}

///////////////////////////////////////////////////////

typedef struct account
{
    char username[30];
    char password[30];
    int number;
    int number_win;
    int isLogin;
} account;

typedef account account;

typedef struct node
{
    account acc;
    struct node *next;
} node;

typedef struct node node;
node *root, *cur;

char userSignedIn[30];

node *makeNewNode(account acc)
{
    node *new = (node *)malloc(sizeof(node));
    new->acc = acc;
    new->next = NULL;
    return new;
}

void addAccount(account acc)
{ //at end
    node *new = makeNewNode(acc);
    if (root == NULL)
    {
        root = new;
    }
    else
    {
        cur = root;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new;
    }
}

void readFile(FILE *f)
{
    account acc;
    while (!feof(f))
    {
        fscanf(f, "%s %s %d %d %d\n", acc.username, acc.password, &acc.number_win, &acc.number, &acc.isLogin);
        acc.isLogin = 0;
        addAccount(acc);
    }
    fclose(f);
}

void writeFile()
{
    FILE *f;
    node *tmp = root;
    f = fopen("../src/account.txt", "w");
    while (tmp != NULL)
    {
        fprintf(f, "%s %s %d %d %d\n", tmp->acc.username, tmp->acc.password, tmp->acc.number_win, tmp->acc.number, tmp->acc.isLogin);
        tmp = tmp->next;
    }
    fclose(f);
}

void writeFileRank()
{
    FILE *f;
    f = fopen("../src/rank.txt", "w");

    int i = 0;
    int preScore;
    int newUser = 0;
    int rankcount = i + 1;
    for (node *pTmp = root; pTmp != NULL; pTmp = pTmp->next, i++)
    {
        int score = pTmp->acc.number_win * 4 - pTmp->acc.number * 1;
        if (score == 0 && pTmp->acc.number == 0)
        {
            newUser++;
            continue;
        }
        if (i == 0)
        {
            preScore = score;
        }
        else if (score != preScore)
        {
            preScore = score;
            rankcount = i + 1 - newUser;
        }
        fprintf(f, "%d %s %d %d %d\n", rankcount, pTmp->acc.username, score, pTmp->acc.number_win, pTmp->acc.number);
    }
    fclose(f);
}

void sortRank()
{
    for (node *pTmp = root; pTmp->next != NULL; pTmp = pTmp->next)
    {
        for (node *pTmp2 = pTmp->next; pTmp2 != NULL; pTmp2 = pTmp2->next)
        {
            int preScore = pTmp->acc.number_win * 4 - pTmp->acc.number * 1;
            int score = pTmp2->acc.number_win * 4 - pTmp2->acc.number * 1;
            if (preScore < score)
            {
                account tmp = pTmp->acc;
                pTmp->acc = pTmp2->acc;
                pTmp2->acc = tmp;
            }
        }
    }
    writeFileRank();
}

void send_file_ranktxt(FILE *fp, int sockfd)
{
    int n;
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
    memset(data, strlen(data), 0);
    strcpy(data, "end");
    send(sockfd, data, sizeof(data), 0);
}

node *checkUsername(char username[])
{
    node *tmp = root;
    while (tmp != NULL)
    {
        if (strcmp(tmp->acc.username, username) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     printf("Wrong num of arguments!\n");
    //     printf("correct syntax: \"server <Port number> \"\n");
    //     return 1;
    // }
    FILE *f;
    f = fopen("../src/account.txt", "r");
    if (f == NULL)
    {
        printf("Can't open file account.txt\n");
        return 0;
    }
    readFile(f);

    int listen_sock, conn_sock;
    int rcvBytes, sendBytes;
    socklen_t len;
    char buff[1000];
    char *str;
    struct sockaddr_in servaddr, cliaddr;
    //
    int selectfd, maxfd, maxi = -1, i;
    int nready, client[FD_SETSIZE];
    ssize_t ret;
    fd_set readfds, allset;

    int room_id = 1;

    node *tmp = (node *)malloc(sizeof(node));
    node_room *tmp1 = (node_room *)malloc(sizeof(node_room));

    ////
    Init(&l);
    loadTuFile(fileIn, &l); // do bai tu file vao dslk

    // if (atoi(argv[1]) < 0 && atoi(argv[1]) > 65535)
    // {
    //     printf("[%s] is a invalid Port number\n", argv[1]);
    //     exit(1);
    // }

    //Step 1: Construct socket
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    //Step 2: Bind address to socket
    char *hostname = "192.168.0.43";
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(hostname);
    servaddr.sin_port = htons(8080);

    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("Error: ");
        return 0;
    }

    //Step 3: Listen request from client
    if (listen(listen_sock, BACKLOG) == -1)
    { /* calls listen() */
        perror("\nError: ");
        return 0;
    }

    //pthread_t tid;

    maxfd = listen_sock; /* initialize */
    maxi = -1;           /* index into client[] array */
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1; /* -1 indicates available entry */

    FD_ZERO(&allset);
    FD_ZERO(&readfds);
    FD_SET(listen_sock, &allset);

    printf("Server started\n");

    //Step 4: Communicate with client
    for (;;)
    {
        readfds = allset; /* structure assignment */
        nready = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (nready < 0)
        {
            perror("\nError: ");
            break;
        }
        if (FD_ISSET(listen_sock, &readfds))
        {
            len = sizeof(cliaddr);
            if ((conn_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &len)) < 0)
                perror("\nError: ");
            else
            {
                // printf("You got a connection from %d\n", conn_sock); /* prints client's IP */
                for (i = 0; i < FD_SETSIZE; i++)
                    if (client[i] < 0)
                    {
                        client[i] = conn_sock; /* save descriptor */
                        break;
                    }
                if (i == FD_SETSIZE)
                {
                    printf("\nToo many clients");
                    close(conn_sock);
                }
                FD_SET(conn_sock, &allset); /* add new descriptor to set */
                if (conn_sock > maxfd)
                    maxfd = conn_sock; /* for select */
                if (i > maxi)
                    maxi = i; /* max index in client[] array */

                if (--nready <= 0)
                    continue; /* no more readable descriptors */
            }
        }
        for (i = 0; i <= maxi; i++)
        { /* check all clients for data */
            if ((conn_sock = client[i]) < 0)
                continue;
            if (FD_ISSET(conn_sock, &readfds))
            {
                Client *c = (Client *)malloc(sizeof(Client));

                rcvBytes = recv(conn_sock, c, sizeof(Client), 0);
                if (rcvBytes < 0)
                {
                    perror("Error: ");
                    return 0;
                }
                memset(buff, 0, strlen(buff));
                switch (c->signal)
                {
                case LOGIN:
                    tmp = checkUsername(c->login.username);
                    if (tmp == NULL)
                    {
                        strcpy(buff, "Tài khoản không tồn tại");
                        send(conn_sock, buff, strlen(buff), 0);
                    }
                    else if (tmp->acc.isLogin == 1)
                    {
                        strcpy(buff, "Tài khoản đã đăng nhập");
                        send(conn_sock, buff, strlen(buff), 0);
                    }
                    else
                    {

                        if (strcmp(tmp->acc.password, c->login.password) == 0)
                        {
                            strcpy(buff, "OK");
                            tmp->acc.isLogin = 1;
                            writeFile();
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                        else
                        {
                            strcpy(buff, "Mật khẩu không đúng");
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                    }
                    break;

                case SIGNUP:
                    if (checkUsername(c->signup.username) != NULL)
                    {
                        strcpy(buff, "Tài khoản đã tồn tại");
                        send(conn_sock, buff, strlen(buff), 0);
                    }
                    else
                    {
                        if (strcmp(c->signup.password, c->signup.confirm_password) == 0)
                        {
                            strcpy(buff, "OK");
                            account acc;
                            strcpy(acc.username, c->signup.username);
                            strcpy(acc.password, c->signup.password);
                            acc.number = 0;
                            acc.number_win = 0;
                            acc.isLogin = 0;
                            addAccount(acc);
                            writeFile();
                            send(conn_sock, buff, strlen(buff), 0);
                            //break;
                        }
                        else
                        {
                            strcpy(buff, "Mật khẩu không đúng");
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                    }
                    break;

                case PLAY_WITH_BOT:
                    tmp = checkUsername(c->login.username);
                    tmp->acc.number++;
                    if (c->play_with_bot.id_player == 1)
                    {
                        tmp->acc.number_win++;
                    }
                    writeFile();
                    break;

                case ADD_ROOM:
                    printf(" ");
                    send_room *send_r = (send_room *)malloc(sizeof(send_room));
                    tmp1 = check_full_room();
                    if (tmp1 == NULL)
                    {
                        room r;
                        r.id = room_id;
                        r.sockfd1.sock = conn_sock;
                        r.sockfd2.sock = -1;
                        r.id_player = -1;
                        strcpy(r.sockfd1.name, c->login.username);
                        addRoom(r);
                        sprintf(send_r->messages, "Room %d. Please wait another person", r.id);
                        send(conn_sock, send_r, sizeof(send_room), 0);
                    }
                    else
                    {

                        tmp1->room.sockfd2.sock = conn_sock;
                        tmp1->room.id_player = tmp1->room.sockfd1.sock;
                        send_r->id_room = room_id;
                        strcpy(tmp1->room.sockfd2.name, c->login.username);
                        strcpy(send_r->name, tmp1->room.sockfd2.name);
                        inPutStack(&s, l);
                        inPutL1(&s, &l1);
                        sprintf(send_r->messages, "OK..Room %d. You(%d) will play with %s", tmp1->room.id, tmp1->room.sockfd1.sock, tmp1->room.sockfd2.name);
                        ITOA(l1, send_r->list);
                        send(tmp1->room.sockfd1.sock, send_r, sizeof(send_room), 0);
                        c->play_with_person.id_room = tmp1->room.id;
                        c->play_with_person.id_player = 0;
                        int up_card = getCardFromStack(1, &s);
                        c->play_with_person.id_bai = 3; //todo
                        c->play_with_person.color = 'z';
                        c->play_with_person.bai_phat = 1;
                        c->play_with_person.played = 1;
                        c->play_with_person.so_luong_bai = 7;
                        send(tmp1->room.sockfd1.sock, &c->play_with_person, sizeof(Play_With_Person), 0);

                        inPutL1(&s, &l2);
                        sprintf(send_r->messages, "OK..Room %d. You(%d) will play with %s", tmp1->room.id, tmp1->room.sockfd2.sock, tmp1->room.sockfd1.name);
                        ITOA(l2, send_r->list);
                        strcpy(send_r->name, tmp1->room.sockfd1.name);
                        send(tmp1->room.sockfd2.sock, send_r, sizeof(send_room), 0);
                        c->play_with_person.id_player = 1;
                        send(tmp1->room.sockfd2.sock, &c->play_with_person, sizeof(Play_With_Person), 0);
                        room_id++;
                    }
                    break;

                // so_luong_bai  |  played
                // 0 | 1 -> thắng -> gửi client -2 -> break
                //
                //-1 -> thua do thoát | client kia bằng 0 | 0 -> break;
                //
                case PLAY_WITH_PERSON:
                    tmp1 = checkRoomID(c->play_with_person.id_room);
                    if (c->play_with_person.played == -3)
                    {
                        tmp = checkUsername(c->login.username);
                        tmp->acc.number++;
                        writeFile();
                    }
                    //**
                    else if (conn_sock == tmp1->room.id_player)
                    {
                        if (c->play_with_person.played == -4)
                        {
                            tmp = checkUsername(c->login.username);
                            tmp->acc.number++;
                            tmp->acc.number_win++;
                            writeFile();
                            displayRoom();
                            break;
                        }
                        else if (c->play_with_person.so_luong_bai == -2)
                        {
                            tmp = checkUsername(c->login.username);
                            tmp->acc.number++;
                            writeFile();
                            break;
                        }
                        else if (c->play_with_person.so_luong_bai == 0 && c->play_with_person.played == 1)
                        {
                            tmp = checkUsername(c->login.username);
                            tmp->acc.number++;
                            tmp->acc.number_win++;
                            writeFile();
                        }
                    }

                    if (conn_sock == tmp1->room.sockfd1.sock)
                    {
                        send(tmp1->room.sockfd2.sock, &c->play_with_person, sizeof(Play_With_Person), 0);
                        tmp1->room.id_player = tmp1->room.sockfd2.sock;
                    }
                    else
                    {
                        send(tmp1->room.sockfd1.sock, &c->play_with_person, sizeof(Play_With_Person), 0);
                        tmp1->room.id_player = tmp1->room.sockfd1.sock;
                    }

                    break;
                case VIEW_RANK:
                    sortRank();
                    sprintf(buff, "OK");
                    send(conn_sock, buff, strlen(buff), 0);
                    sleep(0.01);
                    FILE* fp;
                    fp = fopen("../src/rank.txt", "r");
                    if (fp == NULL)
                    {
                        perror("[-]Error in reading file.");
                        return 0;
                    }
                    send_file_ranktxt(fp, conn_sock);
                
                    break;

                case LOGOUT:
                    tmp = checkUsername(c->login.username);
                    tmp->acc.isLogin = 0;
                    writeFile();
                    sprintf(buff, "bye %s", c->login.username);
                    send(conn_sock, buff, strlen(buff), 0);
                    break;

                case LEAVE_ROOM:
                    tmp1 = check_full_room();
                    tmp1->room.sockfd2.sock = 0;
                    break;
                }
                free_obj(c);
            }

        }
    }
    close(conn_sock);
    close(listen_sock);
    return 1;
}
