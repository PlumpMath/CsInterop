@echo off
color 0a

set ming=c:\mingw\bin
set path=%path%;%ming%;

mingw32-make -f Makefile.win -e CWD=%~dp0
pause