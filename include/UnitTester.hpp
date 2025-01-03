#ifndef UNITTESTER_H
#define UNITTESTER_H
#pragma once

#include "Board.hpp"

using namespace std;

/**
 * @class UnitTester
 * @brief A utility class for testing the functionalities of the Board mechanics.
 *
 * This class is intended to be used in a development environment to verify the integrity 
 * of game logic and algorithms during implementation.
 */
class UnitTester {
public:
    UnitTester();
    // Test for Board functions
    void test_check_game_state(); // Method to test check_game_state
    void test_make_move();
    void test_wall_conditions_update_board();
    void test_middle_conditions_update_board();
    // Test for MCST functions
    void test_roll_out();
    void test_expand();

private:
    void assert_equal(const string& expected, const string& actual, const string& message);
    void assert_true(bool condition, const string& message);
};

#endif
