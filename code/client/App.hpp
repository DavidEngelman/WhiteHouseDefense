#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include <string>
#include <QtWidgets/QApplication>
#include <thread>

#include <QtWidgets>

class AbstractManager;

class App {

private:

    char *server_ip_address;
    int player_id;
    std::string username;
    AbstractManager* current_manager;
    std::thread* background_task;

    QWidget* main_window;

public:

    //App() = default;

    App(char* server_ip_addr);
    virtual void transition(AbstractManager *new_manager);
    virtual void launchBackgroundTask(AbstractManager* manager);

    ~App();

    char *get_ip();
    int get_id();
    std::string get_username();
    
    void set_id(int id);
    void set_username(std::string name);

    void runBackgroundTask(AbstractManager *manager);

    QWidget *getMainWindow();
};


#endif //PROJET_APP_HPP
