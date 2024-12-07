#include "common.h"

char *get_user_input(void);


int main(void)
{
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
    if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Connected to the server!\n");

    char message[1024];

    do
    {
        /* get message from the client */
        strcpy(message, get_user_input());

        /* send message */
        send(client_socket, message, sizeof(message) - 1, 0);
    } while (strcmp(message, "exit\n") != 0);

    // Close the socket
    close(client_socket);

    return 0;
}


/*
Function that reads user input
Returns a string
*/
char *get_user_input(void) {
    char *buffer;
    size_t bufsize = 32;
    size_t number_of_characters;

    /* allocate memory for the string */
    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL) 
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    /* get input */
    number_of_characters = getline(&buffer, &bufsize, stdin);

    return buffer;
}