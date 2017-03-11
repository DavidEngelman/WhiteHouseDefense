
#include "LoginManager.hpp"
#include "LoginGUI.hpp"
#include "../Welcome/WelcomeManager.hpp"

LoginManager::LoginManager(int port, App *my_app) : NetworkedManager(port, my_app),
                                                    loginGUI(new LoginGUI(this)) {}

void LoginManager::run() {
    if (isConsole) {
        std::string success = "-1"; // En fait success contiendra soit -1 si la co a échouée soit l'id du joueur si ca a réussi
        // C est peut etre pas très clair :D

        bool valid = false; // bool qui check si les donnés sont corrects (champs non vide) et peuvent être envoyées au serveur

        while (success == "-1" || success == "-2") {

            while (not valid) {
                loginUI.display(); //demande le  username et pswrd
                loginCredentials.setUsername(loginUI.get_username_entry());

                std::string password_entry = loginUI.get_password_entry();
                password_entry = crypt(password_entry.c_str(), "g4");
                for (unsigned i = 0; i < password_entry.length(); i++) {
                    if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
                }

                loginCredentials.setPassword(password_entry);
                valid = checkCredentialsValidity(loginCredentials);
                if (not valid) {
                    loginUI.displayError();
                }
            }

            success = attemptLogin(loginCredentials);
            if (success == "-1") {
                loginUI.displayError();
                valid = false;
            } else if (success == "-2") {
                loginUI.display_already_co_message();
                valid = false;
            }
        }

        master_app->set_id(stoi(success));
        master_app->set_username(loginCredentials.getUsername());
        goToMain();
    } else {


        loginGUI->setupGUI();
    }
}

bool LoginManager::checkCredentialsValidity(Credentials credentials) {
    return ((credentials.getUsername().length() != 0) && (credentials.getPassword().length() != 0) &&
            (credentials.getUsername().length() <= 16));
    //TODO Peut etre faire une verif plus approfondie :D
}

std::string LoginManager::attemptLogin(Credentials credentials) {
    char server_response[10];

    std::string message = "login," + credentials.getUsername() + "," + credentials.getPassword() + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);
    std::string ret = std::string(server_response);
    return ret;
}

void LoginManager::login() {
    std::string success; // En fait success contiendra soit -1 si la co a échouée soit l'id du joueur si ca a réussi
    // C est peut etre pas très clair :D
    bool valid;

    loginCredentials.setUsername(loginGUI->getUsername());

    std::string password_entry = loginGUI->getPassword();
    password_entry = crypt(password_entry.c_str(), "g4");
    for (unsigned i = 0; i < password_entry.length(); i++) {
        if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
    }

    loginCredentials.setPassword(password_entry);
    valid = checkCredentialsValidity(loginCredentials);
    if (not valid) {
        loginGUI->displayError();
        return;
    }

    success = attemptLogin(loginCredentials);
    if (success == "-1") {
        loginGUI->displayError();
        valid = false;
    } else if (success == "-2") {
        loginGUI->displayAlreadyConnected();
        valid = false;
    }

    if (valid){
        master_app->set_id(stoi(success));
        master_app->set_username(loginCredentials.getUsername());
        goToMain();
    }
}

void LoginManager::goToMain() {
    if (!isConsole) loginGUI->close();
    MainManager *mainManager = new MainManager(5555, master_app);
    master_app->transition(mainManager);
}

void LoginManager::goToWelcome() {
    if (!isConsole) loginGUI->close();
    WelcomeManager *welcomeManager = new WelcomeManager(master_app);
    master_app->transition(welcomeManager);
}