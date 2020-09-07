# Works with 3.14
cmake_minimum_required(VERSION 3.14)

# Set project output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Project name
project(RGE
    VERSION 0.1
    DESCRIPTION "A simple C++ game engine"
    LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Docs only available if this is the main app
    find_package(Doxygen REQUIRED dot)
    if(Doxygen_FOUND)
	    add_subdirectory(docs)
    else()
	    message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# Add option to build shared library
option(RGE_BUILD_SHARED "Toggle to build shared libraries" ON)

# The compiled library code is here
add_subdirectory(src)

# The examples code is here
set(RGE_BUILD_SUBPROJECTS ON CACHE BOOL "Toggle building of subprojects")
if(RGE_BUILD_SUBPROJECTS)
    add_subdirectory(subprojects)
endif()
