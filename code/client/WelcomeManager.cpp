
#include "WelcomeManager.hpp"

WelcomeManager::WelcomeManager(App* my_app) : AbstractManager(my_app), welcomeGUI(this) {}

void WelcomeManager::run() {
    if (isConsole) {
        welcomeUI.display();
        int choice = welcomeUI.select();

        if (choice == 1) goToLogin();
        else if (choice == 2) goToRegister();
    } else {
        welcomeGUI.setupGUI();
    }
}

void WelcomeManager::goToLogin() {
    LoginManager *loginManager = new LoginManager(5555, master_app);
    master_app->transition(loginManager);
}

void WelcomeManager::goToRegister() {
    RegisterManager *registerManager = new RegisterManager(5555, master_app);
    master_app->transition(registerManager);
}
