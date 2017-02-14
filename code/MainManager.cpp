
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfilManager.hpp"
#include "FriendList.hpp"


MainManager::MainManager() {
    mainUI = MainUI();
    mainUI.display();
    switch (mainUI.select()) {
        case 1:
            GameLauncher game = GameLauncher();
            break;
        case 2:
            ProfilManager profile = ProfilManager();
            break;
        case 3:
            FriendList friendList = FriendList();
            break;
        case 4:
            break;
        case 5:
            break;
    }
}
