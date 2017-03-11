//
// Created by jurgen on 2/19/17.
//

#include "ProfileManager.hpp"
#include "ProfileGUI.hpp"

ProfileManager::ProfileManager(int port, App* my_app) :
        NetworkedManager(port, my_app),  profileGUI(new ProfileGUI(this)) {}

void ProfileManager::ProfileManagerProcess() {

    if (isConsole) {
        profileUI.display();
        int choice = profileUI.select();
        while (choice != 3) {
            if (choice == 1) {
                profileUI.displayProfile(getProfile(master_app->get_username()));
            } else if (choice == 2) {

                std::string profile = profileUI.askUsername();
                std::string serv_resp = getProfile(profile);
                if (serv_resp.size() == 3) { // le serveur renvoie ,,;
                    std::cout << "No profile was found with that username" << std::endl;
                } else {
                    profileUI.displayProfile(serv_resp);
                }
            }
            profileUI.display();
            choice = profileUI.select();
        }
        MainManager *mainManager = new MainManager(5555, master_app);
        master_app->transition(mainManager);
    } else{
        profileGUI->setupGUI();

    }
}

std::string ProfileManager::getProfile(std::string username) {
    std::string message = GET_PROFILE + username+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}


void ProfileManager::run() {
    ProfileManagerProcess();

}

std::string ProfileManager::getUsername() {
    std::cout << master_app->get_username() << std::endl;
    return master_app->get_username();
}
