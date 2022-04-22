# CplusplusCi
Learning c++ with Ci

## Generate project
Simple:
``` bash
cmake -S . -B build
```
Or detailed:
``` bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -T v143 -DWINDOWS:BOOL=ON -DUSE_BASE_SHARED_LIBS=ON
```

## BUILD
From the build folder
``` bash
# build the default build type
cmake --build ./build
# build a specific build type
cmake --build ./build --config Release
```
