#include "dal.hpp"

USING_NS_CC;
using namespace OpenMonData;

DAL::DAL() 
{
    const std::string db_name = "data/openmon.sqlite";
    FileUtils *fileUtils = FileUtils::getInstance();

    const std::string db_path = fileUtils->fullPathForFilename(db_name);
    // Try and open a connection using the database file included.
    if (fileUtils->isFileExist(db_path)) 
    {
        int rc = sqlite3_open(db_path.c_str(), &_ppDB);
        if (rc != SQLITE_OK) {
            CCLOG("Error opening database file. sqlite3_open returned code: %d, message: %s", 
                  rc, 
                  sqlite3_errmsg(_ppDB));
        }

    } else {
        CCLOG("Database file not found!");
    }
}

DAL::~DAL() 
{
    sqlite3_close(_ppDB);
}   

std::vector<std::map<std::string, std::string>> DAL::QueryToMapVector(std::string str_stmt) 
{
    int rc; // return code
    sqlite3_stmt *stmt; // compiled sql statment

    rc = sqlite3_prepare_v2(_ppDB, str_stmt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        CCLOG("Error preparing SQL statement. sqlite3_open returned code: %d, message: %s", 
              rc, 
              sqlite3_errmsg(_ppDB));
        return std::vector<std::map<std::string, std::string>>();
    }

    // execute the sql statement and go over results row by row
    std::vector<std::map<std::string, std::string>> result;
    while (( rc = sqlite3_step(stmt)) != SQLITE_ERROR && rc != SQLITE_DONE) {
        // add a map to the results for the current row
        std::map<std::string, std::string> map;
        
        // loop through each column in the row
        for (auto i = 0; i < sqlite3_column_count(stmt); ++i) {
            auto col_name = std::string( reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)) );
            auto col_value = std::string( reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)) );
            map.insert(std::pair<std::string, std::string>(col_name, col_value));
        }

        result.push_back(map);
    } 

    // Destroy the statement, while preserving any error that occured in the last sqlite3_step().
    rc = sqlite3_finalize(stmt);

    if (rc != SQLITE_OK) {
        CCLOG("Error executing SQL statement. sqlite3_open returned code: %d, message: %s", 
              rc, 
              sqlite3_errmsg(_ppDB));
        return std::vector<std::map<std::string, std::string>>();
    }

    return result;
}