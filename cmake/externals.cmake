include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 2.5.1
    GIT_SHALLOW 1
)
FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    # Compile SFML statically
    set(BUILD_SHARED_LIBS OFF)
    set(SFML_STATIC_LIBRARIES ON)

    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG        "v1.10.0"
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()