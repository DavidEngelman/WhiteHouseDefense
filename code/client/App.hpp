#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include <string>
#include <QtWidgets/QApplication>
#include <thread>

#include <QtWidgets>

class GameLauncher;
class AbstractManager;

class App: public QObject {
    Q_OBJECT

private:

    char *serverIpAddress;
    int playerId;
    std::string username;
    AbstractManager* currentManager;
    std::thread* backgroundTask;

    QWidget* mainWindow;
    GameLauncher* gameLauncher;
    bool is_in_queue;

public slots:
    void launchGame(int gameServerSocket);

public:

    App(char* serverIpAddr);

    virtual void transition(AbstractManager *new_manager);

    char *getIp();
    int getId();
    std::string getUsername();
    
    void setId(int id);
    void setUsername(std::string name);

    QWidget *getMainWindow();

    ~App();

    bool isInQueue();

    void leaveQueue();

//    void setMainWindow(QWidget *pWidget);


    void launchMatchmaking(std::string mode, int serverSocket);
};


#endif //PROJET_APP_HPP
