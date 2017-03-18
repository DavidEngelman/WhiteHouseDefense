#include "AccountServer.hpp"
#include "FriendListCommand.h"

AccountServer::AccountServer(int port, const char *databaseName) : Server(port), myDatabase(Database(databaseName)) {}

void* AccountServer::client_handler(int client_sock) {
    std::cout << "Handling new client" << std::endl;
    char message_buffer[BUFFER_SIZE];
    get_and_process_command(client_sock, message_buffer);

}

void AccountServer::run() {
    start_socket_listen();
    int newClient;
    std::thread t1;

    while (1) {
        newClient = accept_connection();

        std::thread t1(&AccountServer::client_handler, this, newClient);
        t1.detach();
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



//Partie Login

void AccountServer::send_success_id(int client_sock_fd, int player_id){
    /*
     * Renvoi l'id du user qui s'est connecté
     */

    std::string string_id = std::to_string(player_id);
    send_message(client_sock_fd,string_id.c_str());
}

void AccountServer::send_already_connected_error(int client_sock) {
    send_message(client_sock, ALREADY_CO);
}
bool AccountServer::checkCredentials(Credentials credentials) {
    return  myDatabase.is_identifiers_valid(credentials);
}


bool AccountServer::handle_login(Credentials credentials, int client_sock_fd) {
    bool success = false;
    //std::cout << credentials.getUsername() << std::endl;
    //std::cout << credentials.getPassword() << std::endl;

    int player_id = myDatabase.getIDbyUsername(credentials.getUsername()); // Retrieve id of the player
    PlayerConnection player = PlayerConnection(player_id,client_sock_fd);

    if (checkCredentials(credentials) && (!is_player_already_connected(player))){
        add_connected_player(player);
        send_success_id(client_sock_fd, player_id);
        success = true;

    }
    else if (!checkCredentials(credentials)) {
        send_error(client_sock_fd);
    }
    else{
        send_already_connected_error(client_sock_fd);
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
std::vector<std::string> AccountServer::getFriendList(std::string username) {
    return myDatabase.getFriendList(username);
}

std::vector<std::string> AccountServer::getFriendRequests(std::string username){
    return myDatabase.getFriendRequests(username);
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
std::vector<std::string> AccountServer::getPendingInvitations(std::string username){
    return myDatabase.getPendingInvitations(username);
}

bool AccountServer::handle_getFriendList(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getFriendList(requester)).c_str());
    return true;
}
bool AccountServer::handle_getFriendRequests(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getFriendRequests(requester)).c_str());
    return true;

}
bool AccountServer::handle_getPendingInvitations(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getPendingInvitations(requester)).c_str());
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
// partie profil
PublicAccountInfos AccountServer::getPublicAccountInfos(std::string username){
    return myDatabase.getUsrInfosByUsrname(username);
}

bool AccountServer::handle_profile(int client_sock_fd, std::string username) {
    PublicAccountInfos profile = getPublicAccountInfos(username);
    std::string stringProfile = profile.username + "," + profile.victories + ","
                                + profile.defeats + "," + profile.pnjKilled + ";";
    send_message(client_sock_fd,stringProfile.c_str());
    return true;
}

///////////////////////////////////////////////////////////////////////////
void AccountServer::get_and_process_command(int client, char* message_buffer) {
    bool ok = false;

    while (!ok) {
        bool success = receive_message_with_timeout(client, message_buffer, 300);
        if (!success) {
            return;
        }
        
        Command command;
        command.parse(message_buffer);
        std::string command_type = command.getAction();

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
            ok = handle_ranking(client);

        } else if (command_type == "getProfileByUsername") {
            FriendListCommand friendListCommand;
            friendListCommand.parse(message_buffer);
            handle_profile(client,friendListCommand.getRequester());

        } else if (command_type == "getFriendList" || command_type == "getFriendRequests" ||
                   command_type == "addFriend" || command_type == "removeFriend" ||
                   command_type == "acceptFriendRequest" || command_type == "declineFriendRequest" ||
                   command_type == "getPendingInvitations") {

            FriendListCommand friendListCommand;
            friendListCommand.parse(message_buffer);
            std::string action = friendListCommand.getAction();

            if (action == "getFriendList") {

                handle_getFriendList(client, friendListCommand.getRequester());

            } else if (action == "getFriendRequests") {

                handle_getFriendRequests(client, friendListCommand.getRequester());

            } else if (action == "addFriend") {
                std::cout<<friendListCommand.getRequester() + " added " + friendListCommand.getReceiver();

                handle_sendFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
                
            }else if (action == "getPendingInvitations") {
                
                handle_getPendingInvitations(client, friendListCommand.getRequester());
                
            } else if (action == "removeFriend") {

                handle_removeFriend(client, friendListCommand.getRequester(), friendListCommand.getReceiver());

            } else if (action == "acceptFriendRequest") {

                handle_acceptFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());

            } else if (action == "declineFriendRequest") {

                handle_declineFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
            }

        } else if (command_type == "Update"){
            ok = handle_accountUpdate(client);

        } else if(command_type == "Exit"){
            int id = stoi(command.getNextToken());
            ok = handle_exit(id);
        }
    }
}

const std::vector<PlayerConnection> &AccountServer::getConnectedPlayers() const {
    return connectedPlayers;
}

void AccountServer::add_connected_player(PlayerConnection& player) {
    this->connectedPlayers.push_back(player);

}

bool AccountServer::is_player_already_connected(PlayerConnection& player){
    return (std::find(connectedPlayers.begin(), connectedPlayers.end(), player) != connectedPlayers.end());
}

/*
 *Remove a player from the connected players (using his ID as identifier)
*/
bool AccountServer::handle_exit(int player_id){
    
    std::vector<PlayerConnection>::iterator iter;
    for (iter = connectedPlayers.begin(); iter != connectedPlayers.end(); iter++){
        if ((*iter).getPlayer_id() == player_id) {
            connectedPlayers.erase(iter);
            break;
        }
    }
}


bool AccountServer::handle_accountUpdate(int client_sock_fd) {
    char message[BUFFER_SIZE];
    for (int i = 0; i < 4; ++i) {
        //Recevoir les infos des 4 joueurs de la game
        receive_message(client_sock_fd, message);
        UpdateStatsCommand command;
        command.parse(message);
        myDatabase.updateAfterGameStats(command.getPlayerId(), command.getPnjKilled(), command.getIsWinner());
    }
    return true;
}







