#include "Character.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

Character::Character()
{
	this->name = "NONE";
	this->distanceTraveled = 0;
	this->gold = 0;
	this->level = 0;
	this->exp = 0;
	this->expNext = static_cast<int> ((50 / 3) * (pow(this->level, 3) -
					6 * pow(this->level, 3) +
					(17 * this->level) - 11) + 100);

	this->strength = 1;
	this->vitality = 0;
	this->dexterity = 0;
	this->intelligence = 0;

	this->hp = 0;
	this->hpMax = 0;
	this->stamina = 0;
	this->damageMin = 0;
	this->damageMax = 0;
	this->defense = 0;
	this->luck = 0;

	this->statPoints = 0;
}

Character::Character(std::string name, int distanceTraveled, int gold, int level, int exp, int expNext, int strength,
		int vitality, int dexterity, int intelligence, int hp, int hpMax, int stamina, int damageMin, int damageMax, 
		int accuracy, int defense, int luck, int statPoints)
{
	this->name = name;
	this->distanceTraveled = distanceTraveled;
	this->gold = gold;
	this->level = level;
	this->exp = exp;
	this->expNext = static_cast<int> ((50 / 3) * (pow(this->level, 3) -
		6 * pow(this->level, 3) +
		(17 * this->level) - 11) + 100);

	this->strength = strength;
	this->vitality = vitality;
	this->dexterity = dexterity;
	this->intelligence = intelligence;

	this->hp = hp;
	this->hpMax = hpMax;
	this->stamina = stamina;
	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->defense = defense;
	this->luck = luck;

	this->statPoints = statPoints;
}

void Character::initialize(std::string name)
{
	this->name = name;
	this->distanceTraveled = 0;
	this->gold = 0;
	this->level = 1;
	this->exp = 0;

	this->strength = 50;
	this->vitality = 5;
	this->dexterity = 5;
	this->intelligence = 5;

	this->statPoints = 0;

	this->updateStats();

	this->hp = this->getHPMax();

	this->inv.addItem(Weapon(1, rand() % 5));
	this->inv.addItem(Weapon(1, rand() % 5));
	this->inv.addItem(Weapon(1, rand() % 5));
	this->inv.addItem(Weapon(1, rand() % 5));
	this->inv.addItem(Weapon(1, rand() % 5));
}

void Character::printStats() const
{
	std::cout << "Character sheets" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Level: " << this->level << std::endl;
	std::cout << "Exp: " << this->exp << std::endl;
	std::cout << "ExpNext: " << this->expNext << std::endl;
	std::cout << "Exp to next level: " << this->expNext << std::endl;
	std::cout << "Stat Points: " << this->statPoints << std::endl;
	std::cout << "strength: " << this->strength << std::endl;
	std::cout << "Vitality: " << this->vitality << std::endl;
	std::cout << "Dexterity: " << this->dexterity << std::endl;
	std::cout << "Intelligence: " << this->intelligence << std::endl;
	std::cout << "HP: " << this->hp << std::endl;
	std::cout << "HP Max: " << this->hpMax << std::endl;
	std::cout << "Stamina: " << this->stamina << std::endl;
	std::cout << "Damage Min: " << this->damageMin << "( +" << this->weapon.getDamageMin() << " )" << std::endl;
	std::cout << "Damage Max: " << this->damageMax << "( +" << this->weapon.getDamageMax() << " )" << std::endl;
	std::cout << "Defense" << this->defense << "\n" << "( +" << std::to_string(this->getAddedDefense()) << " )" << std::endl;
	std::cout << "Stats Points: " << this->statPoints << std::endl;
	std::cout << "Luck: " << this->luck << std::endl;
	std::cout << std::endl;
	std::cout << "Distance Travelled: " << this->distanceTraveled << std::endl;
	std::cout << "Gold: " << this->gold << std::endl;
	std::cout << "Weapon: " << this->weapon.getName() <<
		" L: " << this->weapon.getLevel() << " D: " <<
		this->weapon.getDamageMin() << " - " << this->weapon.getDamageMax() << std::endl << std::endl;

	std::cout << "ARMOR CHEST NAME:" << this->armor_chest.getName() << std::endl;
	std::cout << "Defense: " << this->armor_chest.getDefense() << std::endl;
	std::cout << "Type: " << this->armor_chest.getType() << std::endl << std::endl;

	std::cout << "ARMOR LEGS NAME:" << this->armor_legs.getName() << std::endl;
	std::cout << "Defense: " << this->armor_legs.getDefense() << std::endl;
	std::cout << "Type: " << this->armor_legs.getType() << std::endl << std::endl;

	std::cout << "ARMOR HEAD NAME:" << this->armor_head.getName() << std::endl;
	std::cout << "Defense: " << this->armor_head.getDefense() << std::endl;
	std::cout << "Type: " << this->armor_head.getType() << std::endl << std::endl;

	std::cout << "ARMOR ARMS NAME:" << this->armor_arms.getName() << std::endl;
	std::cout << "Defense: " << this->armor_arms.getDefense() << std::endl;
	std::cout << "Type: " << this->armor_arms.getType() << std::endl << std::endl;
}

