#ifndef MCSTNODE_H
#define MCSTNODE_H
#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "Board.hpp"

using namespace std;

class McstNode {
public:
    McstNode(const Board& board, int node_id, char current_turn);
    bool is_expanded() const;
    void add_child(const McstNode& new_child);
    float calculate_ucb(int total_parent_visits, float exploration_param = 1.41) const;
    Board get_board() const; // Return copy

private:
    int node_id;
    char current_turn;
    float UCB_score;
    int score;
    int visit_count;
    Board board;
    vector<McstNode> childs;

};


#endif
