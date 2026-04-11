#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0); //ipv4 TCP 

    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 3); //3 - ожидание

    client_fd = accept(server_fd, NULL, NULL);

    send(client_fd, "Welcome!", 8, 0);

    close(client_fd);
    close(server_fd);

    return 0;
}