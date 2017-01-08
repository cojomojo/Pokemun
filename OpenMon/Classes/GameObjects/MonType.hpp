#pragma once

#include <map>
#include <string>

namespace OpenMonObjects
{
    /** \brief Represents a type of mon, e.g. Water type.
     *
     * @class MonType
     */
    class MonType 
    {
    public:
        // Constructor without the efficacy map, used for the object testing for simplicity
        // TODO remove and use the actual constructor for the tests later
        MonType(int id, std::string type_name);
        
        MonType(int id, std::string type_name, std::map<int,int> &efficacy);

        /**
         * @return The id of the type as stored in the database.
         */
        int id() const { return id_; }

        /**
         * @return The locale specific name of the type.
         */
        std::string type_name() { return type_name_; }

        /** \brief It returns the damage factor a move of some type has against *this* type.
         *
         * @param The type to get the damage factor for.
         * @return The damage factor as a percentage.
         */
        int DamageFactor(MonType other_type);
    private:
        int id_; // The type id in the database.
        std::string type_name_; // The locale specific name of the type.
        std::map<int, int> efficacy_; // The efficacy map tells us the damage factors all other types have against *this* type.
    };
}
