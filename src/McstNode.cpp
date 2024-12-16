#include "McstNode.hpp"

McstNode::McstNode(const Board& board, int node_id, char current_turn)
    : board(board),
      node_id(node_id),
      current_turn(current_turn),
      score(0),
      UCB_score(0.0),
      visit_count(0) {
}

Board McstNode::get_board() const {
    return board;
}

bool McstNode::is_expanded() const {
    return !childs.empty();
}

void McstNode::add_child(const McstNode& new_child) {
    childs.push_back(new_child);
}

float McstNode::calculate_ucb(int total_parent_visits, float exploration_param) const {
    if (visit_count == 0) {
        return numeric_limits<float>::infinity();
    }
    float exploitation = static_cast<float>(score) / visit_count;
    float exploration = exploration_param * sqrt(log(total_parent_visits) / visit_count);
    return exploitation + exploration;
}
