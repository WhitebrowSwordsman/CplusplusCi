cmake_minimum_required(VERSION 3.12)

set(project_name CplusplusCi)

project(${project_name})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Separate multiple Projects and put them into folders which are on top-level.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "QtDir is ${CMAKE_PREFIX_PATH}")

add_subdirectory(tools)
add_subdirectory(src)
