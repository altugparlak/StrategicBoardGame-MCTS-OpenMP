#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define BOARD_SIZE 7
#define PLAYER_SHAPE 'A'
#define AI_SHAPE 'O'
#define DRAW "DRAW"
#define MOVE_COUNT_FOR_MANY_PIECE 2
#define MOVE_COUNT_FOR_ONE_PIECE 1

using namespace std;

class Board {
public:
    Board();
    Board(const Board& board); // Copy constructor
    
    void make_move(int start_row, int start_col, int end_row, int end_col);
    void print_board();
    
    string get_winner() const;
    char get_current_turn() const;
    int get_move_count() const;
    int get_total_move_count() const;
    
private:
    char positions[BOARD_SIZE][BOARD_SIZE];
    char player_1 = PLAYER_SHAPE;
    char player_2 = AI_SHAPE;
    string winner = DRAW;
    char empty_square = '.';
    char current_turn;
    int move_count;
    int total_move_count;

    void init_board();
    void update_the_board();
    void check_wall_conditions();
    void check_middle_conditions();
    int count_pieces(char player);
    bool check_game_state();
};

#endif