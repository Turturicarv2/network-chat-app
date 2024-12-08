#include "common.h"

/* DEFINES */
#define MAX_CLIENTS 2
#define NO_CLIENT -2
#define WAITING_CLIENT -1

/* FUNCTION DECLARATIONS */
void *handle_client(void *args);
void create_thread(int client_index);

/* GLOBAL VARIABLES */
int number_of_clients = 0;
int server_socket;
int client_arr[MAX_CLIENTS];


int main(void)
{
    /* create a socket for the server */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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
        create_thread(client_index);
    }

    while (number_of_clients == 0)
    {
        /* wait for connection with first client */
    }

    while (number_of_clients != 0)
    {
        int client_index;
        for (client_index = 0; client_index < MAX_CLIENTS; client_index++)
        {
            if (client_arr[client_index] == NO_CLIENT)
            {
                create_thread(client_index);
            }
        }
    }

    /* Close the socket */
    close(server_socket);

    return 0;
}


/*
Function that handles 1 client/user. Called by each thread.
Returns nothing
*/
void *handle_client(void *args)
{
    /* accept client connection */
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_len);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(1);
    }
    
    int client_index;
    for (client_index = 0; client_index < MAX_CLIENTS; client_index++)
    {
        if (client_arr[client_index] == WAITING_CLIENT)
        {
            break;
        }
    }

    client_arr[client_index] = client_socket;
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
    client_arr[client_index] = NO_CLIENT;

    return NULL;
}


void create_thread(int client_index)
{
    client_arr[client_index] = WAITING_CLIENT;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_client, NULL);
    pthread_detach(thread_id);
}
