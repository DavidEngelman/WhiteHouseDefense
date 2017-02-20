#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

class AbstractManager;

class App {

private:

    AbstractManager* current_manager;

public:

    App(char* server_ip_addr);

    virtual void transition(AbstractManager *new_manager);

    virtual ~App() = default;

};


#endif //PROJET_APP_HPP
