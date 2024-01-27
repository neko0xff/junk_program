/*相關函式庫*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*相關定義*/
#define SERVER_USER "\nServer(Output)> "
#define SERVER_GET  "Server(Input)> "
#define PORT 9999

typedef struct sockaddr *pSA;
struct sockaddr_in servaddr, cliaddr;
int sockfd, n, len;
char buffer[1024], buf[1024 + sizeof(SERVER_USER)];

/*建立連線*/
void Server_init() {
    fprintf(stdout, "UDP Single Server Starting...\n");

    /*建立socket連線*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, '\0', sizeof(servaddr)); //填充位址結構

    fprintf(stdout, "UDP Single Server Initialized Successfully!\n");
}

/*伺服端: 取得伺服器位置*/
void Server_address() {
    servaddr.sin_family = AF_INET;         //網路協定: IPV4
    servaddr.sin_port = htons(PORT);       //通訊埠
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP位置
}

/*伺服端: 運行過程*/
void Client_readSend() {
    while (1) {
        //讀取資料
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (pSA)&cliaddr, &len);

        //確保接收到的資料以 null 結尾
        buffer[n] = '\0';
        printf("%s", buffer);

        memcpy(buf, SERVER_USER, strlen(SERVER_USER)); //加入特定字串

        /* 從終端下取得輸入的字串，確保不會超過 buf 緩衝區的大小 */
        printf(SERVER_GET);
        if (fgets(buf + strlen(SERVER_USER), sizeof(buf) - strlen(SERVER_USER), stdin) == NULL) {
            perror("fgets() failed");
            break;
        }

        /* 送出資料 */
        if (sendto(sockfd, buf, strlen(buf), 0, (pSA)&cliaddr, len) < 0) {
            perror("sendto() failed");
            continue;
        }
    }
}
/*伺服端: 指定通訊埠&IP位置*/
void Server_bind(){
    /*綁定IP&通訊埠*/
    if (bind(sockfd, (pSA)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind() failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

int main() {
    Server_init();
    Server_address();
    Server_bind();
    Client_readSend();

    /*關閉連線*/
    close(sockfd);
    return 0;
}
