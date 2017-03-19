#include "App.hpp"
#include "Welcome/WelcomeManager.hpp"
#include "Game/QMatchMakingThread.hpp"
#include "Game/GameManager.hpp"

App::App(char *serverIpAddr) : serverIpAddress(serverIpAddr),
                               playerId(-1), username("\0"), is_in_queue(false) ,
                               currentManager(nullptr), mainWindow(nullptr) {
    if (!isConsole) {
        mainWindow = new QWidget();
        mainWindow->setFixedSize(750, 600); // Will be resized for the menu and games;
    }
    currentManager = new WelcomeManager(this);
    currentManager->run();
}

void App::transition(AbstractManager *new_manager) {
    delete (currentManager);
    currentManager = new_manager;
    currentManager->run();
}

char *App::getIp() {
    return serverIpAddress;
}

int App::getId() {
    return playerId;
}

std::string App::getUsername() {
    return username;
}

void App::setId(int id) {
    playerId = id;
}

void App::setUsername(std::string name) {
    username = name;
}

App::~App() {
    if (username != "") { // Si le joeur est connecté, on envoye un message de deconexion
        int socket = init_connection_to_server(serverIpAddress, ACCOUNT_SERVER_PORT);
        std::string message = "Exit," + std::to_string(playerId);
        send_message(socket, message.c_str());
    }
}

void App::launchMatchmaking(GameLauncher *manager) {
    gameLauncher = manager;
    backgroundTask = new std::thread(&App::runBackgroundTask, this, manager);
}

void App::launchMatchmaking(std::string mode, int serverSocket) {
    is_in_queue = true;
    QMatchMakingThread *matchMakingThread = new QMatchMakingThread(mode, getId(), getIp(), getUsername(), this);

    QObject::connect(matchMakingThread, &QMatchMakingThread::gameIsReady,
                     this, &App::launchGame);

    QObject::connect(matchMakingThread, &QMatchMakingThread::finished,
                     matchMakingThread, &QObject::deleteLater);

    matchMakingThread->start();
}

void App::launchGame(int gameServerSocket) {
    std::cout << "Starting game" << std::endl;
    is_in_queue = false;
    GameManager * gameManager = new GameManager(gameServerSocket, this);
    transition(gameManager);
}

void App::runBackgroundTask(AbstractManager *manager) {
    is_in_queue = true;
    manager->run();
}


QWidget *App::getMainWindow() {
    return mainWindow;
}

bool App::isInQueue() {
    return is_in_queue;
}

void App::leaveQueue() {
    gameLauncher->leaveQueue();
    is_in_queue = false;

}
