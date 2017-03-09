#include <iostream>
#include <cstring>
#include "App.hpp"
#include "global.hpp"

int main(int argc, char *argv[]) {
    isConsole = false;

    if (argc == 1){
        std::cerr << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    } else if (argc == 3) {
        if (strcmp(argv[2], "-c") == 0 or strcmp(argv[2], "--console") == 0) {
            isConsole = true;
        }
    }

    App app(argv[1]);

    return 0;
}