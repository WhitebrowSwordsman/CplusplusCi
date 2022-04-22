
#
option(USE_BASE_SHARED_LIBS "${project_name} use base by shared library." OFF)

if (USE_BASE_SHARED_LIBS)
  message(STATUS "======>> ${project_name} use base by shared library.")
  set(common_name base_lib)
else()
  message(STATUS "======>> ${project_name} use base by static library.")
  set(common_name base_static)
endif()
