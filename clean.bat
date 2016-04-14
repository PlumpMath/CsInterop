@echo off
color 0a

set ming=c:\mingw\bin
set path=%path%;%ming%;

mingw32-make -e CWD=%~dp0 clean
pause