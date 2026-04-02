#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[1024] = {0};
    char server_ip[16];

    printf("Enter Server IP (use 127.0.0.1 if on same WSL): ");
    scanf("%15s", server_ip);
    getchar(); // Clear newline

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected! Type messages (type 'exit' to quit):\n");
    while (1) {
        printf("> ");
        fgets(message, 1024, stdin);
        send(sock, message, strlen(message), 0);
        if (strncmp(message, "exit", 4) == 0) break;
    }

    close(sock);
    return 0;
}