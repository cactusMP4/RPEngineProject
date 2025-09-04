project(RPEngine)

# Library
add_library(RPEngine SHARED
        src/Application.cpp
 "src/Logger.cpp"  "include/Logger.h")

target_include_directories(RPEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/spdlog/include
)

# Put RPEngine outputs into its own bin/bin-int folder
set_target_properties(RPEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/RPEngine
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
)
