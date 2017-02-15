
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "FriendList.hpp"
#include "RankingManager.hpp"


MainManager::MainManager() : Manager(5555, "127.0.0.1")/*TEMPORAIRE*/{
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
            RankingManager rankingManager(5555,ip_address);
            break;
        }
        case 5: {
            std::cout << "Exit !" << std::endl;
            mainUI.exit();
            break;
        }
    }
}
