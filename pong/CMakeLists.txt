cmake_minimum_required(VERSION 3.7)
project(pong)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_PATH "C:\\Users\\marti\\Downloads\\SDL2-2.0.14\\x86_64-w64-mingw32")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )


add_executable(pong main.cpp)
target_link_libraries(pong ${SDL2_LIBRARY} )



