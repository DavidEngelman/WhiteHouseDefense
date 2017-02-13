#include "LoginManager.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    if (argc < 1){
        std::cout << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    }

    LoginManager myTestManager = LoginManager(5555, argv[1]);

    return 0;
}
