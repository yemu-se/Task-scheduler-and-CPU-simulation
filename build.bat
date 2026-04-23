@echo off
echo Compiling CPU Scheduler...

C:\Users\yemanc6505\Desktop\mingw64\bin\g++.exe -static main.cpp src/*.cpp -I include -o scheduler.exe

if %errorlevel% equ 0 (
    echo.
    echo Compilation Successful! Running program...
    echo.
    scheduler.exe
) else (
    echo.
    echo Compilation Failed!
)
pause