#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#define MAX_BUFF_SIZE 1000

#include <iostream>
#include "../../common/Networking.h"
#include "../../common/Strings.hpp"
#include "../NetworkedManager.hpp"
#include "../Main/MainManager.hpp"
#include "../App.hpp"
#include "ProfileUI.hpp"

class ProfileUI;

class ProfileManager : public NetworkedManager {

private:
	ProfileUI * profileUI;

    std::string username;
    int victories;
    int npcKilled;
    
public:
	ProfileManager(int port, App* my_app);
    
	std::string getPlayerUsername();

    int getVictories() const;

    int getNPCKilled() const;
    
    std::string& getUsername();


    void run() override;

    void showMyProfile();

    void showProfile();

    void goToMainMenu();

    void getAndParseProfile(std::string username);

    void parseProfileData(char * profileData);
};


#endif
