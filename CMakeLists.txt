cmake_minimum_required(VERSION 3.30)
project(snakeGame)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        C:/libs_c++/GLFW/include
        C:/libs_c++/GLAD/include
        ${PROJECT_SOURCE_DIR}/include
)
link_directories(
        C:/libs_c++/GLFW/lib
        C:/libs_c++/GLAD/lib
)

file(GLOB_RECURSE SOURCES
        src/*.cpp
)

add_executable(snakeGame
        ${SOURCES}
)

target_link_libraries(snakeGame
        glfw3
        opengl32
        gdi32
        glu32
)
