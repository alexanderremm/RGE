# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Grab list of header and src files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/include/RGE/*.hpp")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${RGE_SOURCE_DIR}/src/*.cpp")

# Filter the list of header and src files based on current OS
if (WIN32)
        list(FILTER HEADER_LIST EXCLUDE REGEX "(Unix_)")
        list(FILTER SRC_LIST EXCLUDE REGEX "(Unix_)")
endif()

if (UNIX)
        list(FILTER HEADER_LIST EXCLUDE REGEX "(WIN32_)")
        list(FILTER SRC_LIST EXCLUDE REGEX "(WIN32_)")
endif()

# Make an automatic library - will be static or dynamic based on user setting
add_library(RGE ${SRC_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(RGE PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(RGE PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

# Set the install location
install(TARGETS RGE
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Install the header files
install (FILES ${HEADER_LIST} DESTINATION include)
