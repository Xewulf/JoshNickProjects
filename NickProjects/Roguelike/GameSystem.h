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
    Level _level;
    Player _player;
};