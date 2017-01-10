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
        BSVs(int hp, int attack, int defense, int speed, int special_attack, int special_defense)
            : hp(hp), attack(attack), defense(defense), speed(speed), special_attack(special_attack), 
              special_defense(special_defense) { }
        BSVs(BSVs &bsvs)
            : hp(bsvs.hp), attack(bsvs.attack), defense(bsvs.defense), speed(bsvs.speed), 
              special_attack(bsvs.special_attack), special_defense(bsvs.special_defense) { }
    };

    struct CSVs : public BSVs 
    {
        int accuracy;

        CSVs() { }
        CSVs(int hp, int attack, int defense, int speed, int special_attack, int special_defense, int accuracy)
            : BSVs(hp, attack, defense, speed, special_attack, special_defense), accuracy(accuracy) { }
        CSVs(BSVs &bsvs)
            : BSVs(bsvs) { }
    };

    class Mon {
    public:
        // Constructors
        Mon(std::string name, BSVs &base_stats, MonType &primary, 
            std::unique_ptr<MonType> secondary = std::unique_ptr<MonType>(nullptr));
        
        Mon(std::string name, BSVs &base_stats, CSVs &current_stats, int level, int max_hp, MonType &primary, 
            std::unique_ptr<MonType> secondary = std::unique_ptr<MonType>(nullptr));
        
        // Getters/Setters
        std::string const& name() const { return name_; }

        BSVs const& base_stats() const { return base_stats_; }
        
        CSVs const& current_stats() const { return current_stats_; }
        
        int current_hp() const { return current_stats_.hp; }
        void current_hp(int value) { current_stats_.hp = value; }
        
        int max_hp() const { return max_hp_; }
        
        int level() const { return level_; }
        
        int speed() const { return current_stats_.speed; }
        
        bool active() const { return active_; }
        void active(bool value) { active_ = value; }
        
        bool fainted() const { return fainted_; }

        bool confused() const { return confused_; }
        void confused(bool value) { confused_ = value; }
        
        MonStatus const& status_condition() const { return status_condition_; }

        int primary_type() const { return primary_type_.id(); }
        int secondary_type() const { return secondary_type_.get() == nullptr ? 0 : secondary_type_->id(); }
        bool has_secondary_type() const { return secondary_type_.get() != nullptr; }

        // Other Methods
        void TakeDamage(int value);
        void RestoreHp(int value);
        void Revive();
        void ResetStatsToDefault();
        void ClearStatusCondition();
        
    private:
        int ScaleHp();
        
        int const MAX_NUM_MOVES = 4;
        int const DEFAULT_ACCURACY = 100;
        
        std::string name_;
        int level_;
        int max_hp_;
        bool active_;
        bool fainted_;
        bool confused_;
        BSVs base_stats_;
        CSVs current_stats_;
        MonStatus status_condition_;
        MonType primary_type_;
        std::unique_ptr<MonType> secondary_type_; // secondary_type_ can be null, therefore we store it as a unique_ptr
        std::vector<Move> move_set_;
    };

}
