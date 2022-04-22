cmake_minimum_required(VERSION 3.12)

set(project_name CplusplusCi)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Separate multiple Projects and put them into folders which are on top-level.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src/base)
add_subdirectory(src/app)
