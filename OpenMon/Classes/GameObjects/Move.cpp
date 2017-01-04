#include "Move.hpp"
using namespace OpenMonObjects;

Move::Move(std::string name, MonType &move_type, int acc, int pwr, int pp,
            int status_effect_probability, int secondary_effect_probability,
            bool priority)
    : move_type_(move_type)
{
    move_name_ = name;
    accuracy_ = acc;
    power_ = pwr;
    current_pp_ = pp;
    max_pp_ = pp;
    status_effect_percentage_ = status_effect_probability;
    secondary_effect_percentage_ = secondary_effect_probability;
    priority_flag_ = priority;
    
    has_status_effect_ = (status_effect_probability > 0);
    has_secondary_effect_ = (secondary_effect_probability > 0);  // != instead of >?
 }

// Returns boolean based on if the move has any pp left,
// for example returns true if the pp is empty for the move
bool Move::IsPPEmpty()
{
    return current_pp_ <= 0;
}

// TODO call as the main move function
void Move::UseMove()
{
    current_pp_ -= 1;
}


// Returns a boolean based on if the status effect for the move
// should be applied or not (if applicable).
bool Move::InflictedStatusEffect()
{
    int rng = (std::rand() % 100) + 1;
    return rng <= status_effect_percentage_;
}

// Returns a boolean based on if the secondary effect for the move
// should be applied or not (if applicable).
bool Move::InflictedSecondaryEffect()
{
    int rng = (std::rand() % 100) + 1;
    return rng <= secondary_effect_percentage_;
}

// Returns true or false based on if the attack should hit or miss
// based on the accuracy stat for the Mon
bool Move::AttackHit()
{
    int rng = (std::rand() % 100) + 1;
    return rng <= accuracy_;
}

// Restores the Move's PP based on the passed in value.
// If the object's PP + value is greater than
// the max pp, the object's current_pp_ will be set to the max.
void Move::RestorePP(int value)
{
    if (current_pp_ + value < max_pp_) {
        current_pp_ += value;
    }
    else {
        current_pp_ = max_pp_;
    }
}
