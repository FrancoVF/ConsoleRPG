#include <iostream>
#include <fstream>
#include <sstream>
#include "Enemy.h"
#include "Event.h"
#include "Puzzle.h"
#include "Game.h"
#include <sqlite3.h>
#include <string>
#include <string.h>

Game::Game()
{
	this->choice = 0;
	this->playing = true;
	this->activeCharacter = 0;
	this->fileName = "characters.txt";
}

Game::~Game()
{

}

void Game::mainMenuDisplay() const
{
	std::cout << "MAIN MENU" << std::endl << std::endl;

	std::cout << "[0] Quit" << std::endl;
	std::cout << "[1] Travel" << std::endl;
	std::cout << "[2] Shop" << std::endl;
	std::cout << "[3] Level Up" << std::endl;
	std::cout << "[4] Rest" << std::endl;
	std::cout << "[5] Character Sheet" << std::endl;
	std::cout << "[6] Character Inventory" << std::endl;
	std::cout << "[7] Create New Character" << std::endl;
	std::cout << "[8] Save Characters" << std::endl;
	std::cout << "[9] Load Characters" << std::endl;
	std::cout << "[10] Select Character" << std::endl;
	std::cout << std::endl;
}

void Game::mainMenuInput()
{
	std::cout << std::endl << "Choice: ";
	std::cin >> choice;

	while (std::cin.fail()) {
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "\nChoice: ";
		std::cin >> choice;
	}

	std::cin.ignore(100, '\n');
	std::cout << '\n';
}

std::string Game::activeCharacterName() const
{
	return this->characters[activeCharacter].getName();
}

void Game::characterLevelUp() const
{
	if (this->characters[activeCharacter].getExp() >=
		this->characters[activeCharacter].getExpNext())
	{
		std::cout << this->characters[activeCharacter].getExpNext();
		std::cout << "%" << "LEVEL UP AVAILABLE! \n\n";
	}
}

void Game::mainMenuChoice()
{
	if (characters[activeCharacter].isAlive())
	{
		characterLevelUp();
		switch (this->choice)
		{
		case 0:
			playing = false;
			this->saveCharacters();
			break;
		case 1:
			this->travel();
			break;
		case 3:
			this->levelUpCharacter();
			break;
		case 4:
			this->rest();
			break;
		case 5:
			this->characterMenu();
			break;
		case 6:
			std::cout << this->characters[this->activeCharacter].getInvAsString();
			break;
		case 7:
			std::cin.ignore();
			this->createNewCharacter();
			this->saveCharacters();
			break;
		case 8:
			this->saveCharacters();
			break;
		case 9:
			this->loadCharacters();
			break;
		case 10:
			this->selectCharacter();
			break;
		default:
			break;
		}
	}
	else {
		std::cout << "YOU ARE DEAD! LOAD?" << std::endl;
		std::cout << "(0) YES/ (1) NO" << std::endl;
		std::cin >> choice;

		while (std::cin.fail() || this->choice < 0 || this->choice > 1) {
			std::cout << "Faulty input!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "(0) YES/ (1) NO" << std::endl;
			std::cin >> choice;
		}

		if (choice == 0)
			this->loadCharacters();
		else
			this->playing = false;

		std::cin.ignore(100, '\n');
		std::cout << '\n';
	}
}

