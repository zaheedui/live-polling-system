#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <winsock2.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int votes[3] = {0, 0, 0}; // Stores results for Option A, B, C

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all network cards
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server listening on Port %d...\n", PORT);
    printf("IP Address of this machine should be: 10.1.18.39\n");

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        
        int incoming_vote;
        recv(new_socket, (char*)&incoming_vote, sizeof(incoming_vote), 0);
        int vote_idx = ntohl(incoming_vote) - 1; // Convert back to local int

        int response[4];
        if (vote_idx >= 0 && vote_idx < 3) {
            votes[vote_idx]++;
            response[0] = htonl(1); // Status: Success
            printf("Vote received for Option %c\n", 'A' + vote_idx);
        } else {
            response[0] = htonl(-1); // Status: Error
        }

        // Fill response with current tallies
        response[1] = htonl(votes[0]);
        response[2] = htonl(votes[1]);
        response[3] = htonl(votes[2]);

        send(new_socket, (char*)response, sizeof(response), 0);
        closesocket(new_socket);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}