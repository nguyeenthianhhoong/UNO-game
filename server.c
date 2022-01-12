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
//#include "uno.h"
#include "object.h"
#define BUFF_SIZE 100
#define BACKLOG 10 //number of pending connections in queue

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

// //
// user *newUser(account acc){
//     user *new = (node *)malloc(sizeof(user));
//     new->acc = acc;
//     Init(&new->l);
//     return new;
// }

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
        addAccount(acc);
    }
    fclose(f);
}

void writeFile()
{
    FILE *f;
    node *tmp = root;
    f = fopen("account.txt", "w");
    while (tmp != NULL)
    {
        fprintf(f, "%s %s %d %d %d\n", tmp->acc.username, tmp->acc.password, tmp->acc.number_win, tmp->acc.number, tmp->acc.isLogin);
        tmp = tmp->next;
    }
    fclose(f);
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
/*
void *client_handler(void *arg)
{
    int clientfd;
    int sendBytes, rcvBytes;
    char buff[BUFF_SIZE];
    node *tmp = (node *)malloc(sizeof(node));
    pthread_detach(pthread_self());
    clientfd = *((int *)arg);
    while (1)
    {
        Client *c = (Client *)malloc(sizeof(Client));
        rcvBytes = recv(clientfd, c, sizeof(Client), 0);
        if (rcvBytes < 0)
        {
            perror("Error: ");
            return 0;
        }

        switch (c->signal)
        {
        case LOGIN:
            printf("------------LOGIN------------\n");
            tmp = checkUsername(c->login.username);
            if (tmp == NULL)
            {
                strcpy(buff, "Tài khoản không tồn tại");
                printf("%s\n", buff);
                send(clientfd, buff, strlen(buff), 0);
                //continue;
            }
            else if (tmp->acc.isLogin == 1)
            {
                strcpy(buff, "Tài khoản đã đăng nhập");
                printf("%s\n", buff);
                send(clientfd, buff, strlen(buff), 0);
                //continue;
            }
            else
            {
                
                if (strcmp(tmp->acc.password, c->login.password) == 0)
                {
                    strcpy(buff, "OK");
                    printf("%s\n", buff);
                    tmp->acc.isLogin = 1;
                    writeFile();
                    send(clientfd, buff, strlen(buff), 0);
                    // strcpy(userSignedIn, username);
                    // is_login = 1;
                    //break;
                }
                else
                {
                    strcpy(buff, "Mật khẩu không đúng");
                    printf("%s\n", buff);
                    send(clientfd, buff, strlen(buff), 0);
                }
            }
            break;

        case SIGNUP:
            printf("------------SIGN UP------------\n"); 
            //tmp = checkUsername(c->signup.username);
            if (checkUsername(c->signup.username) != NULL)
            {
                strcpy(buff, "Tài khoản đã tồn tại");
                printf("%s\n", buff);
                send(clientfd, buff, strlen(buff), 0);
                //continue;
            }
            else
            {
                if (strcmp(c->signup.password, c->signup.confirm_password) == 0)
                {
                    strcpy(buff, "OK");
                    printf("%s\n", buff);
                    account acc;
                    strcpy(acc.username, c->signup.username);
                    strcpy(acc.password, c->signup.password);
                    acc.number = 0;
                    acc.number_win = 0;
                    acc.isLogin = 0;
                    addAccount(acc);
                    writeFile();
                    send(clientfd, buff, strlen(buff), 0);
                    //break;
                }
                else
                {
                    strcpy(buff, "Mật khẩu không đúng");
                    printf("%s\n", buff);
                    send(clientfd, buff, strlen(buff), 0);
                }
            }
            break;

        case PLAY_WITH_BOT:
            printf("------------PLAY WITH BOT------------\n");
            //printf("%s\n", tmp->acc.username);
            tmp->acc.number++;
            if (c->play_with_bot.id_player == 1)
            {
                tmp->acc.number_win++;
            }
            writeFile();
            break;

        case PLAY_WITH_PERSON:

            break;

        case VIEW_RANK:

            break;

        case LOGOUT:
            printf("------------LOGOUT------------\n");
            //tmp = checkUsername(c->login.username);
            printf("%s\n", tmp->acc.username);
            tmp->acc.isLogin = 0;
            writeFile();
            sprintf(buff, "bye %s", c->login.username);
            printf("%s\n", buff);
            send(clientfd, buff, strlen(buff), 0);
            break;

            free_obj(c);
            // default:
            //     break;
            // }
        }

        //break;
    }
    close(clientfd);
}
*/
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong num of arguments!\n");
        printf("correct syntax: \"server <Port number> \"\n");
        return 1;
    }
    FILE *f;
    f = fopen("account.txt", "r");
    if (f == NULL)
    {
        printf("Can't open file account.txt\n");
        return 0;
    }
    readFile(f);

    // LIST l, l1, l2;
    // STACK s, s1;

    // Init(&l);
    // printf("hi\n");
    // loadTuFile(fileIn, &l);

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

    node *tmp = (node *)malloc(sizeof(node));

    if (atoi(argv[1]) < 0 && atoi(argv[1]) > 65535)
    {
        printf("[%s] is a invalid Port number\n", argv[1]);
        exit(1);
    }

    //Step 1: Construct socket
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    //Step 2: Bind address to socket
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
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

    maxfd = listen_sock;
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
                printf("You got a connection from %s\n", inet_ntoa(cliaddr.sin_addr)); /* prints client's IP */
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

                switch (c->signal)
                {
                case LOGIN:
                    printf("------------LOGIN------------\n");
                    tmp = checkUsername(c->login.username);
                    if (tmp == NULL)
                    {
                        strcpy(buff, "Tài khoản không tồn tại");
                        printf("%s\n", buff);
                        send(conn_sock, buff, strlen(buff), 0);
                        //continue;
                    }
                    else if (tmp->acc.isLogin == 1)
                    {
                        strcpy(buff, "Tài khoản đã đăng nhập");
                        printf("%s\n", buff);
                        send(conn_sock, buff, strlen(buff), 0);
                        //continue;
                    }
                    else
                    {

                        if (strcmp(tmp->acc.password, c->login.password) == 0)
                        {
                            strcpy(buff, "OK");
                            printf("%s\n", buff);
                            tmp->acc.isLogin = 1;
                            writeFile();
                            send(conn_sock, buff, strlen(buff), 0);
                            // strcpy(userSignedIn, username);
                            // is_login = 1;
                            //break;
                        }
                        else
                        {
                            strcpy(buff, "Mật khẩu không đúng");
                            printf("%s\n", buff);
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                    }
                    break;

                case SIGNUP:
                    printf("------------SIGN UP------------\n");
                    //tmp = checkUsername(c->signup.username);
                    if (checkUsername(c->signup.username) != NULL)
                    {
                        strcpy(buff, "Tài khoản đã tồn tại");
                        printf("%s\n", buff);
                        send(conn_sock, buff, strlen(buff), 0);
                        //continue;
                    }
                    else
                    {
                        if (strcmp(c->signup.password, c->signup.confirm_password) == 0)
                        {
                            strcpy(buff, "OK");
                            printf("%s\n", buff);
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
                            printf("%s\n", buff);
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                    }
                    break;

                case PLAY_WITH_BOT:
                    printf("------------PLAY WITH BOT------------\n");
                    //printf("%s\n", tmp->acc.username);
                    tmp = checkUsername(c->login.username);
                    tmp->acc.number++;
                    if (c->play_with_bot.id_player == 1)
                    {
                        tmp->acc.number_win++;
                    }
                    writeFile();
                    break;

                case PLAY_WITH_PERSON:

                    break;

                case VIEW_RANK:

                    break;

                case LOGOUT:
                    printf("------------LOGOUT------------\n");
                    tmp = checkUsername(c->login.username);
                    printf("%s\n", tmp->acc.username);
                    tmp->acc.isLogin = 0;
                    writeFile();
                    sprintf(buff, "bye %s", c->login.username);
                    printf("%s\n", buff);
                    send(conn_sock, buff, strlen(buff), 0);
                    break;

                }
                free_obj(c);


            }

            // len = sizeof(cliaddr);
            // if ((conn_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &len)) == -1)
            // {
            //     perror("\nError: ");
            // }
            // printf("You got a connection from %s\n", inet_ntoa(cliaddr.sin_addr));
            //pthread_create(&tid, NULL, &client_handler, (void *)&conn_sock);
        }
    }
    close(conn_sock);
    close(listen_sock);
    return 1;
}
