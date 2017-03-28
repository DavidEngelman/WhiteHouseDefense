#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include <string>
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>


class AbstractManager;

class QMatchMakingThread;

class App : public QObject {
Q_OBJECT

private:

    char *serverIpAddress;
    int playerId;
    std::string username;
    AbstractManager *currentManager;

    bool is_in_queue;
    QMatchMakingThread *matchMakingThread;

    QWidget *mainWindow;
    QMediaPlayer *mediaPlayer;

    bool friendListActive = false;


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

    bool isInQueue();

    void leaveQueue();

    void launchMatchmaking(std::string mode);

    virtual void setMusicFromPath(QString musicPath);

    virtual void centerWindow();

    void launchSupporter(int gameServerSocket);

    void setFriendListActive(bool isFriendListActive);

    bool isFriendListActive() const;

    ~App();
};


#endif //PROJET_APP_HPP
