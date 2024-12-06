#include "common.h"


int main(int argc, char *argv[])
{
    /* 2 parameters should be sent via terminal */
    if (argc < 2)
    {
        perror("Not enough parameters!");
        exit(1);
    }

    /* create a socket for the server */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    /* bind socket to an address and port */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // Convert port to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    /* listen for other sockets */
    if (listen(server_socket, 2) < 0) { // Allow up to 2 pending connections
        perror("Listen failed");
        exit(1);
    }

    /* accept other connection */
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_len);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(1);
    }

    printf("User joined the chat");

    return 0;
}