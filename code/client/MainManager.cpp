
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "RankingManager.hpp"
#include "FriendListManager.hpp"


MainManager::MainManager(char* ip_addr, int id, std::string username) : server_ip_adress(ip_addr), player_id(id), username(username){
    std::cout << "this is your player id: " << player_id << std::endl; //print juste pour test que ca marche
    start_display();
}

void MainManager::start_display() {
    while(1) {
        mainUI.display();
        switch (mainUI.select()) {
            case 1: {
                GameLauncher game = GameLauncher(5556, server_ip_adress, player_id);
                break;
            }
            case 2: {
                ProfileManager profile = ProfileManager(5555, server_ip_adress, player_id, username);
                break;
            }
            case 3: {
                FriendListManager friendList(5555, server_ip_adress,player_id, username);
                break;
            }
            case 4: {
                RankingManager rankingManager(5555, server_ip_adress);
                break;
            }
            default: {
                std::cout << "Exit !" << std::endl;
                return;
            }
        }
    }
}
