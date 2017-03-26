#include "AccountServer.hpp"
//#include "FriendListCommand.h"
#include "../../common/Other/Strings.hpp"
#include "../Commands/FriendListCommand.hpp"

AccountServer::AccountServer(int port, const char *databaseName) : Server(port), database(Database(databaseName)) {}

void* AccountServer::client_handler(int client_sock) {
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

///////////////////////////////////////////////////////////////////////////
void AccountServer::get_and_process_command(int client, char* message_buffer) {
    bool end_communication = false;

    while (!end_communication) {

        bool success = receive_message_with_timeout(client, message_buffer, 300);
        if (!success) {
            return;
        }

        Command command;
        command.parse(message_buffer);
        std::string action = command.getAction();

        if ((action == "login") || (action == "register")) {

            //Si on est dans le cas ou quelqu'un essaye de se connecter/register

            LoginRegisterCommand command;
            command.parse(message_buffer);
            Credentials credentials = command.getCreds();

            if (command.getAction() == "login") {
                handle_login(credentials, client);
            } else if (command.getAction() == "register") {
                handle_register(credentials, client);
            } else {
                // Show "unknown command" error
            }
        } else if (action == "ranking") {
            handle_ranking(client);

        } else if (action == "getProfileByUsername") {
            FriendListCommand friendListCommand;
            friendListCommand.parse(message_buffer);
            handle_profile(client,friendListCommand.getRequester());

        } else if (action == "getFriendList" || action == "getFriendRequests" ||
                   action == "addFriend" || action == "removeFriend" ||
                   action == "acceptFriendRequest" || action == "declineFriendRequest" ||
                   action == "getPendingInvitations" || action == "getStatus") {

            FriendListCommand friendListCommand;
            friendListCommand.parse(message_buffer);
            std::string action = friendListCommand.getAction();
            friendListMutex.lock();

            if (action == "getFriendList") {

                handle_getFriendList(client, friendListCommand.getRequester());
                friendListMutex.unlock();

            } else if (action == "getFriendRequests") {

                handle_getFriendRequests(client, friendListCommand.getRequester());
                friendListMutex.unlock();

            } else if (action == "addFriend") {

                handle_sendFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
                friendListMutex.unlock();

            } else if (action == "getPendingInvitations") {

                handle_getPendingInvitations(client, friendListCommand.getRequester());
                friendListMutex.unlock();

            } else if (action == "removeFriend") {

                handle_removeFriend(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
                friendListMutex.unlock();

            } else if (action == "acceptFriendRequest") {

                handle_acceptFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
                friendListMutex.unlock();

            } else if (action == "declineFriendRequest") {

                handle_declineFriendRequest(client, friendListCommand.getRequester(), friendListCommand.getReceiver());
                friendListMutex.unlock();

            } else if (action == "getStatus") {

                handle_getStatus(client, friendListCommand.getRequester());
                friendListMutex.unlock();

            }

        } else if (action == "Update"){
            handle_accountUpdate(client);

        } else if(action == "Exit"){
            int id = stoi(command.getNextToken());
            handle_exit(id);

        } else if (action == CHANGE_USERNAME) {
            int id = stoi(command.getNextToken());
            std::string newUsername = command.getNextToken();
            handle_changeUsername(newUsername, id, client);

        } else if (action == CHANGE_PASSWORD) {
            int id = stoi(command.getNextToken());
            std::string newPassword = command.getNextToken();
            handle_changePassword(newPassword, id);

        } else if (action == CHANGE_ICON) {
            int id = stoi(command.getNextToken());
            std::string newIcon = command.getNextToken();
            handle_changeIcon(stoi(newIcon), id);

        } else if (action == COMMUNICATION_OVER){
            std::cout  << "Ending communication with " << client << std::endl;
            end_communication = true;

        }
    }
}

/*Register part*/

bool AccountServer::insert_account_in_db(Credentials credentials) {
    return database.insert_account(credentials) != -1;
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



/*Partie Login*/

void AccountServer::send_success_id(int client_sock_fd, int player_id){
    /*
     * Send the id of the user who has just logged in.
     */

    std::string string_id = std::to_string(player_id);
    send_message(client_sock_fd,string_id.c_str());
}

void AccountServer::send_already_connected_error(int client_sock) {
    send_message(client_sock, ALREADY_CO);
}
bool AccountServer::checkCredentials(Credentials credentials) {
    return  database.is_identifiers_valid(credentials);
}


void AccountServer::handle_login(Credentials credentials, int client_sock_fd) {
    //std::cout << credentials.getUsername() << std::endl;
    //std::cout << credentials.getPassword() << std::endl;

    int player_id = database.getIDbyUsername(credentials.getUsername()); // Retrieve id of the player
    PlayerConnection player = PlayerConnection(player_id,client_sock_fd);

    if (checkCredentials(credentials) && (!is_player_already_connected(player))){
        player.setUsername(credentials.getUsername());
        add_connected_player(player);
        send_success_id(client_sock_fd, player_id);
    }
    else if (!checkCredentials(credentials)) {
        send_error(client_sock_fd);
    }
    else{
        send_already_connected_error(client_sock_fd);
    }
}

/*Ranking part*/

std::vector<RankingInfos> AccountServer::getRanking() {
    return database.getRanking();
}

void AccountServer::handle_ranking(int client_sock_fd) {
    send_message(client_sock_fd, vectorTostring(getRanking()).c_str());
}

std::string AccountServer::vectorTostring(std::vector<RankingInfos> vect) {

    /*
     * Creation of a string  "username,nbVictories|username,nvVictories|
    */

    std::string result = "";
    for (int i = 0; i < vect.size(); i++) {
        result+=vect[i].username;
        result+=",";
        result+= std::to_string(vect[i].victories);
        result+="|";
    }
    return result;
}

/*Friendlist part*/

std::vector<std::string> AccountServer::getFriendList(std::string username) {
    return database.getFriendList(username);
}

std::vector<std::string> AccountServer::getFriendRequests(std::string username){
    return database.getFriendRequests(username);
}

bool AccountServer::sendFriendRequest(std::string requester, std::string receiver) {
    return database.sendFriendRequest(requester,receiver) != -1 ;
}
bool AccountServer::acceptFriendRequest(std::string requester, std::string receiver) {
    return database.acceptFriendRequest(requester,receiver) != -1 ;
}
bool AccountServer::declineFriendRequest(std::string requester, std::string receiver) {
    return database.declineFriendRequest(requester, receiver) != -1 ;
}
bool AccountServer::removeFriend(std::string requester, std::string receiver) {
    return database.removeFriend(requester,receiver) != -1 ;
}
std::vector<std::string> AccountServer::getPendingInvitations(std::string username){
    return database.getPendingInvitations(username);
}

void AccountServer::handle_getFriendList(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getFriendList(requester)).c_str());
}

void AccountServer::handle_getFriendRequests(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getFriendRequests(requester)).c_str());
}

