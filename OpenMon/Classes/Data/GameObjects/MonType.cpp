#include "MonType.hpp"

using namespace OpenMonObjects;

MonType::MonType(int id, std::string type_name, std::map<int,int> &efficacy) 
    : id_(id), type_name_(type_name), efficacy_(efficacy)
{

}

// TODO: Implement this method.
int MonType::DamageFactor(MonType other_type) 
{
    return 0;
}