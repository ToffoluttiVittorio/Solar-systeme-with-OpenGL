cmake_minimum_required(VERSION 3.5)

project(OGL_TP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OGL_TP main.cpp camera.cpp camera.h controls.cpp controls.h fpscontrols.cpp fpscontrols.h
    navigationcontrols.cpp navigationcontrols.h object.cpp object.h renderer.cpp renderer.h shader.cpp shader.h
    texture.cpp texture.h uvbuffer.cpp uvbuffer.h vertexarray.cpp vertexarray.h vertexbuffer.cpp vertexbuffer.h
    pointlight.h pointlight.cpp)


target_link_libraries(OGL_TP glfw GLEW libGLEW.so libGLU.so libGL.so)
