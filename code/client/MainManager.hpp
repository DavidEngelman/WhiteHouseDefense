#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"
#include "AbstractManager.h"
#include "App.hpp"

class MainManager : public AbstractManager {

private:
	MainUI mainUI;
	int player_id;
	std::string username;

public:
	MainManager(char* ip_addr, int id, std::string username, App* my_app);
	void run() override;
};

#endif