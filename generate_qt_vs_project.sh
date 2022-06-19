#!/bin/bash
#

bash_dir="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

init_script=${bash_dir}/init.sh

bash ${init_script}
if [[ $? != 0 ]]; then
  echo "Init develop env failed! Need to check the reason."
  exit 1
fi

$bash_dir/generate_qt_vs_project.bat

echo "success!"
