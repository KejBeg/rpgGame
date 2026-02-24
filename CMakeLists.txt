cmake_minimum_required(VERSION 4.2.3)
project(rpgGame LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use a sensible C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Ensure build outputs go into the binary dir (useful for out-of-source builds)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(gameCore
  ${SRC_DIR}/Character.cpp
  ${SRC_DIR}/Weapon.cpp
  ${SRC_DIR}/Enemy.cpp
)

target_include_directories(gameCore
  PUBLIC ${LIB_DIR}
)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE gameCore)
