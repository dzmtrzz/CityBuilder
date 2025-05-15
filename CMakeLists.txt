cmake_minimum_required(VERSION 3.10)
project(CityPlanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(CityBuilder src/main.cpp src/world.cpp src/Tile.cpp src/Buildings.cpp)
target_link_libraries(CityBuilder sfml-graphics sfml-window sfml-system)

# Copy assets/ to the build directory
add_custom_command(TARGET CityBuilder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:CityBuilder>/assets
)