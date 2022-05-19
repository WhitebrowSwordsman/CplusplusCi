include(GitCloneOrUpdateExternal)

if(NOT DEFINED ENV{CI})
  # Git clone or update external
  set(STYLEGUIDE_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/src/styleguide")
  set(STYLEGUIDE_REPO "https://github.com/WhitebrowSwordsman/styleguide.git")
  set(STYLEGUIDE_BRANCH_NAME "gh-pages")
  message(STATUS "Git clone or update ${STYLEGUIDE_REPO}")
  # git_clone_and_update(${STYLEGUIDE_REPO} ${STYLEGUIDE_LOCATION} ${STYLEGUIDE_BRANCH_NAME})
endif()
