all: enemy_query

enemy_query: query.o Character.o Enemy.o
	g++ -g main.o Character.o Enemy.o -l sqlite3 -o main

query.o: enemy_query.cxx
	g++ -c enemy_query.cxx

Character.o: Character.cpp Character.h
	g++ -c Character.cpp

Enemy.o: Enemy.cpp Enemy.h
	g++ -c Enemy.cpp

clean:
	rm -rf *.o main







