

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
#include "../common/Networking.h"


class NetworkedManager : public AbstractManager {

protected:
    int port;
    int server_socket;

public:

    NetworkedManager(int port, char* adress, App* my_app);

    ~NetworkedManager();


};


#endif //PROJET_MANAGER_H
