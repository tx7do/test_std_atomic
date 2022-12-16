# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.0)

project(test_std_atomic LANGUAGES C CXX)

# C++版本
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C版本
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(no_lock)
add_subdirectory(use_lock)
add_subdirectory(use_atomic)
