#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define PORT 8080
#define BACKLOG 0
#define NCLI 5
#define MAX 100
#define SA struct sockaddr
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket not created\n");
        exit(0);
    }
    printf("Socket created\n");
    char buff[50];
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("socket not binded\n");
        exit(0);
    }
    printf("Socket binded\n");
    if (listen(sockfd, 5) != 0)
    {
        printf("listen failed\n");
        exit(0);
    }
    printf("Server listening\n");
    char si[20], ret[20];
    int ws;
    strcpy(buff, "hi");
    while (1)
    {
        int len = sizeof(cli);
        connfd = accept(sockfd, (SA *)&cli, &len);
        if (connfd < 0)
        {
            printf("Server accept failed\n");
            exit(0);
        }
        recv(connfd, si, sizeof(si), 0);
        sscanf(si, "%d", &ws);
        printf("%d\n", ws);
        while (strcmp(buff, "exit") != 0)
        {
            memset(buff, 0, sizeof(buff));
            recv(connfd, buff, sizeof(buff), 0);
            printf("%s\n", buff);
            if (strlen(buff) == ws)
                strcpy(ret, "ack");
            else
                strcpy(ret, "noack");
            send(connfd, ret, sizeof(ret), 0);
        }
    }
    wait(0);
    close(sockfd);
}
