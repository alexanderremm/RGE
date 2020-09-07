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
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.13.0
)
FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2

# Tests need to be added as executables first
add_executable(RGETest RGETest/RGETest.cpp)

# I'm using C++17 in the test
target_compile_features(RGETest PRIVATE cxx_std_17)

# Add dependency to the RGE lib
add_dependencies(RGETest RGE_static)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(RGETest PRIVATE RGE_static Catch2::Catch2)

install(TARGETS RGETest
            RUNTIME DESTINATION bin/)