#include "RegisterManager.hpp"

RegisterManager::RegisterManager(int port, char* address):
        NetworkedManager(port, address) {};

/*void RegisterManager::registerUser() {
    bool correctCredentials = false;
    while( !correctCredentials ){
        registerUI.display();
        toRegister.setUsername(registerUI.get_username_entry());
        toRegister.setPassword(registerUI.get_password_entry());

        if (checkCredentialsValidity(toRegister)) {
            correctCredentials = true;
        }
        else{
            registerUI.displayError();
        }
    }

    if (attemptRegister(toRegister)){
        std::cout<< "Your account was successfully registered, you can now login normally.\n";
        LoginManager loginManager(port, ip_address); // On crée un loginManager pour qu'il puisse se connecter

    }else{
        registerUI.displayError();
    }

}*/

void RegisterManager::registerUser() {
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
    LoginManager loginManager(port, ip_address); // On crée un loginManager pour qu'il puisse se connecter

}

bool RegisterManager::attemptRegister(Credentials credentials){
    char server_response[10];
    std::string message = "register," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);

    if (server_response[0] == '1') {
        return true;
    }
    return false;
}


bool RegisterManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length()!= 0) &&
            (credentials.getUsername().length() <= 16));
}


void RegisterManager::run() {
    registerUser();
}