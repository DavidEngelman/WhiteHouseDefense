
#include "NetworkedManager.hpp"

NetworkedManager::NetworkedManager(int port, char* address) :AbstractManager(address), port(port) {
    init();
}

void NetworkedManager::init() {
    struct hostent *he;
    if ((he=gethostbyname(server_ip_address)) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    server_socket = create_socket();
    if (connect_to_server(server_socket, he) == -1) {
        perror("connect");
        exit(1);
    }

}

int NetworkedManager::create_socket() {
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    return sockfd;

}

int NetworkedManager::connect_to_server(int socket, struct hostent *addr) {
    struct sockaddr_in their_addr;

    their_addr.sin_family = AF_INET;    // host byte order
    their_addr.sin_port = htons(port);  // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)addr->h_addr);

    memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct

    return connect(socket, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
}


