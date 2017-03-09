#include <iostream>
#include "App.hpp"
#include "GameManager.hpp"

int main(int argc, char *argv[]) {
    if (argc == 1){
        std::cerr << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    } else if (argc == 3) {
        if (argv[2] == "-c" or argv[2] == "--console") {
            std::cout << "Console mode" << std::endl;
            //TODO: qqch pour ne pas lancer les GUI mais lancer les UI à la place
        }
    }

    App app(argv[1]);

    return 0;
}