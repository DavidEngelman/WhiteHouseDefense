#ifndef MAINMANAGER_HPP
#define MAINMANAGER_HPP

#include "../Other/NetworkedManager.hpp"
#include "../Abstract/AbstractManager.hpp"
#include "../Abstract/AbstractUI.hpp"
#include "../Other/App.hpp"
#include "MainUI.hpp"

class MainUI;
class MainManager : public NetworkedManager {

private:
	MainUI * mainUI;

public:
	MainManager(int port, App* my_app);
	~MainManager();
	void run() override;

    void handleUserMenuChoice();
    void handleGameModeChoice();

	bool isInQueue();

	void leaveQueue();

};

#endif