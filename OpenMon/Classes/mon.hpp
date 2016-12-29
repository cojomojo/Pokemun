#ifndef mon_hpp
#define mon_hpp

#include "types.hpp"
#include "StatusConditions.hpp"
#include<string>
#include<vector>
using std::string;
using std::vector;


class Mon {
public:
    Mon(string name, int lvl, int b_hp, int b_atk, int b_def,
        int b_spcl_atk, int b_spcl_def, int b_speed,
        Type type_1, Type type_2);
    
    int GetCurrentHp();
    void SetCurrentHp(int value);
    void RestoreHp(int value);
    void TakeDamage(int attackDamage);
    int GetLevel();
    int GetSpeed();
    bool IsFainted();
    bool IsConfused();
    void SetFainted(bool faint);
    string GetName();
    Status GetStatusCondition();
    void ResetStatsToDefault();
    
private:
    int ScaleHp(int bsv_hp_value);
    
    // Base stats (BSVs)
    // https://github.com/PokeAPI/pokeapi/blob/master/data/v2/csv/pokemon_stats.csv
    // Format of CSV is
    // 1: Base HP
    // 2: Base Attack
    // 3: Base Defense
    // 4: Base Special Attack
    // 5: Base Special Defense
    // 6: Base Speed
    
    int base_hp_value;
    int base_attack;
    int base_defense;
    int base_special_attk;
    int base_special_def;
    int base_speed;
    
    // Moves can lower the Stat values of the Mon
    int current_attack;
    int current_defense;
    int current_special_attk;
    int current_special_def;
    int current_speed;
    //int current_accuracy; // TODO mon needs an accuracy stat as well as the move accuracy
    
    // Pokemun attributes
    string mon_name;
    int level;
    int max_hp;
    int current_hp;
    Type primary_type;
    Type secondary_type;
    
    // Status flags
    bool confused;
    bool fainted;
    Status status_cond;
    
    // TODO figure out how to do weaknesses based on type(s) issue will be for edge cases where one type for the mon is weak to
    // some type but the other resists it (think a fire and ground type Mon being neutral to ice moves)
    vector<Type> type_weaknesses;
    vector<Type> type_strengths;
    vector<Type> type_resistances;
    
    //vector<Move> move_set;
    
};

#endif /* mon_hpp */
