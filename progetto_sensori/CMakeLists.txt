cmake_minimum_required(VERSION 3.5)

project(progetto_sensori LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt6.2.4/6.2.4/msvc2019_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(progetto_sensori main.cpp)

target_link_libraries(progetto_sensori Qt6::Widgets)