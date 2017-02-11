#ifndef __SERVER__
#define __SERVER__

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define BACKLOG 5


class Server {

private:

    //Private methods
    void init();

    int create_socket();

    void bind_socket_to_address(struct sockaddr *address);

    struct sockaddr_in build_address();

protected:

    //Attributes
    int port;
    int socket_fd;

    int accept_connection();

    int get_readable_socket(int * sockets, int num_sockets);

public:

    Server(int port);

    void start_socket_listen();

    virtual void run() = 0;

    virtual ~Server();


};

#endif
