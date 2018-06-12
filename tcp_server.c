#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
    char server_message[256] = "You have reached the server!!";

    // Create the server socket
    // docs: man socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    // docs: http://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind to the ip:port
    // docs: man bind
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen to connections
    // docs: man listen
    listen(server_socket, 5);

    // accept connection
    // docs: man accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // send message
    // docs: man send
    send(client_socket, server_message, sizeof(server_message), 0);

    // close socket
    // docs: man close
    close(server_socket);
    return 0;
}
