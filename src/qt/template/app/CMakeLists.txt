# Created by %username% on %date%.
#
# Copyright (c) %year% The %SharedlibName% Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.16)

set(project_name template_name_app)
project(${project_name} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Separate multiple Projects and put them into folders which are on top-level.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# How do I make CMake output into a 'bin' dir?
#   The correct variable to set is CMAKE_RUNTIME_OUTPUT_DIRECTORY.
#   We use the following in our root CMakeLists.txt:
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network WebEngineCore WebEngine WebEngineWidgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network WebEngineCore WebEngine WebEngineWidgets LinguistTools)

# Network include
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5WebEngineCore_INCLUDE_DIRS})
include_directories(${Qt5WebEngine_INCLUDE_DIRS})
include_directories(${Qt5WebEngineWidgets_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
  )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

list(APPEND PROJECT_SOURCES 
  ${project_name}.qrc
  )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(${project_name}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    )

  # Define target properties for Android with Qt 6 as:
  #    set_property(TARGET ${project_name} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
  # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

  qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
else()
  # qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})

  add_executable(${project_name}
    ${PROJECT_SOURCES}
    ${APP_RES}
    ${QT_RES}
    ${WIN_RES}
    )
endif()

target_link_libraries(${project_name} PRIVATE 
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::WebEngineCore
  Qt${QT_VERSION_MAJOR}::WebEngine
  Qt${QT_VERSION_MAJOR}::WebEngineWidgets
  ${common_name}
  )

set_target_properties(${project_name} PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
  )

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(${project_name})
endif()

if(WINDOWS)
  set(deploy_tmp_dir "${CMAKE_BINARY_DIR}/windeploy")
endif()

if(EXISTS ${deploy_tmp_dir})
  # copy deployment directory during installation
  install(
    DIRECTORY "${deploy_tmp_dir}/"
    CONFIGURATIONS Release
    DESTINATION bin
    )
endif()

if(WINDOWS)
  install(TARGETS ${project_name}
    CONFIGURATIONS Release
    RUNTIME DESTINATION bin
    )
endif()

set_target_properties(${project_name} PROPERTIES FOLDER "qt")
