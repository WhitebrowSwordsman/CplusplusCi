#!/bin/bash
#
# Init dev env.

bash_dir="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

echo "init.sh begin..."

package_cpplint_script=${bash_dir}/tools/cpplint/package_cpplint.sh

bash ${package_cpplint_script}

# install pre-commit
echo "install pre-commit"
cp -f ${bash_dir}/git/hooks/pre-commit ${bash_dir}/.git/hooks/

echo "init.sh end!"
