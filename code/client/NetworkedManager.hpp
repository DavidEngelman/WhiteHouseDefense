

#ifndef PROJET_MANAGER_H
#define PROJET_MANAGER_H

#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "AbstractManager.h"


class NetworkedManager : public AbstractManager {

protected:
    int port;
    char *ip_address;
    int server_socket;

public:

    NetworkedManager(int port, char* address);
    void init();
    int create_socket();
    int connect_to_server(int socket, struct hostent* addr);


};


#endif //PROJET_MANAGER_H
