cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC TRUE)
file(GLOB code database.db)

set(CLIENT_FILES "client/NetworkedManager.cpp" "client/ClientLauncher.cpp" "client/Login/LoginManager.cpp" "client/Login/LoginConsoleUI.cpp"
        "client/Register/RegisterManager.cpp" "client/Register/RegisterUI.cpp" "common/Networking.cpp" "common/Credentials.cpp"
        client/Main/MainManager.cpp client/Main/MainUI.hpp common/Map.cpp client/Drawing.cpp client/Drawing.hpp "client/Ranking/RankingManager.cpp" "client/Ranking/RankingUI.cpp" "client/Game/GameLauncher.cpp"
        "client/FriendList/FriendListManager.cpp" "client/FriendList/FriendListUI.cpp" common/AbstractTower.cpp
        "client/Profile/ProfileConsoleUI.cpp" common/Position.cpp client/App.cpp client/App.hpp
        client/Welcome/WelcomeManager.cpp client/Welcome/WelcomeUI.cpp client/Welcome/WelcomeGUI.cpp
        client/FriendList/FriendList.cpp client/Game/GameManager.cpp
        "client/Profile/ProfileManager.cpp" "common/PNJ.cpp" client/Game/GameUI.cpp common/PlayerState.cpp
        common/GameState.cpp common/Wave.cpp common/Constants.h common/AttackTower.cpp common/Tools.hpp
        common/Tools.cpp
        client/Spectator/SpectatorManager.cpp client/Spectator/SpectatorManager.hpp
        client/Spectator/SpectatorUI.cpp client/Spectator/SpectatorUI.hpp
        client/Game/GameInfo.cpp common/GunTower.cpp common/GunTower.hpp
        common/SniperTower.cpp common/SniperTower.hpp
        common/ShockTower.cpp common/ShockTower.hpp
        client/Abstract/AbstractUI.hpp client/Abstract/AbstractGUI.cpp client/Abstract/AbstractGUI.hpp client/FriendList/FriendListGUI.cpp
        client/FriendList/FriendListGUI.hpp client/Game/GameGUI.cpp client/Game/GameGUI.hpp
        client/Login/LoginGUI.cpp client/Login/LoginGUI.hpp
        client/Main/MainGUI.cpp client/Main/MainGUI.hpp  client/Main/MainConsoleUI.cpp
        client/Profile/ProfileGUI.cpp client/Profile/ProfileGUI.hpp
        client/Ranking/RankingGUI.cpp client/Ranking/RankingGUI.hpp client/Register/RegisterGUI.cpp
        client/Register/RegisterGUI.hpp client/Spectator/SpectatorGUI.cpp client/Spectator/SpectatorGUI.hpp
        client/Welcome/WelcomeGUI.cpp client/Welcome/WelcomeGUI.hpp client/global.hpp client/global.cpp
        client/Login/LoginUI.hpp client/Profile/ProfileUI.hpp common/Message.cpp common/Message.hpp)


add_executable(client ${CLIENT_FILES})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)


find_package(Threads)

set(SERVER_FILES "server/ServerLauncher.cpp" "common/Networking.cpp" "server/Server.cpp" "server/AccountServer.cpp" "server/Database.cpp"
        "common/Credentials.cpp" "common/Account.cpp" "common/Command.cpp" "server/LoginRegisterCommand.cpp"
        "server/MatchmakingCommand.cpp" "server/MatchMaker.cpp" "server/MatchMaker.cpp" "server/PendingMatch.cpp"
        common/GameState.cpp "server/GameServer.cpp" "server/TowerCommand.cpp" "server/Timer.cpp"
        "server/FriendListCommand.cpp" common/AbstractTower.cpp server/PlayerConnection.cpp common/PlayerState.cpp common/Wave.cpp
        "common/PNJ.cpp" "common/Position.cpp" common/Map.cpp server/GameEngine.cpp server/GameEngine.hpp common/Constants.h common/Direction.h
        common/AttackTower.cpp common/Tools.hpp common/Tools.cpp server/UpdateStatsCommand.cpp common/GunTower.cpp common/GunTower.hpp common/SniperTower.cpp common/SniperTower.hpp common/ShockTower.cpp common/ShockTower.hpp common/Message.cpp common/Message.hpp)

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(server sqlite3)
target_link_libraries(client crypt)
target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)
target_link_libraries(client Qt5::Widgets Qt5::Multimedia)




