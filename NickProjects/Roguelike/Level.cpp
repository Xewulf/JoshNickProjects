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

void Level::updateEnemies(Player& player)
{

    char aiMove;
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;

    player.getPosition(playerX, playerY);

    for (int i = 0; i < _enemies.size(); i++)
    {
        aiMove = _enemies[i].getMove(playerX, playerY);
        _enemies[i].getPosition(enemyX, enemyY);

        switch (aiMove)
        {
        case 'w': //up
            processEnemyMove(player, i, enemyX, enemyY - 1);
            break;
        case 's': //down
            processEnemyMove(player, i, enemyX, enemyY + 1);
            break;
        case 'a': //left
            processEnemyMove(player, i, enemyX - 1, enemyY);
            break;
        case 'd': //right
            processEnemyMove(player, i, enemyX + 1, enemyY);
            break;
        }
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
    std::string nextlevel = "Level2.txt";

    char moveTile = getTile(targetX, targetY);

    switch (moveTile)
    {
    case '.':
        player.setPosition(targetX, targetY);
        setTile(playerX, playerY, '.');
        setTile(targetX, targetY, '@');
        break;
    case '-':

        //INSERT NEXT LEVEL CODE HERE
        //maplevel++

        break;
    case '_':

        //INSERT PREVIOUS LEVEL CODE HERE
        //maplevel--

        break;
    case '#':
        break;
    default:
        battleMonster(player, targetX, targetY);
        break;

    }
}

void Level::processEnemyMove(Player& player, int enemyIndex, int targetX, int targetY)
{
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;

    _enemies[enemyIndex].getPosition(enemyX, enemyY);

    player.getPosition(playerX, playerY);


    char moveTile = getTile(targetX, targetY);

    switch (moveTile)
    {
    case '.':
        _enemies[enemyIndex].setPosition(targetX, targetY);
        setTile(enemyX, enemyY, '.');
        setTile(targetX, targetY, _enemies[enemyIndex].getTile());
        break;
    case '@':
        battleMonster(player, enemyX, enemyY);
        break;
    default:
        break;

    }
}

void Level::battleMonster(Player& player, int targetX, int targetY)
{
    int enemyX;
    int enemyY;
    int playerX;
    int playerY;
    int attackRoll;
    int attackResult;
    std::string enemyName;

    player.getPosition(playerX, playerY);


    for (int i = 0; i < _enemies.size(); i++)
    {

        _enemies[i].getPosition(enemyX, enemyY);
        enemyName = _enemies[i].getName();

        if (targetX == enemyX && targetY == enemyY)
        {
            //Battle!
            attackRoll = player.attack();
            printf("\nYou attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
            attackResult = _enemies[i].takeDamage(attackRoll);

            if (attackResult != 0)
            {
                setTile(targetX, targetY, '.');
                print();
                printf("Monster died!\n");

                //remove the enemy
                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                i--;

                system("PAUSE");
                player.addExperience(attackResult);

                return;
            }
            //Monster turn!
            attackRoll = _enemies[i].attack();
            printf("%s attacked you with a roll of %d\n", enemyName.c_str(), attackRoll);

            attackResult = player.takeDamage(attackRoll);

            if (attackResult != 0)
            {
                setTile(playerX, playerY, 'x');
                print();
                printf("You died!\n");
                system("PAUSE");

                exit(0);
            }
            system("PAUSE");
            return;
        }
    }
}


