cmake_minimum_required(VERSION 3.9.0)
project(tocomp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# $source_files is a space-delimited list of filenames.
file(GLOB SOURCES "src/*.cpp")
add_executable(tc ${SOURCES})
target_link_libraries(tc ${CONAN_LIBS})