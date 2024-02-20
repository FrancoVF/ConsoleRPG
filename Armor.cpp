#include <string>
#include "Armor.h"

dArr<std::string> Armor::names;

void Armor::initNames()
{
	Armor::names.push("Bro saver");
	Armor::names.push("Cotton Rag");
	Armor::names.push("Devlish Defender");
	Armor::names.push("Angel Balls");
	Armor::names.push("Iron sheets");
	Armor::names.push("Assassin BedSheets");
}

Armor::Armor() {}

Armor::Armor(int level, int rarity)
	:Item(level, rarity)
{
	this->defense = rand() % (level * (rarity + 1));
	this->defense += (rarity + 1) * 5;\
	this->type = rand() % 4;
	this->setName(Armor::names[rand() % Armor::names.size()]);

	switch (this->type)
	{
		case armorType::HEAD:
			this->typeStr = "Head";
				break;
		case armorType::CHEST:
			this->typeStr = "Chest";
				break;
		case armorType::ARMS:
			this->typeStr = "Arms";
				break;
		case armorType::LEGS:
			this->typeStr = "legs";
				break;
		default:
			this->typeStr = "ERROR INVALID!";
				break;
	}

	if (rarity == 3)
		this->defense += level * 5;
	else if (rarity == 4)
		this->defense += level * 10;
}

Armor::Armor(int type, int defense, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(name, level, buyValue, sellValue, rarity)
{
	this->type = type;
	this->defense = defense;
}

Armor::~Armor()
{

}

Armor* Armor::clone() const
{
	return new Armor(*this);
}

std::string Armor::toString() const
{
	std::string str = 
	  this->getName()
	+ this->getTypeStr()
	+ std::to_string(this->getLevel())
	+ std::to_string(this->getRarity())
	+ std::to_string(this->defense);
	
	return str;
}