void Character::levelUp()
{
	if (this->exp >= this->expNext)
	{
		this->exp -= this->expNext;
		this->level++;

		this->statPoints++;

		this->updateStats();

		std::cout << "YOU ARE NOW LEVEL " << this->level << "!" << std::endl << std::endl;
	}
	else
	{
		std::cout << "NOT ENOUGH EXP!" << std::endl << std::endl;
	}
}

std::string Character::getAsString() const
{
	return this->name + ' '
		+ std::to_string(this->distanceTraveled) + ' '
		+ std::to_string(this->gold) + ' '
		+ inv.toString() + ' '
		+ weapon.toString() + ' '
		+ armor.toString() + ' '
		+ armor_head.toString() + ' '
		+ armor_chest.toString() + ' '
		+ armor_arms.toString() + ' '
		+ armor_legs.toString() + ' '
		+ std::to_string(this->level) + ' '
		+ std::to_string(this->exp) + ' '
		+ std::to_string(this->expNext) + ' '
		+ std::to_string(this->strength) + ' '
		+ std::to_string(this->vitality) + ' '
		+ std::to_string(this->dexterity) + ' '
		+ std::to_string(this->intelligence) + ' '
		+ std::to_string(this->hp) + ' '
		+ std::to_string(this->hpMax) + ' '
		+ std::to_string(this->stamina) + ' '
		+ std::to_string(this->damageMin) + ' '
		+ std::to_string(this->damageMax) + ' '
		+ std::to_string(this->accuracy) + ' '
		+ std::to_string(this->defense) + ' '
		+ std::to_string(this->luck) + ' '
		+ std::to_string(this->statPoints);
}

std::string Character::getInvAsString()
{
	std::string inv;
	for (size_t i = 0; i < this->inv.size(); i++)
	{
		inv += std::to_string(i) + ": " + this->inv[i].toString() + "\n";
	}

	if (inv.size() > 0)
		return inv;

	return "NO ITEMS!\n";
}

void Character::addToStats(int stat, int value)
{
	if (this->statPoints < value)
		std::cout << "ERROR! NOT ENOUGH STATPOINTS!" << "\n";
	else
	{
		switch (stat) {
		case 0:
			this->strength += value;
			std::cout << "STRENGTH INCREASED!" << "\n";
			break;
		case 1:
			this->vitality += value;
			std::cout << "VITALITY INCREASED!" << "\n";
			break;
		case 2:
			this->dexterity += value;
			std::cout << "DEXTERITY INCREASED!" << "\n";
		case 3:
			this->intelligence += value;
			std::cout << "INTELLIGENCE INCREASED!" << "\n";
			break;
		default:
			std::cout << "NO SUCH STAT!" << "\n";
		}
		this->statPoints -= value;

		this->updateStats();
	}
}

void Character::updateStats()
{
	this->expNext = static_cast<int> (
		(50 / 3) * ((pow(this->level, 3)
		- 6 * pow(this->level, 2))
		+ 17 * this->level - 12)) + 100;

	this->hpMax = (this->vitality * 2) * (this->strength / 2) + this->level * 5;
	this->damageMin = this->strength;
	this->damageMax = this->strength * 2;
	this->defense = this->dexterity * (this->intelligence / 2);
	this->accuracy = (this->dexterity / 2) + this->intelligence;
	this->luck = this->intelligence;
}

void Character::equipItem(unsigned index)
{
	if (index < 0 || index > this->inv.size())
	{
		std::cout << "NO VALID ITEM" << std::endl;
	}
	else {
		Weapon *w = nullptr;
		w = dynamic_cast<Weapon*>(&this->inv[index]);

		Armor *a = nullptr;
		a = dynamic_cast<Armor*>(&this->inv[index]);

		if (w != nullptr)
		{
			if (this->inv[index].getRarity() >= 0)
				this->inv.addItem(this->weapon);

			this->weapon = *w;
			this->inv.removeItem(index);
		}
		else if (a != nullptr)
		{
			switch(a->getType())
			{
				case armorType::HEAD:
					if (this->armor_head.getRarity() >= 0)
						this->inv.addItem(this->armor_head);
					this->armor_head = *a;
					this->inv.removeItem(index);
					break;
				case armorType::CHEST:
					if (this->armor_chest.getRarity() >= 0)
						this->inv.addItem(this->armor_chest);
					this->armor_head = *a;
					this->inv.removeItem(index);
					break;
				case armorType::ARMS:
					if (this->armor_arms.getRarity() >= 0)
						this->inv.addItem(this->armor_arms);
					this->armor_head = *a;
					this->inv.removeItem(index);
					break;
				case armorType::LEGS:
					if (this->armor_legs.getRarity() >= 0)
						this->inv.addItem(this->armor_legs);
					this->armor_head = *a;
					this->inv.removeItem(index);
					break;
				default:
					std::cout << "ERROR ARMOR TYPE INVALID!" << std::endl;
					break;
			}
		}
		else
		{
			std::cout << "NO ITEM!" << std::endl;
		}
	}
}

const int  Character::getAddedDefense() const
{
	return this->defense + this->armor_arms.getDefense()
		+ this->armor_chest.getDefense() + this->armor_head.getDefense()
		+ this->armor_legs.getDefense();

}

