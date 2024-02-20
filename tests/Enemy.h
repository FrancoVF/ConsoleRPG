#pragma once
#include <string>
#include <stdlib.h>

class Enemy
{
private:
	std::string name;
	int level;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	float dropChance;
	int defense;
	int accuracy;
public:
	Enemy(int level = 0);
	virtual ~Enemy();

	inline bool isAlive() const { return this->hp > 0; }
	std::string getAsString() const;
	inline void takeDamage(int damage) { this->hp -= damage;  }

	inline std::string getName() const { return this->name; };
	inline int getLevel() const { return this->level; }
	inline int getHp() const { return this->hp; }
	inline int getHpMax() const { return hpMax; }
	inline int getDamage() const { return rand() % this->damageMin + this->damageMax; }
	inline int getDamageMin() const { return this->damageMin; }
	inline int getDamageMax() const { return this->damageMax; }
	inline int getExp() const { return this->level * 100; }
	inline int getDropChance() const { return this->dropChance; }
	inline int getDefense() const { return this->defense; }
	inline int getAccuracy() const { return this->accuracy; }
};

