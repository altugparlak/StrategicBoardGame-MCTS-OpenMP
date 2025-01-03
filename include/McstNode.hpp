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
    /**
     * @brief Constructs an McstNode with the specified board, ID, and current turn. 
     * Initializes the score, UCB score, and visit count to default values.
     * 
     * @param board The current state of the game board.
     * @param node_id The unique identifier of the node.
     * @param current_turn The character representing the current player's turn.
     */
    McstNode(const Board& board, int node_id, char current_turn);

    /**
    * @brief If the node already is expanded return true.
    */
    bool is_expanded() const;
    void add_child(const McstNode& new_child);

    /**
     * @brief Calculates the UCB score for the node based on visit count and total visits.
     * 
     * @param total_visits The total number of visits for the parent node.
     * @param exploration_constant The constant used to balance exploration and exploitation.
     * @return The calculated UCB score. Returns infinity if the node or total visits is zero.
     */
    float calculate_ucb(int total_parent_visits, float exploration_param = 1.41) const;
    Board get_board() const; // Return copy
    const vector<McstNode>& get_childs() const;
    vector<McstNode>& get_childs_to_modify(); // Non-const version
    const int& get_visit_count() const;
    const char& get_current_turn() const;
    const int& get_id() const;
    const float& get_ucb_score() const;
    const int& get_score() const;
    void set_ucb_score(float score);
    void set_score(int score);
    void set_visit_count(int visit);

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
