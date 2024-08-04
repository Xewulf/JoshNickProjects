#include <stdio.h>
#include <iostream>
#include <string>
#include "GameSystem.h"

// Check if we are on Windows
#if defined(_WIN32) || defined(_win64)
#include <conio.h>
#define HAS_GETCH 1
#else
#define HAS_GETCH 0
#endif

int main()
{

    GameSystem gameSystem("Level1.txt");

    gameSystem.playGame();

    return 0;
}