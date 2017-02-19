#include "AccountServer.hpp"
#include "FriendListCommand.h"

AccountServer::AccountServer(int port, const char *databaseName) : Server(port), myDatabase(Database(databaseName)) {}

void AccountServer::run() {
    start_socket_listen();
    int newClient;

    while (1) {
        newClient = accept_connection();
        std::cout << "New client connected wouhouuu" << std::endl;
        //add_new_client(newClient); Je laisse ca la au cas ou

        if (!fork()) {
            char message_buffer[BUFFER_SIZE];
            get_and_process_command(newClient, message_buffer);
        }
    }
}


//Partie Register

bool AccountServer::insert_account_in_db(Credentials credentials) {
    //Return True si ca c'est bien passé, false sinon

    return myDatabase.insert_account(credentials) != -1;
}

bool AccountServer::attemptCreateAccount(Credentials credentials) {
    return insert_account_in_db(credentials);
}

bool AccountServer::handle_register(Credentials credentials, int client_sock_fd) {
    bool success = false;

    if (attemptCreateAccount(credentials)) {
        //Success
        send_success(client_sock_fd);
        success = true;
    } else {
        //Error
        send_error(client_sock_fd);
    }
    return success;
}

void AccountServer::send_success(int client_sock_fd){
    send_message(client_sock_fd, "1");

}

void AccountServer::send_error(int client_sock_fd){
    send_message(client_sock_fd, "-1");

}

void AccountServer::send_success_id(int client_sock_fd, std::string username){
    /*
     * Renvoi l'id du user qui s'est connecté
     */

    int id = myDatabase.getIDbyUsername(username);
    std::string string_id = std::to_string(id);
    send_message(client_sock_fd,string_id.c_str());
    //send_message(client_sock_fd, "1");
}

//Partie Login

bool AccountServer::checkCredentials(Credentials credentials) {
    return  myDatabase.is_identifiers_valid(credentials);
}

