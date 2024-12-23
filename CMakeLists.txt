cmake_minimum_required(VERSION 3.31.3)

project(weather C)

add_executable(${CMAKE_PROJECT_NAME} main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} curl cjson)
