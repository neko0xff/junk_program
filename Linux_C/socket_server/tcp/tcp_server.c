/*相關函式庫*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

/*相關定義*/
#define PORT 5150

struct sockaddr_in msin;
struct sockaddr_in clntsin;
time_t ticks;
int msock,clntsock;
int cslen = sizeof(clntsin);
char buf[64];

/*伺服端: 取得伺服器位置*/
void Server_address(){
     msin.sin_family = AF_INET; //協定: IPV4
     msin.sin_port = htons(PORT); //通訊埠
     msin.sin_addr.s_addr = htonl(INADDR_ANY); //IP位置
}

/*伺服端: 指定通訊埠&IP位置*/
void Server_bind(){
    if(bind(msock,(struct sockaddr *) &msin, sizeof(msin))<0){
        perror("bind() Failed");
        close(msock);
        exit(-1);
    }
}

/*伺服端: 開始於指定的通訊埠通信*/
void Server_listen(){
    if(listen(msock,5)<0){
        perror("listen() Failed");
        close(msock);
        exit(-1);
    }
}

/*伺服端: 連結過程*/
void Client_cn(){

    while(1){
        /*接收客戶端連結請求*/
        clntsock = accept(msock, (struct sockaddr *) &clntsin, &cslen);
        if(clntsock<0){
           perror("accept() Failed");
           close(msock);
           exit(-1); 
        }

        /*輸出至終端機部分*/
        fprintf(stdout,"Client> Connection from %s:%d\n",inet_ntoa(clntsin.sin_addr),ntohs(clntsin.sin_port)); //客戶端位置
        
        /*傳送至客戶端*/
        ticks=time(NULL); //取得伺服器的當下連線時間
        snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
        write(clntsock,buf,strlen(buf));

        close(clntsock);
    }
    
}

/*伺服端: 建立連線*/
void Server_init(){
    fprintf(stdout,"TCP Single Server Strating...\n");
    
    /*建立socket連線*/
    msock = socket(AF_INET,SOCK_STREAM,0);
    if(msock<0){
        perror("socket() Failed \n");
        exit(-1);
    }

    fprintf(stdout, "TCP Single Server Initialize Finnish! \n");
}

/*主程式*/
int main(){
   Server_init();
   Server_address();
   Server_bind();
   Server_listen();
   Client_cn();

   /*關閉連線*/
   close(msock);
   return 0;
}

