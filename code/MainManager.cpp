
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "FriendList.hpp"


MainManager::MainManager() {
    mainUI = MainUI();
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            std::cout << "Game Launcher !" << std::endl;
            GameLauncher game = GameLauncher();
            break;
        }
        case 2: {
            std::cout << "Profile !" << std::endl;
            ProfileManager profile = ProfileManager();
            break;
        }
        case 3: {
            std::cout << "Friendlist !" << std::endl;
            FriendList friendList = FriendList();
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            std::cout << "Exit !" << std::endl;
            mainUI.exit();
            break;
        }
    }
}
