# =============================================================================
# RGE Driver Project
# =============================================================================
add_executable(RGEDriver RGEDriver/RGEDriver.cpp)
target_compile_features(RGEDriver PRIVATE cxx_std_17)

add_dependencies(RGEDriver RGE)

target_link_libraries(RGEDriver RGE)
target_include_directories(RGEDriver PUBLIC ${CMAKE_SOURCE_DIR}/include)

install(TARGETS RGEDriver
            RUNTIME DESTINATION bin/)

# =============================================================================
# Unit Test Project
# =============================================================================
FetchContent_Declare(
googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)
# Adds gtest

# Tests need to be added as executables first
add_executable(RGETest RGETest/RGETest.cpp)

# I'm using C++17 in the test
target_compile_features(RGETest PRIVATE cxx_std_17)

# Add dependency to the RGE lib
add_dependencies(RGETest RGE_static)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(RGETest PRIVATE RGE_static gtest_main)

install(TARGETS RGETest
            RUNTIME DESTINATION bin/)