bool AccountServer::handle_login(Credentials credentials, int client_sock_fd) {
    bool success = false;
    //std::cout << credentials.getUsername() << std::endl;
    //std::cout << credentials.getPassword() << std::endl;

    if (checkCredentials(credentials)){
        send_success_id(client_sock_fd, credentials.getUsername());
        success = true;

    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}

//Partie Ranking

std::vector<RankingInfos> AccountServer::getRanking() {
    return myDatabase.getRanking();
}

bool AccountServer::handle_ranking(int client_sock_fd) {
    send_message(client_sock_fd, vectorTostring(getRanking()).c_str());
    return true;
}

std::string AccountServer::vectorTostring(std::vector<RankingInfos> vect) {

    /*creation d'un string du type "username,nbVictories|username,nvVictories|*/

    std::string result = "";
    for (int i = 0; i < vect.size(); i++) {
        result+=vect[i].username;
        result+=",";
        result+= std::to_string(vect[i].victories);
        result+="|";
    }
    return result;
}

// partie friendlist /////////////////////////////////////////////////////
std::vector<std::string> AccountServer::getFriendList(int id) {
    return myDatabase.getFriendList(id);
}

std::vector<std::string> AccountServer::getFriendRequests(int id){
    return myDatabase.getFriendRequests(id);
}

bool AccountServer::sendFriendRequest(std::string requester, std::string receiver) {
    return myDatabase.sendFriendRequest(requester,receiver) != -1 ;
}
bool AccountServer::acceptFriendRequest(std::string requester, std::string receiver) {
    return myDatabase.acceptFriendRequest(requester,receiver) != -1 ;
}
bool AccountServer::declineFriendRequest(std::string requester, std::string receiver) {
    return myDatabase.declineFriendRequest(requester, receiver) != -1 ;
}
bool AccountServer::removeFriend(std::string requester, std::string receiver) {
    return myDatabase.removeFriend(requester,receiver) != -1 ;
}
std::vector<std::string> AccountServer::getPendingInvitations(int id){
    return myDatabase.getPendingInvitations(id);
}

bool AccountServer::handle_getFriendList(int client_sock_fd, int requesterID) {
    send_message(client_sock_fd, vectorTostring(getFriendList(requesterID)).c_str());
    return true;
}
bool AccountServer::handle_getFriendRequests(int client_sock_fd, int requesterID) {
    send_message(client_sock_fd, vectorTostring(getFriendRequests(requesterID)).c_str());
    return true;
}
bool AccountServer::handle_getPendingInvitations(int client_sock_fd, int requesterID) {
    send_message(client_sock_fd, vectorTostring(getPendingInvitations(requesterID)).c_str());
    return true;
}

bool AccountServer::handle_acceptFriendRequest(int client_sock_fd, std::string requester, std::string toAccept) {
    bool success = false;

    if (acceptFriendRequest(requester, toAccept)){
        send_success(client_sock_fd);
        success = true; 
    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}

bool AccountServer::handle_declineFriendRequest(int client_sock_fd, std::string requester, std::string toDecline) {
    bool success = false;
    if (declineFriendRequest(requester, toDecline)){
        send_success(client_sock_fd);
        success = true;
    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}

bool AccountServer::handle_sendFriendRequest(int client_sock_fd, std::string requester, std::string toAdd) {
    bool success = false;
    if (sendFriendRequest(requester, toAdd)){
        send_success(client_sock_fd);
        success = true;
    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}

bool AccountServer::handle_removeFriend(int client_sock_fd, std::string requester, std::string toRemove) {
    bool success = false;
    if (removeFriend(requester, toRemove)){
        send_success(client_sock_fd);
        success = true;
    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}


std::string AccountServer::vectorTostring(std::vector<std::string> vect) {
    std::string result = "";
    for (int i = 0; i < vect.size(); i++) {
        result+=vect[i];
        if (i < vect.size()-1) {
            result += ",";
        }
    }
    return result;
}


///////////////////////////////////////////////////////////////////////////
void AccountServer::get_and_process_command(int client, char* message_buffer) {
    bool ok = false;

    while (!ok) {
        bool success = receive_message_with_timeout(client, message_buffer, 300);
        if (!success) {
            return;
        }

        std::cout << "hi greg" << std::endl;
        std::string command_type = get_command_type(message_buffer);

        if ((command_type == "login") || (command_type == "register")) {

            //Si on est dans le cas ou quelqu'un essaye de se connecter/register

            LoginRegisterCommand command;
            command.parse(message_buffer);
            Credentials credentials = command.getCreds();

            if (command.getAction() == "login") {
                ok = handle_login(credentials, client);
            } else if (command.getAction() == "register") {
                ok = handle_register(credentials, client);
            } else {
                // Show "unknown command" error
            }
        } else if (command_type == "ranking") {

            //Si on est dans le cas ou un user veut voir le ranking

            Command command;
            command.parse(message_buffer);
            ok = handle_ranking(client);

        } else if (command_type == "profile") {
            //TODO: ProfileCommand
            //TODO: handle_profle();

        } else if (command_type == "getFriendList" || command_type == "getFriendRequests" ||
                   command_type == "addFriend" || command_type == "removeFriend" ||
                   command_type == "acceptFriendRequest" || command_type == "declineFriendRequest" ||
                   command_type == "getPendingInvitations") {

            FriendListCommand friendListCommand;
            friendListCommand.parse(message_buffer);
            int requesterID = atoi(friendListCommand.getRequester().c_str());
            std::string requesterUsername = myDatabase.getInfosById(requesterID);
            std::string receiverUsername = friendListCommand.getReceiver();
            std::string action = friendListCommand.getAction();

            if (action == "getFriendList") {

                handle_getFriendList(client, requesterID);

            } else if (action == "getFriendRequests") {

                handle_getFriendRequests(client, requesterID);

            } else if (action == "addFriend") {

                handle_sendFriendRequest(client, requesterUsername, receiverUsername);
                
            }else if (action == "getPendingInvitations") {
                
                handle_getPendingInvitations(client, requesterID); 
                
            } else if (action == "removeFriend") {

                handle_removeFriend(client, requesterUsername, receiverUsername);

            } else if (action == "acceptFriendRequest") {

                handle_acceptFriendRequest(client, requesterUsername, receiverUsername);

            } else if (action == "declineFriendRequest") {

                handle_declineFriendRequest(client, requesterUsername, receiverUsername);
            }
        }
    }
}








