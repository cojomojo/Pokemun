#pragma once

#include <memory>
#include <vector>
#include <string>
#include "MonType.hpp"
#include "MonStatus.hpp"
#include "Move.hpp"

namespace OpenMonObjects
{
    struct BSVs 
    {
        int hp;
        int attack;
        int defense;
        int speed;
        int special_attack;
        int special_defense;

        BSVs() { }
        BSVs(BSVs &bsvs)
            : hp(bsvs.hp), attack(bsvs.attack), defense(bsvs.defense), speed(bsvs.speed), 
              special_attack(bsvs.special_attack), special_defense(bsvs.special_defense) { }
    };

    struct CSVs : public BSVs 
    {
        int accuracy;

        CSVs() { }
        CSVs(BSVs &bsvs)
            : BSVs(bsvs) { }
    };

    class Mon {
    public:
        Mon(std::string name, BSVs &base_stats, MonType &primary, MonType &secondary);
        Mon(std::string name, BSVs &base_stats, CSVs &current_stats, int level, int max_hp, MonType &primary, MonType &secondary);
        
        // Getters/Setters
        BSVs const& base_stats() const { return base_stats_; }
        CSVs const& current_stats() const { return current_stats_; }
        int max_hp() const { return max_hp_; }
        int current_hp() const { return current_stats_.hp; }
        void current_hp(int value) { current_stats_.hp = value; }
        int level() const { return level_; }
        int speed() const { return current_stats_.speed; }
        bool active() const { return active_; }
        void active(bool is_active) { active_ = is_active; }
        std::string const& name() const { return name_; }
        MonStatus const& status_condition() const { return status_condition_; }
        
        // Other Methods
        bool IsFainted();
        bool IsConfused();
        void RestoreHp(int value);
        void TakeDamage(int value);
        void ResetStatsToDefault();
        
    private:
        int ScaleHp();
        
        int const MAX_NUM_MOVES = 4;
        int const DEFAULT_ACCURACY = 100;
        
        std::string name_;
        int level_;
        int max_hp_;
        bool active_;
        BSVs base_stats_;
        CSVs current_stats_;
        MonStatus status_condition_;
        MonType primary_type_;
        MonType secondary_type_;
        std::vector<std::unique_ptr<Move>> move_set_;
    };

}
