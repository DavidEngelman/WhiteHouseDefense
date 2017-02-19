cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
file(GLOB code database.db)

set(CLIENT_FILES  "client/NetworkedManager.cpp" "client/ClientLauncher.cpp" "client/LoginManager.cpp" "client/LoginUI.cpp"
        "client/RegisterManager.cpp" "client/RegisterUI.cpp" "common/Networking.cpp" "common/Credentials.cpp"
        client/MainManager.cpp client/MainUI.cpp common/Map.cpp client/Drawing.cpp client/Drawing.hpp "client/RankingManager.cpp" "client/RankingUI.cpp" "client/GameLauncher.cpp"
        "client/FriendListManager.cpp" "client/FriendListUI.cpp" common/AbstractTower.cpp common/DamageTower.cpp common/DamageTower.h)


add_executable(client ${CLIENT_FILES})


find_package (Threads)

set(SERVER_FILES "server/ServerLauncher.cpp" "common/Networking.cpp" "server/Server.cpp" "server/AccountServer.cpp" "server/Database.cpp"
        "common/Credentials.cpp" "common/Account.cpp" "server/Command.cpp" "server/LoginRegisterCommand.cpp"
        "server/MatchmakingCommand.cpp" "server/MatchMaker.cpp" "server/MatchMaker.cpp" "server/PendingMatch.cpp"
        "server/FriendListCommand.cpp" common/AbstractTower.cpp common/DamageTower.cpp common/DamageTower.h server/PlayerConnection.cpp)

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries( server sqlite3)
target_link_libraries( client crypt)
target_link_libraries(server Threads::Threads)
