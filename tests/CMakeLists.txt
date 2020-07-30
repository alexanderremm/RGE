# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.13.0
)
FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2

# Tests need to be added as executables first
add_executable(testRGE testRGE.cpp)

# I'm using C++17 in the test
target_compile_features(testRGE PRIVATE cxx_std_17)

# Add dependency to the RGE lib
add_dependencies(testRGE RGE)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testRGE PRIVATE RGE Catch2::Catch2)

install(TARGETS testRGE
            RUNTIME DESTINATION bin/tests)
