project(RPEngine)

# Library
add_library(RPEngine SHARED
        src/Application.cpp
        src/Logger.cpp
        src/Window.cpp
        include/Window.h
)

target_precompile_headers(RPEngine PUBLIC include/rpepch.h)


target_include_directories(RPEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/GLFW/include
)

target_link_libraries(RPEngine PRIVATE ${CMAKE_SOURCE_DIR}/RPEngine/3dParty/GLFW/libglfw3.a)

# Put RPEngine outputs into its own bin/bin-int folder
set_target_properties(RPEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/RPEngine
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
)
