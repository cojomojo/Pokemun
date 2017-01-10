#include "AppDelegate.h"
#include "Scenes/HelloWorldScene.h"
#include "Data/DataAccess.hpp"

#include "GameObjects/Mon.hpp"

using namespace OpenMonObjects;
using namespace cocos2d;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    // Begin DataAccess Examples
	try {
        
		OpenMonData::DataAccess db;
		db.OpenConnection();

		std::string sql_statement = "SELECT * FROM mon LIMIT 5";
		OpenMonData::SqlResultList results = db.QueryToSqlResultList(sql_statement);
		auto id = results.front().at("id")->GetValue<int>();
		auto identifier = results.front().at("identifier")->GetValue<std::string>();

		db.CloseConnection();
	} catch(OpenMonData::DataAccessException ex) {
		
	}
    // End DataAccess Examples

    // GameObjects examples/tests
    try {
        
        RunObjectTests();  // TODO more testing
        
    }  catch (...) {

    }
    // End GameObjects examples/tests

    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("OpenMon", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("OpenMon");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


// TODO would be better if the tests were each their own seperate function called
// by this master function. Would help with variable naming issues as they would be
// in seperate function scopes, because these names are trash AF right now
void AppDelegate::RunObjectTests()
{
    // MonType test_type(1, "normal");
    // MonType test_secondary_type(0, "none");
    
    // // Test constants for the move constructors
    // int const ACCURACY = 100;
    // int const POWER = 50;
    // int const PP = 15;
    
    
    // /******************************
    //  * Move Object Tests
    //  ******************************/
    
    // // Test true priority flag
    // Move test_priority_true("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // bool actual_true_priority = test_priority_true.priority_flag();
    // bool expected_true_priority = true;
    // assert(actual_true_priority == expected_true_priority);
    
    // // Test false priority flag
    // Move test_priority_false("testMove", test_type, ACCURACY, POWER, PP, 0, 0, false);
    // bool actual_false_priority = test_priority_false.priority_flag();
    // bool expected_false_priority = false;
    // assert(actual_false_priority == expected_false_priority);
    
    // // Test that the max pp is set correctly at creation of the object
    // Move test_max_pp("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // int actual_max_pp = test_max_pp.max_pp();
    // int expected_max_pp = 15;
    // assert(actual_max_pp == expected_max_pp);
    
    // // Test PP set from 15 to 10
    // Move test_pp_set("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // int set_pp = 10;
    // int expected_pp = 10;
    // test_pp_set.current_pp(set_pp);
    // int actual_pp = test_pp_set.current_pp();
    // assert(actual_pp == expected_pp);
    
    // // Test that a PP restore over max sets to max
    // Move test_pp_max_restore("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // int added_pp_value = 6;
    // int expected_pp_value = 15;
    // int set_value = 10;
    // test_pp_max_restore.current_pp(set_value);
    // test_pp_max_restore.RestorePP(added_pp_value);
    // int actual_pp_value = test_pp_max_restore.current_pp();
    // assert(actual_pp_value == expected_pp_value);
    
    // // Test that a PP partial restore not to the max adds the value and the current pp
    // Move test_pp_partial_restore("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // test_pp_partial_restore.current_pp(6);
    // int pp_value_added = 5;
    // int new_pp_expected = 11;
    // test_pp_partial_restore.RestorePP(pp_value_added);
    // int current_pp_value = test_pp_partial_restore.current_pp();
    // assert(current_pp_value == new_pp_expected);
    
    // // Test Secondary Effect with 0% input (should be false)
    // Move test_no_secondary_effect("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // bool actual_no_secondary = test_no_secondary_effect.has_secondary_effect();
    // bool expected_no_secondary = false;
    // assert(actual_no_secondary == expected_no_secondary);
    
    // // Test Status Effect with 0% input (should be false)
    // Move test_no_status_effect("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // bool actual_no_status = test_no_status_effect.has_status_effect();
    // bool expected_no_status = false;
    // assert(actual_no_status == expected_no_status);
    
    // // Test Status Effect with 25% input (should be true)
    // Move test_status_effect("testMove", test_type, ACCURACY, POWER, PP, 25, 0, true);
    // bool actual_status = test_status_effect.has_status_effect();
    // bool expected_status = true;
    // assert(actual_status == expected_status);
    
    // // Test Secondary Effect with 25% input (should be true)
    // Move test_secondary_effect("testMove", test_type, ACCURACY, POWER, PP, 0, 25, true);
    // bool actual_secondary = test_secondary_effect.has_secondary_effect();
    // bool expected_secondary = true;
    // assert(actual_secondary == expected_secondary);
    
    // // Test Move Used Effects
    // Move test_move_used("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // test_move_used.UseMove();
    // int actual_remaining_pp = test_move_used.current_pp();
    // int expected_remaining_pp = 14;
    // assert(expected_remaining_pp == actual_remaining_pp);
    
    // // Test that the pp is empty
    // Move test_pp_empty("testMove", test_type, ACCURACY, POWER, PP, 0, 0, true);
    // int set_empty = 0;
    // test_pp_empty.current_pp(set_empty);
    // bool actual_pp_is_empty = test_pp_empty.IsPPEmpty();
    // bool expected_pp_is_empty = true;
    // assert(expected_pp_is_empty == actual_pp_is_empty);
    
    
    // /******************************
    // * Mon Object Tests
    // ******************************/
    
    // int const TEST_BSV_VALUE = 30;
    
    // // TODO I think there is a way setting BSVs is supposed to be done and this isn't it
    // BSVs test_bsvs;
    // test_bsvs.hp = TEST_BSV_VALUE;
    // test_bsvs.attack = TEST_BSV_VALUE;
    // test_bsvs.defense = TEST_BSV_VALUE;
    // test_bsvs.speed = TEST_BSV_VALUE;
    // test_bsvs.special_attack = TEST_BSV_VALUE;
    // test_bsvs.special_defense = TEST_BSV_VALUE;
    
    // // Test that the max hp is set correctly at creation of the object
    // Mon test_mon_max_hp("testMon", test_bsvs, test_type, test_secondary_type);
    // int actual_max_hp = test_mon_max_hp.max_hp();
    // int expected_max_hp = 90;
    // assert(expected_max_hp == actual_max_hp);
    
    // // Test HP set from 90 to 50
    // Mon test_hp_set("testMon", test_bsvs, test_type, test_secondary_type);
    // int set_hp = 50;
    // int expected_hp = 50;
    // test_hp_set.current_hp(set_hp);
    // int actual_current_hp = test_hp_set.current_hp();
    // assert(expected_hp == actual_current_hp);
    
    // // Test that a HP restore over max sets to max
    // Mon test_hp_max_restore("testMon", test_bsvs, test_type, test_secondary_type);
    // int added_hp_value = 50;
    // int expected_hp_value = 90;
    // int set_hp_value = 60;
    // test_hp_max_restore.current_hp(set_hp_value);
    // test_hp_max_restore.RestoreHp(added_hp_value);
    // int actual_hp_value = test_hp_max_restore.current_hp();
    // assert(actual_hp_value == expected_hp_value);
    
    // // Test that a HP partial restore not to the max adds the value and the current HP
    // Mon test_hp_partial_restore("testMon", test_bsvs, test_type, test_secondary_type);
    // int added_hp_partial = 25;
    // int expected_value_hp = 55;
    // int set_hp_value_partial = 30;
    // test_hp_partial_restore.current_hp(set_hp_value_partial);
    // test_hp_partial_restore.RestoreHp(added_hp_partial);
    // int actual_hp_value_partial = test_hp_partial_restore.current_hp();
    // assert(actual_hp_value_partial == expected_value_hp);
    
    // // Test that the mon can take damage
    // Mon test_damage("testMon", test_bsvs, test_type, test_secondary_type);
    // int damage = 50;
    // int expected_remaining_hp = 40;
    // test_damage.TakeDamage(damage);
    // int actual_remaining_hp = test_damage.current_hp();
    // assert(expected_remaining_hp == actual_remaining_hp);
    
    
    // /******************************
    //  * Trainer Object Tests
    //  ******************************/
    
    
}
