#ifndef PROJET_REGISTERMANAGER_HPP
#define PROJET_REGISTERMANAGER_HPP

#include "../Other/NetworkedManager.hpp"
#include "RegisterUI.hpp"
#include "../../common/Other/Networking.hpp"
#include "../../common/Other/Credentials.hpp"
#include "../Login/LoginManager.hpp"
#include "../Other/App.hpp"

class RegisterUI;

class RegisterManager : public NetworkedManager {

private:
    RegisterUI *registerUI;
    Credentials registerCredentials;

    bool attemptRegister(Credentials credentials);

    bool checkCredentialsValidity(Credentials credentials);

    void goToLogin();

public:

    RegisterManager(int port, App *my_app);

    virtual ~RegisterManager();

    void run() override;

    void registerUser();

    void goToWelcome();
};

#endif // PROJET_REGISTERMANAGER_HPP