#ifndef PROJET_REGISTERMANAGER_HPP
#define PROJET_REGISTERMANAGER_HPP

#include "../NetworkedManager.hpp"
#include "RegisterUI.hpp"
#include "../../common/Networking.hpp"
#include "../../common/Credentials.hpp"
#include "../Login/LoginManager.hpp"
#include "../App.hpp"

class RegisterUI;

class RegisterManager : public NetworkedManager {

private:
    RegisterUI *registerUI; // TODO: fix, it's a pointer so that it compiles
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