#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "sqlite/sqlite3.h"


namespace OpenMonData 
{
    typedef enum { _INT64, _FLOAT, _BLOB, _TEXT, _NULL } DataType;
    
    struct DynamicType {
        DataType type;
        union {
            int64_t int_val;
            double_t float_val;
            const void* blob_val;
            char *text_val;
        };

        DynamicType() {

        }

        ~DynamicType() {

        }
    };


    class DAL 
    {
    public:
        // Constructor - Will create a sqlite3 connection to the OpenMon database.
        DAL();

        // Destructor - Will destroy the sqlite3 connection to the OpenMon database.
        ~DAL();

        // Runs a SQL query and returns the results in a vector filled with maps. Each map
        // represents a single row returned with the key being the column name, and the 
        // value being row value for that column.
        std::vector<std::map<std::string, DynamicType>> QueryToMapVector(std::string str_stmt);

    private:
        sqlite3 *_ppDB;
    };

}