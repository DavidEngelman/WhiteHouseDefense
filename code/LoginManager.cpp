
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
            loginCredentials.setUsername(loginUI.get_username_entry());
            loginCredentials.setPassword(loginUI.get_password_entry());
            valid = checkCredentialsValidity(loginCredentials);
            if (not valid) {
                loginUI.displayError();
            }
        }

        success = attemptLogin(loginCredentials);
        if (not success){
            loginUI.displayError();
            valid = false;
        }
    }

    std::cout << "Connection succeeded" << std::endl;
    MainManager mainManager; //On lance le jeu

    // TODO: les transitions entre managers sont un peu bizarres, parce que l'objet LoginManager ne disparait
    // pas vraiment. Faudrait trouver un moyen de detruire le loginManager et donner le controle à MainManager
    // Pas d'idée pour l'instant

}

bool LoginManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length()!= 0) &&
            (credentials.getUsername().length() <= 16));
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