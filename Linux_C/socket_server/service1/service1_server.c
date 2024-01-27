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
#define SERVER_USER "\nServer(Output)> "
#define SERVER_GET  "Server(Input)> "
#define PORT 3030

struct sockaddr_in msin;
struct sockaddr_in clntsin;
struct sockaddr_in cliaddr;
typedef struct sockaddr *pSA;
time_t ticks;
int clntsock,msock,n,len;
int cslen = sizeof(clntsin);
char buf1[64];
char buffer[1024], buf2[1024 + sizeof(SERVER_USER)];

/*伺服端: 取得伺服器位置*/
void Server_address(){
     msin.sin_family = AF_INET; //協定: IPV4
     msin.sin_port = htons(PORT); //通訊埠
     msin.sin_addr.s_addr = htonl(INADDR_ANY); //IP位置
}

/*伺服端: 開始於指定的通訊埠通信*/
void Server_listen(){
    if(listen(msock,5)<0){
        perror("listen() Failed");
        close(msock);
        exit(-1);
    }
}

/*伺服端: 指定通訊埠&IP位置*/
void Server_bind(){
    if (bind(msock, (struct sockaddr *) &msin, sizeof(msin)) < 0) {
        perror("bind() Failed");
        close(msock);
        exit(-1);
    }
}

/*伺服端: 運行過程*/
void Client_readSend() {
    while (1) {
        // 讀取資料
        n = recv(clntsock, buffer, sizeof(buffer) - 1, 0);

        // 確保接收到的資料以 null 結尾
        buffer[n] = '\0';
        printf("%s", buffer);

        memcpy(buf2, SERVER_USER, strlen(SERVER_USER)); //加入特定字串

        /* 從終端下取得輸入的字串，確保不會超過 buf 緩衝區的大小 */
        printf(SERVER_GET);
        if (fgets(buf2 + strlen(SERVER_USER), sizeof(buf2) - strlen(SERVER_USER), stdin) == NULL) {
            perror("fgets() failed");
            break;
        }

        /* 送出資料 */
        if (write(clntsock, buf2, strlen(buf2)) < 0) {
            perror("write() failed");
            continue;
        }
    }
}

/*伺服端: 連結過程*/
void Client_cn() {
    while (1) {
        /*接收客戶端連結請求*/
        clntsock = accept(msock, (struct sockaddr *) &clntsin, &cslen);
        if (clntsock < 0) {
            perror("accept() Failed");
            close(clntsock);
            exit(-1);
        }

        /*輸出至終端機部分*/
        char clientAddr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clntsin.sin_addr), clientAddr, INET_ADDRSTRLEN);
        fprintf(stdout, "Client> Connection from %s:%d\n", clientAddr, ntohs(clntsin.sin_port)); //客戶端位置

        /*傳送至客戶端*/
        ticks = time(NULL); //取得伺服器的當下連線時間
        snprintf(buf1, sizeof(buf1), "%s Now Time: %.24s\r\n", SERVER_USER, ctime(&ticks));
        if (write(clntsock, buf1, strlen(buf1)) < 0) {
            perror("write() failed");
            close(clntsock);
            continue;
        }

        Client_readSend();
        
    }
}

/*伺服端: 建立連線*/
void Server_init(){
    fprintf(stdout,"TCP Single Server Strating...\n");
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




