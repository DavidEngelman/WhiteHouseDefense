
#include "LoginManager.hpp"

LoginManager::LoginManager() {};

void LoginManager::login_process() {
    bool success = false;
    bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

    while (not success) {

        while (not valid) {
            loginUI.display(); //demande le  username et pswrd
            valid = checkCredentialsValidity(loginUI.get_username_entry(), loginUI.get_password_entry());
            if (not valid) {
                loginUI.displayError();
            }
        }

        success = attemptLogin(loginUI.get_username_entry(), loginUI.get_password_entry());
        if (not success){
            loginUI.displayError();
            valid = false;
        }
    }

    std::cout << "Connection succeeded" << std::endl;

}

bool LoginManager::checkCredentialsValidity(std::string name, std::string password) {
    return name.length() != 0 && password.length()!= 0;
    //TODO Peut etre faire une verif plus approfondie :D
}

bool LoginManager::attemptLogin(std::string name, std::string password) {

}