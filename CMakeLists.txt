cmake_minimum_required(VERSION 3.22)
project(TrashEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrashEngine src/Core/main.cpp src/Core/Window.hpp src/Core/App.hpp src/Utils/Time.hpp src/Utils/Input.hpp src/Math/Vectors.hpp src/Utils/RenderUtils.hpp src/Graphics/Vertex.hpp src/Graphics/Mesh.hpp src/Utils/Shaders.hpp src/Math/Matrices.hpp src/Math/MatrixTransformation.hpp)

set(TARGET_LIB
        "/usr/lib/x86_64-linux-gnu/libGL.so"
        "/usr/lib/x86_64-linux-gnu/libGLU.so"
        "/usr/lib/x86_64-linux-gnu/libglut.so"
        "/usr/lib/x86_64-linux-gnu/libGLEW.so"
        )

target_link_libraries(TrashEngine ${TARGET_LIB})
