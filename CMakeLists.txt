cmake_minimum_required(VERSION 3.10)
project(rpgGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect source files
file(GLOB_RECURSE ENEMY_SOURCES "${CMAKE_SOURCE_DIR}/src/Enemies/*.cpp")
file(GLOB_RECURSE WEAPON_SOURCES "${CMAKE_SOURCE_DIR}/src/Weapons/*.cpp")
file(GLOB_RECURSE CORE_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(Enemies STATIC ${ENEMY_SOURCES})
add_library(Weapons STATIC ${WEAPON_SOURCES})
add_library(GameCore STATIC ${CORE_SOURCES})

add_library(rpg_includes INTERFACE)
target_include_directories(rpg_includes INTERFACE "${CMAKE_SOURCE_DIR}/lib")

target_link_libraries(Enemies PUBLIC rpg_includes)
target_link_libraries(Weapons PUBLIC rpg_includes)
target_link_libraries(GameCore PUBLIC rpg_includes)

add_executable(rpgGame "${CMAKE_SOURCE_DIR}/main.cpp")

target_link_libraries(rpgGame PRIVATE Enemies Weapons GameCore rpg_includes)
