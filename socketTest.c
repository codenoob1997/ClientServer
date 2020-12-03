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

int main(int argc,char **argv){
    struct sockaddr_in sockaddr;
    int sockfd;
    char sendline[MAXLINE],revline[MAXLINE];
    int n;
    if(argc<2){
        printf("please input address: ./server <ip address> <port> \n");
        exit(0);
    }
    
    //ip地址和端口
    char *addr = argv[1];
    int port = atoi(argv[2]);


    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
        printf("create socket error : %s  errornumber:%d \n",strerror(errno),errno);
        exit(0);
    }
    printf("socket created!\n");
    printf("Dest IP Address: %s     Port:%d\n",addr,port);

    memset(&sockaddr,0,sizeof(sockaddr));
    inet_pton(AF_INET,addr,&sockaddr.sin_addr);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(50000); //centos 7大尾序列

    if(connect(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))==-1){
        printf("cannot connect server : %s   error number: %d\n",strerror(errno),errno);
        exit(0);
    }

    printf("send message to server : ");
while(1){
    printf("enter message:");
    memset(sendline,0,MAXLINE);
    fgets(sendline,MAXLINE,stdin);
    if(strcmp(sendline,"quit\n")==0){
        exit(1);
    }
    if((write(sockfd,sendline,strlen(sendline)))<0){
        printf("send line error : %s    errornumber:    \n",strerror(errno),errno);
        exit(0);
    }
}
close(sockfd);
return 0;

}