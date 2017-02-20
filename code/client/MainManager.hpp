#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"
#include "AbstractManager.h"
#include "App.hpp"

class MainManager : public AbstractManager {

private:
	MainUI mainUI;


public:
    MainManager(char* ip_addr, int id);
	void run() override;
};

#endif