void Game::characterMenu()
{
	do {
		system("clear");

		std::cout << "= CHARACTER MENU =" << std::endl << std::endl;

		characters[activeCharacter].printStats();

		std::cout << "= MENU =" << std::endl;
		std::cout << "1: Back" << std::endl;
		std::cout << "2: Print Inventory" << std::endl;
		std::cout << "3: Equip Item" << std::endl;

		std::cout << std::endl;

		std::cout << "Choice: ";
		std::cin >> this->choice;

		while (std::cin.fail() || this->choice < 0 || this->choice > 2) {
			std::cout << "Faulty input!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "= MENU =" << std::endl;
			std::cout << "1: Back" << std::endl;
			std::cout << "2: Print Inventory" << std::endl;
			std::cout << "3: Equip Item" << std::endl;
			std::cout << std::endl;
			std::cout << "\nChoice: ";
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << '\n';

		switch(this->choice)
		{
			case 1:
				std::cout << this->characters[this->activeCharacter].getInvAsString();
				break;
			case 2:
				std::cout << this->characters[this->activeCharacter].getInvAsString();
				std::cout << "Item Index: ";
				std::cin >> this->choice;

				while (std::cin.fail() || this->choice < 0 || this->choice > this->characters[this->activeCharacter].getInventorySize()) {
					std::cout << "Faulty input!" << "\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');

					std::cout << "Item Index: " << std::endl;
					std::cin >> this->choice;
				}


				this->characters[this->activeCharacter].equipItem(this->choice);
				break;
			default:
				break;
		}

		std::cout << "ENTER to continue..." << std::endl;
		std::cin.get();

		if (this->choice > 0)
		{
			std::cout << "ENTER to continue..." << std::endl;
			std::cin.get();
		}
	} while (this->choice > 0);

}

void Game::stopper()
{
	std::cout << "ENTER to continue..." << std::endl;
	std::cin.get();
	system("clear");
}

void Game::mainMenu()
{
	stopper();
	activeCharacterName();
	mainMenuDisplay();
	mainMenuInput();
	mainMenuChoice();
}

void Game::initGame()
{
	Weapon::initNames();
	Armor::initNames();

	// std::cout << "Load Characters. Yes [1]/ No [0]?" << std::endl;
	// std::cin >> this->choice;
	// while (choice != 0 || choice != 1) {
	// 	std::cout << "Faulty input!" << "\n";
	// 	std::cin.clear();
	// 	std::cin.ignore(100, '\n');

	// 	std::cout << "Load?" << std::endl;
	// 	std::cin >> this->choice;
	// }


	if (true)
		this->loadCharacters();
	else {
		this->createNewCharacter();
		this->saveCharacters();
	}

	// Weapon w1(1, rand() % 5);
	// Weapon w2(1, rand() % 5);
	// Weapon w3(1, rand() % 5);


	// std::cout <<  w1.getName() << " " << w1.getDamageMax() << std::endl;
	// std::cout <<  w2.getName() << " " << w2.getDamageMax() << std::endl;
	// std::cout <<  w3.getName() << " " << w3.getDamageMax() << std::endl;
}

void Game::endGame() {}

void Game::saveCharacters()
{
	std::ofstream outFile(fileName);

	if (outFile.is_open())
	{
		for (size_t i = 0; i < characters.size(); i++)
		{
			outFile << characters[i].getAsString() << "\n";
		}
	}

	outFile.close();
}

void Game::loadCharacters()
{
	
	char * err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("game.db", &db);

    std::string create_table;
    create_table.append("CREATE TABLE IF NOT EXISTS character (");
    create_table.append("id INTEGER PRIMARY KEY AUTOINCREMENT,");
    create_table.append("name TEXT,");
    create_table.append("distanceTraveled INTEGER,");
    create_table.append("gold INTEGER,");
    create_table.append("level INTEGER,");                     
    create_table.append("exp INTEGER,");
    create_table.append("expNext INTEGER,");
    create_table.append("strength INTEGER,");
    create_table.append("vitality INTEGER,");
    create_table.append("dexterity INTEGER,");
    create_table.append("intelligence INTEGER,");
    create_table.append("hp INTEGER,");
    create_table.append("hpMax INTEGER,");
    create_table.append("stamina INTEGER,");
    create_table.append("damageMin INTEGER,");
    create_table.append("damageMax INTEGER,");
    create_table.append("accuracy INTEGER,");
    create_table.append("defense INTEGER,");
    create_table.append("luck INTEGER,");
    create_table.append("statPoints INTEGER");
    create_table.append(");");        

    int rc = sqlite3_exec(db, create_table.c_str(), NULL, NULL, &err);
    if(rc != SQLITE_OK)
      std::cout << "error: " << err << std::endl;

	this->characters.clear();
	sqlite3_prepare_v2(db, "SELECT * FROM character", -1, &stmt, NULL);

	// for(int i = 0; i < 10; i++) {
    //     std::string insert_into;
    //     insert_into.append("INSERT INTO character (");
    //     insert_into.append("name, ");
    //     insert_into.append("distanceTraveled, ");
    //     insert_into.append("gold, ");
    //     insert_into.append("level, ");
    //     insert_into.append("exp, ");
    //     insert_into.append("expNext, ");
    //     insert_into.append("strength, ");
    //     insert_into.append("vitality, ");
    //     insert_into.append("dexterity, ");
    //     insert_into.append("intelligence, ");
    //     insert_into.append("hp, ");
    //     insert_into.append("hpMax, ");
    //     insert_into.append("stamina, ");
    //     insert_into.append("damageMin, ");
    //     insert_into.append("damageMax, ");
    //     insert_into.append("accuracy, ");
    //     insert_into.append("defense, ");
    //     insert_into.append("luck, ");
    //     insert_into.append("statPoints");
    //     insert_into.append(") ");
   
    //     insert_into.append("VALUES (");
    //     insert_into.append("\"Frank\", ");
    //     insert_into.append("0, ");
    //     insert_into.append("0, ");
    //     insert_into.append("1, ");                     
    //     insert_into.append("0, ");
    //     insert_into.append("100, ");
    //     insert_into.append("5, ");
    //     insert_into.append("5, ");
    //     insert_into.append("5, ");
    //     insert_into.append("5, ");
    //     insert_into.append("5, ");
    //     insert_into.append("5, ");
    //     insert_into.append("2, ");
    //     insert_into.append("15, ");
    //     insert_into.append("20, ");
    //     insert_into.append("4, ");
    //     insert_into.append("20, ");
    //     insert_into.append("5, ");
    //     insert_into.append("10");
    //     insert_into.append(");"); 

    //     std::cout << insert_into << std::endl;
    //     rc = sqlite3_exec(db, insert_into.c_str(), NULL, NULL, &err);
    //     if(rc != SQLITE_OK)
    //         std::cout << "error: " << err << std::endl;
    // }
		
	if(rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt) != SQLITE_DONE)
		{
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

			Character temp(name2, distanceTraveled, gold, level, exp, expNext, strength,
				vitality, dexterity, intelligence, hp, hpMax, stamina, damageMin, damageMax, accuracy, defense, luck, statPoints);
		
			this->characters.push_back(Character(temp));

			std::cout << "[name][" << name2 << "]"  << std::endl;
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


			std::cout << "Character: " << characters[activeCharacter].getName() << std::endl;
			std::cout << "CHARACTERS LOADED!!!\n";
		}
	}

	if (this->characters.size() <= 0)
	{
		throw "ERROR! NO CHARACTERS LOADED OR EMPTY FILE!";
	}
}

