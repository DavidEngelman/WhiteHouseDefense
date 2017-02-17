#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "MainUI.hpp"
#include "Manager.hpp"

class MainManager :public Manager{

private:
	MainUI mainUI;

public:
    MainManager();
};

#endif