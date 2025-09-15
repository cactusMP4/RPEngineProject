project(RPEngine)

# Library
add_library(RPEngine SHARED
        src/Application.cpp
        src/Logger.cpp
        src/Window.cpp
        include/Window.h
        include/Layer.h
        src/Layer.cpp
 "include/Core.h")

target_precompile_headers(RPEngine PUBLIC include/rpepch.h)


target_include_directories(RPEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/Glad/include
)

set(GLFW_LIBRARY_TYPE "STATIC" CACHE STRING "" FORCE)
add_subdirectory(3dParty/GLFW)
add_subdirectory(3dParty/Glad)
target_link_libraries(RPEngine PRIVATE
        glfw
        glad
)

target_compile_features(RPEngine PRIVATE cxx_std_17)
target_compile_options(RPEngine PRIVATE /utf-8)

target_compile_definitions(RPEngine PRIVATE RPE_BUILD_DLL)

# Put RPEngine outputs into its own bin/bin-int folder
set_target_properties(RPEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int/RPEngine
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/RPEngine
)
