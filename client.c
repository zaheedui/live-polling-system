#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    int vote;

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 🔴 PUT YOUR SERVER IP HERE
    serv_addr.sin_addr.s_addr = inet_addr("10.1.21.239");

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return 1;
    }

    printf("\n===== LIVE POLL =====\n");
    printf("1. Option A\n");
    printf("2. Option B\n");
    printf("3. Option C\n");
    printf("Enter your vote (1/2/3): ");
    scanf("%d", &vote);

    vote = htonl(vote);
    send(sock, (char*)&vote, sizeof(vote), 0);

    int response[4];
    recv(sock, (char*)response, sizeof(response), 0);

    int status = ntohl(response[0]);

    if(status == -1) {
        printf("\n❌ You have already voted!\n");
    } else {
        printf("\n📊 Live Results:\n");
        printf("Option A: %d\n", ntohl(response[1]));
        printf("Option B: %d\n", ntohl(response[2]));
        printf("Option C: %d\n", ntohl(response[3]));
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}