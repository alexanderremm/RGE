# Fetch Windowing/Input library
FetchContent_Declare(
glfw
GIT_REPOSITORY https://github.com/glfw/glfw.git
GIT_TAG        3.3.2
)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
FetchContent_MakeAvailable(glfw)

# Fetch OpenGL Extension Loader library
FetchContent_Declare(
glad
GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)


# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Grab list of header and src files
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/src/*.cpp" "${RGE_SOURCE_DIR}/src/*.hpp")

# Create the library
add_library(RGE ${SRC_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(RGE PUBLIC ../include)
target_include_directories(RGE PUBLIC "${RGE_SOURCE_DIR}/src")

# All users of this library will need at least C++11
target_compile_features(RGE PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

# Link libraries
if (UNIX)
        find_package(OpenGL REQUIRED)
        find_package(X11 REQUIRED)
        target_link_libraries(RGE ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
endif()

# Link to glfw/glad
target_link_libraries(RGE glfw glad)

# Set the install location
install(TARGETS RGE
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Install the header files
install (FILES ${HEADER_LIST} DESTINATION include)
