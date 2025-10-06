cmake_minimum_required(VERSION 3.20)
project(RPEngineProject)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set global output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (MSVC)
    add_compile_options(/utf-8)
endif()

# Add subprojects
add_subdirectory(RPEngine)
add_subdirectory(Sandbox)

#add assets
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "${CMAKE_SOURCE_DIR}/bin/assets")

if(EXISTS "${ASSETS_SOURCE_DIR}")
    add_custom_target(copy_assets ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_SOURCE_DIR}"
            "${ASSETS_DEST_DIR}"
            COMMENT "Copying assets to bin directory..."
    )
    add_dependencies(Sandbox copy_assets)
else()
    message(WARNING "Assets folder not found: ${ASSETS_SOURCE_DIR}")
endif()