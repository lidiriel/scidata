set(Examples_Path "${PROJECT_SOURCE_DIR}/examples")

# in the generated config/Global_Build_Config.h
configure_file( global_build_config.h.in ${CMAKE_BINARY_DIR}/config/global_build_config.h )

# The config directory should be added as a include-searchpath
#include_directories( ${CMAKE_BINARY_DIR}/config/ )
