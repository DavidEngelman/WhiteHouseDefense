#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "../NetworkedManager.hpp"
#include "../Abstract/AbstractManager.hpp"
#include "../App.hpp"

class MainGUI;

class MainManager : public NetworkedManager {

private:
	MainUI mainUI;
	MainGUI *mainGUI;

public:
	MainManager(int port, App* my_app);
	void run() override;
};

#endif