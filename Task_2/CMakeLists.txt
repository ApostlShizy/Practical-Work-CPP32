cmake_minimum_required(VERSION 3.1.7)
project(cinema)

set(CMAKE_STANDARD_CXX 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(cinema main.cpp)

target_link_libraries(cinema PRIVATE nlohmann_json::nlohmann_json)