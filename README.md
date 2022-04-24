# CplusplusCi

Learning c++ with Ci

[<img src="https://raw.githubusercontent.com/isocpp/logos/master/cpp_logo.png" height="25"/> <img src="https://upload.wikimedia.org/wikipedia/commons/1/13/Cmake.svg" height="25"/> <img src="https://dka575ofm4ao0.cloudfront.net/pages-transactional_logos/retina/16896/ApwXsQaJT16xVdsGs7aY" height="25"/>](#references)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](/LICENSE)

| Build status          | Systems / Compilers         |
| ------------- | ------------------------------------------ |
| [![Visual Studio Builds](https://ci.appveyor.com/api/projects/status/t6i95u07gw1gqhql/branch/master?svg=true)](https://ci.appveyor.com/project/WhitebrowSwordsman/cplusplusci/branch/main)       | Windows (Visual Studio 2022 / 2019)  |

## Generate project

Simple:
``` bash
cmake -S . -B build
```
Or detailed:
``` bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -T v143 -DWINDOWS:BOOL=ON -DUSE_BASE_SHARED_LIBS=ON
```

## Build

From the build folder
``` bash
# build the default build type
cmake --build ./build
# build a specific build type
cmake --build ./build --config Release
```

## References

- https://github.com/LearningByExample/ModernCppCI/
- https://cmake.org/
- https://www.appveyor.com/docs/lang/cpp/
- https://ci.appveyor.com/tools/validate-yaml

