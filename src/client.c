#include "common.h"

static char *get_user_input(void);
static void *handle_receiving_messages(void *args);

int client_socket;

int main(void)
{
    /* create a socket for the client */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
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

    /* create a thread that waits for messages from server */
    pthread_t receiving_thread;
    if (pthread_create(&receiving_thread, NULL, handle_receiving_messages, NULL) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }

    char message[1024];

    /* get input from current user and send to server */
    do
    {
        /* get message from the client */
        strcpy(message, get_user_input());

        /* send message */
        send(client_socket, message, sizeof(message) - 1, 0);
    } while (strcmp(message, "exit\n") != 0);

    // Cancel the thread that waits for messages
    if (pthread_cancel(receiving_thread) != 0) {
        perror("Failed to cancel thread");
        return 1;
    }

    // Wait for the thread to terminate
    if (pthread_join(receiving_thread, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    // Close the socket
    close(client_socket);

    return 0;
}


/*
Function that reads user input
Returns a string
*/
static char *get_user_input(void) {
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


/* 
Function that will print messages from other clients
Returns nothing
*/
static void *handle_receiving_messages(void *args)
{
    while (1)
    {
        char message[1024];
        int bytes_recieved = recv(client_socket, message, sizeof(message) - 1, 0);
        if (bytes_recieved > 0)
        {
            printf("%s", message);
        }
    }
}
