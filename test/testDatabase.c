#include <stdio.h>
#include <D:\ESGI\Language c et algorithmie\Projet\sqlite\snap\sqlite3.c>
#include <D:\ESGI\Language c et algorithmie\Projet\sqlite\snap\sqlite3.h>
#include <D:\ESGI\Language c et algorithmie\Projet\sqlite\snap\sqlite3ext.h>
#include <D:\ESGI\Language c et algorithmie\Projet\sqlite\snap\sqlite3rc.h>


int main() {
    sqlite3* db;
    char *err_message = 0;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Opened database successfully\n");
    }

  
    const char *sql_stmt = "INSERT INTO ip_addresses (ip, mask, binary, hexadecimal) VALUES ('192.168.1.1', '255.255.255.0', '11000000.10101000.00000001.00000001', 'C0.A8.01.01');";

    //create table
    //const char *sql_stmt = "CREATE TABLE ip_addresses ("
    //                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
     //                  "ip TEXT(12),"
     //                  "mask TEXT(12),"
     //                  "binary TEXT(32),"
    //                   "hexadecimal TEXT(8)"
     //                  ");";
    rc = sqlite3_exec(db, sql_stmt, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_close(db);
    return 0;
}
