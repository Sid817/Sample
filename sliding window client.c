#include <netdb.h>
#include <unistd.h> 
#include <fcntl.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX 100
#define PORT 8080
#define SA struct sockaddr
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[100], str[100];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket not created\n");
        exit(0);
    }
    printf("Socket created\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed\n");
        exit(0);
    }
    char name[30], id[10], loan[20];
    int ws;
    printf("connected to the server \n");
    printf("Types of Loans : ");
    printf("\nHousing\nEducation\nVehicle\n");
    printf("\nEnter the customer name : ");
    scanf("%s", name);
    getchar();
    printf("\nEnter the customer id : ");
    scanf("%s", id);
    printf("\nEnter the type of loan : ");
    scanf("%s", loan);
    printf("\nEnter the window size : ");
    scanf("%d", &ws);
    int i = 0, k;
    int l, chk;
    l = strlen(name);
    for (k = 0; k < l; k++)
        buff[i++] = name[k];
    chk = l % ws;
    if (chk > 0)
    {
        chk = ws - chk;
        while (chk > 0)
        {
            buff[i++] = '$';
            chk--;
        }
    }
    //.....................
    l = strlen(id);
    for (k = 0; k < l; k++)
        buff[i++] = id[k];
    chk = l % ws;
    if (chk > 0)
    {
        chk = ws - chk;
        while (chk > 0)
        {
            buff[i++] = '$';
            chk--;
        }
    }

    l = strlen(loan);
    for (k = 0; k < l; k++)
        buff[i++] = loan[k];
    chk = l % ws;
    if (chk > 0)
    {
        chk = ws - chk;
        while (chk > 0)
        {
            chk--;
            buff[i++] = '$';
        }
    }
    buff[i] = '\0';
    char si[20], ans[20], fin[10];
    sprintf(si, "%d", ws);
    send(sockfd, si, sizeof(si), 0);
    int flag = -1;
    i = 0;
    while (i < strlen(buff))
    {
        send(sockfd, &buff[i], ws, 0);
        i = i + ws;
        recv(sockfd, ans, sizeof(ans), 0);
        if (strcmp(ans, "noack") == 0)
        {
            printf("No Acknowledgement Received..\n");
            flag = i;
        }
        else
            printf("Acknowledgement Recieved..\n");
        if (i == strlen(buff) && flag != -1)
        {
            i = flag;
            flag = -1;
        }
    }
    strcpy(fin, "exit");
    send(sockfd, fin, sizeof(fin), 0);
    close(sockfd);
}
