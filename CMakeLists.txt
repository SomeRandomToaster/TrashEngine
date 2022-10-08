cmake_minimum_required(VERSION 3.22)
project(TrashEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(TrashEngine src/main.cpp src/Window.hpp src/App.hpp)

set(TARGET_LIB
        "/usr/lib/x86_64-linux-gnu/libGL.so"
        "/usr/lib/x86_64-linux-gnu/libGLU.so"
        "/usr/lib/x86_64-linux-gnu/libglut.so"
        )

target_link_libraries(TrashEngine ${TARGET_LIB})
