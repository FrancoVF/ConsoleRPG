#include <iostream>
#include <string.h>
#include <string>
#include <sqlite3.h>
#include "Enemy.h"
#include "dArr.h"
#include "Character.h"

int main()
{
    int nrOfEnemies = rand() % 3 + 1;
    dArr<Enemy> enemies;
    char * err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("game.db", &db);

    sqlite3_step(stmt);
    sqlite3_prepare_v2(db, "SELECT * FROM character", -1, &stmt, NULL);
    
    const char * name = (const char *) sqlite3_column_text(stmt, 1);
    std::string name2;
    for(int index = 0; index < strlen((const char*) sqlite3_column_text(stmt, 1)); index++) {
        name2 += name[index];
    }

    int distanceTraveled = sqlite3_column_int(stmt, 2);
    int gold = sqlite3_column_int(stmt, 3);
    int level = sqlite3_column_int(stmt, 4);
    int exp = sqlite3_column_int(stmt, 5);
    int expNext = sqlite3_column_int(stmt, 6);
    int strength = sqlite3_column_int(stmt, 7);
    int vitality = sqlite3_column_int(stmt, 8);
    int dexterity = sqlite3_column_int(stmt, 9);
    int intelligence = sqlite3_column_int(stmt, 10);
    int hp = sqlite3_column_int(stmt, 11);
    int hpMax = sqlite3_column_int(stmt, 12);
    int stamina = sqlite3_column_int(stmt, 13);
    int damageMin = sqlite3_column_int(stmt, 14);
    int damageMax = sqlite3_column_int(stmt, 15);
    int accuracy = sqlite3_column_int(stmt, 16);
    int defense = sqlite3_column_int(stmt, 17);
    int luck = sqlite3_column_int(stmt, 18);
    int statPoints = sqlite3_column_int(stmt, 19);
    
    std::cout << "[name][" << name << "]"  << std::endl;
    std::cout << "[distanceTraveled][" << distanceTraveled << "]"  << std::endl;
    std::cout << "[gold]" << gold << "]" << std::endl;
    std::cout << "[level][" << level << "]" << std::endl;
    std::cout << "[exp][" << exp << "]" << std::endl;
    std::cout << "[expNext][" << expNext << "]" << std::endl;
    std::cout << "[strength][" << strength << "]" << std::endl;
    std::cout << "[vitality][" << vitality << "]" << std::endl;
    std::cout << "[dexterity][" << dexterity << "]" << std::endl;
    std::cout << "[intelligence][" << intelligence << "]";
    std::cout << "[hp][" << hp << "]" << std::endl;
    std::cout << "[hpMax][" << hpMax << "]" << std::endl;
    std::cout << "[stamina][" << stamina << "]" << std::endl;
    std::cout << "[damageMin][" << damageMin << "]" << std::endl;
    std::cout << "[damageMax][" << damageMax << "]" << std::endl;
    std::cout << "[defense][" << defense << "]" << std::endl;
    std::cout << "[luck][" << luck << "]" << std::endl;
    std::cout << "[statPoints][" << statPoints << "]" << std::endl << std::endl;

    

    Character character(name2, distanceTraveled, gold, level, exp, expNext, strength,
		vitality, dexterity, intelligence, hp, hpMax, stamina, damageMin, damageMax, 
		accuracy, defense, luck, statPoints);

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		enemies.push(Enemy(character.getLevel() + rand() % 3));
	}

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		Enemy enemy = enemies[i];
		std::string query_insert = "INSERT INTO enemy (name, level, hp, hpMax, damageMin, damageMax, dropChance, defense, accuracy) VALUES (" + 
        enemy.getName() + ", " + std::to_string(enemy.getLevel()) + ", " 
		+ std::to_string(enemy.getHp()) + ", " + std::to_string(enemy.getHpMax()) + ", " + std::to_string(enemy.getDamageMin()) + \
		", " + std::to_string(enemy.getDamageMax()) + ", " + std::to_string(enemy.getDropChance()) + ", " +
		std::to_string(enemy.getDefense()) + ", " + std::to_string(enemy.getAccuracy());

		int rc = sqlite3_exec(db, query_insert.c_str(), NULL, NULL, &err);
		if(rc != SQLITE_OK)
		std::cout << "error: " << err << std::endl;

		std::cout << query_insert << std::endl;
	}
    
    return EXIT_SUCCESS;
}