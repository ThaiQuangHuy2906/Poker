# Poker Game Collection

A collection of poker game variants implemented in C++ for Windows, including Texas Hold'em Poker, Two Five Hihi, and Surprising Swap.

## Features

### 1. Texas Hold'em Poker
- Full Texas Hold'em implementation with betting rounds (Pre-flop, Flop, Turn, River)
- Support for 2-10 players
- Ante, Small Blind, and Big Blind betting system
- All-in, Fold, Call, Raise, Check, and Bet actions
- Leaderboard system tracking wins, winrate, and favorite strategies
- Dealer button rotation

### 2. Two Five Hihi
- Alternative poker variant with button scoring system
- Players vote on scoring method (button points vs. poker hands)
- 5-card community cards
- Support for multiple players

### 3. Surprising Swap
- Unique poker variant with card swapping mechanism
- Players vote to randomly swap cards between players
- 5-card hands with standard poker rankings
- Elimination-style gameplay

## Requirements

- **Platform**: Windows (uses Windows-specific APIs for colors and sound)
- **Compiler**: C++11 or later (tested with MSVC and MinGW)
- **Dependencies**: Standard C++ library, Windows.h

## Project Structure

```
Poker/
├── include/                # Header files
│   ├── Utils.h
│   ├── TexasHoldemPoker.h
│   ├── TwoFiveHihi.h
│   └── SurprisingSwap.h
├── src/                    # Source files
│   ├── main.cpp
│   ├── Utils.cpp
│   ├── TexasHoldemPoker.cpp
│   ├── TwoFiveHihi.cpp
│   └── SurprisingSwap.cpp
├── docs/                   # Documentation
│   ├── BUILD.md
│   ├── QUICKSTART.md
│   ├── CHANGELOG.md
│   └── CONTRIBUTING.md
├── README.md
├── LICENSE
├── .gitignore
├── build.bat
└── CMakeLists.txt
```

## Building the Project

### Using g++ (MinGW/MSYS2):
```bash
g++ -std=c++11 -Iinclude src/main.cpp src/Utils.cpp src/TexasHoldemPoker.cpp src/TwoFiveHihi.cpp src/SurprisingSwap.cpp -o Poker.exe
```

Or simply run:
```bash
build.bat
```

### Using Visual Studio:
1. Create a new C++ Console Application project
2. Add all `.h` and `.cpp` files to the project
3. Build and run (F5)

### Using CMake (optional):
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## How to Play

1. Run the executable
2. Choose a game from the menu (1-3)
3. Enter the number of players
4. Follow on-screen prompts for each betting round

### Texas Hold'em Controls:
- **1**: Fold - Give up current hand
- **2**: Call - Match current bet
- **3**: Raise - Increase the current bet
- **4**: All-In - Bet all remaining chips
- **5**: Check - Pass when no bet is active
- **6**: Bet - Place the first bet of a round

## Game Rules

### Texas Hold'em
- Each player starts with 10,000 chips
- Ante: 5 chips (mandatory bet)
- Small Blind: 10 chips
- Big Blind: 20 chips
- Players eliminated when chips reach 0
- Winner determined by best 5-card hand from 2 hole cards + 5 community cards

### Hand Rankings (Highest to Lowest)
1. Straight Flush
2. Four of a Kind
3. Full House
4. Flush
5. Straight
6. Three of a Kind
7. Two Pair
8. One Pair
9. High Card

## Features

- **Colored Console Output**: Different colors for each betting round
- **Sound Effects**: Beep sounds and optional MP3 music for winners
- **Statistics Tracking**: Wins, winrate, games played, favorite hand types
- **Leaderboard**: Shows active and eliminated players with full stats

## Known Limitations

- Windows-only (uses Windows.h for colors and sounds)
- Music playback requires Windows Media Player or compatible media player
- Console-based interface (no GUI)
- Vietnamese comments in some sections of code

## Future Improvements

- Cross-platform support (Linux, macOS)
- Network multiplayer
- GUI implementation
- Save/load game state
- More game variants
- AI opponents

## License

This project is open source. Feel free to use, modify, and distribute.

## Author

Created as a personal project for learning C++ and poker game logic.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Notes

- The `music.mp3` file is optional. The game will attempt to play it when a player wins, but the game functions fine without it.
- The code includes Vietnamese comments explaining game logic.
- All three game modes are fully implemented and ready to play.
