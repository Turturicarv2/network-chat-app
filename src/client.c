#include "common.h"


int main(int argc, char *argv[])
{
    /* 2 parameters should be sent via terminal */
    if (argc < 2)
    {
        perror("Not enough parameters!");
        exit(1);
    }

    /* create a socket for the client */
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;  // IPv4
    server_address.sin_port = htons(8080); // Port 8080
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Connected to the server!\n");

    // Close the socket
    close(client_socket);

    return 0;
}