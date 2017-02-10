#ifndef __SERVER__
#define __SERVER__

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG 5


class Server {

private:

    //Attributes
    int port;
    int socket_fd;

    //Private methods
    int init();
    int create_socket();
    void bind_socket_to_address(struct sockaddr *address);
    int accept_connection();

    struct sockaddr_in build_address(char *address, int port);


public:

    Server();

    void start_socket_listen();

    ~Server();






};

#endif
