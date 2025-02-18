cmake_minimum_required(VERSION 3.13)  # CMake version check

project(Demo_solution_level)

message(STATUS ${PROJECT_NAME})
# Setup building variable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output all the executable to ./bin directory

add_subdirectory(proj_1)
add_subdirectory(proj_2)