#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<time.h>
void main(){

int s,k,len;
const  int on=1;
size_t file_size, file_size1, file_size_2;
char file_buffer[1024]="welcome", file_buffer1[1024]="Hai", file_buffer2[1024]="how are you?", buff[1024];

struct sockaddr_in servaddr, cliaddr1, cliaddr2, cliaddr3;

s = socket(AF_INET, SOCK_DGRAM,0);
perror("Socket status\n");

bzero(&servaddr, sizeof(servaddr));
servaddr.sin_port=htons(5000);
servaddr.sin_family=AF_INET;
inet_pton(AF_INET, "192.168.43.191",&servaddr.sin_addr.s_addr);

bzero(&cliaddr1, sizeof(cliaddr1));
cliaddr1.sin_port=htons(5000);
cliaddr1.sin_family=AF_INET;
inet_pton(AF_INET, "127.0.0.1",&cliaddr1.sin_addr.s_addr);
len=sizeof(struct sockaddr);
sendto(s,file_buffer,sizeof(file_buffer),0,(struct sockaddr*)&cliaddr1,len);

bzero(&cliaddr2, sizeof(cliaddr2));
cliaddr2.sin_port=htons(5000);
cliaddr2.sin_family=AF_INET;
inet_pton(AF_INET, "127.0.0.16",&cliaddr2.sin_addr.s_addr);
sendto(s,file_buffer1,sizeof(file_buffer1),0,(struct sockaddr*)&cliaddr2,len);


bzero(&cliaddr3, sizeof(cliaddr3));
cliaddr3.sin_port=htons(5000);
cliaddr3.sin_family=AF_INET;
inet_pton(AF_INET, "127.0.0.32",&cliaddr3.sin_addr.s_addr);
sendto(s,file_buffer2,sizeof(file_buffer2),0,(struct sockaddr*)&cliaddr3,len);

perror("status");

}



