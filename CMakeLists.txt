cmake_minimum_required(VERSION 3.23)
project(PolePosition)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(/opt/homebrew/include/SDL2)

add_executable(PolePosition main.c)
add_executable(PolePositionServer servidor.c)
target_link_libraries(PolePosition ${SDL2_LIBRARIES})
