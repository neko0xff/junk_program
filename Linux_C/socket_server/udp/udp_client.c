/*相關函式庫*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*相關定義*/
#define USER "\nClient(Output)> "
#define MAIN "Client(Input)> "
#define PORT 9999

typedef struct sockaddr *pSA;
struct sockaddr_in servaddr;
int sockfd, n;
char sendline[1024], recvline[1025];

/*伺服器位置設置*/
void Client_address(){
    servaddr.sin_family = AF_INET; //網路協定: IPV4
    servaddr.sin_port = htons(PORT); //通訊埠
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP位置
}

/*客戶端初始化*/
void Client_init(){
    /*建立Socket連線*/
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "UDP Client Strating...\n");
}

/*伺服器運行階段: 把輸入的內容傳至伺服端*/
void Server_runtime(){
    printf(MAIN);
    if (fgets(sendline + strlen(USER), sizeof(sendline) - strlen(USER), stdin) == NULL) {
        perror("fgets");
    }

    memcpy(sendline, USER, strlen(USER));
    if (sendto(sockfd, sendline, strlen(sendline), 0, (pSA)&servaddr, sizeof(servaddr)) == -1) {
        perror("sendto");
    }

    n = recvfrom(sockfd, recvline,1024, 0, NULL, NULL);
    if (n == -1) {
        perror("recvfrom");
    }

    recvline[n] = 0;
    fputs(recvline, stdout);
}

/*主程式*/
int main(int argc, char *argv[]){
    /*輸入部分: 如果未輸入伺服器位置時*/
    if (argc != 2){
        fprintf(stderr, "usage: udp_client <IPADDRESS>");
        return EXIT_FAILURE;
    }

    /*輸入部分: 若輸入的伺服器位置是無效時*/
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) == -1){
        perror("inet_pton");
        fprintf(stderr, "Invalid IPADDRESS: %s", argv[1]);
        return EXIT_FAILURE;
    }

    Client_init();
    Client_address();

    while (1){
        Server_runtime();
    }

    /*關閉連線*/
    close(sockfd);
    return EXIT_SUCCESS;
}
