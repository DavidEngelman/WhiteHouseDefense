cmake_minimum_required(VERSION 3.6)
project(projet)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_LINK_FLAGS "-lcrypt")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

add_subdirectory(code)

