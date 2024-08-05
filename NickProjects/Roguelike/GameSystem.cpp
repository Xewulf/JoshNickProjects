#include "GameSystem.h"
#include <iostream>
#include <conio.h>

//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName)
{
    _player.init(1, 100, 10, 10, 0);

    _level.load(levelFileName, _player);

    system("PAUSE");
}

void GameSystem::playGame()
{
    bool isDone = false;

    while (isDone != true)
    {
        _level.print();
        playerMove();
        _level.updateEnemies(_player);
    }

}

void GameSystem::playerMove()
{
    char input;

    printf("Enter a move command (w/s/a/d): ");

#if HAS_GETCH
    char c = _getch(); // Use _getch() on Windows
#else
    char c = std::cin.get(); // Use std::cin.get() on other platforms
#endif

    input = c;
    _level.movePlayer(input, _player);

}



