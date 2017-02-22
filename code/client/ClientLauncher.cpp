#include "Drawing.hpp"
#include "../common/Map.hpp"
#include "App.hpp"

int main(int argc, char *argv[]) {

    if (argc <= 1){
        std::cout << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    }

    Drawing::drawWhiteHouse("LAUNCHER");

    App app(argv[1]);

    return 0;
}