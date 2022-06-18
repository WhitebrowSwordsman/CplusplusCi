# cc source code

add_subdirectory(base)
add_subdirectory(app)
add_subdirectory(qt)

if("${CMAKE_PREFIX_PATH}" STREQUAL "")
else()
  if(WINDOWS AND "${QT_DLL_DIR}" STREQUAL "")
  else()
    # Only build qt_cpp when Qt env available
    add_subdirectory(qt_cpp)
  endif()
endif()
