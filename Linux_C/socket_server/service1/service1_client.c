#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define USER "\nClient(Output)> "
#define MAIN "Client(Input)> "
#define PORT 3030

struct sockaddr_in servaddr;
typedef struct sockaddr *pSA;
int msock, n;
char sendline[1024], recvline[1025];

/*伺服器位置設置*/
void Client_address(const char *ip) {
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) == -1) {
        perror("Invalid IPADDRESS");
        exit(EXIT_FAILURE);
    }
}

/*客戶端: 初始化*/
void Client_init() {
    fprintf(stdout, "TCP Client Starting...\n");
    msock = socket(AF_INET, SOCK_STREAM, 0);
    if (msock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

/*客戶端: 測試連線過程*/
void Server_testCN() {
    /*向伺服器連線*/
    if (connect(msock, (pSA)&servaddr, sizeof(servaddr)) < 0) {
        perror("TCP Connection to Server Error!!!");
        close(msock);
        exit(EXIT_FAILURE);
    } else {
        fprintf(stdout, "TCP Client connect to Server is Succeed\n");
    }
}

/*客戶端: 把輸入的內容傳至伺服端*/
void Server_runtime() {
    printf(MAIN);
    if (fgets(sendline + strlen(USER), sizeof(sendline) - strlen(USER), stdin) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    memcpy(sendline, USER, strlen(USER));
    if (send(msock, sendline, strlen(sendline), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    n = recv(msock, recvline, sizeof(recvline) - 1, 0);
    if (n == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    recvline[n] = '\0';
    fputs(recvline, stdout);
}

/*主程式*/
int main(int argc, char *argv[]) {
    /*輸入部分: 如果未輸入伺服器位置時*/
    if (argc != 2) {
        fprintf(stderr, "Usage: tcpcli <IPADDRESS>");
        exit(EXIT_FAILURE);
    }

    Client_address(argv[1]);
    Client_init();
    Server_testCN();

    while (1) {
        Server_runtime();
    }

    /*關閉連線*/
    close(msock);
    return 0;
}
