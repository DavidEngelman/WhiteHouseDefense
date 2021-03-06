#include "App.hpp"
#include "../Welcome/WelcomeManager.hpp"
#include "../Game/GameManager.hpp"
#include "../Game/QMatchMakingThread.hpp"
#include "../Game/GameLauncher.hpp"

App::App(char *serverIpAddr) : serverIpAddress(serverIpAddr),
                               playerId(-1), username("\0"), is_in_queue(false),
                               currentManager(nullptr), mainWindow(nullptr),
                               mediaPlayer(new QMediaPlayer(this)),
                               matchMakingThread(nullptr) {
    if (!isConsole) {
        mainWindow = new QWidget();
        mainWindow->setFixedSize(750, 600); // Will be resized for the menu and games;
        centerWindow();
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

void App::launchMatchmaking(std::string mode) {
    is_in_queue = true;
    if (!isConsole) {
        matchMakingThread = new QMatchMakingThread(mode, getId(), getIp(), getUsername(), this);

        QObject::connect(matchMakingThread, &QMatchMakingThread::gameIsReady,
                         this, &App::launchGame);

        QObject::connect(matchMakingThread, &QMatchMakingThread::finished,
                         matchMakingThread, &QObject::deleteLater);

        matchMakingThread->start();
    } else {
        GameLauncher gameLauncher(MATCHMAKER_SERVER_PORT, this, mode);
        gameLauncher.run();
    }
}

void App::launchGame(int gameServerSocket) {
    matchMakingThread = nullptr;
    std::cout << "Starting game" << std::endl;
    is_in_queue = false;
    if (!isConsole) {
        getMainWindow()->setVisible(false);//So we can reuse the window after the game
    }
    mediaPlayer->stop();
    GameManager *gameManager = new GameManager(gameServerSocket, this);
    transition(gameManager);
}


QWidget *App::getMainWindow() {
    return mainWindow;
}

bool App::isInQueue() {
    return is_in_queue;
}

void App::leaveQueue() {
    if (matchMakingThread != nullptr) {
        matchMakingThread->quitMatchmaking();
        matchMakingThread = nullptr;
        is_in_queue = false;
    }
}

void App::setMusicFromPath(QString musicPath) {

    if (mediaPlayer->currentMedia() ==
        QMediaContent(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath())))
        return;
    mediaPlayer->stop();

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath()));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    mediaPlayer->setVolume(100);
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
}

void App::centerWindow() {
    mainWindow->move(QApplication::desktop()->screen()->rect().center() - mainWindow->rect().center());
}


void App::launchSupporter(int gameServerSocket) {
    std::cout << "Starting game" << std::endl;
    if (!isConsole) {
        getMainWindow()->setVisible(false);//So we can reuse the window after the game
    }
    GameManager *gameManager = new GameManager(gameServerSocket, true, this);
    transition(gameManager);
}

App::~App() {
    // Si le joeur est connecté, on envoye un message de deconnexion au AccountServer
    // et si il est dans un queue du matchmaking, on sort de la queue

    if (username != "") {
        if (matchMakingThread != nullptr) {
            leaveQueue();
        }

        int socket = init_connection_to_server(serverIpAddress, ACCOUNT_SERVER_PORT);
        std::string message = "Exit," + std::to_string(playerId) + ";";
        send_message(socket, message.c_str());

        send_message(socket, COMMUNICATION_OVER.c_str());
    }
}

void App::setFriendListActive(bool isFriendListActive) {
    App::friendListActive = isFriendListActive;
}

bool App::isFriendListActive() const {
    return friendListActive;
}

