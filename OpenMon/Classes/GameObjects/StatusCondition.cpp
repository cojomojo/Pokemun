#include "StatusCondition.hpp"

using OpenMonObjects;

StatusCondition::StatusCondition(int id, std::string condition_name, bool persistent)
    : id_(id), condition_name_(condition_name), persistent(persistent)
{
}