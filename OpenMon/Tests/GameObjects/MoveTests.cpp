#include "../catch.hpp"
#include "../../Classes/GameObjects/Mon.hpp"

using namespace OpenMonObjects;

TEST_CASE("Test Move Generation","[Move, GameObjects]")
{
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    MonType test_type(1, "normal", efficacy);
    Move test_move_a("test_move", test_type, 100, 50, 15, 25, 0, 1); // priority, status effect, and no secondary effect
    Move test_move_b("test_move", test_type, 100, 50, 15, 0, 25, 0); // no priority, no status effect, and secondary effect
    
    SECTION("Priority Flag") {
        REQUIRE(test_move_a.priority_flag() == true);
    }
    
    SECTION("No Prority Flag") {
        REQUIRE(test_move_b.priority_flag() == false);
    }
    
    SECTION("No Status Effect") {
        REQUIRE(test_move_b.has_status_effect() == false);
    }
    
    SECTION("Has Status Effect") {
        REQUIRE(test_move_a.has_status_effect() == true);
    }
    
    SECTION("No Secondary Effect") {
        REQUIRE(test_move_a.has_secondary_effect() == false);
    }
    
    SECTION("Has Secondary Effect") {
        REQUIRE(test_move_b.has_secondary_effect() == true);
    }
    
    SECTION("Test Other Object Variables") {
        REQUIRE(test_move_a.max_pp() == 15);
        REQUIRE(test_move_a.current_pp() == 15);
    }
}

TEST_CASE("Test PP Restore","[Move, GameObjects]")
{
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    MonType test_type(1, "normal", efficacy);
    Move test_move("test_move", test_type, 100, 50, 15, 0, 0, 0);
    
    SECTION("Test PP partial restore doesn't set to max.") {
        test_move.current_pp(5);
        test_move.RestorePP(5);
        REQUIRE(test_move.current_pp() != test_move.max_pp());
        REQUIRE(test_move.current_pp() == 10);
    }
    
    SECTION("Test PP max restore.") {
        test_move.current_pp(5);
        test_move.RestorePP(20);
        REQUIRE(test_move.current_pp() == test_move.max_pp());
    }
}

TEST_CASE("Test Move Used Effects", "[Move, GameObjects]")
{
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    MonType test_type(1, "normal", efficacy);
    Move test_move("test_move", test_type, 100, 50, 15, 0, 0, 0);
    
    SECTION("Used Move") {
        test_move.UseMove();
        REQUIRE(test_move.current_pp() == 14);
    }
}

TEST_CASE("Test PP is Empty Flag", "[Move, GameObjects]")
{
    std::map<int, int> efficacy = {
        {1, 100},
        {2, 200}
    };
    MonType test_type(1, "normal", efficacy);
    Move test_move("test_move", test_type, 100, 50, 15, 0, 0, 0);
    
    SECTION("PP is Empty") {
        test_move.current_pp(0);
        REQUIRE(test_move.IsPPEmpty() == true);
    }
    
    SECTION("PP is Not Empty") {
        REQUIRE(test_move.IsPPEmpty() == false);
    }
}
