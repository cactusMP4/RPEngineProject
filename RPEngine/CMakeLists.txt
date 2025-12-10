project(RPEngine)

# Library
add_library(RPEngine SHARED
        src/Application.cpp
        src/Core/Logger.cpp
        src/Window.cpp
        src/Core/Layer.cpp
        src/ImGui/ImGuiLayer.cpp
        src/ImGui/ImGuiBuild.cpp
        src/Core/Input.h
        src/Core/Input.cpp
        src/Render/Context.cpp
        "src/Render/Shader.cpp"
        "src/Render/Shader.h"
        src/Render/Buffer.cpp
        src/Render/Buffer.h
 "src/Render/BufferLayout.h" "src/Render/VertexArray.cpp"
        src/Render/Renderer.cpp
        src/Render/Renderer.h
        src/Render/Camera.h
        src/Core/TimeStep.h
        src/Core/Transform.h
 "src/Core/Time.h" "src/Core/Time.cpp" "src/Render/Camera.cpp")

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(RPEngine PRIVATE X11::X11)
endif()

target_include_directories(RPEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/Glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/ImGui/src
        ${CMAKE_CURRENT_SOURCE_DIR}/3dParty/glm
)

set(GLFW_LIBRARY_TYPE "STATIC" CACHE STRING "" FORCE)
add_subdirectory(3dParty/GLFW)
add_subdirectory(3dParty/Glad)
add_subdirectory(3dParty/ImGui)
target_link_libraries(RPEngine PRIVATE
        glfw
        glad
)
if(WIN32)
    target_compile_definitions(imgui PRIVATE "IMGUI_API=__declspec(dllexport)")
endif()

target_link_libraries(RPEngine PUBLIC
        imgui
)

target_compile_features(RPEngine PRIVATE cxx_std_17)
target_compile_definitions(RPEngine PRIVATE RPE_BUILD_DLL)