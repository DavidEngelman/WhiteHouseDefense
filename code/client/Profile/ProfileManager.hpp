#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#define MAX_BUFF_SIZE 1000

#include <iostream>
#include "../../common/Other/Networking.hpp"
#include "../../common/Other/Strings.hpp"
#include "../Other/NetworkedManager.hpp"
#include "../Main/MainManager.hpp"
#include "../Other/App.hpp"
#include "ProfileUI.hpp"

class ProfileUI;

class ProfileManager : public NetworkedManager {

private:
	ProfileUI * profileUI;

    std::string username;
    int victories;
	int defeats;
    int npcKilled;
	int iconID;

public:
	ProfileManager(int port, App* my_app);

    int getVictories() const;

    int getNPCKilled() const;

    std::string& getUsername();


    void run() override;

    void showMyProfile();

    void showProfile();

    void goToMainMenu();

    void getAndParseProfile(std::string username);

    void parseProfileData(char * profileData);

	~ProfileManager();

	int getDefeats() const;

	int getIconID() const;
};


#endif
