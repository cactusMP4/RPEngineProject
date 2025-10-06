project(Sandbox)

# Executable
add_executable(Sandbox
        src/Sandbox.cpp
)

target_link_libraries(Sandbox PRIVATE RPEngine)
target_include_directories(Sandbox PRIVATE
        ${CMAKE_SOURCE_DIR}/RPEngine/include
)

target_compile_features(Sandbox PRIVATE cxx_std_17)

# Put Sandbox outputs into its own bin/bin-int folder
set_target_properties(Sandbox PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/Sandbox
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Sandbox
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Sandbox
)
