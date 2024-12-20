#include "Mcst.hpp"

Mcst::Mcst(const Board& board) 
    : root_node(board, 0, board.get_current_turn()) {

        expand(root_node);
        //McstNode node = select_child_node(root_node);
        //node.get_board().print_board();
    }

Board Mcst::play_best_move_parallel(int iterations) {
    vector<McstNode>& root_childs = root_node.get_childs_to_modify();

    int total_visit = 0;
    omp_set_num_threads(10);
    #pragma omp parallel for schedule(dynamic) shared(total_visit)
    for (int i = 0; i < root_childs.size(); i++)
    {
        for (int j = 0; j < iterations; j++) {
            McstNode* tempNode = &root_childs[i];
            vector<McstNode*> searchPath = {tempNode};

            while (tempNode->is_expanded()) {
                // Select a child based on UCBScore
                tempNode = select_child_node(*tempNode);
                searchPath.push_back(tempNode);

                if (tempNode->get_visit_count() > 0) {
                    expand(*tempNode);
                }
            }

            int score_to_be_added = roll_out(*tempNode);

            for (auto node : searchPath) {
                int updated_score = node->get_score() + score_to_be_added;
                node->set_score(updated_score);
                //node->set_score(node->get_score() + score_to_be_added);
                node->set_visit_count(node->get_visit_count() + 1);
            }
        }
    }

    return select_child_node(root_node)->get_board();
}

Board Mcst::play_best_move(int iterations) {
    for (int i = 0; i < iterations; i++) {
        McstNode* tempNode = &root_node;
        vector<McstNode*> searchPath = {tempNode};

        while (tempNode->is_expanded()) {
            // Select a child based on UCBScore
            tempNode = select_child_node(*tempNode);
            searchPath.push_back(tempNode);

            if (tempNode->get_visit_count() > 0) {
                expand(*tempNode);
            }
        }

        int score_to_be_added = roll_out(*tempNode);

        for (auto node : searchPath) {
            int updated_score = node->get_score() + score_to_be_added;
            node->set_score(updated_score);
            //node->set_score(node->get_score() + score_to_be_added);
            node->set_visit_count(node->get_visit_count() + 1);
        }
    }

    return select_child_node(root_node)->get_board();
}

McstNode* Mcst::select_child_node(McstNode& root_node) const {
    vector<McstNode>& root_childs = root_node.get_childs_to_modify();

    if (root_childs.empty()) {
        throw runtime_error("No child nodes available for selection");
    }

    //int total_visits = root_node.get_visit_count();
    /*
    for (int i = 0; i < root_childs.size(); i++) {
        total_visits += root_childs[i].get_visit_count();
    }
    */
    int total_visits = 0;
    for (const auto& child : root_childs) {
        total_visits += child.get_visit_count();
    }

    cout << "Total visits: " << total_visits << endl;

    McstNode* best_child = nullptr;
    float best_score = -numeric_limits<float>::infinity();

    for (auto& child : root_childs) {
        float ucb_score = child.calculate_ucb(total_visits, 1.41);
        child.set_ucb_score(ucb_score);

        if (ucb_score > best_score) {
            best_score = ucb_score;
            best_child = &child;
        }
    }

    for (int i = 0; i < root_node.get_childs().size(); i++)
    {
        cout << "Child-" << i << " has UCB_score: " << root_node.get_childs()[i].get_ucb_score() <<
        " -- " << "has score: " << root_node.get_childs()[i].get_score() <<
        " -- " << "has visit count: " << root_node.get_childs()[i].get_visit_count() << endl;
    }

    cout << "Choosen child nodes UCB_score = " << best_child->get_ucb_score() << endl;
    if (!best_child) {
        throw runtime_error("Failed to select a child node");
    }

    return best_child;
}

void Mcst::expand(McstNode& node) {
    if(node.is_expanded())
        return;
    Board board = node.get_board();
    vector<tuple<int, int, int, int>> possible_move_coordinates;
    possible_move_coordinates = get_valid_moves(board, node.get_current_turn());

    int id = node.get_id();
    for (int i = 0; i < possible_move_coordinates.size(); i++)
    {
        tuple<int, int, int, int> move = possible_move_coordinates[i];
        int start_x = get<0>(move);
        int start_y = get<1>(move);
        int end_x = get<2>(move);
        int end_y = get<3>(move);

        Board new_board = board.make_move(start_x, start_y, end_x, end_y);
        McstNode new_node = McstNode(new_board, id, new_board.get_current_turn());
        node.add_child(new_node);
        //cnew_board.print_board();
        id++;
    }
    
}

int Mcst::roll_out(McstNode& node) const {
    Board simulation_board = node.get_board();

    while (!simulation_board.check_game_state()) {
        auto valid_moves = get_valid_moves(simulation_board, simulation_board.get_current_turn());
        if (valid_moves.empty()) {
            break;
        }

        auto random_move = random_choice(valid_moves);
        int start_x = get<0>(random_move);
        int start_y = get<1>(random_move);
        int end_x = get<2>(random_move);
        int end_y = get<3>(random_move);

        simulation_board = simulation_board.make_move(start_x, start_y, end_x, end_y);
    }
    //simulation_board.print_board();
    if (simulation_board.get_winner() == string(1, PLAYER_SHAPE)) {
        return -1;
    } else if (simulation_board.get_winner() == string(1, AI_SHAPE)) {
        return 1;
    } else {
        return 0;
    }
}

vector<tuple<int, int, int, int>> Mcst::get_valid_moves(const Board& board, char current_turn) const {
    vector<tuple<int, int, int, int>> valid_moves;
    vector<vector<char>> positions = board.get_positions();

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (positions[i][j] == current_turn) {
                vector<tuple<int, int>> moves = {
                    {i, j - 1}, // Left
                    {i, j + 1}, // Right
                    {i - 1, j}, // Up
                    {i + 1, j}  // Down
                };

                for (const auto& move : moves) {
                    int move_x = get<0>(move);
                    int move_y = get<1>(move);
                    char target_piece = board.get_piece(move_x, move_y);
                    if (target_piece != OUT_OF_BOARD && target_piece != PLAYER_SHAPE &&
                        target_piece != AI_SHAPE) {
                        valid_moves.emplace_back(i, j, move_x, move_y);
                    }
                }
            }
        }
    }

    return valid_moves;
}

std::tuple<int, int, int, int> Mcst::random_choice(const vector<tuple<int, int, int, int>>& moves) const {
    int random_choice = rand() % moves.size();
    return moves[random_choice];
}
