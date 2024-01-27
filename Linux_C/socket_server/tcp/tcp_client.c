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
#include <sys/time.h>

/*相關定義*/
#define PORT 5150

struct sockaddr_in msin;
unsigned long iaddr;
struct hostent *host;
time_t ticks;
int msinlen=sizeof(msin);
int msock;
char buf[64];
char *hostname = 0;

/*伺服器位置設置*/
void Clinet_address(){
    memset(&msin,'\0',sizeof(msin));
    msin.sin_family=AF_INET;
    msin.sin_port=htons(PORT);
}

/*客戶端: 初始化*/
void Client_init(){
    fprintf(stdout,"TCP Client Strating...\n");
    msock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
}
/*客戶端: 過程*/
void Server_clientMessage(){
    memset(buf,0,sizeof(buf));
    read(msock,buf,sizeof(buf));
    fprintf(stdout,"Server> Now Time: %s\n",buf);
}
/*客戶端: 測試連線過程*/
void Server_testCN(){
     /*向伺服器連線*/
    if(connect(msock,(struct sockaddr *)&msin, msinlen)<0){
        fprintf(stderr,"TCP Connection to Server Error!!!\n");
        exit(-1);
    }else{
        fprintf(stdout,"TCP Client connect to Server is Succeed\n");
    }
}

/*主程式*/
int main(int argc,char *argv[]){

    /*輸入部分: 如果未輸入伺服器位置時*/
    if(argc!=2){
        fprintf(stderr,"Usage: udpcli <IPADDRESS>");
        exit(0);
    }

    /*輸入部分: 若輸入的伺服器位置是無效時*/
    if(inet_pton(AF_INET,argv[1],&msin.sin_addr) == -1){
        fprintf(stderr,"Invaild IPADDRESS: %s",argv[1]);
        exit(0);
    }

    Clinet_address();
    Client_init();
    Server_testCN();
    Server_clientMessage();

    /*關閉連線*/
    close(msock);
    return 0;
}
