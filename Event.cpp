#include "Event.h"
#include "dArr.h"
#include <sqlite3.h>
#include <string>

Event::Event()
{
	this->nrOfEvents = 0;
}
Event::~Event() {}

void Event::generateEvent(Character &character, dArr<Enemy> enemies)
{
	int index = rand() % 2 - 1;
	// std::cout << "NR: " << this->nrOfEvents;

	switch (index)
	{
	case 0:
		enemyEncounter(character, enemies);
		break;
	case 1:
		puzzleEncounter(character);
		break;
	default:
		break;
	}
}

void Event::puzzleEncounter(Character &character)
{
	bool completed = false;
	int userAns = 0;
	int chances = 3;
	int gainExp = (chances * character.getLevel() * (rand() % 10 + 1));

	Puzzle puzzle("./1");



	while (!completed && chances > 0)
	{
		std::cout << "Chances: " << chances << "\n\n";
		chances--;
		std::cout << puzzle.getAsString() << "\n";

		std::cout << "\nYour ANSWER: ";
		std::cin >> userAns;
		std::cout << "\n";

		while (std::cin.fail()) {
			std::cout << "Faulty input!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "\nYour ANSWER: ";
			std::cin >> userAns;
		}

		std::cin.ignore(100, '\n');
		std::cout << '\n';

		if (puzzle.getCorrectAns() == userAns)
		{
			completed = true;

			character.gainExp(gainExp);
			character.gainGold(gainExp);

			std::cout << "YOU GAINED " << gainExp << " EXP!"  << std::endl;
			std::cout << "YOU GAINED " << gainExp << " GOLD!" << std::endl;
		}
	}

	if (completed)
	{
		std::cout << "CONGRATZ YOU SUCCEEDED! \n\n";
	}
	else
	{
		std::cout << "YOU FAILED!" << std::endl;
	}
}

