project(RPEngine)

# Library
add_library(RPEngine SHARED
        src/Application.cpp
)

target_include_directories(RPEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Put RPEngine outputs into its own bin/bin-int folder
set_target_properties(RPEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/RPEngine
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
)
