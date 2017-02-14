
#include "LoginManager.hpp"

LoginManager::LoginManager(int port, char* address): Manager(port, address) {
    login_process();
};

void LoginManager::login_process() {
    bool success = false;
    bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

    while (not success) {

        while (not valid) {
            loginUI.display(); //demande le  username et pswrd
            toLogin.setUsername(loginUI.get_username_entry());
            toLogin.setPassword(loginUI.get_password_entry());
            valid = checkCredentialsValidity(toLogin);
            if (not valid) {
                loginUI.displayError();
            }
        }

        success = attemptLogin(toLogin);
        if (not success){
            loginUI.displayError();
            valid = false;
        }
    }

    std::cout << "Connection succeeded" << std::endl;
    MainManager mainManager; //On lance le jeu

}

bool LoginManager::checkCredentialsValidity(Credentials credentials) {
    return credentials.getUsername().length() != 0 && credentials.getPassword().length()!= 0;
    //TODO Peut etre faire une verif plus approfondie :D
}

bool LoginManager::attemptLogin(Credentials credentials) {
    char server_response[10];

    std::string message = "login," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;
}