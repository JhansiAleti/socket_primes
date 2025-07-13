#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int isprime(int num)
{
        for(int j=2;j<num;j++)
        {
                if((num%j)==0)
                {
                        return 0;
                }
        }
        return 1;

}
int main(int argc, char *argv[])
{
        int cfd,sfd,csize=0,min,max;
        struct sockaddr_in caddr,saddr;
        sfd=socket(AF_INET,SOCK_STREAM,0);
        if(sfd<0)
        {
                perror("socket");
        }
        puts("socket is created");

        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(atoi(argv[1]));
        saddr.sin_addr.s_addr=inet_addr("0.0.0.0");

        puts("assign the local address");
        if((bind(sfd,(const struct sockaddr*)&saddr, sizeof(saddr)))<0)
        {
                perror("bind");
        }
        puts("local address was assigned");
        puts("creating the queue");
        if((listen(sfd,1))<0)
        {
                perror("listen");
        }
        puts("queue was created");

        puts("accept the client request");
        csize=sizeof(caddr);
        cfd=accept(sfd,(struct sockaddr*)&caddr, &csize);
        if(cfd<0)
        {
                perror("accept");
        }
        puts("client request was accepted");

        recv(cfd,&min,sizeof(min),0);
        recv(cfd,&max,sizeof(max),0);
        for(int i=min;i<=max;i++)
        {
                if(isprime(i))
                {
                        send(cfd,&i,sizeof(i),0);
                        sleep(1);
                }
        }
        int done=-1;
        send(cfd,&done,sizeof(done),0);


}