#include "Mon.hpp"

using namespace OpenMonObjects;

Mon::Mon(std::string name, BSVs &base_stats, MonType &primary, MonType &secondary)
    : base_stats_(base_stats), current_stats_(base_stats),
      primary_type_(primary), secondary_type_(secondary)
{
    // TODO: Come up with algorithms for initial stats
    name_ = name;
    level_ = 1;
    current_stats_.hp = ScaleHp();
    max_hp_ = current_stats_.hp;
    current_stats_.accuracy = DEFAULT_ACCURACY;
    active_ = false;
    move_set_.reserve(MAX_NUM_MOVES);
}

 Mon::Mon(std::string name, BSVs &base_stats, CSVs &current_stats, int level, int max_hp, MonType &primary, MonType &secondary)
        : base_stats_(base_stats), current_stats_(current_stats),
          level_(level), max_hp_(max_hp),
          primary_type_(primary), secondary_type_(secondary)
 {
     name_ = name;
     move_set_.reserve(MAX_NUM_MOVES);
 }

// Restores the Mon's HP based on the passed in value.
// If the objects current_stats.hp + vaule is greater than
// the max hp, the Mon's current_stats.hp will be set to the max.
void Mon::RestoreHp(int value) 
{
    if (current_stats_.hp + value < max_hp_) {
        current_stats_.hp += value;
    }
    else {
        current_stats_.hp = max_hp_;
    }
}

void Mon::TakeDamage(int value) 
{
    current_stats_.hp -= value; // TODO type checking for weakness/resistance
    if (current_stats_.hp <= 0) {
        status_condition_.fainted();
    }
}

bool Mon::IsFainted()
{
    return status_condition_.IsFainted();
}

bool Mon::IsConfused() 
{
    return status_condition_.IsConfused();
}

// When you swap the active mon, confusion is removed
// and current stat values are reset to their base values
void Mon::ResetStatsToDefault() 
{
    status_condition_.reset(); // TODO only confused can be reset on swap
    current_stats_ = CSVs(base_stats_);
}

// Private methods

// Multiplies the Mon's stored BSV HP value by 3 to set the initial HP for the Mon.
int Mon::ScaleHp() 
{
    // TODO if we want the algorithm to be 100% accurate to the main games
    // we need to do std::floor(((2 * base_stats_.hp + iv + std::floor(ev/4)) * level_)/100) + level_ + 10;
    return base_stats_.hp * 3;
    
}
