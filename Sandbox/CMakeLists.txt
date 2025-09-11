project(Sandbox)

# Executable
add_executable(Sandbox
        src/Sandbox.cpp
)

# Link Sandbox against RPEngine
target_link_libraries(Sandbox PRIVATE RPEngine)

# Include engine headers
target_include_directories(Sandbox PRIVATE
        ${CMAKE_SOURCE_DIR}/RPEngine/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/GLFW/include
)

# Put Sandbox outputs into its own bin/bin-int folder
set_target_properties(Sandbox PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/Sandbox
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Sandbox
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Sandbox
)
