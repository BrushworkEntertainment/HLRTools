echo off
pushd %~dp0\..\
call dependencies\premake5.exe vs2019
popd
PAUSE
echo on