#include "Server.hpp"

Server::Server() {

    init();
}

void Server::init(){

    struct sockaddr_in server_addr;
    int server_socket;

    //Creation du socket
    this.socket_fd = create_socket();

    //Config du sockaddr_in server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //binding du socket
    bind_socket_to_address();

}

void Server::bind_socket_to_address(struct sockaddr *address) {

    int result = bind(this.socket_fd, address, sizeof(struct sockaddr));
    if (result == -1) {
        perror("Bind");
        exit(EXIT_FAILURE);
    }
}

int Server::create_socket() {

    int socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("Error during socket creation");
        exit(1);
    }

    int yes = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    return socket_descriptor;
}

int Server::accept_connection(){

    struct sockaddr_in client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    return accept(this.socket_fd , (struct sockaddr *)&client_addr, &sin_size);
}

struct Server::sockaddr_in build_address(){

    struct sockaddr_in my_address;
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons((uint16_t) this.port);
    my_address.sin_addr.s_addr = INADDR_ANY;

    // On met sin_zero à 0
    memset(&(my_address.sin_zero), 0, 8);
    return my_address;
}


void Server::start_socket_listen() {

    int error_code = listen(this.socket_fd, BACKLOG);
    if (error_code == -1) {
        perror("Listen");
        exit(1);
    }
}

Server::~Server() {}