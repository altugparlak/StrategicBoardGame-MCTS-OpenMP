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
