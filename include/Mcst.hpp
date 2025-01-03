#ifndef MCST_H
#define MCST_H

#include <vector>
#include <tuple>
#include <random>
#include "McstNode.hpp"
#include "omp.h"

class Mcst {
public:
    /**
     * @brief Constructs the Mcst object and initializes the root node.
     * @param board The initial game board to start the MCTS algorithm.
     */
    Mcst(const Board& board);

    /**
     * @brief Executes the MCTS algorithm with a squential search 
     * to determine the best move.
     * @param iterations The number of iterations for the MCTS simulation.
     * @return The board state (best board) after applying the best move.
     */
    Board play_best_move(int iterations = 1);

    /**
     * @brief Executes the MCTS algorithm in parallel using OpenMP 
     * to determine the best move.
     * Root parallelization is utilized.
     * @param iterations The number of iterations for the MCTS simulation.
     * @return The board state (best board) after applying the best move.
     */
    Board play_best_move_parallel(int iterations = 1);

private:
    McstNode root_node;

    /**
     * @brief Selects the best child node based on the UCB score.
     * @param root_node The current root node to select a child from.
     * @return A pointer to the selected child node.
     */
    McstNode* select_child_node(McstNode& root_node) const;

    /**
     * @brief Retrieves valid moves for the current turn on the given board.
     * @param board The board to analyze for valid moves.
     * @param current_turn The current player's turn.
     * @return A vector of valid move coordinates.
     */
    vector<tuple<int, int, int, int>> get_valid_moves(const Board& board, char current_turn) const;
   
   /**
     * @brief Expands the given node by generating its child nodes based on possible moves.
     * @param node The node to expand.
     */
    void expand(McstNode& node);

    /**
     * @brief Simulates a random play from the given node until the game ends.
     * @param node The node from which to start the simulation.
     * @return The score to be added to the node after the simulation.
     */
    int roll_out(McstNode& node) const;

    /**
     * @brief Selects a random move from a list of valid moves.
     * @param moves The list of valid moves to select from.
     * @return A tuple representing the randomly chosen move.
     */
    tuple<int, int, int, int> random_choice(const vector<tuple<int, int, int, int>>& moves) const;
    
};

#endif
