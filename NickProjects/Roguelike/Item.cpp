#include "Item.h"

Item::Item(string name, int count, int value, int attack, int defense)
{
	_name = name;
	_value = value;
	_count = count;
}


void Item::addOne()
{
	_count++;
}

void Item::removeOne()
{
	if (_count > 0)
	{
		_count--;
	}
}