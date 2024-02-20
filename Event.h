#ifndef EVENT_H
#define EVENT_H
#include <cstdlib>
#include "Character.h"
#include "Puzzle.h"
#include "dArr.h"
#include "Enemy.h"

class Event
{
private:
	int nrOfEvents;

public:
	Event();
	virtual ~Event();

	void enemyEncounter(Character &character, dArr<Enemy> enemies);
	void puzzleEncounter(Character &character);
	void generateEvent(Character& character, dArr<Enemy> enemies);
};
#endif
