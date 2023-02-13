cmake_minimum_required(VERSION 3.21)
project(VoxelRender)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(VoxelRender/vendor/glfw)
add_subdirectory(VoxelRender/vendor/glm)
add_subdirectory(VoxelRender/vendor/Glad)

add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(
    VoxelRender/src
    VoxelRender/vendor/glfw/include
    VoxelRender/vendor/glm/
    VoxelRender/vendor/Glad/include)

add_executable(VoxelRender
    VoxelRender/src/Graphics/Camera.cpp
    VoxelRender/src/Graphics/Camera.h
    VoxelRender/src/Graphics/Renderer.cpp
    VoxelRender/src/Graphics/Renderer.h
    VoxelRender/src/Graphics/Scene.cpp
    VoxelRender/src/Graphics/Scene.h
    VoxelRender/src/Graphics/Shader.cpp
    VoxelRender/src/Graphics/Shader.h
    VoxelRender/src/Graphics/VoxelArray.cpp
    VoxelRender/src/Graphics/VoxelArray.h
    VoxelRender/src/Graphics/Window.cpp
    VoxelRender/src/Graphics/Window.h
    VoxelRender/src/Input/Input.cpp
    VoxelRender/src/Input/Input.h
    VoxelRender/src/Utils/Utils.h
    VoxelRender/src/VoxelReader/Chunks/Chunk.cpp
    VoxelRender/src/VoxelReader/Chunks/Chunk.h
    VoxelRender/src/VoxelReader/Chunks/PaletteChunk.h
    VoxelRender/src/VoxelReader/Chunks/SizeChunk.h
    VoxelRender/src/VoxelReader/Chunks/VoxelChunk.h
    VoxelRender/src/VoxelReader/Reader.cpp
    VoxelRender/src/VoxelReader/Reader.h
    VoxelRender/src/main.cpp
)

target_link_libraries(VoxelRender Glad glfw glm)