#ifndef UNITTESTER_H
#define UNITTESTER_H
#pragma once

#include "Board.hpp"

using namespace std;

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
    void assert_equal(const std::string& expected, const std::string& actual, const std::string& message);
    void assert_true(bool condition, const std::string& message);
};

#endif
