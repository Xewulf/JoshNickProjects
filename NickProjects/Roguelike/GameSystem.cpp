#include <iostream>
#include <string>
#include "GameSystem.h"
#include "Shop.h"
#include <conio.h>


// Check if we are on Windows
#if defined(_WIN32) || defined(_win64)
#include <conio.h>
#define HAS_GETCH 1
#else
#define HAS_GETCH 0
#endif




//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName)
{
    _player.init(1, 30, 5, 2, 0); //level, health, attack, defense, experience
    list<Shop> shops;
    _shop.initShops(shops);
    

    _level.load(levelFileName, _player);

    system("PAUSE");
}

void GameSystem::playGame()
{
    bool isDone = false;



    while (isDone != true)
    {

        _level.printvoid();
        _player.printstats();
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



