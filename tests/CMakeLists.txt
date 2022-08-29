# ============================================================================ #
#                            RGE Test Framework                                #
# ============================================================================ #
project(RGETest
    VERSION 0.1
    DESCRIPTION "Testing framework for RGE library"
    LANGUAGES CXX
)

# Create main test executable
add_executable(${PROJECT_NAME})

# Define source files
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        test_asset_manager.cpp
)

# Add dependencies
add_dependencies(${PROJECT_NAME} RGE gtest gtest_main)

# Link to RGE
target_link_libraries(${PROJECT_NAME} PUBLIC RGE gtest gtest_main)

# Copy test assets over to the binary directory so we can access them during
# testing 
add_custom_target(copy_test_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_test_assets)