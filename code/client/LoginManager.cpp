
#include "LoginManager.hpp"

LoginManager::LoginManager(int port, char* address): NetworkedManager(port, address) {
    login_process();
};

void LoginManager::login_process() {
    std::string success = "-1"; // En fait success contiendra soit -1 si la co a échouée soit l'id du joueur si ca a réussi
                                // C est peut etre pas très clair :D

    bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

    while (success == "-1" || success == "-2") {

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
        if (success == "-1"){
            loginUI.displayError();
            valid = false;
        }
        else if (success == "-2"){
            loginUI.display_already_co_message();
            valid = false;
        }
    }

    std::cout << "Connection succeeded" << std::endl;
    std::cout << "your id is" << success <<  std::endl;

    MainManager mainManager(ip_address, stoi(success), loginCredentials.getUsername()); //On lance le jeu

    // TODO: les transitions entre managers sont un peu bizarres, parce que l'objet LoginManager ne disparait
    // pas vraiment. Faudrait trouver un moyen de detruire le loginManager et donner le controle à MainManager
    // Pas d'idée pour l'instant

}

bool LoginManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length()!= 0) &&
            (credentials.getUsername().length() <= 16));
    //TODO Peut etre faire une verif plus approfondie :D
}

std::string LoginManager::attemptLogin(Credentials credentials) {
    char server_response[10];

    std::string message = "login," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    std::string ret = std::string(server_response);
    return server_response;
}