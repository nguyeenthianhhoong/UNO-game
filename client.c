#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include "uno.h"
#include "interface.h"
// #include "structData.h"
#define BUFF_SIZE 80



int menu()
{
    int choice;
    do
    {
        printf("\n--------------------------\n");
        printf("1. Đăng nhập\n");
        printf("2. Đăng ký\n");
        printf("3. Thoát\n");
        printf("--------------------------\nYour choice: ");
        scanf("%d", &choice);
    } while (choice < 1 && choice > 3);
    return choice;
}

int main_menu()
{
    int choice;
    do
    {
        printf("1. Chơi\n");
        printf("2. Xếp hạng\n");
        printf("3. Đăng xuất\n");
        printf("--------------------------\nYour choice: ");
        scanf("%d", &choice);
    } while (choice < 1 && choice > 3);
    return choice;
}

// void trim(char s[])
// {
//     int i = strlen(s);
//     while (s[0] == ' ')
//     {
//         for (int j = 0; j < i; j++)
//             s[j] = s[j + 1];
//         i--;
//     }
//     while (s[i - 1] == ' ' || s[i - 1] == '\n')
//         i--;
//     s[i] = '\0';
// }

// int checkSpace(char s[])
// {
//     for (int i = 0; i < strlen(s); i++)
//     {
//         if (s[i] == ' ')
//             return 1;
//     }
//     return 0;
// }

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong num of arguments!\n");
        printf("correct syntax: \"client <IP address> <Port number> \"\n");
        return 1;
    }
    int sockfd, rcvBytes, sendBytes;
    int choice, choice1;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    char buff2[BUFF_SIZE + 1];
    char buff3[BUFF_SIZE + 1];
    // LIST l, l1, l2;
    // STACK s, s1;
    // Init(&l);
    // loadTuFile(fileIn, &l);
    // inPutStack(&s, l);
    // user *username = (user *)malloc(sizeof(user));
    // Init(&username->l);

    //char SERV_ADDR[50];
    struct sockaddr_in servaddr;
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("[%s] is a invalid IP address\n", argv[1]);
        exit(1);
    }
    if (atoi(argv[2]) < 0 && atoi(argv[2]) > 65535)
    {
        printf("[%s] is a invalid Port number\n", argv[2]);
        exit(1);
    }
    
    // may(&s, &s1, &l1, &l2);
    //Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    // Step2: Specify server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    // Step3: Request to connect server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
    {
        printf("\nError! Can not connect to sever! ");
        return 0;
    }
    
    // GTK
    app(argc,argv,sockfd);

    
    close(sockfd);
    return 1;
}