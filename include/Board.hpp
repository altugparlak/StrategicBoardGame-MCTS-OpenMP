#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "UnitTester.hpp"

#define BOARD_SIZE 7
#define PLAYER_SHAPE 'O'
#define AI_SHAPE 'A'
#define OUT_OF_BOARD 'N'
#define DRAW "DRAW"
#define TOTAL_MOVE 50
#define MOVE_COUNT_FOR_MANY_PIECE 2
#define MOVE_COUNT_FOR_ONE_PIECE 1

using namespace std;

class Board {
public:
    Board(bool debug = false);
    Board(const Board& board); // Copy constructor
    
    Board make_move(int start_row, int start_col, int end_row, int end_col);
    void print_board();
    void log(const string& message);

    const string& get_winner() const;
    char get_current_turn() const;
    int get_move_count() const;
    int get_total_move_count() const;
    bool check_game_state();
    vector<vector<char>> get_positions() const;
    char get_piece(int x, int y) const;

private:
    char positions[BOARD_SIZE][BOARD_SIZE];
    char player_1 = AI_SHAPE;
    char player_2 = PLAYER_SHAPE;
    string winner = DRAW;
    char empty_square = '.';
    char current_turn;
    int move_count;
    int total_move_count;
    static bool debug;
    friend class UnitTester;

    void init_board();
    void update_the_board();
    void check_wall_conditions(vector<pair<int, int>>& to_removed);
    void check_middle_conditions(vector<pair<int, int>>& to_removed);
    int count_pieces(char player);

};

#endif
