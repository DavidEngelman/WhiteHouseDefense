cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
file(GLOB code database.db)

set(CLIENT_FILES  "client/NetworkedManager.cpp" "client/ClientLauncher.cpp" "client/LoginManager.cpp" "client/LoginUI.cpp"
        "client/RegisterManager.cpp" "client/RegisterUI.cpp" "common/Networking.cpp" "common/Credentials.cpp"
        client/MainManager.cpp client/MainUI.cpp common/Map.cpp client/Drawing.cpp client/Drawing.hpp "client/RankingManager.cpp" "client/RankingUI.cpp" "client/GameLauncher.cpp"
        "client/FriendListManager.cpp" "client/FriendListUI.cpp" common/AbstractTower.cpp
        "client/ProfileUI.cpp" common/Position.cpp client/App.cpp client/App.hpp client/AbstractManager.cpp
        client/WelcomeManager.cpp client/WelcomeUI.cpp
          client/FriendList.cpp client/GameManager.cpp
        "client/ProfileManager.cpp" "common/PNJ.cpp" client/GameUI.cpp common/PlayerState.cpp
        common/GameState.cpp common/Wave.cpp common/Constants.h common/AttackTower.cpp common/Tools.hpp common/Tools.cpp client/SpectatorManager.cpp client/SpectatorManager.hpp client/SpectatorUI.cpp client/SpectatorUI.hpp client/GameInfo.cpp common/GunTower.cpp common/GunTower.hpp common/SniperTower.cpp common/SniperTower.hpp common/ShockTower.cpp common/ShockTower.hpp client/AbstractUI.cpp client/AbstractUI.hpp client/AbstractGUI.cpp client/AbstractGUI.hpp client/FriendListGUI.cpp client/FriendListGUI.hpp client/GameGUI.cpp client/GameGUI.hpp client/LoginGUI.cpp client/LoginGUI.hpp client/MainGUI.cpp client/MainGUI.hpp client/ProfileGUI.cpp client/ProfileGUI.hpp client/RankingGUI.cpp client/RankingGUI.hpp client/RegisterGUI.cpp client/RegisterGUI.hpp client/SpectatorGUI.cpp client/SpectatorGUI.hpp client/WelcomeGUI.cpp client/WelcomeGUI.hpp client/global.hpp client/global.cpp)


add_executable(client ${CLIENT_FILES})

find_package(Qt5Widgets REQUIRED)

find_package (Threads)

set(SERVER_FILES "server/ServerLauncher.cpp" "common/Networking.cpp" "server/Server.cpp" "server/AccountServer.cpp" "server/Database.cpp"
        "common/Credentials.cpp" "common/Account.cpp" "server/Command.cpp" "server/LoginRegisterCommand.cpp"
        "server/MatchmakingCommand.cpp" "server/MatchMaker.cpp" "server/MatchMaker.cpp" "server/PendingMatch.cpp"
        common/GameState.cpp "server/GameServer.cpp" "server/TowerCommand.cpp" "server/Timer.cpp"
        "server/FriendListCommand.cpp" common/AbstractTower.cpp server/PlayerConnection.cpp common/PlayerState.cpp common/Wave.cpp
        "common/PNJ.cpp" "common/Position.cpp" common/Map.cpp server/GameEngine.cpp server/GameEngine.hpp common/Constants.h common/Direction.h
        common/AttackTower.cpp common/Tools.hpp common/Tools.cpp server/UpdateStatsCommand.cpp common/GunTower.cpp common/GunTower.hpp common/SniperTower.cpp common/SniperTower.hpp common/ShockTower.cpp common/ShockTower.hpp)

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(server sqlite3)
target_link_libraries(client crypt)
target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)
target_link_libraries(client Qt5::Widgets)




