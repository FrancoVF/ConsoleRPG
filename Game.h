#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "dArr.h"

class Game
{
private:
	int choice;
	bool playing;
	int activeCharacter;
	std::string fileName;
	std::vector<Character> characters;
	dArr<Enemy> enemies;

public:
	Game();
	virtual ~Game();

	void mainMenu();
	void initGame();
	void endGame();
	void levelUpCharacter();
	void createNewCharacter();
	void saveCharacters();
	void loadCharacters();
	void selectCharacter();
	void travel();
	void mainMenuDisplay() const;
	void mainMenuInput();
	std::string activeCharacterName() const;
	void mainMenuChoice();
	void stopper();
	void characterLevelUp() const;
	inline bool getPlaying() const { return this->playing; }
	void rest();
	void characterMenu();
};
#endif

