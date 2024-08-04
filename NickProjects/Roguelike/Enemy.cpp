#include "Enemy.h"

#include <random>
#include <ctime>

Enemy::Enemy(std::string name, char tile, int level, int attack, int defense, int health, int xp)
{
    _name = name;
    _tile = tile;
    _level = level;
    _attack = attack;
    _defense = defense;
    _health = health;
    _experienceValue = xp;
}

//Sets the position of the enemy
void Enemy::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

//Gets the position of the enemy using reference variables
void Enemy::getPosition(int& x, int& y) {
    x = _x;
    y = _y;
}

int Enemy::attack()
{
    static std::default_random_engine randomEngine(time(NULL));
    std::uniform_int_distribution<int> attackRoll(0, _attack);

    return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack)
{
    attack -= _defense;
    //check if the attack does damage
    if (attack > 0)
    {
        _health -= attack;
        //check if he died
        if (_health <= 0)
        {
            return _experienceValue;
        }

    }
    return 0;
}



