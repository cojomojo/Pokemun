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
        MonType(int id, std::string type_name, std::map<int, int> &efficacy);

        int id() const { return id_; }

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
