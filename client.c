#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char *argv[])
{
        int cfd,min,max,num;
        struct sockaddr_in saddr;
        cfd=socket(AF_INET, SOCK_STREAM,0);
        if(cfd<0)
        {
                perror("socket");
        }
        puts("socket is created successfully");
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(atoi(argv[2]));
        saddr.sin_addr.s_addr=inet_addr(argv[1]);
        min=atoi(argv[3]);
        max=atoi(argv[4]);
        if(connect(cfd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
        {
                perror("connect");
        }
        puts("client is connected to the sockwt");
        send(cfd, &min,sizeof(min),0);
        send(cfd,&max,sizeof(max),0);
        while(1)
        {
        recv(cfd,&num,sizeof(num),0);
        if(num==-1)
        {
                printf("data returned sucessfully");
                break;
        }
        printf("%d\n", num);
        }
        close(cfd);

}