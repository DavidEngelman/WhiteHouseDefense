
#include "Manager.h"

Manager::Manager(int port, char *address) : port(port), ip_address(address) {
    init();
}

void Manager::init() {
    struct hostent *he;
    if ((he=gethostbyname(ip_address)) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    int server_socket = create_socket();
    if (connect_to_server(server_socket, he) == -1) {
        perror("connect");
        exit(1);
    }

}

int Manager::create_socket() {
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    return sockfd;

}

int Manager::connect_to_server(int socket, struct hostent *addr) {
    struct sockaddr_in their_addr;

    their_addr.sin_family = AF_INET;    // host byte order
    their_addr.sin_port = htons(port);  // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)addr->h_addr);

    memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct

    return connect(socket, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
}


