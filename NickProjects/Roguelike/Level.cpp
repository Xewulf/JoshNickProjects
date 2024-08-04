#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>

Level::Level()
{

}

void Level::load(std::string fileName, Player& player)
{
    //Loads the level
    std::ifstream file;

    file.open(fileName);
    if (file.fail()) {
        perror(fileName.c_str());
        system("PAUSE");
        exit(1);
    }

    std::string line;

    while (getline(file, line)) {
        _levelData.push_back(line);
    }

    file.close();

    //Process the level
    char tile;

    for (int i = 0; i < _levelData.size(); i++)
    {
        for (int j = 0; j < _levelData[i].size(); j++)
        {
            tile = _levelData[i][j];

            switch (tile)
            {
            case '@': //Player
                player.setPosition(j, i);
                break;
            case 'S': //Skeleton
                _enemies.push_back(Enemy("Skeleton", tile, 1, 3, 1, 10, 10));
                _enemies.back().setPosition(j, i);
                break;
            case 'D': //Skeleton
                _enemies.push_back(Enemy("Death Knight", tile, 5, 15, 10, 100, 100));
                _enemies.back().setPosition(j, i);
                break;
            case 'L': //Skeleton
                _enemies.push_back(Enemy("Lich King", tile, 10, 30, 20, 300, 1000));
                _enemies.back().setPosition(j, i);
                break;
            }
        }
    }
}

void Level::print()
{

    std::cout << std::string(100, '\n');

    for (int i = 0; i < _levelData.size(); i++)
    {
        printf("%s\n", _levelData[i].c_str());
    }
    printf("\n");
}

void Level::movePlayer(char input, Player& player)
{
    int playerX;
    int playerY;

    player.getPosition(playerX, playerY);

    char moveTile;

    switch (input)
    {
    case 'w': //up
    case 'W':
        processPlayerMove(player, playerX, playerY - 1);
        break;
    case 's': //down
    case 'S':
        processPlayerMove(player, playerX, playerY + 1);
        break;
    case 'a': //left
    case 'A':
        processPlayerMove(player, playerX - 1, playerY);
        break;
    case 'd': //right
    case 'D':
        processPlayerMove(player, playerX + 1, playerY);
        break;
    default:
        printf("INVALID INPUT!\n");
        system("PAUSE");
        break;
    }
}

char Level::getTile(int x, int y)
{
    return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
    _levelData[y][x] = tile;
}

void Level::processPlayerMove(Player& player, int targetX, int targetY)
{
    int playerX;
    int playerY;
    player.getPosition(playerX, playerY);


    char moveTile = getTile(targetX, targetY);

    switch (moveTile)
    {
    case '.':
        player.setPosition(targetX, targetY);
        setTile(playerX, playerY, '.');
        setTile(targetX, targetY, '@');
        break;
    case '#':
        break;
    default:
        battleMonster(player, targetX, targetY);
        break;

    }
}

void Level::battleMonster(Player& player, int targetX, int targetY)
{
    int enemyX;
    int enemyY;
    int attackRoll;
    int attackResult;

    for (int i = 0; i < _enemies.size(); i++)
    {
        _enemies[i].getPosition(enemyX, enemyY);
        if (targetX == enemyX && targetY == enemyY)
        {
            //Battle!
            attackRoll = player.attack();
            printf("Player attacked monster with a roll of %d \n", attackRoll);
            attackResult = _enemies[i].takeDamage(attackRoll);

            if (attackResult != 0)
            {
                setTile(targetX, targetY, '.');
                print();
                printf("Monster died!\n");
                system("PAUSE");
                player.addExperience(attackResult);

                return;
            }
            //Monster turn!
            attackRoll = _enemies[i].attack();
            printf("%s attacked you with a roll of %d \n", attackRoll);

            attackResult = player.takeDamage(attackRoll);

            if (attackResult != 0)
            {
                setTile(targetX, targetY, 'x');
                print();
                printf("You died!\n");
                system("PAUSE");

                exit(0);
            }

            return;
        }
    }
}


