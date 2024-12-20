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

const vector<McstNode>& McstNode::get_childs() const {
    return childs;
}

vector<McstNode>& McstNode::get_childs_to_modify() {
    return childs;
}

const int& McstNode::get_visit_count() const {
    return visit_count;
}

const int& McstNode::get_score() const {
    return score;
}

const char& McstNode::get_current_turn() const {
    return current_turn;
}

const int& McstNode::get_id() const {
    return node_id;
}

const float& McstNode::get_ucb_score() const {
    return UCB_score;
}

bool McstNode::is_expanded() const {
    return !childs.empty();
}

void McstNode::add_child(const McstNode& new_child) {
    childs.push_back(new_child);
}

float McstNode::calculate_ucb(int total_visits, float exploration_constant) const {
    if (visit_count == 0) {
        return numeric_limits<float>::infinity(); // Return infinity if the node hasn't been visited yet
    }
    if (total_visits == 0) {
        return numeric_limits<float>::infinity();
    }
    float exploitation = static_cast<float>(score) / visit_count;

    float exploration = exploration_constant * sqrt(log(total_visits) / visit_count);
    //cout << "Exploitation: " << exploitation 
    // << ", Exploration: " << exploration 
    // << ", UCB: " << (exploitation + exploration) << endl;

    return exploitation + exploration;
}


void McstNode::set_ucb_score(float score) {
    UCB_score = score;
}


void McstNode::set_score(int new_score) {
    score = new_score;
}

void McstNode::set_visit_count(int visit) {
    visit_count = visit;
}
