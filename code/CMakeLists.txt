cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)

set(CLIENT_FILES main.cpp)
add_executable(client ${CLIENT_FILES})

set(SERVER_FILES "serverLauncher.cpp" "Networking.cpp" "Server.cpp" "AccountServer.cpp" "Database.cpp" Credentials.cpp Credentials.h)
add_executable(server ${SERVER_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries( server sqlite3)
