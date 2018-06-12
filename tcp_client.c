#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
    // Use integer to hold socket descriptor
    int network_socket;
    // create a socket
    // docs: man socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address to connect to
    // docs: http://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    // call connect
    // docs: man connect
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // throw error if connect returns -1
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }
    
    // string to hold data we get back
    char server_response[256];

    // receive data
    // docs: man recv
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out response
    printf("The server sent the data. %s\n", server_response);

    // close the socket
    // docs: man close
    close(network_socket);
    return 0;
}
