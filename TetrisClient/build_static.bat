@echo off
setlocal enabledelayedexpansion


set "QT_PATH=C:\Qt\6.10.2\mingw_64"
set "CMAKE_PATH=C:\Qt\Tools\CMake_64\bin"
set "NINJA_PATH=C:\Qt\Tools\Ninja"
set "ENIGMA_PATH=C:\Program Files (x86)\Enigma Virtual Box\enigmavb.exe"

set "PROJECT_NAME=TetrisClient"
set "BUILD_DIR=build_release"
set "DEPLOY_DIR=deploy"
:: -------------------------------------

echo [1/5] Cleaning old builds...
if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
if exist %DEPLOY_DIR% rd /s /q %DEPLOY_DIR%
mkdir %BUILD_DIR%
mkdir %DEPLOY_DIR%

echo [2/5] Configuring CMake (Release)...
path %QT_PATH%\bin;%CMAKE_PATH%;%NINJA_PATH%;%PATH%
cd %BUILD_DIR%
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
if %ERRORLEVEL% neq 0 (echo CMake failed! & pause & exit)

echo [3/5] Building project...
ninja
if %ERRORLEVEL% neq 0 (echo Build failed! & pause & exit)

echo [4/5] Running windeployqt...
copy "TetrisClient.exe" "..\%DEPLOY_DIR%\"
cd "..\%DEPLOY_DIR%"
windeployqt --release --no-translations --compiler-runtime TetrisClient.exe

echo [5/5] Packaging into single EXE (Enigma Virtual Box)...

if exist "%ENIGMA_PATH%" (
    echo Packaging...
    
    echo Done! Check %DEPLOY_DIR% folder.
) else (
    echo Enigma Virtual Box not found. App is ready in %DEPLOY_DIR% folder (with DLLs).
)

pause