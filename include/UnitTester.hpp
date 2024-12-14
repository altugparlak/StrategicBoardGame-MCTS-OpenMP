#ifndef UNITTESTER_H
#define UNITTESTER_H
#pragma once

#include "Board.hpp"

using namespace std;

class UnitTester {
public:
    UnitTester();
    void test_check_game_state(); // Method to test check_game_state
    void test_make_move();
    void test_update_board();

private:
    void assert_equal(const std::string& expected, const std::string& actual, const std::string& message);
    void assert_true(bool condition, const std::string& message);
};

#endif
