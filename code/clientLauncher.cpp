#include "LoginManager.hpp"
#include "RegisterManager.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    if (argc < 1){
        std::cout << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    }

    int choice = 0;
    bool ok = false;

    while (!ok) {
        std::cout << "Press 1 to log in or 2 to register a new account" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            LoginManager myLoginManager = LoginManager(5555, argv[1]);
            ok = true;
        }

        else if (choice == 2) {
            RegisterManager myRegisterManager = RegisterManager(5555, argv[1]);
            ok = true;
        }
        else
            std::cout << "Please enter 1 or 2" << std::endl;

    }

    return 0;
}
