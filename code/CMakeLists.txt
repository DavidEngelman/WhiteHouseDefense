cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
file(GLOB code database.db)

set(CLIENT_FILES  "Manager.cpp" "ClientLauncher.cpp" "LoginManager.cpp" "LoginUI.cpp"
        "RegisterManager.cpp" "RegisterUI.cpp" "Networking.cpp" "Credentials.cpp"
        MainManager.cpp MainUI.cpp GameManager.cpp Map.cpp RankingUI.cpp RankingManager.cpp)

add_executable(client ${CLIENT_FILES})

set(SERVER_FILES "serverLauncher.cpp" "Networking.cpp" "Server.cpp" "AccountServer.cpp" "Database.cpp"
        "Credentials.cpp" "Account.cpp" "Command.cpp" "LoginRegisterCommand.cpp"
        "MatchmakingCommand.cpp")

add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries( server sqlite3)
