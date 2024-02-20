#ifndef ARMOR_H
#define ARMOR_H
#include "Item.h"
#include "dArr.h"

enum armorType {HEAD = 0, CHEST, ARMS, LEGS};

class Armor:
	public Item
{
private:
	int type;
	int defense;
	std::string name;
	int level;
	int buyValue;
	int sellValue;
	int rarity;
	std::string typeStr;
public:
	Armor();
	Armor(int level, int rarity);
	Armor(int type, int defense, std::string name, int level, int buyValue,
		int sellValue, int rarity);
	virtual ~Armor();
	// pure virtual
	virtual Armor* clone() const;

	//functions
	std::string toString() const;

	inline int getDefense() const { return this->defense; }
	inline int getType() const { return this->type; }
	inline int getRarity() const { return rarity; }
	std::string getTypeStr() const { return typeStr; }

	// Static
	static dArr<std::string> names;
	static void initNames();
};
#endif