void AccountServer::handle_getPendingInvitations(int client_sock_fd, std::string requester) {
    send_message(client_sock_fd, vectorTostring(getPendingInvitations(requester)).c_str());
}

void AccountServer::handle_acceptFriendRequest(int client_sock_fd, std::string requester, std::string toAccept) {

    if (acceptFriendRequest(requester, toAccept)){
        send_success(client_sock_fd);
    }
    else {
        send_error(client_sock_fd);
    }
}

void AccountServer::handle_declineFriendRequest(int client_sock_fd, std::string requester, std::string toDecline) {
    if (declineFriendRequest(requester, toDecline)){
        send_success(client_sock_fd);
    } else {
        send_error(client_sock_fd);
    }
}

void AccountServer::handle_sendFriendRequest(int client_sock_fd, std::string requester, std::string toAdd) {
    if (sendFriendRequest(requester, toAdd)){
        send_success(client_sock_fd);
    } else {
        send_error(client_sock_fd);
    }
}

void AccountServer::handle_removeFriend(int client_sock_fd, std::string requester, std::string toRemove) {
    if (removeFriend(requester, toRemove)){
        send_success(client_sock_fd);
    } else {
        send_error(client_sock_fd);
    }
}

void AccountServer::handle_getStatus(int client_sock_fd, std::string username) {
    bool connected = false;

    for(PlayerConnection player : getConnectedPlayers()){
        if (player.getUsername() == username){
            connected = true;
            send_message(client_sock_fd,"1");
            break;
        }
    }
    if (!connected) {
        send_message(client_sock_fd, "0");
    }
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
/*Profil part*/
PublicAccountInfos AccountServer::getPublicAccountInfos(std::string username){
    return database.getUsrInfosByUsrname(username);
}

bool AccountServer::handle_profile(int client_sock_fd, std::string username) {
    PublicAccountInfos profile = getPublicAccountInfos(username);

    std::string stringProfile = profile.username + "," + profile.victories + ","
    + profile.defeats + "," + profile.pnjKilled + "," + profile.iconID + ";";

    send_message(client_sock_fd,stringProfile.c_str());
    std::cout << stringProfile << std::endl;
    return true;
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
void AccountServer::handle_exit(int player_id){
    std::vector<PlayerConnection>::iterator iter;
    for (iter = connectedPlayers.begin(); iter != connectedPlayers.end(); iter++){
        if ((*iter).getPlayer_id() == player_id) {
            connectedPlayers.erase(iter);
            break;
        }
    }
}


void AccountServer::handle_accountUpdate(int client_sock_fd) {
    char message[BUFFER_SIZE];
    for (int i = 0; i < 4; ++i) {
        receive_message(client_sock_fd, message); //receive the infos (player_id, npcKilled, isWinner) of the 4 players
        UpdateStatsCommand command;
        command.parse(message);
        database.updateAfterGameStats(command.getPlayerId(), command.getPnjKilled(), command.getIsWinner());
    }
}

void AccountServer::handle_changeUsername(std::string username, int id, int client_socket) {
    if(database.update_username(id, username) != -1){
        send_success(client_socket);
    } else{
        send_error(client_socket);
    }
}

void AccountServer::handle_changePassword(std::string password, int id) {
    database.update_password(id, password);
}

void AccountServer::handle_changeIcon(int iconName, int id) {
    database.updateIcon(id, iconName);
}







