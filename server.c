#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "uno.h"
#define BUFF_SIZE 100
#define BACKLOG 1 //number of pending connections in queue

typedef struct account
{
    char username[30];
    char password[30];
    int number;
    int number_win;
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
        fscanf(f, "%s %s %d %d\n", acc.username, acc.password, &acc.number, &acc.number_win);
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
        fprintf(f, "%s %s %d %d\n", tmp->acc.username, tmp->acc.password, tmp->acc.number, tmp->acc.number_win);
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

    LIST l, l1, l2;
    STACK s, s1;

    // đọc file, xáo bài
    //printf("hi\n");
    Init(&l);
    //Init(l1);
    printf("hi\n");
    loadTuFile(fileIn, &l);

    //printf("hi\n");

    int listen_sock, conn_sock;
    int rcvBytes, sendBytes;
    int is_login = 0;
    socklen_t len;
    char buff[1000];
    char username[30], password[30], confirm_pass[30];
    char *str;
    struct sockaddr_in servaddr, cliaddr;
    //
    int selectfd, maxfd, maxi = -1;
    int nready, client[FD_SETSIZE];
    fd_set readfds, allset;

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

    printf("Server started\n");

    //Step 4: Communicate with client
    for (;;)
    {

        len = sizeof(cliaddr);
        if ((conn_sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &len)) == -1)
        {
            perror("\nError: ");
        }
        printf("You got a connection from %s\n", inet_ntoa(cliaddr.sin_addr));
        while (1)
        {
            rcvBytes = recv(conn_sock, buff, sizeof(buff), 0);
            if (rcvBytes < 0)
            {
                perror("Error: ");
                return 0;
            }
            buff[rcvBytes] = '\0';

            if (is_login == 0)
            {
                if (strcmp(buff, "1") == 0)
                {
                    strcpy(buff, "ĐĂNG NHẬP");
                    send(conn_sock, buff, strlen(buff), 0);
                    while (1)
                    {
                        rcvBytes = recv(conn_sock, buff, sizeof(buff), 0);
                        if (rcvBytes < 0)
                        {
                            perror("Error: ");
                            return 0;
                        }
                        buff[rcvBytes] = '\0';
                        str = strtok(buff, " ");
                        strcpy(username, str);
                        str = strtok(NULL, " ");
                        strcpy(password, str);
                        printf("%s %s\n", username, password);
                        node *tmp = checkUsername(username);
                        if (tmp == NULL)
                        {
                            strcpy(buff, "Tài khoản không tồn tại");
                            printf("%s\n", buff);
                            send(conn_sock, buff, strlen(buff), 0);
                            continue;
                        }
                        else
                        {
                            if (strcmp(tmp->acc.password, password) == 0)
                            {
                                strcpy(buff, "OK");
                                //bonus
                                //player = newUser(tmp->acc);
                                printf("%s\n", buff);
                                send(conn_sock, buff, strlen(buff), 0);
                                strcpy(userSignedIn, username);
                                is_login = 1;
                                break;
                            }
                            else
                            {
                                strcpy(buff, "Mật khẩu không đúng");
                                printf("%s\n", buff);
                                send(conn_sock, buff, strlen(buff), 0);
                            }
                        }
                    }
                }
                else if (strcmp(buff, "2") == 0)
                {
                    account acc;
                    strcpy(buff, "ĐĂNG KÝ");
                    send(conn_sock, buff, strlen(buff), 0);
                    while (1)
                    {
                        rcvBytes = recv(conn_sock, buff, sizeof(buff), 0);
                        if (rcvBytes < 0)
                        {
                            perror("Error: ");
                            return 0;
                        }
                        buff[rcvBytes] = '\0';
                        str = strtok(buff, " ");
                        strcpy(acc.username, str);
                        str = strtok(NULL, " ");
                        strcpy(acc.password, str);
                        str = strtok(NULL, " ");
                        strcpy(confirm_pass, str);

                        if (checkUsername(acc.username) != NULL)
                        {
                            strcpy(buff, "Tài khoản đã tồn tại");
                            printf("%s\n", buff);
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                        else if (strcmp(acc.password, confirm_pass) == 0)
                        {
                            strcpy(buff, "OK");
                            printf("%s\n", buff);
                            acc.number = 0;
                            acc.number_win = 0;
                            addAccount(acc);
                            writeFile();
                            send(conn_sock, buff, strlen(buff), 0);
                            break;
                        }
                        else
                        {
                            strcpy(buff, "Mật khẩu không đúng");
                            printf("%s\n", buff);
                            send(conn_sock, buff, strlen(buff), 0);
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            if (is_login == 1) // signed in
            {
                if (strcmp(buff, "1") == 0)
                {
                    strcpy(buff, "Let's play!!!!!\n");
                    send(conn_sock, buff, strlen(buff), 0); //send bài người chơi
                    //show(l1);
                }
                else if (strcmp(buff, "2") == 0)
                { // xem rank
                }
                else
                { //đăng xuất
                }
            }
        }
        printf("bye\n");
        close(conn_sock);
        break;
    }
    close(listen_sock);
    return 1;
}
