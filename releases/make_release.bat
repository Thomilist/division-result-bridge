@echo off
setlocal EnableDelayedExpansion

set /p version_tag=Enter version tag: 

echo Choose CPU architecture:
echo 1) x86_64
echo 2) arm64
set /p cpu_arch_choice=

if %cpu_arch_choice%==1 (
    set cpu_arch=x86_64
) else if %cpu_arch_choice%==2 (
    set cpu_arch=arm64
)

echo Choose OS:
echo 1) Windows
echo 2) Linux
set /p os_choice=

if %os_choice%==1 (
    set os=windows
) else if %os_choice%==2 (
    set os=linux
)

set project_name=division-result-bridge
set version_name=%project_name%-%version_tag%-%os%-%cpu_arch%
set project_dir=D:\Programming\cpp\projects\%project_name%
set release_dir=%project_dir%\releases\%version_name%
set dll_dir=C:\msys64\mingw64\bin
set build_dir=%project_dir%\build
set rar="C:\Program Files\WinRAR\WinRAR.exe"
set ntldd=C:\msys64\mingw64\bin\ntldd.exe
set qtdeploy=windeployqt6

echo Creating new release titled %version_name%...

echo Creating directory...
mkdir %release_dir%

echo Copying DLL files...
for /f %%d in ('%ntldd% -R %build_dir%\%project_name%.exe ^| grep lib') do (
    xcopy %dll_dir%\%%d %release_dir%
)

echo Copying %project_name% executable...
xcopy %build_dir%\%project_name%.exe %release_dir%

echo Fetching Qt resources...
%qtdeploy% %release_dir%\%project_name%.exe

echo Compressing release...
%rar% a -ep1 -afzip %release_dir%\..\%version_name%.zip %release_dir%
move %release_dir%\..\%version_name%.zip %release_dir%

echo Done!