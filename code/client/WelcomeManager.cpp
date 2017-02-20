//
//

#include "WelcomeManager.h"

WelcomeManager::WelcomeManager(char *ip_addr) : AbstractManager(ip_addr) {
    run();
}

void WelcomeManager::welcome_process() {
    welcomeUI.display();
    int choice = welcomeUI.select();

    if (choice == 1) {

        LoginManager loginManager(5555, server_ip_address);
        my_master_app->transition(&loginManager);

    } else if (choice == 2) {
        RegisterManager registerManager(5555, server_ip_address);
        my_master_app->transition(&registerManager);
        //
    } else if (choice == 3) {
        //
    }
}

void WelcomeManager::run() {
    welcome_process();
}