void Event::enemyEncounter(Character& character, dArr<Enemy> enemies)
{
	bool playerTurn = false;
	int choice = 0;

	// Coint toss for help
	int coinToss = rand() % 2 - 1;
	std::cout << "Coin Toss: " << rand() % 2 - 1 << std::endl;
	if (coinToss)
		playerTurn = true;
	else
		playerTurn = false;

	// end conditions
	bool escape = false;
	bool playerDefeated = false;
	bool enemiesDefeated = false;

	// Enemies
	int nrOfEnemies = rand() % 3 + 1;

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		enemies.push(Enemy(character.getLevel() + rand() % 3));
	}

    char * err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("game.db", &db);

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		Enemy enemy = enemies[i];
		std::string query_insert = "INSERT INTO enemy (name, level, hp, hpMax, damageMin, damageMax, dropChance, defense, accuracy) VALUES (" + enemy.getName() + ", " + std::to_string(enemy.getLevel()) + ", " 
		+ std::to_string(enemy.getHp()) + ", " + std::to_string(enemy.getHpMax()) + ", " + std::to_string(enemy.getDamageMin()) + ", "\ 
		", " + std::to_string(enemy.getDamageMax()) + ", " + std::to_string(enemy.getDropChance()) + ", " +
		std::to_string(enemy.getDefense()) + ", " + std::to_string(enemy.getAccuracy());

		int rc = sqlite3_exec(db, query_insert.c_str(), NULL, NULL, &err);
		if(rc != SQLITE_OK)
		std::cout << "error: " << err << std::endl;

		std::cout << query_insert << std::endl;
	}

	// Battle variables
	int damage = 0;
	int gainExp = 0;
	int gainGold = 0;
	int playerTotal = 0;
	int enemyTotal = 0;
	int combatTotal = 0;
	int combatRollPlayer = 0;
	int combatRollEnemy = 0;

	// Battle variables
	int attackRoll = 0;
	int defendRoll = 0;



	while (!escape && !playerDefeated && !enemiesDefeated)
	{
		if (playerTurn && !playerDefeated)
		{
			std::cout << "\n0: Escape" << "\n";
			std::cout << "1: Attack" << "\n";
			std::cout << "2: Defend" << "\n";
			std::cout << "3: Use Item" << "\n";

			std::cout << std::endl << "FIRST CHOICE: ";
			std::cin >> choice;

			std::cout << "Player Turn\n\n";

			combatTotal = enemies[choice].getDefense() + character.getAccuracy();
			std::cout << "Combat total: " << combatTotal << std::endl;
			enemyTotal = (enemies[choice].getDefense() / (double)combatTotal) * 100;
			std::cout << "Enemy total: " << enemyTotal << std::endl;
			playerTotal = (character.getAccuracy() / (double)combatTotal) * 100;
			std::cout << "Player total: " << playerTotal << std::endl;
			/*
			std::cout << "Values 0: " << combatTotal << std::endl;
			std::cout << "Values 1: " << playerTotal << std::endl;
			std::cout << "Values 2: " << enemyTotal << std::endl;
			*/
			combatRollPlayer = rand() % (playerTotal + 1) + 1;
			combatRollEnemy = rand() % (enemyTotal + 1) + 1;

			std::cin.get();
			std::cout << "Continue..." << std::endl << std::endl;
			system("clear");

			std::cout << "= BATTLE MENU =\n\n";

			std::cout << "HP: " << character.getHP() << "/" << character.getHPMax();

			while (std::cin.fail() && choice > 3 && choice < 0) {
				std::cout << "Faulty input!" << "\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');

				std::cout << "= BATTLE MENU =\n\n";
				std::cout << "0: Escape" << "\n";
				std::cout << "1: Attack" << "\n";
				std::cout << "2: Defend" << "\n";
				std::cout << "3: Use Item" << "\n";

				std::cout << "\nChoice: ";
				std::cin >> choice;
			}

			switch (choice)
			{
			case 0:
				escape = true;
				break;
			case 1:
				// Select enemy
				std::cout << "Select enemy: " << "\n\n";

				for (size_t i = 0; i <= enemies.size() - 1; i++)
				{
					std::cout << i << ": " <<
						"Level: " << enemies[i].getLevel() <<
						"\nHp: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
						"\nDefense: " << enemies[i].getDefense() <<
						"\nAccuracy: " << enemies[i].getAccuracy() <<
						"\nDamage: " << enemies[i].getDamageMin() << "-" << enemies[i].getDamageMax();
					std::cout << std::endl << std::endl;

				}

				std::cout << "\n";
				std::cout << "\nSelect enemy: " << std::endl;
				// std::cout << "Second Select" << std::endl;
				std::cin >> choice;
				std::cout << "\n";

				while (std::cin.fail() || choice >= enemies.size() || choice < 0) {
					std::cout << "Faulty input!" << "\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');

					std::cout << "Select enemy: " << "\n\n";

					std::cout << "\nChoice: ";
					std::cin >> choice;
				}

				std::cin.ignore(100, '\n');
				std::cout << '\n';

				if (combatRollPlayer > combatRollEnemy) // Hit
				{
					std::cout << "HIT! " << std::endl;
					// std::cout << "Here 1!\n";
					damage = character.getDamage();
					std::cout << "Damage dealt " << damage << std::endl;
					std::cout << "Here 2!\n";
					enemies[choice].takeDamage(damage);
					std::cout << "Here 3!\n";
					if (!enemies[choice].isAlive())
					{
						gainExp = enemies[choice].getExp();
						character.gainExp(gainExp);
						gainGold = rand() % enemies[choice].getLevel() * 10 + 1;
						character.gainGold(gainGold);
						std::cout << "EXP GAINED: " << gainExp << std::endl;
						std::cout << "GOLD GAINED" << gainGold << std::endl;
						int rarity = 0;

						// ITEM ROLL
						int roll = rand() % 50 + 1;
						if(roll > 20) {
							rarity = 0;

							roll = rand() % 100 + 1;
							if (roll > 30)
							{
								rarity = 1; // Uncommon

								roll = rand() % 100 + 1;
								if (roll > 50)
								{
									rarity = 2; // Rare

									roll = rand() % 100 + 1;
									if (roll > 70)
									{
										rarity = 3; // Legendary

										roll = rand() % 100 + 1;
										if (roll > 90)
										{
											rarity = 4; // Mythic
										}
									}
								}
							}
						}

						if (roll >= 0)
						{
							roll = rand() % 100 + 1;

							if (roll > 50)
							{
								Weapon tempW(character.getLevel(), rand() % 5);
								character.addItem(tempW);
								std::cout << "WEAPON DROP!" << std::endl;
							}
							else
							{
								Weapon tempA(character.getLevel(), rand() % 5);
								character.addItem(tempA);
								std::cout << "ARMOR DROP!" << std::endl;
							}
						}
						enemies.remove(choice, true);
					}
					std::cout << "Damage: " << damage << "!" << "\n\n";
				}
				else // Mis
				{
					std::cout << "YOU MISSED AN ATTACK: " << choice << std::endl;
					break;
				}
				break;
			case 2:

				break;
			default:
				break;
			}
			playerTurn = false;
			// std::cin.ignore(100, '\n');
			// std::cout << '\n';
		}
		else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			std::cout << "= Enemy Turn =";
			std::cin.get();
			std::cout << "Continue..." << std::endl << std::endl;
			system("clear");

			for (size_t i = 0; i < enemies.size(); i++)
			{
				std::cout << "Continue..." << std::endl;
				std::cin.get();
				// ATTACK ROLLS
				combatTotal = enemies[i].getAccuracy() + character.getDefense();
				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				playerTotal = character.getDefense() / (double)combatTotal * 100;

				if (playerTotal == 0)
					playerTotal = 1;

				if (enemyTotal == 0)
					playerTotal = 1;

				combatRollPlayer = rand() % (playerTotal) + 1;
				combatRollEnemy = rand() % (enemyTotal) + 1;


				std::cin.get();
				std::cout << "Continue..." << std::endl << std::endl;
				system("clear");

				std::cout << "Enemy: " << i << std::endl << std::endl;

				std::cout << "Player roll: " << combatRollPlayer << "\n";
				std::cout << "Enemy roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer < combatRollEnemy) // Hit
				{
					std::cout << "HIT! " << std::endl;
					damage = enemies[i].getDamage();
					character.takeDamage(damage);

					std::cout << "Damage: " << damage << "!" << "\n\n";

					std::cout << "Character HP/HP Max: " << character.getHP() << " / " << character.getHPMax();
					if (character.getHP() < 0)
						character.setIsAlive(false);

					if (!character.isAlive())
					{
						std::cout << "YOU ARE DEFEATED!\n\n";
						playerDefeated = true;
					}
				}
				else // Mis
				{
					std::cout << "ENEMY MISSED ATTACK: " << choice << std::endl;
				}
			}
			playerTurn = true;
		}

		// Conditions
		if (!character.isAlive())
			playerDefeated = true;
		else if (enemies.size() <= 0)
			enemiesDefeated = true;
	}
}
