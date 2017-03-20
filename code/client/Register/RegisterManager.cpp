#include "RegisterManager.hpp"
#include "RegisterGUI.hpp"
#include "RegisterConsoleUI.hpp"
#include "../Welcome/WelcomeManager.hpp"

//REFACTORED
RegisterManager::RegisterManager(int port, App *my_app) : NetworkedManager(port, my_app) {
    if (isConsole) {
        registerUI = new RegisterConsoleUI(this);
    } else {
        registerUI = new RegisterGUI(this, master_app->getMainWindow());
    }
}

//REFACTORED
RegisterManager::~RegisterManager() {
    registerUI->destroy();
}

//REFACTORED
void RegisterManager::run() {
    registerUI->display();
}

//NO CHANGES
bool RegisterManager::attemptRegister(Credentials credentials) {
    char server_response[10];
    std::string message = "register," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);
    return server_response[0] == '1';
}

//NO CHANGES
bool RegisterManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length() != 0) &&
            (credentials.getUsername().length() <= 16));
}

//REFACTORED
void RegisterManager::registerUser() {
    bool success;
    bool valid = true; // vérifie la validité des données (champs non vides) et si elles peuvent être envoyées au serveur.

    registerCredentials.setUsername(registerUI->getUsername());

    std::string password_entry = registerUI->getPassword();
    if (registerUI->getConfirm() != password_entry) {
        registerUI->displayConfirmError();
        valid = false;
    } else {
        password_entry = crypt(password_entry.c_str(), "g4");
        for (unsigned i = 0; i < password_entry.length(); i++) {
            if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
        }
    }
    registerCredentials.setPassword(password_entry);

    if (valid) {
        valid = checkCredentialsValidity(registerCredentials);
        if (not valid) {
            registerUI->displayError();
        }
    }

    success = attemptRegister(registerCredentials);
    if (not success) {
        registerUI->displayError();
        valid = false;
    }

    if (valid) goToLogin();
}

//REFACTORED
void RegisterManager::goToLogin() {
    registerUI->displaySuccess();
    LoginManager *loginManager = new LoginManager(port, master_app);
    master_app->transition(loginManager);
}

//REFACTORED
void RegisterManager::goToWelcome() {
    WelcomeManager *welcomeManager = new WelcomeManager(master_app);
    master_app->transition(welcomeManager);
}
