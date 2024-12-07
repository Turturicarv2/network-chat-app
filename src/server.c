#include "common.h"

#define MAX_CLIENTS 2

void *handle_client(void *server_socket_ptr);

int number_of_clients = 0;


int main(void)
{
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
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(1);
    }

    int client_index;
    for (client_index = 0; client_index < MAX_CLIENTS; client_index++)
    {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, &server_socket);
        pthread_detach(thread_id);
    }

    while (number_of_clients == 0)
    {
        /* wait for connection with first client */
    }

    while (number_of_clients != 0)
    {
        /* do nothing, don't terminate the program */
    }

    /* Close the socket */
    close(server_socket);

    return 0;
}


void *handle_client(void *server_socket_ptr)
{
    int server_socket = *(int *) server_socket_ptr;
    /* accept other connection */
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_len);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(1);
    }
    
    number_of_clients++;

    printf("User joined the chat\n");

    char message[1024];
    do
    {
        int bytes_recieved = recv(client_socket, message, sizeof(message) - 1, 0);
        if (bytes_recieved > 0)
        {
            printf("%s", message);
        }
    } while (strcmp(message, "exit\n") != 0);

    close(client_socket);
    number_of_clients--;

    return NULL;
}
