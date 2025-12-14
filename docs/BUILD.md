# Build Instructions

This document provides detailed instructions for building the Poker Game Collection on Windows.

## Prerequisites

### Option 1: MinGW/MSYS2 (Recommended for beginners)
1. Download and install MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and install GCC:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
3. Add MinGW to your PATH:
   - Add `C:\msys64\mingw64\bin` to your system PATH

### Option 2: Visual Studio
1. Download Visual Studio 2019 or later (Community Edition is free)
2. During installation, select "Desktop development with C++"
3. Ensure C++ compiler and Windows SDK are installed

### Option 3: CMake (Cross-platform)
1. Download CMake from https://cmake.org/download/
2. Install and add to PATH
3. Install a C++ compiler (MinGW or Visual Studio)

## Building

### Method 1: Command Line with g++ (Quick)

```powershell
# Navigate to project directory
cd "e:\Personal Project\Poker"

# Compile all files
g++ -std=c++11 -Iinclude src/main.cpp src/Utils.cpp src/TexasHoldemPoker.cpp src/TwoFiveHihi.cpp src/SurprisingSwap.cpp -o Poker.exe

# Or use the build script
.\build.bat

# Run the game
.\Poker.exe
```

### Method 2: Visual Studio IDE

1. Open Visual Studio
2. File → New → Project
3. Select "Console App" (C++)
4. Name it "Poker" and choose location
5. Delete the default .cpp file
6. Project → Add Existing Item → Add all .h and .cpp files
7. Build → Build Solution (Ctrl+Shift+B)
8. Debug → Start Without Debugging (Ctrl+F5)

### Method 3: CMake

```powershell
# Navigate to project directory
cd "e:\Personal Project\Poker"

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run (executable will be in build/bin/)
cd bin
.\Poker.exe
```

### Method 4: PowerShell Build Script

Create a file named `build.ps1`:

```powershell
# Build script for Poker Game
Write-Host "Building Poker Game..." -ForegroundColor Green

$sourceFiles = @(
    "main.cpp",
    "Utils.cpp",
    "TexasHoldemPoker.cpp",
    "TwoFiveHihi.cpp",
    "SurprisingSwap.cpp"
)

$outputFile = "Poker.exe"
$compiler = "g++"
$flags = "-std=c++11 -O2"

$command = "$compiler $flags $($sourceFiles -join ' ') -o $outputFile"

Write-Host "Executing: $command" -ForegroundColor Yellow
Invoke-Expression $command

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful! Executable: $outputFile" -ForegroundColor Green
    Write-Host "Run with: .\$outputFile" -ForegroundColor Cyan
} else {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}
```

Run it:
```powershell
.\build.ps1
```

## Troubleshooting

### "g++ is not recognized"
- Ensure MinGW/GCC is installed
- Add compiler to system PATH
- Restart terminal/IDE after PATH changes

### Missing Windows.h
- Ensure you're using a Windows compiler (MinGW or MSVC)
- This project uses Windows-specific APIs

### Linker errors
- Ensure all .cpp files are included in compilation
- Check that all .h files are in the same directory

### Runtime errors
- Ensure music.mp3 is in the same directory as the executable (optional)
- Run from directory containing the .exe file

## Cleaning Build Files

### Manual
```powershell
Remove-Item *.exe, *.o, *.obj
```

### CMake
```powershell
cd build
cmake --build . --target clean
```

## Running the Game

```powershell
.\Poker.exe
```

Or double-click `Poker.exe` in File Explorer.

## Development Tips

### Hot Reload Development
Use this command for quick recompilation during development:
```powershell
g++ -std=c++11 -g main.cpp Utils.cpp TexasHoldemPoker.cpp TwoFiveHihi.cpp SurprisingSwap.cpp -o Poker.exe && .\Poker.exe
```

### Debug Build
```powershell
g++ -std=c++11 -g -O0 main.cpp Utils.cpp TexasHoldemPoker.cpp TwoFiveHihi.cpp SurprisingSwap.cpp -o Poker_debug.exe
```

### Release Build (Optimized)
```powershell
g++ -std=c++11 -O3 main.cpp Utils.cpp TexasHoldemPoker.cpp TwoFiveHihi.cpp SurprisingSwap.cpp -o Poker.exe
```

## Notes

- All three game modes (Texas Hold'em, Two-Five Hihi, Surprising Swap) are fully implemented
- The project uses C++11 standard features
- Windows.h is required for console color and sound effects

## Next Steps

After successful build:
1. Run the game and test all three variants
2. Check for any compilation warnings
3. Commit your changes to Git
4. Push to GitHub

## Support

If you encounter issues:
1. Check this document first
2. Review error messages carefully
3. Search for similar issues online
4. Open an issue on GitHub with:
   - Your compiler version
   - Full error message
   - Steps to reproduce
