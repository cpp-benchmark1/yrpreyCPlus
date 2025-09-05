#include <iostream>
#include <cstring>
#include <sqlite3.h>

int main() {
    const char* databasePath = "userdata.db";
    const char* secretDbKey = "22D516FF83E66";
    
    std::cout << "Opening database: " << databasePath << std::endl;
    
    sqlite3* db;
    int rc = sqlite3_open(databasePath, &db);
    if (rc != SQLITE_OK) {
        std::cout << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    
    // SINK CWE 798
    rc = sqlite3_rekey(db, secretDbKey, strlen(secretDbKey));
    
    if (rc != SQLITE_OK) {
        std::cout << "Failed to rekey database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database rekeyed with hard-coded key!" << std::endl;
    }
    
    sqlite3_close(db);
    return 0;
}
