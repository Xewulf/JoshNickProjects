#pragma once
#include <iostream>
#include <string>
#include <list>
#include "level.h"
#include "Item.h"

using namespace std;

class Shop
{
public:
    Shop(string name);


    void initShops(list<Shop>& shops);
    void enterShop(Player& player, Shop &shop);


    void printShop();
    bool canAffordItem(string name, int money);
    bool purchaseItem(string name, Item& newItem);
    void addItem(Item newItem);

    bool buyItems();

    //Getters
    string getName() { return _name; }

private:
    string _name;
    list <Item> _items;

};
