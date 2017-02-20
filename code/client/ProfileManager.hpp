#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include <iostream>
#include "ProfileUI.hpp"
#include "../common/Networking.h"
#include "NetworkedManager.hpp"
#include "MainManager.hpp"
#include "App.hpp"


class ProfileManager : public NetworkedManager {

private:
    int player_id;
	ProfileUI profileUI;

public:
	ProfileManager(int port, char* address, int id);
	void ProfileManagerProcess();
	std::string getProfile(std::string username);
	std::string getProfile(int id);
	void run() override;

};


#endif
