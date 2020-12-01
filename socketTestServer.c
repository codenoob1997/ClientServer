#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAXLINE 1024

int main(int argc,char **argv){
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    int n;
    int port;

    if(argc<1){
        printf("./server <port>\n");
        exit(0);
    }

    //Port
    port = atoi(argv[1]);

    //Initialize socket
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);       //0.0.0.0

    if((listenfd = socket(AF_INET,SOCK_STREAM,0))==-1){
        printf("cant not create socket! error:%s        errno:%d\n",strerror(errno),errno);
        exit(0);
    }
    printf("=============socket created!\n");

    //bind socket
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1){
        printf("cannot bind socket! error:%s        errno:%d\n",strerror(errno),errno);
        exit(0);
    }
    printf("=============socket bind!   PROTOCOL:AF_INET   IP:0.0.0.0  PORT:%d\n",port);

    //listen port
    if(listen(listenfd,port)==-1){
        printf("cannot listen port! error:%s    errno:%d\n",strerror(errno),errno);
        exit(0);
    }
    printf("=============listening port:%d \n",port);

    while(1){
        if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1){
            printf("cannot connect! error:%s    errno:%d\b",strerror(errno),errno);
            continue;
        }
        n = recv(connfd,buff,MAXLINE,0);
        buff[n] = '\0';
        printf("Received message from client:%s",buff);
        close(connfd);
    }
    close(listenfd);

}
