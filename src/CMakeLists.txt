cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0100 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -g")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(timekeeper main.cpp timekeeper.cpp timekeeper.hh)

target_link_libraries(timekeeper Qt5::Widgets Qt5::Core yaml-cpp)
install(TARGETS timekeeper DESTINATION ${CMAKE_INSTALL_DIR}/bin)
install(FILES ${CMAKE_SOURCE_DIR}/config/config.yml DESTINATION ${CMAKE_INSTALL_DIR}/config)

