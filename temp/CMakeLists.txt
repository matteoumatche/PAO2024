cmake_minimum_required(VERSION 3.1)

project(PAO2024)

find_package(Qt6 6.2.4 REQUIRED COMPONENTS Gui Widgets)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt6.2.4/6.2.4/msvc2019_64")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

add_executable(PAO2024 main.cpp)

target_link_libraries(progetto_sensori Qt6::Widgets)