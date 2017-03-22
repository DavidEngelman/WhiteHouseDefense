#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets>



class AbstractManager;
class QMatchMakingThread;

class App : public QObject {
Q_OBJECT

private:

    char *serverIpAddress;
    int playerId;
    std::string username;
    AbstractManager *currentManager;

    QWidget *mainWindow;
    bool is_in_queue;

    QMatchMakingThread *matchMakingThread;


public slots:

    void launchGame(int gameServerSocket);


public:

    App(char *serverIpAddr);

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

    void launchMatchmaking(std::string mode);
};


#endif //PROJET_APP_HPP
