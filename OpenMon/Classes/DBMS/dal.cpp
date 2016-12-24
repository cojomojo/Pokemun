#include <sstream>
#include "dal.hpp"

#define SharedPtrTypedSqlValue(type, name, value) (std::make_shared<TypedSqlValue<type>>(TypedSqlValue<type>(name, value)))
#define StdPairSqlValue(key, value) (std::pair< std::string, std::shared_ptr<SqlValue> >(key, value))

using namespace cocos2d;
using namespace OpenMonData;

DAL::DAL() 
    : open_(false) {}

DAL::~DAL() 
{
    CloseConnection();
}   

void DAL::OpenConnection()
{
    const std::string db_name = "data/openmon.sqlite";
    FileUtils *fileUtils = FileUtils::getInstance();

    const std::string db_path = fileUtils->fullPathForFilename(db_name);
    // Try and open a connection using the database file included.
    if (fileUtils->isFileExist(db_path)) 
    {
        int rc = sqlite3_open(db_path.c_str(), &_pDB);
        if (rc != SQLITE_OK) {
            std::ostringstream oss;
            oss << "Error opening database file. sqlite3_open returned code: " << "; message: "  << sqlite3_errmsg(_pDB);
            // CCLOG(oss.str().c_str());
            throw DbmsException(oss.str());
        }
    } else {
        throw DbmsException("Database file not found!");
    }

    open_ = true;
}

void DAL::CloseConnection()
{
    if (!open_)
        return;

    int rc = sqlite3_close(_pDB);
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error closing database. sqlite3_open returned code: " << "; message: "  << sqlite3_errmsg(_pDB);
        // CCLOG(oss.str().c_str());
        throw DbmsException(oss.str());
    }
        
    open_ = false;
}

SqlResultList DAL::QueryToMapVector(std::string str_stmt) 
{
    // First, make sure we have an open connection.
    if (!open_) {
        throw DbmsException("A connection must be open before querying.");
    }

    int rc; // return code
    sqlite3_stmt *stmt; // compiled sql statment

    rc = sqlite3_prepare_v2(_pDB, str_stmt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error preparing SQL statement. sqlite3_open returned code: " << "; message: "  << sqlite3_errmsg(_pDB);
        // CCLOG(oss.str().c_str());
        throw DbmsException(oss.str());
    }

    // execute the sql statement and go over results row by row
    SqlResultList result;
    while ((rc = sqlite3_step(stmt)) != SQLITE_ERROR && rc != SQLITE_DONE) {
        // add a map to the results for the current row
        std::map<std::string, std::shared_ptr<SqlValue>> map;
        
        // loop through each column in the row
        for (auto i = 0; i < sqlite3_column_count(stmt); ++i) {
            auto col_name = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)));
            int col_type = sqlite3_column_type(stmt, i);

            switch (col_type) {
                case SQLITE_INTEGER:
                    map.insert( StdPairSqlValue(col_name, SharedPtrTypedSqlValue(int, "int", sqlite3_column_int(stmt, i))) );
                    break;
                case SQLITE_NULL:
                    map.insert( StdPairSqlValue(col_name, SharedPtrTypedSqlValue(int, "null", 0)) );
                    break;
                case SQLITE_FLOAT:
                    map.insert( StdPairSqlValue(col_name, SharedPtrTypedSqlValue(float, "float", sqlite3_column_double(stmt, i))) );
                    break;
                case SQLITE_BLOB:
                case SQLITE_TEXT:
                default:
                    map.insert( StdPairSqlValue(col_name, SharedPtrTypedSqlValue(std::string, "string", std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i))))) );
            }
            
        }

        result.push_back(map);
    } 

    // Destroy the statement, while preserving any error that occured in the last sqlite3_step().
    rc = sqlite3_finalize(stmt);

    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error executing SQL statement. sqlite3_open returned code: " << "; message: "  << sqlite3_errmsg(_pDB);
        // CCLOG(oss.str().c_str());
        throw DbmsException(oss.str());
    }

    return result;
}
