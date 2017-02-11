//
// Created by benjamin on 11/02/17.
//
#include "AccountServer.hpp"


AccountServer::AccountServer(int port): Server(port){}

void AccountServer::run(){
    int newClient;

    while (1){
        newClient = accept_connection();
        add_new_client(newClient);



    }
}

void AccountServer::attemptCreateAccount(std::string name, std::string password) {}

void AccountServer::checkCredentials(std::string name, std::string password) {}