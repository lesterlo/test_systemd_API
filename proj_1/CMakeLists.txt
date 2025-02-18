cmake_minimum_required(VERSION 3.13)  # CMake version check
project(demo_project_1)


# Setup variable
set(EXE_NAME ${PROJECT_NAME}) # setup the executable output name

# Setup compile files
include_directories(include/) #Add include files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.cpp)# Add source files automatically

# Define the source files explicitly
# set(SOURCE_FILES  # Add source files
#     src/main.cpp
# )

# Building process
add_executable(${EXE_NAME} ${SOURCE_FILES}) # Make executable

# Post build command
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/unstrip)
add_custom_command( # Post build command
    TARGET ${EXE_NAME} 
    POST_BUILD 
    COMMAND cp ${CMAKE_BINARY_DIR}/bin/${EXE_NAME} ${CMAKE_BINARY_DIR}/bin/unstrip/${EXE_NAME}
    COMMAND ${CMAKE_STRIP} ${CMAKE_BINARY_DIR}/bin/${EXE_NAME}
)