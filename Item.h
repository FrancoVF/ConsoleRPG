#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include "dArr.h"

class Item
{
private:
	std::string name;
	int buyValue;
	int sellValue;
	int level;
	int rarity;
	unsigned int id;
public:
	Item();
	Item(int level);
	Item(int level, int rarity);
	Item(std::string name, int level, int buyValue, int sellValue, int rarity);
	Item(const Item& item);
	
	
	virtual ~Item();
	
	std::string getName() { return name; }
	inline std::string debugPrint() const { return this->name; }

	virtual Item* clone() const = 0;
	virtual std::string toString() const = 0;

	inline const std::string& getName() const { return this->name; }
	inline const int& getBuyValue() const { return this->buyValue; }
	inline const int& getSellValue() const { return this->sellValue; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getRarity() const { return this->rarity; }

	inline void setName(std::string name) { this->name = name; }

	static void initNames();
};

enum rarity {
	COMMON = 0,
	UNCOMMON,
	RARE,
	LEGENDARY,
	MYTHIC
};
#endif
