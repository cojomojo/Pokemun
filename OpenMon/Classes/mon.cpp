#include "mon.hpp"

Mon::Mon(string name, int lvl, int b_hp, int b_atk, int b_def,
         int b_spcl_atk, int b_spcl_def, int b_speed,
         Type type_1, Type type_2) {
    
    name = mon_name;
    max_hp = ScaleHp(b_hp);
    level = lvl;
    
    base_attack = b_atk;
    base_defense = b_def;
    base_special_attk = b_spcl_atk;
    base_special_def = b_spcl_def;
    base_speed = b_speed;
    
    current_attack = b_atk;
    current_defense = b_def;
    current_special_attk = b_spcl_atk;
    current_special_def = b_spcl_def;
    current_speed = b_speed;
    
    primary_type = type_1;
    secondary_type = type_2;
    current_hp = max_hp;
    status_cond = no_condition;
    confused = false;
    fainted = false;
}

int Mon::GetCurrentHp() {
    return current_hp;
}

void Mon::SetCurrentHp(int value) {
    current_hp = value;
}


// Restores the Mon's HP based on the passed in value.
// If the objects current_hp + vaule is greater than
// the max hp, the Mon's current_hp will be set to the max.
void Mon::RestoreHp(int value) {
    if (current_hp + value < max_hp) {
        current_hp += value;
    }
    else {
        current_hp = max_hp;
    }
}

void Mon::TakeDamage(int value) {
    current_hp -= value; // TODO type checking for weakness/resistance
    if (current_hp <= 0) {
        fainted = true;
    }
}

int Mon::GetLevel() {
    return level;
}

int Mon::GetSpeed() {
    return current_speed;
}

bool Mon::IsFainted() {
    return fainted;
}

bool Mon::IsConfused() {
    return confused;
}

void Mon::SetFainted(bool faint) {
    fainted = faint;
}

string Mon::GetName() {
    return mon_name;
}

Status Mon::GetStatusCondition() {
    return status_cond;
}

// When you swap the active mon, confusion is removed
// and current stat values are reset to their base values
void Mon::ResetStatsToDefault() {
    confused = false;
    current_attack = base_attack;
    current_defense = base_defense;
    current_special_attk = base_special_attk;
    current_special_def = base_special_def;
    current_speed = base_speed;
}

// Private functions

// Multiplies the Mon's stored BSV HP value by 3 to set the initial HP for the Mon
int Mon::ScaleHp(int bsv_hp_value) {
    return bsv_hp_value * 3; // TODO figure out a better algorithim
}
