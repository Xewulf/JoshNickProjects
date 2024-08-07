#pragma once
#include <string>
#include <list>
#include "Item.h"

class Player
{
public:
    Player();
    void init(int level, int health, int attack, int defense, int experience);

    int attack();
    int takeDamage(int attack);

    bool canAffordItem(string name, int money);

    void removeItem(string name);
    void addItem(Item newItem);


    //Setters
    void setPosition(int x, int y);
    void printstats();
    void printInventory();
    void addExperience(int experience);
    void addGold(int gold) { _gold += gold; }

    //Getters
    void getPosition(int& x, int& y);
    int getGold() { return _gold; }
    void subtractGold(int amount) { _gold -= amount; }

private:
    //Properties
    int _level;
    int _health;
    int _maxhealth;
    int _attack;
    int _defense;
    int _experience;
    int _experiencecap = 50;

    //Items + money
    string _name;
    list<Item> _items;
    int _gold;

    //Position
    int _x;
    int _y;

};