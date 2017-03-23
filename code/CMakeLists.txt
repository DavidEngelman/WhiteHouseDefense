cmake_minimum_required(VERSION 3.6)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC TRUE)
file(GLOB code database.db)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Charts REQUIRED)

find_package(Threads)

set(CLIENT_FILES client/ClientLauncher.cpp


        #ABSTRACT
        client/Abstract/AbstractUI.hpp
        client/Abstract/AbstractGUI.cpp
        client/Abstract/AbstractConsoleUI.hpp
        client/Abstract/AbstractManager.cpp

        #MANAGER
        client/NetworkedManager.cpp

        #MAIN
        client/Main/MainManager.cpp
        client/Main/MainGUI.cpp
        client/Main/MainConsoleUI.cpp
        client/Main/MainUI.hpp
        client/InQueueWidget.cpp
        client/InQueueWidget.hpp
        client/Game/QMatchMakingThread.hpp

        #WELCOME
        client/Welcome/WelcomeManager.cpp
        client/Welcome/WelcomeUI.cpp
        client/Welcome/WelcomeGUI.cpp
        client/Welcome/WelcomeGUI.cpp

        #REGISTER
        client/Register/RegisterGUI.cpp
        client/Register/RegisterUI.hpp
        client/Register/RegisterManager.cpp
        client/Register/RegisterConsoleUI.cpp

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
        client/Ranking/RankingUI.hpp
        common/RankingInfos.hpp

        #SUPPORTER
        client/Spectator/SpectatorGUI.cpp
        client/Spectator/SpectatorManager.cpp
        client/Spectator/SpectatorConsoleUI.cpp
        client/Spectator/SpectatorUI.hpp
        client/Spectator/SpectatorUI.cpp

        #FRIENDLIST
        #"client/FriendList/FriendListManager.cpp"
        #"client/FriendList/FriendListUI.cpp"
        #client/FriendList/FriendListGUI.cpp
        #client/FriendList/FriendList.cpp

        #SETTINGS
        client/Settings/SettingsManager.cpp
        client/Settings/SettingsUI.hpp
        client/Settings/SettingsGUI.cpp
        client/Settings/SettingsConsoleUI.cpp
        client/Settings/IconSelectionWidget.cpp
        client/IconLabel.cpp

        #GAME
        common/Map.cpp
        client/MapGUI.cpp

            #TOWER
        common/tower/AbstractTower.cpp
        common/tower/AttackTower.cpp
        common/tower/OneTargetTower.cpp
        common/tower/GunTower.cpp
        common/tower/SniperTower.cpp
        common/tower/ShockTower.cpp
        common/tower/MissileTower.cpp

            #PNJ
        common/pnj/PNJ.cpp
        common/pnj/MexicanPNJ.cpp
        common/pnj/CommunistPNJ.cpp
        common/pnj/MuslimPNJ.cpp

        common/gamestate/GameState.cpp
        common/gamestate/Wave.cpp
        common/gamestate/PlayerState.cpp
        client/Game/GameConsoleUI.cpp
        client/Game/GameGUI.cpp
        client/Game/GameManager.cpp
        client/Game/GameUI.hpp
        common/Position.cpp

        client/Game/InGameChatWidget.cpp
        client/Game/InGameChatWidget.hpp

        #OTHERS
        client/Game/GameInfo.cpp
        client/global.cpp
        common/Message.cpp
        common/Command.cpp
        client/QCustomButton.cpp
        common/Networking.cpp
        common/Credentials.cpp
        client/Drawing.cpp
        client/App.cpp
        common/Constants.hpp
        common/Strings.hpp
        common/Tools.cpp
        client/QHandPointerButton.hpp
        client/InQueueWidget.cpp)


add_executable(client ${CLIENT_FILES})

set(SERVER_FILES "server/ServerLauncher.cpp"

        server/Server.cpp

        #GAME
        server/GameServer.cpp

            #TOWER
        common/tower/AbstractTower.cpp
        common/tower/AttackTower.cpp
        common/tower/OneTargetTower.cpp
        common/tower/GunTower.cpp
        common/tower/SniperTower.cpp
        common/tower/ShockTower.cpp
        common/tower/MissileTower.cpp

            #PNJ
        common/pnj/PNJ.cpp
        common/pnj/MexicanPNJ.cpp
        common/pnj/CommunistPNJ.cpp
        common/pnj/MuslimPNJ.cpp

        common/gamestate/PlayerState.cpp
        common/gamestate/Wave.cpp
        common/Position.cpp
        common/Map.cpp
        server/GameEngine.cpp
        common/Direction.hpp
        common/gamestate/GameState.cpp

        #ACCOUNT
        server/AccountServer.cpp
        server/Database.cpp

        #COMMANDS
        common/Command.cpp
        server/LoginRegisterCommand.cpp
        server/MatchmakingCommand.cpp
        server/TowerCommand.cpp
        server/FriendListCommand.cpp
        server/UpdateStatsCommand.cpp

        #MATCHMAKING
        server/MatchMaker.cpp
        server/PendingMatch.cpp

        #TOOLS
        common/Constants.hpp
        common/Strings.hpp
        common/Tools.cpp
        server/Timer.cpp
        server/PlayerConnection.cpp
        common/Networking.cpp
        common/Credentials.cpp
        common/Message.cpp
        common/RankingInfos.hpp)

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(server sqlite3)
target_link_libraries(client crypt)
target_link_libraries(server crypt)
target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)
target_link_libraries(client Qt5::Widgets Qt5::Multimedia Qt5::Charts)