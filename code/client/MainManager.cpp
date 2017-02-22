
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "RankingManager.hpp"
#include "FriendListManager.hpp"


MainManager::MainManager(char* ip_addr, int id, std::string username, App* my_app) :
    AbstractManager(ip_addr, my_app), player_id(id), username(username){}

void MainManager::start_display() {
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            std::cout << "Game Launcher !" << std::endl;
            GameLauncher game = GameLauncher(5556, server_ip_address, player_id, my_master_app);
            my_master_app->transition(&game);
            break;
        }
        case 2: {
            std::cout << "Profile !" << std::endl;
            ProfileManager * profile = new ProfileManager(5555, server_ip_address, player_id, username, my_master_app);
            my_master_app->transition(profile);
            break;
        }
        case 3: {
            std::cout << "Friendlist !" << std::endl;
            FriendListManager * friendList = new FriendListManager(5555, server_ip_address, player_id, username, my_master_app);
            my_master_app->transition(friendList);
            break;
        }
        case 4: {
            RankingManager * rankingManager = new RankingManager(5555, server_ip_address, my_master_app);
            my_master_app->transition(rankingManager);
            break;
        }
        default: {
            std::cout << "Exit !" << std::endl;
            mainUI.exit();
            break;
        }
    }
}

void MainManager::run() {
    start_display();
}