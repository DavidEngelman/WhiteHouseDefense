#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#define MAX_BUFF_SIZE 1000

#include <iostream>
#include "../../common/Networking.h"
#include "../../common/Strings.hpp"
#include "../NetworkedManager.hpp"
#include "../Main/MainManager.hpp"
#include "../App.hpp"
#include "ProfileUI.hpp"

class ProfileUI;

class ProfileManager : public NetworkedManager {

private:
	ProfileUI * profileUI;
public:
	ProfileManager(int port, App* my_app);
	void ProfileManagerProcess();

    std::string getProfile(std::string username);
	std::string getUsername();

    void run() override;
	void handleUserChoice();

    void showMyProfile();

    void showProfile();

    void goToMainMenu();
};


#endif
