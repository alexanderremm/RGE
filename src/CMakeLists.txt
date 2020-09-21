include(GenerateExportHeader)

# Prevent 3rd party libs from updating if already downloaded (speeds up configure time)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Enable position independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Fetch Windowing/Input library
message(STATUS "Fetching GLFW")
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
message(STATUS "Fetching GLAD")
FetchContent_Declare(
glad
GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)

# Fetch FreeType2 (font rendering library)
message(STATUS "Fetching FreeType2")
FetchContent_Declare(
freetype
GIT_REPOSITORY https://github.com/freetype/freetype2.git
GIT_TAG        VER-2-10-2
)
FetchContent_MakeAvailable(freetype)

# Fetch GLM (OpenGL Mathmatics Library)
message(STATUS "Fetching GLM")
FetchContent_Declare(
glm
GIT_REPOSITORY https://github.com/g-truc/glm.git
GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Fetch spdlog (logging library)
message(STATUS "Fetching spdlog")
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.8.0
)
FetchContent_MakeAvailable(spdlog)

# Create list of 3rd party libs
set(THIRD_PARTY_LIBS glfw glad freetype glm spdlog)

# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Grab list of header and src files
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/src/*.cpp" "${RGE_SOURCE_DIR}/src/*.hpp")

# This is the "object library" target: compiles the sources only once
add_library(RGE_objlib OBJECT ${SRC_LIST} ${HEADER_LIST})

# Include directories
target_include_directories(RGE_objlib PUBLIC ../include "${RGE_SOURCE_DIR}/src")

# Link to 3rd party libraries
add_dependencies(RGE_objlib ${THIRD_PARTY_LIBS})

# Link libraries
if (UNIX)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    target_link_libraries(RGE_objlib ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
endif()

# Link to glfw/glad
target_link_libraries(RGE_objlib ${THIRD_PARTY_LIBS})

# Determine whether to build static/shared library
if (RGE_BUILD_SHARED)
    message(STATUS "Building shared library")

    # To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
    # See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
    # See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
    # set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    # Create shared library
    add_library(RGE SHARED $<TARGET_OBJECTS:RGE_objlib>)

    # Generate the export header
    GENERATE_EXPORT_HEADER(RGE
        EXPORT_FILE_NAME ${PROJECT_SOURCE_DIR}/include/RGE/rge_exports.h)

    target_include_directories(RGE PUBLIC ../include)
    target_include_directories(RGE PUBLIC "${RGE_SOURCE_DIR}/src")

    # All users of this library will need at least C++11
    target_compile_features(RGE PUBLIC cxx_std_11)
endif()

# Add static library
add_library(RGE_static STATIC $<TARGET_OBJECTS:RGE_objlib>)

# We need this directory, and users of our library will need it too
target_include_directories(RGE_static PUBLIC ../include)
target_include_directories(RGE_static PUBLIC "${RGE_SOURCE_DIR}/src")

# All users of this library will need at least C++11
target_compile_features(RGE_static PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

# Link to glfw/glad
if (RGE_BUILD_SHARED)
    target_link_libraries(RGE RGE_objlib ${THIRD_PARTY_LIBS})
endif()
target_link_libraries(RGE_static RGE_objlib ${THIRD_PARTY_LIBS})

# Set the install location
install(TARGETS RGE RGE_static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Install the header files
install (FILES ${HEADER_LIST} DESTINATION include)
