#include "RegisterManager.hpp"
#include "RegisterGUI.hpp"
#include "RegisterConsoleUI.hpp"
#include "../Welcome/WelcomeManager.hpp"

RegisterManager::RegisterManager(int port, App *my_app) : NetworkedManager(port, my_app) {
    if (isConsole) {
        registerUI = new RegisterConsoleUI(this);
    } else {
        registerUI = new RegisterGUI(this, master_app->getMainWindow());
    }
}

RegisterManager::~RegisterManager() {
    registerUI->destroy();
}

void RegisterManager::newRun() {
    registerUI->display();
}

void RegisterManager::run() {
    if (isConsole) {
        bool success = false;
        bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

        while (not success) {

            while (not valid) {
                valid = true;
                registerUI->display(); //demande le  username et pswrd
                toRegister.setUsername(registerUI->getUsername());

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

                toRegister.setPassword(password_entry);

                if (valid) {
                    valid = checkCredentialsValidity(toRegister);
                    if (not valid) {
                        registerUI->displayError();
                    }
                }
            }

            success = attemptRegister(toRegister);
            if (not success) {
                registerUI->displayError();
                valid = false;
            }
        }

        goToLogin();
    } else {
        registerGUI->display();
    }
}

bool RegisterManager::attemptRegister(Credentials credentials) {
    char server_response[10];
    std::string message = "register," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);
    return server_response[0] == '1';
}


bool RegisterManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length() != 0) &&
            (credentials.getUsername().length() <= 16));
}

void RegisterManager::registerUser() {
    bool success;
    bool valid = true; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

    toRegister.setUsername(registerGUI->getUsername());

    std::string password_entry = registerGUI->getPassword();
    if (registerGUI->getConfirm() != password_entry) {
        registerGUI->displayConfirmError();
        valid = false;
    } else {
        password_entry = crypt(password_entry.c_str(), "g4");
        for (unsigned i = 0; i < password_entry.length(); i++) {
            if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
        }
    }

    toRegister.setPassword(password_entry);

    if (valid) {
        valid = checkCredentialsValidity(toRegister);
        if (not valid) {
            registerGUI->displayError();
        }
    }


    success = attemptRegister(toRegister);
    if (not success) {
        registerGUI->displayError();
        valid = false;
    }

    if (valid) goToLogin();
}

void RegisterManager::goToLogin() {
    if (!isConsole) {
        registerGUI->displaySuccess();
        registerGUI->close();
    } else std::cout << "Your account was registered successfully, you can now login normally.\n";

    LoginManager *loginManager = new LoginManager(port, master_app);
    master_app->transition(loginManager);
}

void RegisterManager::goToWelcome() {
    if (!isConsole) registerGUI->close();
    WelcomeManager *welcomeManager = new WelcomeManager(master_app);
    master_app->transition(welcomeManager);
}
