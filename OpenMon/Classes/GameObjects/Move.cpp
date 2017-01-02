#include "Move.hpp"

Move::Move(string name, Type type, int acc, int pwr, int pp,
           int secondary_effect_probability, int status_effect_probability,
           bool priority) {
    move_name = name;
    move_type = type;
    accuracy = acc;
    power = pwr;
    current_pp = pp;
    max_pp = pp;
    status_effect_percentage = status_effect_probability;
    secondary_effect_percentage = secondary_effect_probability;
    priority_flag = priority;
    has_status_effect = false;     // TODO
    has_secondary_effect = false;  // TODO
}

// returns boolean based on if the move has any pp left
bool Move::IsPPEmpty() {
    return current_pp <= 0;
}

int Move::GetPP(){
    return current_pp;
}

void Move::UseMove() {
    current_pp -= 1;
}

string Move::GetMoveName() {
    return move_name;
}

// Returns a boolean based on if the status effect for the move
// should be applied or not (if applicable).
bool Move::InflictedStatusEffect() {
    int rng = (rand() % 100) + 1;
    return rng <= status_effect_percentage;
}

// Returns a boolean based on if the secondary effect for the move
// should be applied or not (if applicable).
bool Move::InflictedSecondaryEffect() {
    int rng = (rand() % 100) + 1;
    return rng <= secondary_effect_percentage;
}

// Returns true or false based on if the attack should hit or miss
// based on the accuracy stat for the Mon
bool Move::AttackHit() {
    int rng = (rand() % 100) + 1;
    return rng <= accuracy;
}

bool Move::HasPriority() {
    return priority_flag;
}

Type Move::GetMoveType() {
    return move_type;
}
