# Created by WhitebrowSwordsman on 2022/04/22.
#
# Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
# 

cmake_minimum_required(VERSION 3.12)

set(project_name base)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_REGENERATION ON)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Separate multiple Projects and put them into folders which are on top-level.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# How do I make CMake output into a 'bin' dir?
#   The correct variable to set is CMAKE_RUNTIME_OUTPUT_DIRECTORY.
#   We use the following in our root CMakeLists.txt:
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
option(BASE_BUILD_SHARED_LIBS "Build ${project_name} as a shared library." ON)
option(BASE_BUILD_STATIC_LIBS "Build ${project_name} as a static library." ON)
if(BASE_BUILD_SHARED_LIBS)
  message(STATUS "======>> Build ${project_name} as a shared library.")
endif()
if(BASE_BUILD_STATIC_LIBS)
  message(STATUS "======>> Build ${project_name} as a static library.")
endif()

add_definitions(-DBASE_IMPLEMENTATION)
if (WINDOWS)
  add_definitions(-DOS_WINDOWS)
endif()

set(base_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE base_public_header
  ${base_include_dir}/*.h
  )

source_group(TREE ${base_include_dir} PREFIX "Public API" FILES ${base_public_header})

file(GLOB_RECURSE base_src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  )

# Removes items from the list that match the mode's pattern.
# Removes the content of 'src/platform' folder.

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${base_src})

# build different libs
if (BASE_BUILD_SHARED_LIBS)
  set(shared_lib ${project_name}_lib)
  add_library(${shared_lib} SHARED ${base_src} ${base_public_header})
  set_target_properties(${shared_lib} PROPERTIES
    OUTPUT_NAME ${project_name}
    POSITION_INDEPENDENT_CODE ${BASE_BUILD_SHARED_LIBS}
    )
  target_include_directories(${shared_lib} PUBLIC 
    $<BUILD_INTERFACE:${base_include_dir}>
    )
  target_compile_definitions(${shared_lib} PUBLIC BASE_COMPONENT_BUILD)
  if(MACOS)
    set_target_properties(${shared_lib} PROPERTIES
      FRAMEWORK TRUE
      FRAMEWORK_VERSION A
      MACOSX_FRAMEWORK_IDENTIFIER com.example.cplusplus-ci-common
      VALID_ARCHS[variant=Release] "arm64 armv7"
      VALID_ARCHS[variant=Debug] "arm64 armv7 x86_64"
    )
  endif()
  if(WINDOWS)
  install(TARGETS ${shared_lib}
      CONFIGURATIONS Release
      RUNTIME DESTINATION bin
      )
  endif()
endif()
if (BASE_BUILD_STATIC_LIBS)
  set(static_lib ${project_name}_static)
  add_library(${static_lib} STATIC ${base_src} ${base_public_header})
  # avoid name clashes on windows as the shared import lib is also named jsoncpp.lib
  if(NOT DEFINED static_suffix AND BASE_BUILD_SHARED_LIBS)
    if(MSVC OR ANDROID)
      set(static_suffix "_static")
    else()
      set(static_suffix "")
    endif()
  endif()
  set_target_properties(${static_lib} PROPERTIES
    OUTPUT_NAME ${project_name}${static_suffix}
    )
  target_include_directories(${static_lib} PUBLIC 
    $<BUILD_INTERFACE:${base_include_dir}>
    )
endif()
