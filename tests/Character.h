#pragma once
#include "Inventory.h"
#include "STLINCLUDE.h"
#include <string>
#include "Armor.h"
#include "Weapon.h"

class Character
{
public:
	Character();
	Character(std::string name, int distanceTraveled, int gold, int level, int exp, int expNext, int strength,
		int vitality, int dexterity, int intelligence, int hp, int hpMax, int stamina, int damageMin, int damageMax, 
		int accuracy, int defense, int luck, int statPoints);

	// virtual ~Character();
	// functions
	void initialize(std::string name);
	void printStats() const;
	void levelUp();
	std::string getAsString() const;
	std::string getInvAsString();
	void updateStats();
	void addToStats(int stat, int value);
	inline void resetHP() { this->hp = this->hpMax; }
	void setIsAlive(bool alive) { this->alive = alive; }
	void addItem(const Item &item) { this->inv.addItem(item); }
	void equipItem(unsigned index);

	// Accessors
	inline std::string getName() const { return this->name; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline const int& getHP() const { return this->hp; }
	inline const bool isAlive() const { return this->alive; }
	inline const int& getHPMax() const { return this->hpMax; }
	inline const int getDamage() const { return this->damageMin + this->damageMax; }
	inline const int& getStamina() const { return this->stamina; }
	inline const int& getDamageMin() const { return this->damageMin; }
	inline const int& getDamageMax() const { return this->damageMax; }
	inline const int& getDefense() const { return this->defense; }
	inline const int& getAccuracy() const { return this->accuracy; }
	inline const int getGold() { return this->gold; }

	inline void setDistTravelled(const int& distance) { this->distanceTraveled = distance;  }
	inline void travel() { this->distanceTraveled++;  }
	inline void gainExp(const int& exp) { this->exp += exp; }
	inline void gainGold(const int gold) { this->gold += gold; }
	void takeDamage(int damage) { this->hp -= damage; };
	inline void payGold(const int gold) { this->gold -= gold; }
	inline int getInventorySize() { return this->inv.size(); }
	inline const int getAddedDefense() const;

private:
	std::string name;
	int distanceTraveled;
	int gold;
	int level;
	int exp;
	int expNext;
	int strength;
	int vitality;
	int dexterity;
	int intelligence;
	int hp;
	int hpMax;
	int stamina;
	int damageMin;
	int damageMax;
	int accuracy;
	int defense;
	int luck;
	int statPoints;
	int alive;
	
	Inventory inv;
	Weapon weapon;
	Armor armor;
	Armor armor_head;
	Armor armor_chest;
	Armor armor_arms;
	Armor armor_legs;
};

