#include <sqlite3.h>
#include <iostream>

int main()
{
    sqlite3* db;
    int res = sqlite3_open("test.db", &db);
    if(res)
        //database failed to open
        std::cout << "Database failed to open" << std::endl;
    else
    {
        //your database code here
    }
    sqlite3_close(db);

    return EXIT_SUCCESS;
}

