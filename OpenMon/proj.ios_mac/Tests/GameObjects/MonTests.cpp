#include "../catch.hpp"
#include "../../Classes/GameObjects/Mon.hpp"

using namespace OpenMonObjects;

TEST_CASE("Example of Mon construction.", "[Mon, GameObjects, Examples]")
{
    BSVs base_stats(
                    35, // hp
                    50, // attack
                    50, // defense
                    50, // speed
                    20, // special_attack
                    20  // special_defense
                    );
    
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    
    MonType type1(1, "normal", efficacy);
    MonType type2(2, "electric", efficacy);
    
    SECTION("It constructs with one type and only base stat values.") {
        Mon mon1("PikaTest", base_stats, type1);
        
        REQUIRE(mon1.primary_type() == 1);
        REQUIRE(!mon1.has_secondary_type());
        REQUIRE(mon1.secondary_type() == 0);
        REQUIRE(mon1.max_hp() == 105);
        REQUIRE(mon1.current_hp() == mon1.max_hp());
    }
    
    SECTION("It constructs with two types and only base stat values.") {
        Mon mon1("PikaTest", base_stats, type1, std::make_unique<MonType>(type2));
        
        REQUIRE(mon1.primary_type() == 1);
        REQUIRE(mon1.has_secondary_type());
        REQUIRE(mon1.secondary_type() == 2);
        REQUIRE(mon1.max_hp() == 105);
        REQUIRE(mon1.current_hp() == mon1.max_hp());
    }
}

TEST_CASE("It does take damage.", "[Mon, GameObjects]")
{
    BSVs base_stats(
                    35, // hp
                    50, // attack
                    50, // defense
                    50, // speed
                    20, // special_attack
                    20  // special_defense
                    );
    
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    
    MonType type1(1, "normal", efficacy);
    Mon test_mon("test", base_stats, type1);
    
    SECTION("It takes damage that does not drain hp completely.") {
        test_mon.TakeDamage(100);
        REQUIRE(test_mon.fainted() == false);
        REQUIRE(test_mon.current_hp() == 5);
    }
    
    SECTION("It faints when damage causes hp to be drained.") {
        test_mon.TakeDamage(105);
        REQUIRE(test_mon.fainted() == true);
    }
}

TEST_CASE("Test HP restore.", "[Mon, GameObjects]")
{
    BSVs base_stats(
                    35, // hp
                    50, // attack
                    50, // defense
                    50, // speed
                    20, // special_attack
                    20  // special_defense
                    );
    
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    
    MonType type1(1, "normal", efficacy);
    Mon test_mon("test", base_stats, type1);
    
    SECTION("Test HP partial restore doesn't set to max.") {
        test_mon.current_hp(25);
        test_mon.RestoreHp(50);
        REQUIRE(test_mon.current_hp() != test_mon.max_hp());
        REQUIRE(test_mon.current_hp() == 75);
    }
    
    SECTION("Test HP max restore.") {
        test_mon.current_hp(25);
        test_mon.RestoreHp(200);
        REQUIRE(test_mon.current_hp() == test_mon.max_hp());
    }
}

TEST_CASE("Test Revive", "[Mon, GameObjects]")
{
    BSVs base_stats(
                    35, // hp
                    50, // attack
                    50, // defense
                    50, // speed
                    20, // special_attack
                    20  // special_defense
                    );
    
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    
    MonType type1(1, "normal", efficacy);
    Mon test_mon("test", base_stats, type1);
    
    SECTION("With status condition") {
        // TODO set the status condition to something and test the reset on revive
        test_mon.TakeDamage(105);
        test_mon.Revive();
        REQUIRE(test_mon.fainted() == false);
    }
    
    SECTION("With confused condition") {
        test_mon.confused(true);
        test_mon.TakeDamage(105);
        test_mon.Revive();
        REQUIRE(test_mon.confused() == false);
        REQUIRE(test_mon.fainted() == false);
    }
    
    SECTION("With no status condition") {
        test_mon.TakeDamage(105);
        test_mon.Revive();
        REQUIRE(test_mon.fainted() == false);
    }
}
