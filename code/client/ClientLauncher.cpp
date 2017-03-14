#include <iostream>
#include <QtWidgets/QApplication>
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

    /*if (!isConsole) { // Pour tester Qt
        QApplication application(argc, argv);

        QPushButton button("TEST");
        button.show();

        return application.exec();
    }*/

    if (!isConsole) {
        QApplication application(argc, argv);
        App app(argv[1]);

        /* Pour tester la MapGUI
        MapGUI mapGUI(1);
        int quadrant = 0;
        GameState gameState = GameState(TEAM_MODE);
        PlayerState playerState = PlayerState();
        gameState.addPlayerState(playerState);
        gameState.addTower(new GunTower(Position(6, 2)), quadrant);
        gameState.addTower(new SniperTower(Position(7, 2)), quadrant);
        gameState.addTower(new ShockTower(Position(8, 2)), quadrant);
        mapGUI.display(gameState, quadrant);
        */

        return application.exec();
    }

    App app(argv[1]);

    return 0;
}