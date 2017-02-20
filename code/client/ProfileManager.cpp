//
// Created by jurgen on 2/19/17.
//

#include "ProfileManager.hpp"

ProfileManager::ProfileManager(int port, char *address, int id) :
        NetworkedManager(port, address), player_id(id) {

    ProfileManagerProcess();
}

void ProfileManager::ProfileManagerProcess() {
    profileUI.display();
    int choice = profileUI.select();
    while (choice != 3){
        if (choice == 1){
            profileUI.displayProfile(getProfile(player_id));
        }else if (choice == 2){
            
            std::string profile = profileUI.askUsername();
            std::string serv_resp = getProfile(profile);
            if (serv_resp.size() == 3 ){ // le serveur renvoie ,,;
                std::cout<< "No profile was found with that username";
            }else{
                profileUI.displayProfile(serv_resp);
            }
        }
        profileUI.display();
        choice = profileUI.select();
    }
    MainManager mainManager(ip_address, player_id, my_master_app);
    my_master_app.transition(mainManager);

}

std::string ProfileManager::getProfile(std::string username) {
    std::string message = "getProfileByUsername;" + username+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

std::string ProfileManager::getProfile(int id) {
    std::string message = "getProfileByID;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

