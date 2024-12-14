#include "UnitTester.hpp"
#include "Board.hpp"
#include <iostream>
using namespace std;

UnitTester::UnitTester() {}

void UnitTester::assert_true(bool condition, const string& message) {
    if (!condition) {
        cerr << "Test failed: " << message << endl;
    } else {
        cout << "Test passed: " << message << endl;
    }
}

void UnitTester::assert_equal(const string& expected, const string& actual, const string& message) {
    if (expected != actual) {
        cerr << "Test failed: " << message << "\nExpected: " << expected << "\nActual: " << actual << endl;
    } else {
        cout << "Test passed: " << message << endl;
    }
}

void UnitTester::test_make_move() {
    cout << "Testing make_move...\n";

    // Test 1: Valid move
    {
        cout << "-------------Test 1-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 0, start_col = 0, end_row = 1, end_col = 0;

        Board new_board = board.make_move(start_row, start_col, end_row, end_col);

        assert_equal(".", string(1, new_board.positions[start_row][start_col]), "Start position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[end_row][end_col]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 2: Invalid move (Moving an opponent's piece)
    {
        cout << "-------------Test 2-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 5, start_col = 0, end_row = 5, end_col = 1;

        try {
            // board.positions[start_row][start_col] = board.player_2; // Make opponent's piece in the start position
            board.make_move(start_row, start_col, end_row, end_col);
            assert_true(false, "Invalid move: Should have thrown exception for moving opponent's piece");
        } catch (const invalid_argument& e) {
            assert_true(true, "Exception caught for moving opponent's piece");
        }
        cout << "--------------------------------" << endl;
    }

    // Test 3: Invalid move (Destination square is not empty)
    {
        cout << "-------------Test 3-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 0, start_col = 0, end_row = 0, end_col = 1;

        board.positions[end_row][end_col] = 'A'; // Occupy destination square with a piece
        try {
            board.make_move(start_row, start_col, end_row, end_col);
            assert_true(false, "Invalid move: Should have thrown exception for destination square not empty");
        } catch (const invalid_argument& e) {
            assert_true(true, "Exception caught for destination square not empty");
        }
        cout << "--------------------------------" << endl;
    }

    // Test 4: Invalid move (Diagonal move)
    {
        cout << "-------------Test 4-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 0, start_col = 0, end_row = 1, end_col = 1;

        try {
            board.make_move(start_row, start_col, end_row, end_col);
            assert_true(false, "Invalid move: Should have thrown exception for diagonal move");
        } catch (const invalid_argument& e) {
            assert_true(true, "Exception caught for diagonal move");
        }
        cout << "--------------------------------" << endl;
    }

    // Test 5: Invalid move (Moving more than one square)
    {
        cout << "-------------Test 5-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 0, start_col = 0, end_row = 0, end_col = 2;

        try {
            board.make_move(start_row, start_col, end_row, end_col);
            assert_true(false, "Invalid move: Should have thrown exception for moving more than one square");
        } catch (const invalid_argument& e) {
            assert_true(true, "Exception caught for moving more than one square");
        }
        cout << "--------------------------------" << endl;
    }

    // Test 6: Move 2 piece that changes the current turn
    {
        cout << "-------------Test 6-------------" << endl;
        Board board;
        board.init_board();
        int start_row = 0, start_col = 0, end_row = 0, end_col = 1;
        Board new_board = board.make_move(start_row, start_col, end_row, end_col);
        Board new_board2 = new_board.make_move(end_row, end_col, 0, 2);
        assert_equal("O", string(1, new_board2.get_current_turn()), "Turn should switch after the move");
        cout << "--------------------------------" << endl;
    }

    // Test 7: Checking total move count after the move
    {
        cout << "-------------Test 7-------------" << endl;
        Board board;
        board.init_board();
        board.total_move_count = 0;
        int start_row = 0, start_col = 0, end_row = 0, end_col = 1;

        Board new_board = board.make_move(start_row, start_col, end_row, end_col);
        assert_equal("1", to_string(new_board.total_move_count), "Total move count should increase by 1");
        cout << "--------------------------------" << endl;
    }

    cout << "All tests for make_move completed.\n";
}

void UnitTester::test_update_board() {
    cout << "Testing updating board...\n";

    // Test 1: Wall conditions (Left Wall one piece)
    {
        cout << "-------------Test 1-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = AI_SHAPE;
        board.positions[0][2] = PLAYER_SHAPE;
        Board new_board = board.make_move(0, 2, 0, 1);

        assert_equal(".", string(1, new_board.positions[0][0]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[0][1]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 2: Wall conditions (Left Wall two piece)
    {
        cout << "-------------Test 2-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = AI_SHAPE;
        board.positions[0][1] = AI_SHAPE;
        board.positions[0][3] = PLAYER_SHAPE;
        Board new_board = board.make_move(0, 3, 0, 2);

        assert_equal(".", string(1, new_board.positions[0][0]), "AI position should be empty after the move");
        assert_equal(".", string(1, new_board.positions[0][1]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[0][2]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 3: Wall conditions (Right Wall one piece)
    {
        cout << "-------------Test 3-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][6] = AI_SHAPE;
        board.positions[0][4] = PLAYER_SHAPE;
        Board new_board = board.make_move(0, 4, 0, 5);

        assert_equal(".", string(1, new_board.positions[0][6]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[0][5]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 4: Wall conditions (Right Wall two piece)
    {
        cout << "-------------Test 4-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][6] = AI_SHAPE;
        board.positions[0][5] = AI_SHAPE;
        board.positions[0][3] = PLAYER_SHAPE;
        Board new_board = board.make_move(0, 3, 0, 4);

        assert_equal(".", string(1, new_board.positions[0][6]), "AI position should be empty after the move");
        assert_equal(".", string(1, new_board.positions[0][5]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[0][4]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 5: Wall conditions (Top Wall one piece)
    {
        cout << "-------------Test 5-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = AI_SHAPE;
        board.positions[2][0] = PLAYER_SHAPE;
        Board new_board = board.make_move(2, 0, 1, 0);

        assert_equal(".", string(1, new_board.positions[0][0]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[1][0]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 6: Wall conditions (Top Wall two piece)
    {
        cout << "-------------Test 4-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = AI_SHAPE;
        board.positions[1][0] = AI_SHAPE;
        board.positions[3][0] = PLAYER_SHAPE;
        Board new_board = board.make_move(3, 0, 2, 0);

        assert_equal(".", string(1, new_board.positions[0][0]), "AI position should be empty after the move");
        assert_equal(".", string(1, new_board.positions[1][0]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[2][0]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 7: Wall conditions (Bottom Wall one piece)
    {
        cout << "-------------Test 7-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[6][0] = AI_SHAPE;
        board.positions[4][0] = PLAYER_SHAPE;
        Board new_board = board.make_move(4, 0, 5, 0);

        assert_equal(".", string(1, new_board.positions[6][0]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[5][0]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }

    // Test 8: Wall conditions (Bottom Wall two piece)
    {
        cout << "-------------Test 8-------------" << endl;
        Board board;
        board.init_board();

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[6][0] = AI_SHAPE;
        board.positions[5][0] = AI_SHAPE;
        board.positions[3][0] = PLAYER_SHAPE;
        Board new_board = board.make_move(3, 0, 4, 0);

        assert_equal(".", string(1, new_board.positions[6][0]), "AI position should be empty after the move");
        assert_equal(".", string(1, new_board.positions[5][0]), "AI position should be empty after the move");
        assert_equal("A", string(1, new_board.positions[4][0]), "End position should have player's piece");
        cout << "--------------------------------" << endl;
    }
}

void UnitTester::test_check_game_state() {
    cout << "Testing check_game_state...\n";

    // Test 1: Total moves reach TOTAL_MOVE and it's a draw
    {
        cout << "-------------Test 1-------------" << endl;
        Board board;
        board.total_move_count = TOTAL_MOVE;
        board.init_board();

        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when total moves reach TOTAL_MOVE");
        assert_equal(DRAW, board.get_winner(), "Winner should be DRAW when equal pieces");
        cout << "--------------------------------" << endl;
    }

    // Test 2: Total moves reach TOTAL_MOVE and Player has more pieces
    {
        cout << "-------------Test 2-------------" << endl;
        Board board;
        board.total_move_count = TOTAL_MOVE;
        board.init_board();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = PLAYER_SHAPE;
        board.positions[0][1] = PLAYER_SHAPE;
        board.positions[3][3] = AI_SHAPE;

        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when total moves reach TOTAL_MOVE");
        assert_equal(string(1, PLAYER_SHAPE), board.get_winner(), "Winner should be Player when TOTAL_MOVE");
        cout << "--------------------------------" << endl;
    }

    // Test 3: Total moves reach TOTAL_MOVE and AI has more pieces
    {
        cout << "-------------Test 3-------------" << endl;
        Board board;
        board.total_move_count = TOTAL_MOVE;
        board.init_board();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = AI_SHAPE;
        board.positions[0][1] = AI_SHAPE;
        board.positions[3][3] = PLAYER_SHAPE;

        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when total moves reach TOTAL_MOVE");
        assert_equal(string(1, AI_SHAPE), board.get_winner(), "Winner should be AI when TOTAL_MOVE");
        cout << "--------------------------------" << endl;
    }

    // Test 4: Player 1 has no pieces
    {
        cout << "-------------Test 4-------------" << endl;
        Board board;
        board.init_board();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = AI_SHAPE; // Fill board with AI pieces
            }
        }
        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when Player 1 has no pieces");
        assert_equal(string(1, AI_SHAPE), board.get_winner(), "Winner should be AI");
        cout << "--------------------------------" << endl;
    }

    // Test 5: Player 2 has no pieces
    {
        cout << "-------------Test 5-------------" << endl;
        Board board;
        board.init_board();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = PLAYER_SHAPE; // Fill board with Player 1 pieces
            }
        }
        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when Player 2 has no pieces");
        assert_equal(string(1, PLAYER_SHAPE), board.get_winner(), "Winner should be Player 1");
        cout << "--------------------------------" << endl;
    }

    // Test 6: Both players have one piece each
    {
        cout << "-------------Test 6-------------" << endl;
        Board board;
        board.init_board();
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board.positions[i][j] = '.'; // Clear the board
            }
        }
        board.positions[0][0] = PLAYER_SHAPE;
        board.positions[0][1] = AI_SHAPE;

        bool game_over = board.check_game_state();
        assert_true(game_over, "Game over when both players have one piece each");
        assert_equal(DRAW, board.get_winner(), "Winner should be DRAW");
        cout << "--------------------------------" << endl;    
    }

    // Test 7: Normal gameplay (game continues)
    {
        cout << "-------------Test 7-------------" << endl;
        Board board;
        board.init_board();

        bool game_over = board.check_game_state();
        assert_true(!game_over, "Game continues when there are sufficient pieces for both players");
        cout << "--------------------------------" << endl;
    }

    cout << "All tests for check_game_state completed.\n";
    cout << "--------------------------------" << endl;
}
