# git clone or update third_party

function(git_clone_and_update _repo _location _branch)
  if(EXISTS "${_location}/.git")
    execute_process(
      COMMAND git -C ${_location} pull
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE _git_result
    )
    if(NOT ("${_git_result}" STREQUAL "0"))
      message(WARNING "error: git -C ${_location} pull failed")
    endif()
  else()
    execute_process(
      COMMAND git clone ${_repo} ${_location}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE _git_result
    )
    if(NOT ("${_git_result}" STREQUAL "0"))
      message(FATAL_ERROR "error: git clone ${_repo} ${_location} failed")
    endif()
  endif()
  # checkout
  execute_process(
    COMMAND git -C ${_location} checkout ${_branch}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _git_result
  )
  if(NOT ("${_git_result}" STREQUAL "0"))
    message(WARNING "error: git -C ${_location} checkout ${_branch} failed")
  endif()
  # pull
  execute_process(
    COMMAND git -C ${_location} pull
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _git_result
  )
  if(NOT ("${_git_result}" STREQUAL "0"))
    message(WARNING "error: git -C ${_location} pull failed")
  endif()
endfunction()
