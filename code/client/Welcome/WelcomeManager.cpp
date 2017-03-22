#include "WelcomeManager.hpp"
#include "WelcomeGUI.hpp"
#include "WelcomeConsoleUI.hpp"

WelcomeManager::WelcomeManager(App *my_app) : AbstractManager(my_app) {
    if (isConsole) {
        welcomeUI = new WelcomeConsoleUI(this);
    }else{
        welcomeUI = new WelcomeGUI(this, master_app->getMainWindow()))
    }
}

void WelcomeManager::run() {
    if (isConsole) {
        welcomeUI->display();
        int choice = welcomeUI->select();

        if (choice == 1) goToLogin();
        else if (choice == 2) goToRegister();
    } else {
        welcomeGUI->display();
    }
}

void WelcomeManager::goToLogin() {
    if (!isConsole) welcomeGUI->close();
    LoginManager *loginManager = new LoginManager(5555, master_app);
    master_app->transition(loginManager);
}

void WelcomeManager::goToRegister() {
    if (!isConsole) welcomeGUI->close();
    RegisterManager *registerManager = new RegisterManager(5555, master_app);
    master_app->transition(registerManager);
}

WelcomeManager::~WelcomeManager() {
    // TODO: use better system.
    if (!isConsole) delete (welcomeGUI);
}
