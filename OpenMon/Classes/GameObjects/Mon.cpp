#include "Mon.hpp"

using namespace OpenMonObjects;

Mon::Mon(std::string name, BSVs &base_stats, MonType &primary, std::unique_ptr<MonType> secondary)
    : name_(name), base_stats_(base_stats), primary_type_(primary), secondary_type_(std::move(secondary)), 
      fainted_(false), confused_(false), active_(false)
{ 
    // TODO: Come up with algorithms for initial stats
     level_ = 1;
     max_hp_ = ScaleHp();
     current_stats_.hp = max_hp_;
     current_stats_.accuracy = DEFAULT_ACCURACY;
     move_set_.reserve(MAX_NUM_MOVES);
}

Mon::Mon(std::string name, BSVs &base_stats, CSVs &current_stats, int level, int max_hp, MonType &primary, 
         std::unique_ptr<MonType> secondary)
    : name_(name), base_stats_(base_stats), current_stats_(current_stats), level_(level), max_hp_(max_hp), 
      fainted_(false), confused_(false), primary_type_(primary), secondary_type_(std::move(secondary))
{
}

// Restores the Mon's HP based on the passed in value.
// If the objects current_stats.hp + vaule is greater than
// the max hp, the Mon's current_stats.hp will be set to the max.
void Mon::RestoreHp(int value) 
{
    if (current_stats_.hp + value < max_hp_) {
        current_stats_.hp += value;
    } else {
        current_stats_.hp = max_hp_;
    }
}

void Mon::TakeDamage(int value) 
{
    // TODO: type checking for weakness/resistance
    current_stats_.hp -= value;
    if (current_stats_.hp <= 0) {
        fainted_ = true;
    }
}

void Mon::ResetStatsToDefault() 
{
    current_stats_ = CSVs(base_stats_);
}

void Mon::ClearStatusCondition()
{
    status_condition_.reset();
}

void Mon::Revive()
{
    fainted_ = false;
    confused_ = false;
    ClearStatusCondition();
    current_stats_.hp = max_hp_;
}

// Private methods

// Multiplies the Mon's stored BSV HP value by 3 to set the initial HP for the Mon.
int Mon::ScaleHp() 
{
    // TODO: if we want the algorithm to be 100% accurate to the main games
    // we need to do std::floor(((2 * base_stats_.hp + iv + std::floor(ev/4)) * level_)/100) + level_ + 10;
    return base_stats_.hp * 3;
}
