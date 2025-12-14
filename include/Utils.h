#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <string>

// Utility functions for sound and color
void setTextColor(int color);
void playSoundEffect();
void playMp3(const char *filePath, int seconds);

#endif // UTILS_H
