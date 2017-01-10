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
        20  // specifal_defense
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
    }

    SECTION("It constructs with two types and only base stat values.") {
        Mon mon1("PikaTest", base_stats, type1, std::make_unique<MonType>(type2));

        REQUIRE(mon1.primary_type() == 1);
        REQUIRE(mon1.has_secondary_type());
        REQUIRE(mon1.secondary_type() == 2);
    }
}

TEST_CASE("It does take damage.", "[Mon, GameObjects]") 
{
    SECTION("It takes damage that does not drain hp completely.") {

    }

    SECTION("It faints when damage causes hp to be drained.") {

    }
}