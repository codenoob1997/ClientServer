/*
struct in_addr{
    in_addr_t s_addr;   //32位的IPV4地址
};
struct sockaddr_in{
    uint8_t sin_len;
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;    
    char sin_zero[8];
};

*/
#include<stdio.h>     
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>

#define MAXLINE 4096 //块对齐？
#define PORT 6666;

int main(){
    printf("start!");
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    inet_pton(AF_INET,"192.168.1.1",&servaddr.sin_addr);
    char recvline[MAXLINE],sendline[MAXLINE];
    char buf[MAXLINE];
    int n;
    printf("beginning!!");
   // printf("=======%d=========",__LINE__);
    if((listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) )==-1){
        printf("cant not create socket!");
        exit(0);
    }
    printf("socket create success!");
    //printf("=======%d=========",__LINE__);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666); 
    /*if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0){
        printf("inet_pton error for %s\n",argv[1]);
    }
    */
    if((connfd = connect(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))<0){
        printf("can not connect socket!");
       // printf("=======%d=========",__LINE__);
    }
    printf("created!");
    printf("send msg to server:\n");

    fgets(sendline,MAXLINE,stdin);
    /*if(send(listenfd,sendline,strlen(sendline),0)<0){
        printf("cannot send message");
        exit(0);
    }
    */
    printf("exiting");

    close(listenfd);
    exit(0);
}