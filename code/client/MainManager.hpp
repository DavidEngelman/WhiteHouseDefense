#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "NetworkedManager.hpp"

class MainManager :public NetworkedManager{

private:
	MainUI mainUI;

public:
    MainManager();
};

#endif