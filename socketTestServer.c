#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 4096

int main(){
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)==-1)){
        printf("cannot create socket!\n");
        exit(0);
    }
    printf("socket created!\n");

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = 6666;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("PROTOCOL : %d\t",servaddr.sin_family);
    printf("PORT :%d\t",servaddr.sin_port);
    printf("LISTEN ADDRESS : %d\n",ntohl(INADDR_ANY));


    if((bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)){
        printf("cannot bind socket!\n");
        exit(0);
    }

    if(listen(listenfd,10)==-1){
        printf("cannot listen socket\n");
    }
    printf("==============================waiting for request=================");
    while(1){
        if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1){
            printf("accept socket error:%s(errno:%d)",strerror(errno),errno);
            continue;

        }
        n = recv(connfd,buff,MAXLINE,0);
        buff[n] = '\0';
        printf("recv msg from client:%s\n",buff);
        close(connfd);
    }
    close(listenfd);
    
}