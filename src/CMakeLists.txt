cmake_minimum_required(VERSION 3.5)

project(MyQtProject)

set(CMAKE_CXX_STANDARD 11)

# Trova il pacchetto Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Json REQUIRED)

add_executable(MyQtProject main.cpp)

# Linka le librerie Qt5
target_link_libraries(MyQtProject Qt5::Core Qt5::Json)
