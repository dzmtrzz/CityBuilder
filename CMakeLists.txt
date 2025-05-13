cmake_minimum_required(VERSION 3.10)
project(CityPlanner)

# Use Clang if available
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(CityBuilder src/main.cpp src/world.cpp)
target_link_libraries(CityBuilder sfml-graphics sfml-window sfml-system)

