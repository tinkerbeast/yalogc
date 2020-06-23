cmake_minimum_required(VERSION 3.8.2) 
# 3.8.2 released May 2017, required for c++17

project(yalogc 
        VERSION 0.1
        LANGUAGES CXX)

# default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# default c and cpp version
# Read this https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
# PRIVATE, PUBLIC, INTERFACE https://cmake.org/pipermail/cmake/2016-May/063400.html
# Header only libaries http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#include_directories ("${PROJECT_SOURCE_DIR}/src/")

if(BUILD_TESTING OR YALOGC_BUILD_TESTING)
    enable_testing()
    
    include(googletest)

    message("In cmake build testing")
    add_subdirectory(test)
endif(BUILD_TESTING OR YALOGC_BUILD_TESTING)


message("In cmake main")
