cmake_minimum_required(VERSION 3.17)
project(pong)

set(CMAKE_CXX_STANDARD 14)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

#set(SDL2_INCLUDE_DIR C:/Users/marti/Downloads/SDL2-2.0.14/x86_64-w64-mingw32/include/SDL2)
#set(SDL2_LIB_DIR C:/Users/marti/Downloads/SDL2-2.0.14/x86_64-w64-mingw32/lib)

#set(SDL2_PATH C:/Users/marti/Downloads/SDL2-2.0.14/x86_64-w64-mingw32)

#include_directories(${SDL2_INCLUDE_DIR})
#link_directories(${SDL2_LIB_DIR})

#include_directories(${PROJECT_SOURCE_DIR}/include)
#link_directories(${PROJECT_SOURCE_DIR}/lib)


set(SOURCE_FILES main.cpp)


add_executable(pong ${SOURCE_FILES})
#target_link_libraries(pong SDL2main SDL2 )




