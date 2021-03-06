cmake_minimum_required(VERSION 3.16)

set(project_name qt_cpp_app)
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

include(TranslationUtils)
include(${CMAKE_CURRENT_SOURCE_DIR}/../base/cmake/base.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../base/include)
# Network include
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5WebEngineCore_INCLUDE_DIRS})
include_directories(${Qt5WebEngine_INCLUDE_DIRS})
include_directories(${Qt5WebEngineWidgets_INCLUDE_DIRS})

set(TS_DIR_NAME i18n)
set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${TS_DIR_NAME}")
set(TS_FILES 
    "${TS_DIR}/${project_name}_zh_CN.ts"
    )
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/${TS_DIR_NAME}")

file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

if(WIN32)
    set(WIN_RES "${CMAKE_CURRENT_SOURCE_DIR}/win/resource.h" "${CMAKE_CURRENT_SOURCE_DIR}/win/app.rc")
endif()

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

    message(STATUS "qm files ${QM_FILES}")
    
    add_app_translations_resource(APP_RES ${TS_DIR_NAME} ${QM_FILES})
    add_qt_translations_resource(QT_RES es zh_CN)
    
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
    ${common_name})

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
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/images/mandrill_512.png" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/images")
  list(APPEND qt_dll_lists "Qt5Core" "Qt5Gui" "Qt5Widgets" "Qt5WinExtras" 
      "Qt5Concurrent" 
      "Qt5Network" 
      "Qt5WebEngineCore" "Qt5WebEngine" "Qt5WebEngineWidgets" "Qt5Quick" "Qt5QuickWidgets" "Qt5PrintSupport" "Qt5Positioning" "Qt5WebChannel" "Qt5Qml" "Qt5QmlModels"
      )
  
  # Debug configuration, copy qt runtime to bin
  if ("$ENV{APPVEYOR}" STREQUAL "")
    foreach(qt_dll_name IN LISTS qt_dll_lists)
      file(COPY ${QT_DLL_DIR}/${qt_dll_name}d.dll DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug")
      file(COPY ${QT_DLL_DIR}/${qt_dll_name}d.pdb DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug")
    endforeach()
    file(COPY "${QT_DLL_DIR}/../plugins/platforms/qwindowsd.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/plugins/platforms/")
    file(COPY "${QT_DLL_DIR}/../plugins/platforms/qwindowsd.pdb" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/plugins/platforms/")
    file(COPY "${QT_DLL_DIR}/QtWebEngineProcessd.exe" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/")
    file(COPY "${QT_DLL_DIR}/QtWebEngineProcessd.pdb" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/")
    file(COPY "${QT_DLL_DIR}/../resources/icudtl.dat" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/resources/")
    file(COPY "${QT_DLL_DIR}/../resources/qtwebengine_resources.pak" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/resources/")
    file(COPY "${QT_DLL_DIR}/../translations/qtwebengine_locales" DESTINATION "${CMAKE_BINARY_DIR}/bin/Debug/translations/")
  endif()

  # Copy qt runtime to windeploy
  set(deploy_tmp_dir "${CMAKE_BINARY_DIR}/windeploy")
  foreach(qt_dll_name IN LISTS qt_dll_lists)
    file(COPY ${QT_DLL_DIR}/${qt_dll_name}.dll DESTINATION "${deploy_tmp_dir}")
  endforeach()
  file(COPY "${QT_DLL_DIR}/../plugins/platforms/qwindows.dll" DESTINATION "${deploy_tmp_dir}/plugins/platforms/")
  file(COPY ${QT_DLL_DIR}/QtWebEngineProcess.exe DESTINATION "${deploy_tmp_dir}/")
  file(COPY ${QT_DLL_DIR}/../resources/icudtl.dat DESTINATION "${deploy_tmp_dir}/resources/")
  file(COPY ${QT_DLL_DIR}/../resources/qtwebengine_resources.pak DESTINATION "${deploy_tmp_dir}/resources/")
  file(COPY ${QT_DLL_DIR}/../resources/qtwebengine_resources_100p.pak DESTINATION "${deploy_tmp_dir}/resources/")
  file(COPY ${QT_DLL_DIR}/../resources/qtwebengine_resources_200p.pak DESTINATION "${deploy_tmp_dir}/resources/")
  file(COPY ${QT_DLL_DIR}/../translations/qtwebengine_locales DESTINATION "${deploy_tmp_dir}/translations/")

  # Release configuration, copy qt runtime to bin
  file(COPY "${deploy_tmp_dir}/" DESTINATION "${CMAKE_BINARY_DIR}/bin/Release/")

  # Copy doc
  file(COPY "${CMAKE_SOURCE_DIR}/pack/doc" DESTINATION "${deploy_tmp_dir}/")

  set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${project_name})
endif()

if(OFF)
# windeployqt usage
if(Qt5_FOUND AND WIN32 AND TARGET Qt5::qmake AND NOT TARGET Qt5::windeployqt)
    get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)

    execute_process(
        COMMAND "${_qt5_qmake_location}" -query QT_INSTALL_PREFIX
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE qt5_install_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(windeployqt_path "${qt5_install_prefix}/bin/windeployqt.exe")
    set(imported_location ${windeployqt_path})

    if(EXISTS ${imported_location})
        add_executable(Qt5::windeployqt IMPORTED)

        set_target_properties(Qt5::windeployqt PROPERTIES
            IMPORTED_LOCATION ${imported_location}
        )

        if(TARGET Qt5::windeployqt)
            # execute windeployqt in a tmp directory after build
            add_custom_command(TARGET ${project_name}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
                COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
                COMMAND Qt5::windeployqt --dir "${CMAKE_CURRENT_BINARY_DIR}/windeployqt" "$<TARGET_FILE_DIR:${project_name}>/$<TARGET_FILE_NAME:${project_name}>"
            )
        endif()
    endif()
endif()
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
