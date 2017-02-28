
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "RankingManager.hpp"
#include "FriendListManager.hpp"


MainManager::MainManager(char* ip_addr, int id, std::string username, App* my_app) :
    AbstractManager(ip_addr, my_app), player_id(id), username(username){}

void MainManager::run() {
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            mainUI.displayGameModes();
            switch(mainUI.selectGameMode()){
                case 1:{
                    GameLauncher * game = new  GameLauncher(5556, server_ip_address, player_id, username, master_app, CLASSIC_MODE);
                    master_app->transition(game);
                    break;
                }
                case 2:{
                    GameLauncher * game = new  GameLauncher(5556, server_ip_address, player_id, username, master_app, TIMED_MODE);
                    master_app->transition(game);
                    break;

                }
                case 3:{
                    GameLauncher * game = new  GameLauncher(5556, server_ip_address, player_id, username, master_app, TEAM_MODE);
                    master_app->transition(game);
                    break;
                }

            }

        }
        case 2: {
            ProfileManager * profile = new ProfileManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(profile);
            break;
        }
        case 3: {
            FriendListManager * friendListManager = new FriendListManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(friendListManager);
            break;
        }
        case 4: {
            RankingManager * rankingManager = new RankingManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(rankingManager);
            break;
        }
        default: {
            std::cout << "Exit !" << std::endl;
            break;
        }
    }
}