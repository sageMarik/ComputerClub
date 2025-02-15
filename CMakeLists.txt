cmake_minimum_required(VERSION 3.16)

project(ComputerClub LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ComputerClub main.cpp
    time_utils.h time_utils.cpp
    computer_club.h computer_club.cpp)

include(GNUInstallDirs)
install(TARGETS ComputerClub
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
