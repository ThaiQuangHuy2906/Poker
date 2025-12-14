@echo off
REM Build script for Poker Game Collection
echo ========================================
echo Building Poker Game Collection...
echo ========================================
echo.

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: g++ compiler not found!
    echo Please install MinGW or add it to your PATH.
    echo See BUILD.md for instructions.
    pause
    exit /b 1
)

REM Compile the project
echo Compiling source files...
g++ -std=c++11 -O2 -Iinclude src/main.cpp src/Utils.cpp src/TexasHoldemPoker.cpp src/TwoFiveHihi.cpp src/SurprisingSwap.cpp -o Poker.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Build successful!
    echo ========================================
    echo Executable: Poker.exe
    echo.
    echo Run with: Poker.exe
    echo.
) else (
    echo.
    echo ========================================
    echo Build FAILED!
    echo ========================================
    echo Check the error messages above.
    echo.
)

pause
