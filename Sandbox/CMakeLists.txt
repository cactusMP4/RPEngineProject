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