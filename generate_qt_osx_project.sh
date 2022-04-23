#!/bin/bash
#
# Generate 'macOS' project for CplusplusCi.

bash_dir="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

echo "generate qt macos project ..."

qt_osx_path="/Users/tinsauliu/Qt5.15.2/5.15.2/clang_64"
qt_osx_dir="$bash_dir/build/macos/CplusplusCi"
cmake -S "$bash_dir" -B "$qt_osx_dir" -G "Xcode" -DMACOS:BOOL=ON -DCMAKE_PREFIX_PATH=${qt_osx_path}

app_xcodeproj="$bash_dir/CplusplusCi.xcodeproj"
if ! [ -h "$app_xcodeproj" ]; then
  ln -s "$qt_osx_dir/CplusplusCi.xcodeproj" "$app_xcodeproj"
fi

echo "success!"