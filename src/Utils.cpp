#include "../include/Utils.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

void setTextColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void playSoundEffect()
{
    Beep(750, 300); // Tần số 750Hz, thời gian 300ms
}

void playMp3(const char *filePath, int seconds)
{
    string command = "start ";
    command += filePath;
    system(command.c_str());

    cout << "Music for Winner ~!\n";

    // Chờ thời gian chỉ định (giới hạn thời gian phát)
    this_thread::sleep_for(chrono::seconds(seconds));

    // Dừng ứng dụng phát nhạc (bằng cách kết thúc tiến trình mặc định)
    system("taskkill /IM wmplayer.exe /F >nul 2>&1");    // Tắt Windows Media Player
    system("taskkill /IM Music.UI.exe /F >nul 2>&1");    // Tắt Groove Music (Windows 10+)
    system("taskkill /IM MediaPlayer.exe /F >nul 2>&1"); // Trình phát Đa phương tiện Windows 11

    cout << "End music and start a new game!\n\n";
    playSoundEffect();
}
