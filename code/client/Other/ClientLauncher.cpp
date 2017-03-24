#include <iostream>
#include <cstring>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <thread>
#include "App.hpp"
#include "global.hpp"
#include "../Profile/ProfileManager.hpp"
#include "../Profile/ProfileGUI.hpp"
#include "MapGUI.hpp"
#include "../Game/GameGUI.hpp"

static const bool DEBUG = true;

App * app;

void launchApp(char *address){
    App * app = new App(address);
}

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

    if (!isConsole) {
        QApplication application(argc, argv);
        application.setApplicationName("White house defense");
        App app(argv[1]);
        return application.exec();
    } else {
        App app(argv[1]);
    }
}

