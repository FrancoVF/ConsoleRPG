#include "Item.h"

Item::Item()
{
	this->name = "Empty";
	this->level = 0;
	this->buyValue = 0;
	this->sellValue = 0;
	this->rarity = -1;
}

Item::Item(int level, int rarity)
{
	this->name = "Random";
	this->level = rand() % (level + 2) + 1;
	this->rarity =  rand() % 5;
	this->buyValue = level * this->rarity * 10;
	this->sellValue = this->buyValue / 2;
	this->rarity = rarity;
}

Item::Item(const Item& item) 
{
	this->name = item.name;
	this->buyValue = item.buyValue;
	this->sellValue = item.sellValue;
}

Item::Item(std::string name, int level, int buyValue, int sellValue, int rarity) 
{
	this->name = name;
	this->level = level;
	this->buyValue = buyValue;
	this->sellValue = sellValue;
	this->rarity = rarity;
}

Item::~Item() {}
