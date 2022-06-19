# bash

## Function

1. A function to print out error messages along with other status information.
   ```bash
   # err function
   err() {
     echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $*" >&2
   }
   
   # test
   if ! do_something; then
     err "Unable to do_something" "now!"
     exit 1
   fi
   ```

## Comments

1. File header
   ```bash
   #!/bin/bash
   #
   # Perform bash tests.
   
   bash_dir="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
   echo ${bash_dir}
   ```

2. Function
   ```bash
   #######################################
   # Get current bash directory.
   # Globals:
   #   BASHDIR
   # Arguments:
   #   None
   # Outputs:
   #   Writes location to stdout
   #######################################
   function get_dir() {
     echo "${BASHDIR}"
   }
   
   # test
   BASHDIR="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
   get_dir

   #######################################
   # Delete a file in a sophisticated manner.
   # Arguments:
   #   File to delete, a path.
   # Returns:
   #   0 if thing was deleted, non-zero on error.
   #######################################
   function del_thing() {
     rm "$1"
   }
   
   # test del_thing
   del_thing "tmp.bash2"
   ```

3. TODO
   ```bash
   # TODO(mrmonkey): Handle the unlikely edge cases (bug ####)
   ```

## Naming Conventions
### Function Names
Lower-case, with underscores to separate words.
```bash
# Single function
my_func() {
  …
}

# Part of a package
mypackage::my_func() {
  …
}
```
### Variable Names
As for function names.
```bash
for zone in "${zones[@]}"; do
  something_with "${zone}"
done
```
### Constants and Environment Variable Names
All caps, separated with underscores, declared at the top of the file.
```bash
# Constant
readonly PATH_TO_FILES='/some/path'

# Both constant and environment
declare -xr ORACLE_SID='PROD'
```
Some things become constant at their first setting (for example, via getopts). Thus, it’s OK to set a constant in getopts or based on a condition, but it should be made readonly immediately afterwards.
```bash
#!/bin/bash
#
# tmp.bash

bash_dir="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
echo ${bash_dir}

VERBOSE='false'
while getopts 'v' flag; do
  case "${flag}" in
    v) VERBOSE='true' ;;
  esac
done
readonly VERBOSE
if [[ "${VERBOSE}" == 'true' ]]; then
  echo 'VERBOSE'
fi

# test
# ./tmp.bash -v
```