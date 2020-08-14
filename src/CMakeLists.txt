# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Grab list of header and src files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/include/RGE/*.hpp")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/src/*.cpp" "${RGE_SOURCE_DIR}/src/*.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(RGE ${SRC_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(RGE PUBLIC ../include)
target_include_directories(RGE PUBLIC /)

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

# Set the install location
install(TARGETS RGE
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Install the header files
install (FILES ${HEADER_LIST} DESTINATION include)
