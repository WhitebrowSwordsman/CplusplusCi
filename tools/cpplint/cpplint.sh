#!/bin/bash
#
# Perform bash tests.

bash_dir="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

cpplint_script=${bash_dir}/src/cpplint.py
cpplint_filters='-build/include,-whitespace/comments,-whitespace/indent'
cppcode_dir=${bash_dir}/../../src

python2_path=/c/Python27/python.exe
cpplint_cmd=${bash_dir}/dist/cpplint

for fullfile in $(find ${cppcode_dir} -type f); do
  filename=$(basename -- "${fullfile}")
  if [[ "${filename}" == "resource.h" ]]; then
    continue
  fi
  extension="${filename##*.}"
  if [[ "${extension}" == "h" || "${extension}" == "cc" ]]; then
    # echo ${fullfile}
    # use python2 script
    # ${python2_path} ${cpplint_script} --linelength=128 --filter="${cpplint_filters}" ${fullfile}
    # or use exe 
    ${cpplint_cmd} --linelength=128 --filter="${cpplint_filters}" ${fullfile}
  fi
done
