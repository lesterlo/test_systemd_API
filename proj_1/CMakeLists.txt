cmake_minimum_required(VERSION 3.13)  # CMake version check
project(test_systemd)


# Setup variable
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXE_NAME ${PROJECT_NAME}) # setup the executable output name


# [Option1]: Use FindPkgConfig to find systemd
# find_library(SYSTEMD_LIBRARY systemd)

# [Option2]: Use pkg-config to find systemd
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED IMPORTED_TARGET libsystemd)

# Setup compile files
include_directories(include/) #Add include files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.cpp)# Add source files automatically

# Define the source files explicitly
# set(SOURCE_FILES  # Add source files
#     src/main.cpp
# )

# Building process
add_executable(${EXE_NAME} ${SOURCE_FILES}) # Make executable

# [Option1]: Use FindPkgConfig to find systemd
# target_link_libraries(${EXE_NAME} PRIVATE ${SYSTEMD_LIBRARY})


# [Option2]: Use pkg-config to find systemd
target_link_libraries(${EXE_NAME} PRIVATE PkgConfig::SYSTEMD)

# Post build command
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/unstrip)


add_custom_command( # Post build command
    TARGET ${EXE_NAME} 
    POST_BUILD 
    COMMAND cp ${CMAKE_BINARY_DIR}/bin/${EXE_NAME} ${CMAKE_BINARY_DIR}/bin/unstrip/${EXE_NAME}
    COMMAND ${CMAKE_STRIP} ${CMAKE_BINARY_DIR}/bin/${EXE_NAME}
)

install(TARGETS ${EXE_NAME} DESTINATION /opt/test/test_systemd/)
install(FILES resources/my_test_systemd.service DESTINATION /etc/systemd/system)