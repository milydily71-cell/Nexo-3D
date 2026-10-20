cmake_minimum_required(VERSION 3.20)
project(Nexo3D VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(nexo3d
    engine/src/main.cpp
)
target_include_directories(nexo3d PRIVATE engine/include)

if(MSVC)
    target_compile_options(nexo3d PRIVATE /W4 /permissive-)
else()
    target_compile_options(nexo3d PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
