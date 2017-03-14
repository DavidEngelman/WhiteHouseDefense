#include <iostream>
#include <cstring>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "App.hpp"
#include "global.hpp"
#include "Profile/ProfileManager.hpp"
#include "Profile/ProfileGUI.hpp"

static const bool DEBUG = true;

int main(int argc, char *argv[]) {

    isConsole = false;

    if (argc == 1) {
        std::cerr << "Don't forget the ip_adress of the server as argument! ;)" << std::endl;
        exit(1);
    } else if (argc == 3) {
        if (strcmp(argv[2], "-c") == 0 or strcmp(argv[2], "--console") == 0) {
            isConsole = true;
        }
    }

    /*if (!isConsole) { // Pour tester Qt
        QApplication application(argc, argv);

        QPushButton button("TEST");
        button.show();

        return application.exec();
    }*/

    if (!isConsole) {
        QApplication application(argc, argv);
        App app(argv[1]);
        std::cout << argv[1] << std::endl;
        return application.exec();

    }

//    App app(argv[1]);


    return 0;
}