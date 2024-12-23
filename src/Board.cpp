#include "Board.hpp"

Board::Board() {
    current_turn = AI_SHAPE;
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

const string& Board::get_winner() const {
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

char Board::get_piece(int row, int col) const {
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
        return positions[row][col];
    else
        return OUT_OF_BOARD;
}

vector<vector<char>> Board::get_positions() const {
    vector<vector<char>> positions_vector(BOARD_SIZE, vector<char>(BOARD_SIZE));
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            positions_vector[i][j] = positions[i][j];
        }
    }
    return positions_vector;
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
    if (start_row < 0 || start_row >= BOARD_SIZE || start_col < 0 || start_col >= BOARD_SIZE ||
        end_row < 0 || end_row >= BOARD_SIZE || end_col < 0 || end_col >= BOARD_SIZE) {
        cout << "Invalid move: Coordinates must be between 0 and " << BOARD_SIZE - 1 << "." << endl;
        return *this;
    }
    
    if (positions[start_row][start_col] != current_turn) {
        printf("Invalid move: You can only move your own pieces.\n");
        return *this;
    }
    
    if (positions[end_row][end_col] != empty_square) {
        printf("Invalid move: Destination square is not empty.\n");
        return *this;
    }

    int row_diff = abs(start_row - end_row);
    int col_diff = abs(start_col - end_col);
    if ((row_diff != 1 && col_diff != 1) || (row_diff == 1 && col_diff == 1)) {
        printf("Invalid move: You can only move one square up, down, left, or right.\n");
        return *this;
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

    for (int i = 0; i < to_removed.size(); i++) {
        //cout << "Piece location: " << to_removed[i].first << ":" << to_removed[i].second << endl;
        positions[to_removed[i].first][to_removed[i].second] = empty_square;
    }
    
}

void Board::check_wall_conditions(vector<pair<int, int>>& to_removed) {
    // Left Wall
    vector<pair<int, int>> stack_to_remove;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (positions[i][0] != empty_square) {
            for (int j = 0; j < BOARD_SIZE - 1; j++) {
                char next_piece = positions[i][j + 1];
                if (next_piece != positions[i][0] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(i, 0));
                    for (int n = 0; n < stack_to_remove.size(); n++)
                        to_removed.push_back(stack_to_remove[n]);                    
                }
                else if (next_piece == positions[i][0]) {
                    stack_to_remove.push_back(make_pair(i, j + 1));
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
    stack_to_remove.clear();
    // Right Wall
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (positions[i][BOARD_SIZE - 1] != empty_square) {
            for (int j = BOARD_SIZE - 1; j > 0; j--) {
                char next_piece = positions[i][j - 1];
                if (next_piece != positions[i][BOARD_SIZE - 1] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(i, BOARD_SIZE - 1));
                    for (int n = 0; n < stack_to_remove.size(); n++)
                        to_removed.push_back(stack_to_remove[n]);
                }
                else if (next_piece == positions[i][BOARD_SIZE - 1]) {
                    stack_to_remove.push_back(make_pair(i, j - 1));
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
    stack_to_remove.clear();
    // Top Wall
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (positions[0][j] != empty_square) {
            for (int i = 0; i < BOARD_SIZE - 1; i++) {
                char next_piece = positions[i + 1][j];
                if (next_piece != positions[0][j] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(0, j));
                    for (int n = 0; n < stack_to_remove.size(); n++)
                        to_removed.push_back(stack_to_remove[n]);
                }
                else if (next_piece == positions[0][j]) {
                    stack_to_remove.push_back(make_pair(i + 1, j));
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
    stack_to_remove.clear();
    // Bottom Wall
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (positions[BOARD_SIZE - 1][j] != empty_square) {
            for (int i = BOARD_SIZE - 1; i > 0; i--) {
                char next_piece = positions[i - 1][j];
                if (next_piece != positions[BOARD_SIZE - 1][j] && next_piece != empty_square) {
                    to_removed.push_back(make_pair(BOARD_SIZE - 1, j));
                    for (int n = 0; n < stack_to_remove.size(); n++)
                        to_removed.push_back(stack_to_remove[n]);
                }
                else if (next_piece == positions[BOARD_SIZE - 1][j]) {
                    stack_to_remove.push_back(make_pair(i - 1, j));
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
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (positions[i][j] != empty_square) {
                char current_piece = positions[i][j];
                char left_piece = get_piece(i, j - 1);
                char right_piece = get_piece(i, j + 1);
                char top_piece = get_piece(i - 1, j);
                char bottom_piece = get_piece(i + 1, j);

                // Check horizontal condition
                if (left_piece != OUT_OF_BOARD && right_piece != OUT_OF_BOARD &&
                left_piece != current_piece && left_piece != empty_square &&
                left_piece == right_piece)
                    to_removed.push_back(make_pair(i, j));

                // Check vertical condition
                if (top_piece != OUT_OF_BOARD && bottom_piece != OUT_OF_BOARD &&
                top_piece != current_piece && top_piece != empty_square &&
                top_piece == bottom_piece)
                    to_removed.push_back(make_pair(i, j));
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(positions[i][j] != empty_square) {
                char current_piece = positions[i][j];

                // Check horizontally
                char left_piece = get_piece(i, j - 1);
                if (left_piece != OUT_OF_BOARD && left_piece != current_piece) {
                    int k = j + 1;
                    while (k < BOARD_SIZE && positions[i][k] == current_piece)
                        k += 1;
                    
                    char right_piece = get_piece(i, k);
                    if (right_piece == left_piece && right_piece != empty_square) {
                        // Add all pieces between left_piece and right_piece
                        for (int x = j; x < k; ++x)
                            to_removed.push_back(make_pair(i, x));                        
                    }
                }

                // Check vertically
                char top_piece = get_piece(i - 1, j);
                if (top_piece != OUT_OF_BOARD && top_piece != current_piece) {
                    int k = i + 1;
                    while (k < BOARD_SIZE && positions[k][j] == current_piece)
                        k += 1;
                    
                    char bottom_piece = get_piece(k, j);
                    if (bottom_piece == top_piece && bottom_piece != empty_square) {
                        // Add all pieces between top_piece and bottom_piece
                        for (int x = i; x < k; ++x)
                            to_removed.push_back(make_pair(x, j));                        
                    }
                }
            }
        }
    }
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
    cout << "----------------\n" << turn << " turn:\n" << "Remaining turns: " <<
    (50-total_move_count) << "\n----------------\n";

    cout << "  "; 
    for (int col = 0; col < BOARD_SIZE; ++col) {
        cout << col << ' ';
    }
    cout << '\n';

    for (int row = 0; row < BOARD_SIZE; ++row) {
        cout << row << ' ';
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << positions[row][col] << ' ';
        }
        cout << '\n';
    }
}
