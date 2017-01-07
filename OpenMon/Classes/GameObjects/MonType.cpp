#include "MonType.hpp"

using namespace OpenMonObjects;

// Constructor without the efficacy map, used for the object testing for simplicity
// TODO remove and use the actual constructor for the tests later
MonType::MonType(int id, std::string type_name)
: id_(id), type_name_(type_name)
{
    
}

MonType::MonType(int id, std::string type_name, std::map<int,int> &efficacy)
    : id_(id), type_name_(type_name), efficacy_(efficacy)
{

}

// TODO: Implement this method.
int MonType::DamageFactor(MonType other_type) 
{
    return 0;
}
