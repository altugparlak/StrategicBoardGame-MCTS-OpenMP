#ifndef MCST_H
#define MCST_H

#include <vector>
#include <tuple>
#include <random>
#include "McstNode.hpp"
#include "omp.h"

class Mcst {
public:
    Mcst(const Board& board);

    Board play_best_move(int iterations = 1);
    Board play_best_move_parallel(int iterations = 1);

private:
    McstNode root_node;

    McstNode* select_child_node(McstNode& root_node) const;
    vector<tuple<int, int, int, int>> get_valid_moves(const Board& board, char current_turn) const;
    void expand(McstNode& node);
    int roll_out(McstNode& node) const;
    tuple<int, int, int, int> random_choice(const vector<tuple<int, int, int, int>>& moves) const;
    
};

#endif
