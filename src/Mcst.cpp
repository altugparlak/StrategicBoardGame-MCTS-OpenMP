#include "Mcst.hpp"

Mcst::Mcst(const Board& board) 
    : root_node(board, 0, board.get_current_turn()) {}

