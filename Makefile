all: main


main: main.o Game.o Inventory.o Character.o Item.o Armor.o Weapon.o Enemy.o Event.o Puzzle.o
	g++ -g main.o Game.o Inventory.o Character.o Item.o Armor.o Weapon.o Enemy.o Event.o Puzzle.o -l sqlite3 -o main

main.o: main.cpp
	g++ -c main.cpp

Game.o: Game.cpp Game.h
	g++ -c  Game.cpp -l sqlite3

Inventory.o: Inventory.cpp Inventory.h
	g++ -c Inventory.cpp

Character.o: Character.cpp Character.h
	g++ -c Character.cpp

Item.o: Item.cpp Item.h
	g++ -c Item.cpp

Weapon.o: Weapon.cpp Weapon.h
	g++ -c Weapon.cpp

Armor.o: Armor.cpp Armor.h
	g++ -c Armor.cpp

Enemy.o: Enemy.cpp Enemy.h
	g++ -c Enemy.cpp

Event.o: Event.cpp Event.h dArr.h
	g++ -c Event.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -c Puzzle.cpp

clean:
	rm -rf *.o main







