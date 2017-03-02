#include "RegisterManager.hpp"

RegisterManager::RegisterManager(int port, App* my_app):
        NetworkedManager(port, my_app) {};

void RegisterManager::run() {
    bool success = false;
    bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

    while (not success) {

        while (not valid) {
            registerUI.display(); //demande le  username et pswrd
            toRegister.setUsername(registerUI.get_username_entry());
            toRegister.setPassword(registerUI.get_password_entry());
            valid = checkCredentialsValidity(toRegister);
            if (not valid) {
                registerUI.displayError();
            }
        }

        success = attemptRegister(toRegister);
        if (not success){
            registerUI.displayError();
            valid = false;
        }
    }

    std::cout<< "Your account was successfully registered, you can now login normally.\n";
    LoginManager * loginManager = new LoginManager(port, master_app);
    master_app->transition(loginManager);
}

bool RegisterManager::attemptRegister(Credentials credentials){
    char server_response[10];
    std::string message = "register," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);

    return server_response[0] == '1';
}


bool RegisterManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length()!= 0) &&
            (credentials.getUsername().length() <= 16));
}