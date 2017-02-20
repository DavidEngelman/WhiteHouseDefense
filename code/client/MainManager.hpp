#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"
#include "AbstractManager.h"

class MainManager : public AbstractManager {

private:
	MainUI mainUI;
	char* server_ip_adress;
	int player_id;

	void start_display();

public:
    MainManager(char* ip_addr, int id);
	void run() override;
};

#endif