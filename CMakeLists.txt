# ============================================================================ #
#                            RGE Library                                       #
# ============================================================================ #
cmake_minimum_required(VERSION 3.14)

# Set project output directories
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Project name
set(namespace "RGE")
project(RGE
    VERSION 0.1
    DESCRIPTION "A simple C++ game engine"
    LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Set the C++ standard to C++20
    set(TARGET RGE PROPERTY CXX_STANDARD 20)
    
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Look for Doxygen
    find_package(Doxygen REQUIRED dot)
    if(Doxygen_FOUND)
	    add_subdirectory(docs)
    else()
	    message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# ============================================================================ #
#                              Third-party                                     #
# ============================================================================ #
# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# ============================================================================ #
#                              Options                                         #
# ============================================================================ #
# Option to build shared library
option(RGE_BUILD_SHARED "Toggle to build shared libraries" ON)
if(RGE_BUILD_SHARED)
    set(build_type SHARED)
    # Check if on Windows (must export all symbols)
    if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    endif()
else()
    set(build_type STATIC)
endif()

# ============================================================================ #
#                              Library Files                                   #
# ============================================================================ #
add_library(${PROJECT_NAME} ${build_type})

# Source files
target_sources(${PROJECT_NAME}
    PRIVATE
        src/asset_manager.cpp
        src/logging.cpp
        src/state_machine.cpp

        src/networking/net_host.cpp
)

# Set public headers
set(public_headers
    include/asset_manager.hpp
    include/logging.hpp
    include/state_machine.hpp
    include/state.hpp

    include/networking/net_commands.hpp
    include/networking/net_constants.hpp
    include/networking/net_host.hpp
    include/networking/net_types.hpp
)
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

# Set where the project will look for header files
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # Where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # Where the library itself will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # Where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Set where our CMake modules are located
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(installing)