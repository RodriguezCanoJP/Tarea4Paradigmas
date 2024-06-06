cmake_minimum_required(VERSION 3.23)
project(PolePosition)

set(CMAKE_CXX_STANDARD 17)


find_package(SDL2 REQUIRED)
include_directories(/opt/homebrew/include/SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(cJSON)
include_directories(cJSON)


add_executable(PolePosition main.c main.c)
add_executable(PolePositionServer servidor.c)
target_link_libraries(PolePosition ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} cjson)
