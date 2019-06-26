cmake_minimum_required(VERSION 3.10)

project(sun_moon_earth)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ggdb -O2")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


message(${CMAKE_CXX_FLAGS})


include_directories("../learn_opengl/glad/include")
include_directories("../learn_opengl/glm")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


if(glfw3_FOUND)
    message("found glfw3")
endif()

if(OpenGL_FOUND)
    message("found opengl")
endif()



add_executable(${PROJECT_NAME} sun_moon_earth/main.cpp sun_moon_earth/glad_src/glad.c 
                               sun_moon_earth/shader_creator.cpp
                               sun_moon_earth/vertex_creator.cpp)

target_link_libraries(${PROJECT_NAME}
    # Boost::system
    glfw3 #if do not link glfwxxx.a will: undefined reference to symbol 'pthread_key_delete@@GLIBC_2.2.5'
    pthread
    m
    GL
    GLU
    X11
    Xxf86vm
    Xrandr
    Xi
    dl
)

