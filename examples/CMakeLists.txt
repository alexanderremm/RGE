# Add the individual example applications with the following structure:
#   add_executable(EXAMPLE_##_NAME file.cpp)
#   target_compile_features(EXAMPLE_##_NAME cxx_std_17)
#   install(TARGETS EXAMPLE_##_NAME
#               RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/examples)
#
# Note: Add any additional parameters/settings as needed

# EXAMPLE_01_Initialization
add_executable(EXAMPLE_01_Initialization 01_Initialization/init.cpp)
target_compile_features(EXAMPLE_01_Initialization PRIVATE cxx_std_17)

add_dependencies(EXAMPLE_01_Initialization RGE)

target_link_libraries(EXAMPLE_01_Initialization RGE)
target_include_directories(EXAMPLE_01_Initialization PUBLIC ${CMAKE_SOURCE_DIR}/include)

install(TARGETS EXAMPLE_01_Initialization
            RUNTIME DESTINATION bin/examples)

# EXAMPLE_02_...

# EXAMPLE_03_... and so on
