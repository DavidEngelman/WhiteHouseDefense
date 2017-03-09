#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include <string>
#include <QtWidgets/QApplication>

class AbstractManager;

class App {

private:

    char *server_ip_address;
    int player_id;
    std::string username;
    AbstractManager* current_manager;

public:

    //App() = default;

    App(char* server_ip_addr);
    virtual void transition(AbstractManager *new_manager);

    ~App() = default;

    char *get_ip();
    int get_id();
    std::string get_username();
    
    void set_id(int id);
    void set_username(std::string name);
};


#endif //PROJET_APP_HPP
