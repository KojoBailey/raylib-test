cmake_minimum_required(VERSION 3.28)
project(Raylib_Test)

set(CMAKE_CXX_STANDARD 17) # or whatever C++ version ya want

add_executable(Raylib_Test src/main.cpp)

add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)