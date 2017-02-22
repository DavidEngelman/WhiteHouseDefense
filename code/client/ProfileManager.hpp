#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include <iostream>
#include "ProfileUI.hpp"
#include "../common/Networking.h"
#include "../common/Strings.hpp"
#include "NetworkedManager.hpp"
#include "MainManager.hpp"
#include "App.hpp"


class ProfileManager : public NetworkedManager {

private:
    int player_id;
	ProfileUI profileUI;
	std::string username;

public:
	ProfileManager(int port, char* address, int id, std::string username, App* my_app);
	void ProfileManagerProcess();
	std::string getProfile(std::string username);
	void run() override;
};


#endif
