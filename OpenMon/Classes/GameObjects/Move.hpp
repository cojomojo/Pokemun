#pragma once

#include "MonType.hpp"
#include <string>

namespace OpenMonObjects {

    class Move
    {
    public:
        Move(std::string name, MonType &move_type, int acc, int pwr, int pp,
             int status_effect_probability, int secondary_effect_probability,
             bool priority);


        // Getters and Setters
        int current_pp() const { return current_pp_; }
        void current_pp(int value) { current_pp_ = value; }
        int max_pp() const { return max_pp_; }
        int power() const { return power_; }
        std::string const& Name() const { return move_name_; }
        MonType const& move_type() const { return move_type_; }
        bool priority_flag() const { return priority_flag_; }
        bool has_status_effect() const { return has_status_effect_; }
        bool has_secondary_effect() const { return has_secondary_effect_; }

        // Other Methods
        void UseMove();
        bool InflictedStatusEffect();
        bool InflictedSecondaryEffect();
        bool AttackHit();
        bool IsPPEmpty();
        void RestorePP(int value);
        
    private:
        std::string move_name_;
        MonType move_type_;
        int current_pp_;
        int max_pp_;
        int power_;
        int accuracy_;
        int status_effect_percentage_;     // chance of burn, poison, sleep, etc. (0 if no status effects)
        int secondary_effect_percentage_;  // chance of lowering speed, defense, etc. (0 if no secondary effects)
        bool priority_flag_;               // true if the move has priority (goes first independent of speed stat)
        bool has_status_effect_;
        bool has_secondary_effect_;
//        Status status_type_inflicted_;

    };
}
