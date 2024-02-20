#pragma once
#include "Item.h"

class Weapon:
	public Item
{
private:
	int damageMin;
	int damageMax;
public:
	Weapon();
	Weapon(int level, int rarity);
	Weapon(int damageMin, int damageMax,
		std::string name, int level,
		int buyValue, int sellValue, int rarity);
	virtual ~Weapon();

	
	// Accessors
	inline const int& getDamageMin() const { return this->damageMin; }
	inline const int& getDamageMax() const { return this->damageMax; }

	// Pure virtual
	virtual Weapon* clone() const;

	// Functions
	std::string toString() const;

	// Static
	static dArr<std::string> names;
	static void initNames();
};

