#include "Player.h"
#include <random>
#include <ctime>
#include <iostream>

//Constructor, just initializes position to zero
Player::Player() {
    _x = 0;
    _y = 0;
}

//Initializes the player with properties
void Player::init(int level, int health, int attack, int defense, int experience) {
    _level = level;
    _maxhealth = health;
    _health = health;
    _attack = attack;
    _defense = defense;
    _experience = experience;
}

int Player::attack()
{
    static std::default_random_engine randomEngine(time(NULL));
    std::uniform_int_distribution<int> attackRoll(0, _attack);

    return attackRoll(randomEngine);
}

//Sets the position of the player
void Player::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

void Player::printstats()
{
    int attack = _attack;
    int defense = _defense;
    int health = _health;
    int maxhealth = _maxhealth;
    int level = _level;
    int experience = _experience;
    int maxexperience = _experiencecap;

    std::cout << "You are level " << level << "\n";
    std::cout << "Atk: " << attack << "   Def: " << defense << "   Hp: " << health << " / " << maxhealth << "\n";
    std::cout << "Exp: " << experience << " / " << maxexperience << "\n";

}

void Player::addExperience(int experience)
{
    _experience += experience;

    //Level Up!
    while (_experience > _experiencecap)
    {
        printf("Leveled up!\n");
        _experience -= _experiencecap;
        _attack += 1;
        _defense += 1;
        _maxhealth += 10;
        _health += 10;
        _level++;
        _experiencecap *= 1.2;
        system("PAUSE");
    }

}

//Gets the position of the player using reference variables
void Player::getPosition(int& x, int& y) {
    x = _x;
    y = _y;
}


int Player::takeDamage(int attack)
{
    attack -= _defense;
    //check if the attack does damage
    if (attack > 0)
    {
        _health -= attack;
        //check if he died
        if (_health <= 0)
        {
            return 1;
        }

    }
    return 0;
}

