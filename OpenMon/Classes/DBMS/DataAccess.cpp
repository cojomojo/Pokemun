#include <sstream>
#include "DataAccess.hpp"

#define SharedPtrTypedSqlValue(type, name, value) (std::make_shared<TypedSqlValue<type>>(TypedSqlValue<type>(name, value)))
#define StdPairSqlValue(key, value) (std::pair< std::string, std::shared_ptr<SqlValue> >(key, value))

using namespace cocos2d;
using namespace OpenMonData;

DataAccess::DataAccess() 
    : open_(false) {}

DataAccess::~DataAccess() 
{
    CloseConnection();
}   

void DataAccess::OpenConnection()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    const std::string db_name = "openmon.sqlite";
#else
	const std::string db_name = "data/openmon.sqlite";
#endif

    FileUtils *fileUtils = FileUtils::getInstance();

    const std::string db_path = fileUtils->fullPathForFilename(db_name);
    // Try and open a connection using the database file included.
    if (fileUtils->isFileExist(db_path)) 
    {
        int rc = sqlite3_open(db_path.c_str(), &pDB_);
        if (rc != SQLITE_OK) {
            std::ostringstream oss;
            oss << "Error opening database file. sqlite3_open returned code: " << rc <<  "; message: "  << sqlite3_errmsg(pDB_);
            // CCLOG(oss.str().c_str());
            throw DataAccessException(oss.str());
        }
    } else {
        throw DataAccessException("Database file not found!");
    }

    open_ = true;
}

void DataAccess::CloseConnection()
{
    if (!open_)
        return;

    int rc = sqlite3_close(pDB_);
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error closing database. sqlite3_open returned code: " << rc <<  "; message: "  << sqlite3_errmsg(pDB_);
        // CCLOG(oss.str().c_str());
        throw DataAccessException(oss.str());
    }
        
    open_ = false;
}

SqlResultList DataAccess::QueryToSqlResultList(std::string str_stmt) 
{
    // First, make sure we have an open connection.
    if (!open_) {
        throw DataAccessException("Cannot execute sql without an open connection.");
    }

    int rc; // return code
    sqlite3_stmt *stmt; // compiled sql statment

    rc = sqlite3_prepare_v2(pDB_, str_stmt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error preparing SQL statement. sqlite3_open returned code: " << rc <<  "; message: "  << sqlite3_errmsg(pDB_);
        // CCLOG(oss.str().c_str());
        throw DataAccessException(oss.str());
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
		oss << "Error finalizing SQL statement. sqlite3_finalize returned code: " << rc <<  "; message: " << sqlite3_errmsg(pDB_);
		// CCLOG(oss.str().c_str());
		throw DataAccessException(oss.str());
	}

    return result;
}

// Runs a SQL query and returns a single result which represents a single database row.
SqlResult DataAccess::QueryToSqlResult(std::string str_stmt)
{
    return QueryToSqlResultList(str_stmt).front();
}

// Executes a SQL statment that does not return a result set. It returns the number of
// rows affected by the non query.
int DataAccess::ExecuteNonQuery(std::string str_stmt)
{
    // First, make sure we have an open connection.
    if (!open_) {
        throw DataAccessException("Cannot execute SQL without an open connection.");
    }
    
    int rc; // return code
    sqlite3_stmt *stmt; // compiled sql statment
    
    rc = sqlite3_prepare_v2(pDB_, str_stmt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error preparing SQL statement. sqlite3_open returned code: " << rc <<  "; message: "  << sqlite3_errmsg(pDB_);
        // CCLOG(oss.str().c_str());
        throw DataAccessException(oss.str());
    }
    
    // Execute the sql statement.
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE) {
		if (rc == SQLITE_ERROR || rc == SQLITE_READONLY) {
			// Destroy the statement, while preserving any error that occured in the last sqlite3_step().
			rc = sqlite3_finalize(stmt);
			std::ostringstream oss;
			oss << "Error executing SQL statement. sqlite3_step returned code: " << rc <<  "; message: " << sqlite3_errmsg(pDB_);
			throw DataAccessException(oss.str());
			break;
		} 
		rc = sqlite3_step(stmt);
	}
    
    // Destroy the statement, while preserving any error that occured in the last sqlite3_step().
    rc = sqlite3_finalize(stmt);
    
    if (rc != SQLITE_OK) {
        std::ostringstream oss;
        oss << "Error finalizing SQL statement. sqlite3_finalize returned code: " << rc <<  "; message: "  << sqlite3_errmsg(pDB_);
        // CCLOG(oss.str().c_str());
        throw DataAccessException(oss.str());
    }
    
    return sqlite3_changes(pDB_);
}
