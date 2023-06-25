cmake_minimum_required(VERSION 3.15)
project(to-compiler CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})