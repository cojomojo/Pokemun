#include "MonStatus.hpp"

using namespace OpenMonObjects;

std::map<MonStatus::StatusConditions, std::string> const MonStatus::status_condition_strings = {
    {MonStatus::StatusConditions::NONE, "None"},
    {MonStatus::StatusConditions::PARALYZED, "Paralyzed"},
    {MonStatus::StatusConditions::POISONED, "Poisoned"},
    {MonStatus::StatusConditions::BADLY_POISONED, "Badly poisoned"},
    {MonStatus::StatusConditions::BURNED, "Burned"},
    {MonStatus::StatusConditions::FROZEN, "Frozen"},
    {MonStatus::StatusConditions::FLINCH, "Flinched"},
    {MonStatus::StatusConditions::INFATUATED, "Infatuated"}
};

std::map<MonStatus::StatusConditions, bool> const MonStatus::status_condition_volatility = {
    {MonStatus::StatusConditions::NONE, false},
    {MonStatus::StatusConditions::PARALYZED, false},
    {MonStatus::StatusConditions::POISONED, false},
    {MonStatus::StatusConditions::BADLY_POISONED, false},
    {MonStatus::StatusConditions::BURNED, false},
    {MonStatus::StatusConditions::FROZEN, false},
    {MonStatus::StatusConditions::FLINCH, true},
    {MonStatus::StatusConditions::INFATUATED, true},
};

MonStatus::MonStatus()
    : condition_(StatusConditions::NONE)
{
}

bool MonStatus::IsPersistent() 
{
    return MonStatus::status_condition_volatility.at(condition_);
}

bool MonStatus::IsParalyzed()
{
    return condition_ == MonStatus::StatusConditions::PARALYZED;
}

bool MonStatus::IsPoisoned()
{
    return condition_ == MonStatus::StatusConditions::POISONED;
}

bool MonStatus::IsBadlyPoisoned()
{
    return condition_ == MonStatus::StatusConditions::BADLY_POISONED;
}

bool MonStatus::IsBurned()
{
    return condition_ == MonStatus::StatusConditions::BURNED;
}

bool MonStatus::IsFrozen()
{
    return condition_ == MonStatus::StatusConditions::FROZEN;
}

bool MonStatus::IsFlinch()
{
    return condition_ == MonStatus::StatusConditions::FLINCH;
}

bool MonStatus::IsInfatuated()
{
    return condition_ == MonStatus::StatusConditions::INFATUATED;
}

bool MonStatus::IsCustom()
{
    return condition_ == MonStatus::StatusConditions::CUSTOM;
}