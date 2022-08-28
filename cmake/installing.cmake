# ============================================================================ #
#                              Install                                         #
# ============================================================================ #
# Set project installation path
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where ${PROJECT_NAME} will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

# For CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

# Install the public header files
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# Add a "d" to DEBUG library versions
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# Install the target and create the export-set
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    # These get default values from GNUInstallDirs, no need to set them
    #   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # Except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/RGE
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

# Generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)

# Generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
)

# Create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)

# Generate the export targets for the build tree
export(EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
)