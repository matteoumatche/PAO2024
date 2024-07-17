cmake_minimum_required(VERSION 3.5)

project(progetto_sensori)

set(CMAKE_CXX_STANDARD 11)

# Trova il pacchetto Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Json REQUIRED)

add_executable(progetto_sensori C:\Users\bzagh\Documents\GitHub\PAO2024\progetto_sensori\src)

# Linka le librerie Qt5
target_link_libraries(progetto_sensori Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Json)
