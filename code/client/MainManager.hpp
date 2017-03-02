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
	MainManager(int id, std::string username, App* my_app);
	MainManager(App* my_app);
	void run() override;
};

#endif