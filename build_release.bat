@cls
@title Build 'Visual Studio 17 2022' release
@echo off

rem The %~dp0 (that is a zero) variable when referenced within a Windows batch file will expand to the drive letter and path of that batch file.
set bat_dir=%~dp0%

rem The variables %0-%9 refer to the command line parameters of the batch file.
rem %1-%9 refer to command line arguments after the batch file name. %0 refers to the batch file itself.

set batch_file=%0

echo Generate CplusplusCi
set qt5_dir="C:\Qt\Qt5.15.2\5.15.2\msvc2019_64"
set build_dir=%bat_dir%\build\Release\CplusplusCi

rem Generate
cmake -S . -B "%build_dir%" -Ax64 -DWINDOWS:BOOL=ON -DCMAKE_PREFIX_PATH=%qt5_dir% -DQT_DLL_DIR="%qt5_dir%\bin"

rem Build
cmake --build "%build_dir%" -v --config Release

echo "..."
