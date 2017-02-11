cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)

set(CLIENT_FILES main.cpp)
add_executable(client ${CLIENT_FILES})


set(SERVER_FILES "serverLauncher.cpp" "Server.cpp" "AccountServer.cpp" Database.cpp)
add_executable(server ${SERVER_FILES})

