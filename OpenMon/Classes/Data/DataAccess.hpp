#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <exception>
#include <map>
#include <memory>
#include "SqlValue.hpp"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "sqlite3.h"
#else
#include "sqlite/sqlite3.h"
#endif


namespace OpenMonData 
{
    typedef std::map<std::string, std::shared_ptr<SqlValue>> SqlResult;
    typedef std::vector<SqlResult> SqlResultList;
    
    class DataAccess 
    {
    public:
        DataAccess();

        // Destructor - Will destroy the sqlite3 connection to the OpenMon database.
        ~DataAccess();

        // Will create a sqlite3 connection to the OpenMon database.
        void OpenConnection();

        // Will destroy the sqlite3 connection to the OpenMon database.
        void CloseConnection();

        // Runs a SQL query and returns the results in a vector filled with maps. Each map
        // represents a single row returned with the key being the column name, and the 
        // value being row value for that column.
        SqlResultList QueryToSqlResultList(std::string str_stmt);

        // Runs a SQL query and returns a single result which represents a single database row.
        SqlResult QueryToSqlResult(std::string str_stmt);

        // Executes a SQL statment that does not return a result set. It returns the number of
        // rows affected by the non query. 
        int ExecuteNonQuery(std::string str_stmt);
    private:
        bool open_;
        sqlite3 *pDB_;
    };


    class DataAccessException: public std::exception
    {
    public:
        /** Constructor (C strings).
        *  @param message C-style string error message.
        *                 The string contents are copied upon construction.
        *                 Hence, responsibility for deleting the char* lies
        *                 with the caller. 
        */
        explicit DataAccessException(const char* message):
            msg_(message) {}

        /** Constructor (C++ STL strings).
        *  @param message The error message.
        */
        explicit DataAccessException(const std::string& message)
            : msg_(message) {}

        /** Destructor.
        * Virtual to allow for subclassing.
        */
        virtual ~DataAccessException() throw (){}

        /** Returns a pointer to the (constant) error description.
        *  @return A pointer to a const char*. The underlying memory
        *          is in posession of the Exception object. Callers must
        *          not attempt to free the memory.
        */
        virtual const char* what() const throw () { return msg_.c_str(); }

    protected:
        // Error message.
        std::string msg_;
    };
}