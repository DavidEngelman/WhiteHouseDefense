cmake_minimum_required(VERSION 3.6)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC TRUE)
file(GLOB code database.db)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Charts REQUIRED)

find_package(Threads)

set(CLIENT_FILES client/Other/ClientLauncher.cpp


        #ABSTRACT
        client/Abstract/AbstractUI.hpp
        client/Abstract/AbstractGUI.cpp
        client/Abstract/AbstractConsoleUI.hpp
        client/Abstract/AbstractManager.cpp

        #MANAGER
        client/Other/NetworkedManager.cpp

        #MAIN
        client/Main/MainManager.cpp
        client/Main/MainGUI.cpp
        client/Main/MainConsoleUI.cpp
        client/Main/MainUI.hpp
        client/Other/InQueueWidget.cpp
        client/Other/InQueueWidget.hpp
        client/Game/QMatchMakingThread.hpp

        #WELCOME
        client/Welcome/WelcomeManager.cpp
        client/Welcome/WelcomeConsoleUI.cpp
        client/Welcome/WelcomeGUI.cpp
        client/Welcome/WelcomeUI.hpp

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
        common/Other/RankingInfos.hpp

        #SUPPORTER
        client/Spectator/SpectatorGUI.cpp
        client/Spectator/SpectatorManager.cpp
        client/Spectator/SpectatorConsoleUI.cpp
        client/Spectator/SpectatorUI.hpp
        client/Spectator/SpectatorUI.cpp

        #FRIENDLIST
        client/FriendList/FriendListManager.cpp
        client/FriendList/FriendListGUI.cpp
        client/FriendList/FriendList.cpp


        #SETTINGS
        client/Settings/SettingsManager.cpp
        client/Settings/SettingsUI.hpp
        client/Settings/SettingsGUI.cpp
        client/Settings/SettingsConsoleUI.cpp
        client/Settings/IconSelectionWidget.cpp
        client/Other/IconLabel.cpp

        #GAME
        common/Other/Map.cpp
        client/Other/MapGUI.cpp

            #TOWER
        common/Tower/AbstractTower.cpp
        common/Tower/AttackTower.cpp
        common/Tower/OneTargetTower.cpp
        common/Tower/GunTower.cpp
        common/Tower/SniperTower.cpp
        common/Tower/ShockTower.cpp
        common/Tower/MissileTower.cpp

            #PNJ
        common/Npc/PNJ.cpp
        common/Npc/MexicanPNJ.cpp
        common/Npc/CommunistPNJ.cpp
        common/Npc/MuslimPNJ.cpp

        common/Gamestate/GameState.cpp
        common/Gamestate/Wave.cpp
        common/Gamestate/PlayerState.cpp
        client/Game/GameConsoleUI.cpp
        client/Game/GameGUI.cpp
        client/Game/GameManager.cpp
        client/Game/GameUI.hpp
        common/Other/Position.cpp

        client/Game/InGameChatWidget.cpp
        client/Game/InGameChatWidget.hpp

        #OTHERS
        client/Game/GameInfo.cpp
        client/Other/global.cpp
        common/Other/Message.cpp
        common/Other/Command.cpp
        client/Other/QCustomButton.cpp
        common/Other/Networking.cpp
        common/Other/Credentials.cpp
        client/Other/Drawing.cpp
        client/Other/App.cpp
        common/Other/Constants.hpp
        common/Other/Strings.hpp
        common/Other/Tools.cpp
        client/Other/QHandPointerButton.hpp
        client/Other/InQueueWidget.cpp client/FriendList/FriendListConsoleUI.cpp client/FriendList/FriendListConsoleUI.h)


add_executable(client ${CLIENT_FILES})

set(SERVER_FILES "server/Other/ServerLauncher.cpp"

        server/Other/Server.cpp

        #GAME
        server/Game/GameServer.cpp

            #TOWER
        common/Tower/AbstractTower.cpp
        common/Tower/AttackTower.cpp
        common/Tower/OneTargetTower.cpp
        common/Tower/GunTower.cpp
        common/Tower/SniperTower.cpp
        common/Tower/ShockTower.cpp
        common/Tower/MissileTower.cpp

            #PNJ
        common/Npc/PNJ.cpp
        common/Npc/MexicanPNJ.cpp
        common/Npc/CommunistPNJ.cpp
        common/Npc/MuslimPNJ.cpp

        common/Gamestate/PlayerState.cpp
        common/Gamestate/Wave.cpp
        common/Other/Position.cpp
        common/Other/Map.cpp
        server/Game/GameEngine.cpp
        common/Other/Direction.hpp
        common/Gamestate/GameState.cpp

        #ACCOUNT
        server/Account/AccountServer.cpp
        server/Account/Database.cpp

        #COMMANDS
        common/Other/Command.cpp
        server/Commands/LoginRegisterCommand.cpp
        server/Commands/MatchmakingCommand.cpp
        server/Commands/TowerCommand.cpp
        server/Commands/FriendListCommand.cpp
        server/Commands/UpdateStatsCommand.cpp

        #MATCHMAKING
        server/Game/MatchMaker.cpp
        server/Game/PendingMatch.cpp

        #TOOLS
        common/Other/Constants.hpp
        common/Other/Strings.hpp
        common/Other/Tools.cpp
        server/Other/Timer.cpp
        server/Other/PlayerConnection.cpp
        common/Other/Networking.cpp
        common/Other/Credentials.cpp
        common/Other/Message.cpp
        common/Other/RankingInfos.hpp)

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(server sqlite3)
target_link_libraries(client crypt)
target_link_libraries(server crypt)

target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)
target_link_libraries(client Qt5::Widgets Qt5::Multimedia Qt5::Charts)