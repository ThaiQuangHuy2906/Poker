cmake_minimum_required(VERSION 3.10)
project(PokerGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add executable
add_executable(Poker
    src/main.cpp
    src/Utils.cpp
    src/TexasHoldemPoker.cpp
    src/TwoFiveHihi.cpp
    src/SurprisingSwap.cpp
)

# For Windows-specific features
if(WIN32)
    target_compile_definitions(Poker PRIVATE _WIN32_WINNT=0x0601)
endif()

# Output directory
set_target_properties(Poker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
