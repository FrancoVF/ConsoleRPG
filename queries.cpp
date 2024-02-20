// cppsqlite
#include <iostream>
#include <sqlite3.h>
#include <string>

int main()
{
    char * err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("test.db", &db);

    std::string create_table;
    create_table.append("CREATE TABLE IF NOT EXISTS character (");
    create_table.append("id INTEGER PRIMARY KEY,");
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

    for(int i = 0; i < 10; i++) {
        std::string insert_into;
        insert_into.append("INSERT INTO character (");
        insert_into.append("name, ");
        insert_into.append("distanceTraveled, ");
        insert_into.append("gold, ");
        insert_into.append("level, ");
        insert_into.append("exp, ");
        insert_into.append("expNext, ");
        insert_into.append("strength, ");
        insert_into.append("vitality, ");
        insert_into.append("dexterity, ");
        insert_into.append("intelligence, ");
        insert_into.append("hp, ");
        insert_into.append("hpMax, ");
        insert_into.append("stamina, ");
        insert_into.append("damageMin, ");
        insert_into.append("damageMax, ");
        insert_into.append("accuracy, ");
        insert_into.append("defense, ");
        insert_into.append("luck, ");
        insert_into.append("statPoints");
        insert_into.append(") ");
   
        insert_into.append("VALUES (");
        insert_into.append("\"Frank\", ");
        insert_into.append("0, ");
        insert_into.append("0, ");
        insert_into.append("1, ");                     
        insert_into.append("0, ");
        insert_into.append("100, ");
        insert_into.append("5, ");
        insert_into.append("5, ");
        insert_into.append("5, ");
        insert_into.append("5, ");
        insert_into.append("5, ");
        insert_into.append("5, ");
        insert_into.append("2, ");
        insert_into.append("15, ");
        insert_into.append("20, ");
        insert_into.append("4, ");
        insert_into.append("20, ");
        insert_into.append("5, ");
        insert_into.append("10");
        insert_into.append(");"); 

        std::cout << insert_into << std::endl;
        rc = sqlite3_exec(db, insert_into.c_str(), NULL, NULL, &err);
        if(rc != SQLITE_OK)
            std::cout << "error: " << err << std::endl;
    }
    
    sqlite3_prepare_v2(db, "SELECT * FROM character", -1, &stmt, NULL);
    
    while(sqlite3_step(stmt) != SQLITE_DONE) {
      const unsigned char * name = sqlite3_column_text(stmt, 1); 
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
    }

      return EXIT_SUCCESS;
}