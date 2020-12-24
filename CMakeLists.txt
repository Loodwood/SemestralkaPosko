cmake_minimum_required(VERSION 3.7)
project(SemkaPos C)

set(CMAKE_C_STANDARD 99)

add_executable(SemkaPos HTTP_client.c shared.h)
target_link_libraries(SemkaPos -pthread)

