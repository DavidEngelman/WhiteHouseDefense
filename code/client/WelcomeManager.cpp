
#include "WelcomeManager.hpp"

WelcomeManager::WelcomeManager(App* my_app) : AbstractManager(my_app) {}

void WelcomeManager::run() {
    if (isConsole) {
        welcomeUI.display();
        int choice = welcomeUI.select();

        if (choice == 1) {
            LoginManager *loginManager = new LoginManager(5555, master_app);
            master_app->transition(loginManager);
        } else if (choice == 2) {
            RegisterManager *registerManager = new RegisterManager(5555, master_app);
            master_app->transition(registerManager);
        }
    } else {
        //TODO : GUI part
    }
}
