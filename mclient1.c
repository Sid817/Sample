#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>
#include<strings.h>
#include<unistd.h>
#include<net/if.h>
#include<time.h>
void main()
{
int s,k,mlen,on=1;
char buff1[100], msg[200],id[34];
struct sockaddr_in servaddr, cliaddr;
struct ip_mreq mreq;

s = socket(PF_INET, SOCK_DGRAM,0);
perror("Socket status\n");

setsockopt(s,SOL_SOCKET, SO_REUSEADDR,&on, sizeof(on));

bzero((void *)&servaddr, sizeof(servaddr));
servaddr.sin_port=htons(5000);
servaddr.sin_family=AF_INET;
//cliaddr.sin_addr.s_addr=INADDR_ANY;
inet_pton(AF_INET, "192.168.43.191",&servaddr.sin_addr.s_addr);

bzero((void *)&cliaddr, sizeof(cliaddr));
cliaddr.sin_port=htons(5000);
cliaddr.sin_family=AF_INET;
//cliaddr.sin_addr.s_addr=INADDR_ANY;
inet_pton(AF_INET, "127.0.0.1",&cliaddr.sin_addr.s_addr);

mlen=sizeof(struct sockaddr_in);

bind(s,(struct sockaddr* )&cliaddr, sizeof(struct sockaddr));
perror("Bind status\n");

inet_pton(AF_INET, "127.0.0.1",(struct inaddr*)&mreq.imr_multiaddr);
inet_pton(AF_INET, "192.168.43.191",(struct inaddr*)&mreq.imr_interface);
setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,&mlen,sizeof(mlen));


recvfrom(s,buff1,sizeof(buff1),0,(struct sockaddr *) & servaddr, &mlen);

printf("msg from server is: %s\n",buff1);
close(s);
}


