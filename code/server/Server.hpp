#ifndef __SERVER__
#define __SERVER__

#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include "../common/Networking.h"

#define BACKLOG 5

static const int BUFFER_SIZE = 500;

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
    //std::vector<int> client_sockets; Peut etre on aura besoin mais pas sur

    int accept_connection();

    void add_new_client(int his_socket);

    int get_readable_socket(int * sockets, int num_sockets);

public:

    Server(int port);

    void start_socket_listen();

    virtual void run() = 0;

    virtual ~Server();


};

#endif
