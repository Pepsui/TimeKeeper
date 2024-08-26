cmake_minimum_required(VERSION 3.2)

project(timekeeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0100 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(timekeeper main.cpp timekeeper.cpp timekeeper.hh)

target_link_libraries(timekeeper Qt5::Widgets Qt5::Core yaml-cpp)

