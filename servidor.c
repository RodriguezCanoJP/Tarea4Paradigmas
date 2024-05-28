//
// Created by Juan Pablo Rodriguez on 23/5/24.
//
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "constants.h"

int main(int argc, char* argv[]){
    char server_message[32] = "You have reached the server";
    char buffer[32] = {0};
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 5);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message), 0);

    int valread;
    while ((valread = read(client_socket, buffer, 32)) > 0) {
        buffer[valread] = '\0';
        send(client_socket, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
    }

    if (valread == 0) {
        printf("Client disconnected\n");
    } else if (valread < 0) {
        perror("read");
    }
    close(client_socket);
    close(server_socket);
    return 0;
}
