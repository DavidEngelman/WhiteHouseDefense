#include "WelcomeManager.hpp"
#include "WelcomeGUI.hpp"
#include "WelcomeConsoleUI.hpp"

WelcomeManager::WelcomeManager(App *my_app) : AbstractManager(my_app) {
    if (isConsole) {
        welcomeUI = new WelcomeConsoleUI(this);
    }else{
        welcomeUI = new WelcomeGUI(this, master_app->getMainWindow());
    }
}

void WelcomeManager::run() {
    welcomeUI->display();
}

WelcomeManager::~WelcomeManager() {
    welcomeUI->destroy();
}

void WelcomeManager::goToLogin() {
    LoginManager *loginManager = new LoginManager(5555, master_app);
    master_app->transition(loginManager);
}

void WelcomeManager::goToRegister() {
    RegisterManager *registerManager = new RegisterManager(5555, master_app);
    master_app->transition(registerManager);
}
