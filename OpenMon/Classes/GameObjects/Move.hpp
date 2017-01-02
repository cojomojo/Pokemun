#ifndef Move_hpp
#define Move_hpp

#include "types.hpp"
#include "StatusConditions.hpp"

#include<string>
using std::string;
using std::rand;


class Move {
    
public:
    Move(string name, Type type, int acc, int pwr, int pp,
         int secondary_effect_probability, int status_effect_probability,
         bool priority);
    
    bool IsPPEmpty();
    int GetPP();
    void UseMove();
    string GetMoveName();
    bool InflictedStatusEffect();
    bool InflictedSecondaryEffect();
    bool AttackHit();
    bool HasPriority();
    Type GetMoveType();
    
private:
    string move_name;
    int current_pp;
    int max_pp;
    int power;
    int accuracy;
    Type move_type;
    
    int status_effect_percentage;     // chance of burn, poison, sleep, etc. (0 if no status effects)
    int secondary_effect_percentage;  // chance of lowering speed, defense, etc. (0 if no secondary effects)
    Status status_type_inflicted;
    bool priority_flag;               // true if the move has priority (goes first independent of speed stat)
    bool has_status_effect;
    bool has_secondary_effect;
    
};

#endif /* Move_hpp */
