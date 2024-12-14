#include "Board.hpp"

Board::Board() {
    current_turn = PLAYER_SHAPE;
    move_count = 0;
    total_move_count = 0;
    init_board();
}

Board::Board(const Board& board) {
    // Copy the entire Board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            positions[i][j] = board.positions[i][j];
        }
    }
    player_1 = board.player_1;
    player_2 = board.player_2;
    winner = board.winner;
    empty_square = board.empty_square;
    current_turn = board.current_turn;
    move_count = board.move_count;
    total_move_count = board.total_move_count;
}

string Board::get_winner() const {
    return winner;
}

char Board::get_current_turn() const {
    return current_turn;
}

int Board::get_move_count() const {
    return move_count;
}

int Board::get_total_move_count() const {
    return total_move_count;
}

char Board::get_piece(int row, int col) {
    return positions[row][col];
}

void Board::init_board() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            positions[row][col] = empty_square;
        }
    }
    positions[0][0] = player_1;
    positions[2][0] = player_1;
    positions[4][6] = player_1;
    positions[6][6] = player_1;
    positions[4][0] = player_2;
    positions[6][0] = player_2;
    positions[0][6] = player_2;
    positions[2][6] = player_2;
}

Board Board::make_move(int start_row, int start_col, int end_row, int end_col) {
    if (positions[start_row][start_col] != current_turn) {
        throw invalid_argument("Invalid move: You can only move your own pieces.");
    }
    
    if (positions[end_row][end_col] != empty_square) {
        throw std::invalid_argument("Invalid move: Destination square is not empty.");
    }

    int row_diff = abs(start_row - end_row);
    int col_diff = abs(start_col - end_col);
    if ((row_diff != 1 && col_diff != 1) || (row_diff == 1 && col_diff == 1)) {
        throw std::invalid_argument("Invalid move: You can only move one square up, down, left, or right.");
    }

    Board new_board(*this); // Create a deep copy of the board
    new_board.positions[start_row][start_col] = empty_square;
    new_board.positions[end_row][end_col] = current_turn;

    new_board.update_the_board();

    new_board.move_count++;
    new_board.total_move_count = total_move_count + 1;
    
    if (new_board.count_pieces(new_board.current_turn) > MOVE_COUNT_FOR_ONE_PIECE && new_board.move_count < MOVE_COUNT_FOR_MANY_PIECE) {
        std::cout << new_board.current_turn << " can make another move with a different piece." << std::endl;
    } else {
        new_board.current_turn = (new_board.current_turn == player_1) ? player_2 : player_1;
        new_board.move_count = 0;
    }
    return new_board;
}

void Board::update_the_board() {
    vector<pair<int, int>> to_removed;
    check_wall_conditions(to_removed);
    check_middle_conditions(to_removed);

    for (int i = 0; i < to_removed.size(); i++)
    {
        //cout << "Piece location: " << to_removed[i].first << ":" << to_removed[i].second << endl;
        positions[to_removed[i].first][to_removed[i].second] = empty_square;
    }
    
}

void Board::check_wall_conditions(vector<pair<int, int>>& to_removed) {
    // Left Wall
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (positions[i][0] != empty_square) {
            for (int j = 0; j < BOARD_SIZE - 1; j++) {
                char next_piece = positions[i][j + 1];
                if (next_piece != positions[i][0] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(i, 0));
                }
                else if (next_piece == positions[i][0]) {
                    to_removed.push_back(make_pair(i, j + 1));
                    continue;
                }
                else if (next_piece == empty_square) {
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }

    // Right Wall
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (positions[i][BOARD_SIZE - 1] != empty_square) {
            for (int j = BOARD_SIZE - 1; j > 0; j--) {
                char next_piece = positions[i][j - 1];
                if (next_piece != positions[i][BOARD_SIZE - 1] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(i, BOARD_SIZE - 1));
                }
                else if (next_piece == positions[i][BOARD_SIZE - 1]) {
                    to_removed.push_back(make_pair(i, j - 1));
                    continue;
                }
                else if (next_piece == empty_square) {
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }

    // Top Wall
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (positions[0][j] != empty_square) {
            for (int i = 0; i < BOARD_SIZE - 1; i++) {
                char next_piece = positions[i + 1][j];
                if (next_piece != positions[0][j] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(0, j));
                }
                else if (next_piece == positions[0][j]) {
                    to_removed.push_back(make_pair(i + 1, j));
                    continue;
                }
                else if (next_piece == empty_square) {
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }

    // Bottom Wall
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (positions[BOARD_SIZE - 1][j] != empty_square) {
            for (int i = BOARD_SIZE - 1; i > 0; i--) {
                char next_piece = positions[i - 1][j];
                if (next_piece != positions[BOARD_SIZE - 1][j] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(BOARD_SIZE - 1, j));
                }
                else if (next_piece == positions[BOARD_SIZE - 1][j]) {
                    to_removed.push_back(make_pair(i - 1, j));
                    continue;
                }
                else if (next_piece == empty_square) {
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }
}


void Board::check_middle_conditions(vector<pair<int, int>>& to_removed) {

}

int Board::count_pieces(char player) {
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (positions[row][col] == player)
                count++;            
        }
    }
    return count;
}

bool Board::check_game_state() {
    int player_1_pieces = count_pieces(player_1);
    int player_2_pieces = count_pieces(player_2);

    if (total_move_count == TOTAL_MOVE) {
        if (player_1_pieces == player_2_pieces) {
            cout << "Draw!" << endl;
            return true;
        } else if (player_1_pieces > player_2_pieces) {
            cout << "Player 1 wins!" << endl;
            winner = string(1, player_1);
            return true;
        } else {
            cout << "AI wins!" << endl;
            winner = string(1, player_2);
            return true;
        }
    }

    if (player_1_pieces == 0) {
        cout << "AI wins!" << endl;
        winner = string(1, player_2);
        return true;
    } else if (player_2_pieces == 0) {
        cout << "Player 1 wins!" << endl;
        winner = string(1, player_1);
        return true;
    } else if (player_1_pieces == 1 && player_2_pieces == 1) {
        cout << "Draw!" << endl;
        return true;
    }
    return false;
}

void Board::print_board() {
    string turn = (current_turn == PLAYER_SHAPE) ? "Players" : "AI's";
    cout << "----------------\n" << turn << " turn:\n----------------\n";
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << positions[row][col] << ' ';
        }
        cout << '\n';
    }
}