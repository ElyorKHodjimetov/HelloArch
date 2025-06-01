cmake_minimum_required(VERSION 3.5)

project(HelloArch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(HelloArch HelloArch.cpp)

if (WIN32)
    message(STATUS "Configuring for Windows")
elseif (UNIX)
    message(STATUS "Configuring for Linux (Raspberry Pi)")
endif()

install(TARGETS HelloArch DESTINATION bin)
