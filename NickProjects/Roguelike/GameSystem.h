#pragma once
#include "Player.h"
#include "Level.h"
#include <string>

class GameSystem
{
public:
    GameSystem(std::string levelFileName);
   
    void playGame();
    void playerMove();

private:
    Shop _shop;
    Level _level;
    Player _player;
};