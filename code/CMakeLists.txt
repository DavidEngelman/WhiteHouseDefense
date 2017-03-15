cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC TRUE)
file(GLOB code database.db)

set(CLIENT_FILES client/ClientLauncher.cpp


        #ABSTRACT
        client/Abstract/AbstractUI.hpp
        client/Abstract/AbstractGUI.cpp
        client/Abstract/AbstractConsoleUI.hpp
        client/Abstract/AbstractManager.hpp

        #MANAGER
        client/NetworkedManager.cpp

        #MAIN
        client/Main/MainManager.cpp
        client/Main/MainGUI.cpp
        client/Main/MainConsoleUI.cpp
        client/Main/MainUI.hpp

        #WELCOME
        client/Welcome/WelcomeManager.cpp
        client/Welcome/WelcomeUI.cpp
        client/Welcome/WelcomeGUI.cpp
        client/Welcome/WelcomeGUI.cpp

        #REGISTER
        client/Register/RegisterGUI.cpp
        client/Register/RegisterGUI.hpp
        client/Register/RegisterManager.cpp
        client/Register/RegisterUI.cpp

        #LOGIN
        client/Login/LoginGUI.cpp
        client/Login/LoginUI.hpp
        client/Login/LoginManager.cpp
        client/Login/LoginConsoleUI.cpp

        #PROFIL
        client/Profile/ProfileConsoleUI.cpp
        client/Profile/ProfileManager.cpp
        client/Profile/ProfileGUI.cpp
        client/Profile/ProfileUI.hpp

        #RANKING
        client/Ranking/RankingManager.cpp
        client/Ranking/RankingConsoleUI.cpp
        client/Ranking/RankingGUI.cpp
        client/Ranking/RankingUI.h

        #SUPPORTER
        client/Spectator/SpectatorGUI.cpp
        client/Spectator/SpectatorManager.cpp
        client/Spectator/SpectatorConsoleUI.cpp
        client/Spectator/SpectatorUI.hpp

        #FRIENDLIST
        #"client/FriendList/FriendListManager.cpp"
        #"client/FriendList/FriendListUI.cpp"
        #client/FriendList/FriendListGUI.cpp
        #client/FriendList/FriendList.cpp

        #GAME
        common/Map.cpp
        common/AttackTower.cpp
        common/AbstractTower.cpp
        common/GunTower.cpp
        common/ShockTower.cpp
        common/SniperTower.cpp
        common/PNJ.cpp
        common/GameState.cpp
        common/Wave.cpp
        client/Game/GameUI.cpp
        common/PlayerState.cpp
        #client/Game/GameLauncher.cpp
        #client/Game/GameGUI.cpp
        #client/Game/GameManager.cpp
        common/Position.cpp

        #OTHERS
        client/Game/GameInfo.cpp
        client/global.cpp
        common/Message.cpp
        client/QCustomButton.cpp
        common/Networking.cpp
        common/Credentials.cpp
        client/Drawing.cpp
        client/Drawing.hpp
        client/App.cpp
        common/Constants.h common/Tools.hpp
        common/Tools.cpp
        )


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