void Game::levelUpCharacter()
{
	this->characters[activeCharacter].levelUp();
}

void Game::createNewCharacter() 
{
	std::string name = "";
	std::cout << "Character name: ";
	std::getline(std::cin, name);

	for (size_t i = 0; i < this->characters.size(); i++)
	{
		while (name == this->characters[i].getName())
		{
			std::cout << "Error! Character already exists!\n";
			std::cout << "Character name: ";
			std::getline(std::cin, name);
		}
	}

	characters.push_back(Character());
	activeCharacter = characters.size() - 1;
	characters[activeCharacter].initialize(name);
}

void Game::selectCharacter()
{
	std::cout << "Select character: ";

	for (size_t i = 0; i < characters.size(); i++)
	{
		std::cout << "Index: " << i << " = " << this->characters[i].getName()
			<< this->characters[i].getLevel() << std::endl;
	}

	std::cout << std::endl << "Choose Character: ";
	std::cin >> this->choice;

	while (std::cin.fail() || this->choice >= characters.size() || this->choice < 0) {
		std::cout << "Faulty input!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "\nChoose Character: ";
		std::cin >> this->choice;
	}

	std::cin.ignore(100, '\n');
	std::cout << '\n';

	this->activeCharacter = choice;

	std::cout << this->characters[activeCharacter].getName() << " IS SELECTED!" << std::endl;
}

void Game::travel() 
{
	this->characters[activeCharacter].travel();
	Event ev;

	ev.generateEvent(this->characters[activeCharacter], this->enemies);
}

void Game::rest()
{
	int restCost = this->characters[this->activeCharacter].getHPMax() - this->characters[this->activeCharacter].getHP();
	std::cout << "= Rest =" << std::endl;
	std::cout << "= Resting costs you: ";
	std::cout << restCost;

	std::cout << std::endl << "Your gold: ";
	std::cout << this->characters[this->activeCharacter].getGold() << std::endl;
	std::cout << "HP: " << this->characters[this->activeCharacter].getHP() << " / "
			  << this->characters[this->activeCharacter].getHPMax() << std::endl;

	if (this->characters[this->activeCharacter].getGold() < restCost)
		std::cout << "NOT ENOUGH MONEY, SORRY BUDDY!" << std::endl;
	else if(this->characters[this->activeCharacter].getHP() >= this->characters[this->activeCharacter].getHPMax())
	{
		std::cout << "ALREADY AT FULL HEALTH BUDDY!" << std::endl;
	}
	else
	{
		std::cout << std::endl << std::endl << "Rest? (0) Yes, (1) No ... " << std::endl << std::endl;

		while (std::cin.fail() || this->choice < 0 || this->choice > 1) {
			std::cout << "Faulty input!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << std::endl << "Rest? (0) Yes, (1) No..." << std::endl;
			std::cin >> this->choice;
		}
		std::cin.ignore();
		std::cout << std::endl;

		if (choice == 0) {
			this->characters[this->activeCharacter].resetHP();
			this->characters[this->activeCharacter].payGold(restCost);

			std::cout << "RESTED!" << std::endl;
		}
		else
		{
			std::cout << "MAYBE NEXT TIME!" << std::endl;
		}
	}

}
