#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("--- Server Active ---\n");
    printf("Listening on port: %d\n", PORT);
    printf("To find your IP for the client, run 'ip addr' in another WSL tab.\n");
    printf("Waiting for connection...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected! (IP: %s)\n", inet_ntoa(address.sin_addr));

    while (1) {
        memset(buffer, 0, 1024);
        int valread = recv(new_socket, buffer, 1024, 0);
        if (valread <= 0) {
            printf("\nClient disconnected.\n");
            break;
        }
        printf("Client: %s", buffer);
        if (strncmp(buffer, "exit", 4) == 0) break;
    }

    close(new_socket);
    close(server_fd);
    return 0;
}