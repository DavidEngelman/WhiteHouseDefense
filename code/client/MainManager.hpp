#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"
#include "AbstractManager.h"
#include "App.hpp"

class MainManager : public NetworkedManager {

private:
	MainUI mainUI;

public:
	MainManager(int port, App* my_app);
	void run() override;
};

#endif