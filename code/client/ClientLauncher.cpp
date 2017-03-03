#include <iostream>
#include "App.hpp"
#include "GameManager.hpp"

int main(int argc, char *argv[]) {
    if (argc <= 1){
        std::cerr << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    }

    App app(argv[1]);

    return 0;
}