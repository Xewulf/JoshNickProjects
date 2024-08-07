#include "Shop.h"
#include "Item.h"
#include <iostream>
#include <string>

Shop::Shop(string name)
{
	_name = name;
}


void Shop::initShops(list<Shop> &shops)
{
	shops.push_back(Shop("The Blacksmith"));
	shops.back().addItem(Item("Dagger", 50, 1, 2, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Short Sword", 1, 150, 4, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Long Sword", 400, 1, 10, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Knight Sword", 1000, 1, 25, 0));//(Name, Value, Atk, Def)

	shops.push_back(Shop("The Armory"));
	shops.back().addItem(Item("Leather Armor", 50, 1, 0, 2));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Copper Armor", 150, 1, 0, 4));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Iron Armor", 400, 0, 1, 10));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Knight Armor", 1000, 1, 0, 25));//(Name, Value, Atk, Def)


	shops.push_back(Shop("The Forge of the Gods"));
	shops.back().addItem(Item("Divine Short Sword", 5000, 1, 125, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Divine Long Sword", 15000, 1, 400, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Divine Knight Sword", 40000, 1, 800, 0));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Excalibur", 100000, 1, 2000, 0));//(Name, Value, Atk, Def)

	shops.push_back(Shop("The Divine Reliquary"));
	shops.back().addItem(Item("Cobalt Armor", 5000, 1, 0, 125));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Mythril Armor", 15000, 1, 0, 400));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Adamantite Armor", 40000, 1, 0, 800));//(Name, Value, Atk, Def)
	shops.back().addItem(Item("Divine Knight Armor", 100000, 1, 0, 2000));//(Name, Value, Atk, Def)

}

void Shop::enterShop(Player &player, Shop &shop)
{
	bool isDone = false;
	char input;
	string itemName;
	Item newItem("NO ITEM", 0, 1);

	while (isDone == false) {
		shop.printShop();
		player.printInventory();

		cout << "Enter the item you wish to buy: ";
		getline(cin, itemName);

		if (shop.canAffordItem(itemName, player.getGold()))
		{

			if (shop.purchaseItem(itemName, newItem) == true)
			{
				player.addGold(-newItem.getValue());
				player.addItem(newItem);
			}
			else
			{
				cout << "That is an invalid item!\n";
				system("PAUSE");
			}
		}
		else
		{
			cout << "You don't have enough money!\n";
			system("PAUSE");
		}


	}
}

void Shop::printShop()
{

	std::cout << "*** Welcome to the item shop! ***\n";
	list<Item>::iterator lit;

	int i = 0;

	for (lit = _items.begin(); lit != _items.end(); lit++)
	{
		cout << i << ". " << (*lit).getName() << endl;
		i++;
	}
	cout << "*********************************\n\n";
}

bool Shop::canAffordItem(string name, int money)
{
	list<Item>::iterator lit;

	for (lit = _items.begin(); lit != _items.end(); lit++) {
		if ((*lit).getName() == name) {
			if ((*lit).getValue() <= money) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool Shop::purchaseItem(string name, Item &newItem)
{
	list<Item>::iterator lit;
	for (lit = _items.begin(); lit != _items.end(); lit++)
	{
		if ((*lit).getName() == name)
		{
			newItem = (*lit);
			newItem.setCount(1);
			(*lit).removeOne();

			if ((*lit).getCount() == 0)
			{
				_items.erase(lit);
			}
			return true;
		}
	}
	return false;
}

void Shop::addItem(Item newItem)
{
	list<Item>::iterator lit;
	for (lit = _items.begin(); lit != _items.end(); lit++)
	{
		if ((*lit).getName() == newItem.getName())
		{
			(*lit).addOne();
			return;
		}
	}

	_items.push_back(newItem);
}


bool Shop::buyItems()
{
	int input;
	cout << "\n\n\n\nWhat would you like to buy? Enter (" << 1 << "-" << 6 << ")\nEnter -1 to leave the shop.\n\n";
	cin >> input;

	if (input == -1)
	{
		return false; //Leave shop
	}

	if (input < 0 || input > 6)
	{
		cout << "That was a bad input!\n";
		return true; // Keep shopping
	}

	//playerInventory[input - 1]++;

	return true; //Keep shopping


}