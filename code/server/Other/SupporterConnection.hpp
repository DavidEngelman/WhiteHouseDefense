//
//

#ifndef PROJET_SUPPORTERCONNECTION_H
#define PROJET_SUPPORTERCONNECTION_H

#include <string>

class SupporterConnection {

private:
    int supporterSocket;
    std::string playerSupported;

public:
    SupporterConnection() = default;

    int getSupporterSocket();
    void setSupporterSocket(int socket);

    std::string getPlayerSupported();
    void setPlayerSupported(std::string &player);
};


#endif //PROJET_SUPPORTERCONNECTION_H
