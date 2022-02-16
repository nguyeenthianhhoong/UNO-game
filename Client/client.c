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
#define BUFF_SIZE 80


int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     printf("Wrong num of arguments!\n");
    //     printf("correct syntax: \"client <IP address> <Port number> \"\n");
    //     return 1;
    // }
    char *hostname = "192.168.0.43";
    int sockfd, rcvBytes, sendBytes;
    int choice, choice1;
    socklen_t len;
    char buff[BUFF_SIZE + 1];
    char buff2[BUFF_SIZE + 1];
    char buff3[BUFF_SIZE + 1];

    struct sockaddr_in servaddr;
    inet_pton(AF_INET, hostname, &servaddr.sin_addr);
    // if (inet_pton(AF_INET, hostname, &servaddr.sin_addr) <= 0)
    // {
    //     printf("[%s] is a invalid IP address\n", hostname);
    //     exit(1);
    // }
    // if (atoi(argv[2]) < 0 && atoi(argv[2]) > 65535)
    // {
    //     printf("[%s] is a invalid Port number\n", argv[2]);
    //     exit(1);
    // }
    
    //Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        return 0;
    }

    // Step2: Specify server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = inet_addr(hostname);

    // Step3: Request to connect server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
    {
        displayDisconnectToServer(argc,argv);
    }else{
         // GTK
        app(argc,argv,sockfd);
    }

    close(sockfd);
    return 1;
}
