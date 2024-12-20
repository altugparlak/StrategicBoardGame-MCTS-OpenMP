#include <iostream>
#include <iomanip>
#include <sstream>
#include "Mcst.hpp"
#include "Board.cpp"

using namespace std;

void DisplayMenu()
{
    using namespace std;

    cout << left;
    cout << "Menu:\n";
    cout << "1. " << setw(20) << "Play with AI ☺⚔♝" << endl;
    cout << "2. " << setw(20) << "Multiplayer ☺⚔☺" << endl;
    cout << "3. " << setw(20) << "Change difficulty ✎" << endl;
    cout << "4. " << setw(20) << "Exit the program ☒"  << endl;
    return;
}

void Game(int difficulty) {
    Board board = Board();
    board.print_board();

    bool running = true;
    while (running) {
        char whose_turn = board.get_current_turn();
        if(whose_turn == PLAYER_SHAPE) {
            // Player moves
            int start_row, start_col, end_row, end_col;
            bool valid_input = false;
            while (!valid_input) {
                cout << "Enter move (start_row start_col end_row end_col): ";
                string input_line;
                getline(std::cin, input_line);

                istringstream iss(input_line);
                if (iss >> start_row >> start_col >> end_row >> end_col) {
                    valid_input = true;
                } else {
                    cerr << "Invalid input format! Please enter 4 integers.\n";
                }
            }
            board = board.make_move(start_row, start_col, end_row, end_col);

        }
        else {
            // AI Moves
            cout << "AI is thinking.." << endl;
            Mcst mcst = Mcst(board);
            //board = mcst.play_best_move(10000);
            int simulations = (difficulty == 1) ? 100 : (difficulty == 2) ? 500 : 1000;
            board = mcst.play_best_move_parallel(simulations);
            board.print_board();
        }
        board.print_board();
        running = !board.check_game_state();
    }
}

void MultiplayerGame() {
    Board board = Board();
    board.print_board();

    bool running = true;
    while (running) {
        int start_row, start_col, end_row, end_col;
        bool valid_input = false;

        while (!valid_input) {
            cout << "Enter move (start_row start_col end_row end_col): ";
            string input_line;
            getline(std::cin, input_line);

            istringstream iss(input_line);
            if (iss >> start_row >> start_col >> end_row >> end_col) {
                valid_input = true;
            } else {
                cerr << "Invalid input format! Please enter 4 integers.\n";
            }
        }

        board = board.make_move(start_row, start_col, end_row, end_col);
        board.print_board();
        running = !board.check_game_state();
    }
}

void ChangeDifficulty(int &dif) {
    int new_difficulty;
    cout << "\nSelect difficulty:" << endl;
    cout << "1. " << setw(4) << "Easy," << endl;
    cout << "2. " << setw(4) << "Normal," << endl;
    cout << "3. " << setw(4) << "Hard," << endl;

    cin >> new_difficulty;

    if (new_difficulty >= 1 && new_difficulty <= 3) {
        dif = new_difficulty;
        cout << "Difficulty changed to " << ((dif == 1) ? "Easy" : (dif == 2) ? "Normal" : "Hard") << "." << endl;
    } else {
        cout << "Invalid input. Difficulty remains unchanged." << endl;
    }
}

int main(int argc, char* argv[]) {

    //UnitTester tester;
    //tester.test_check_game_state();
    //tester.test_make_move();
    //tester.test_wall_conditions_update_board();
    //tester.test_middle_conditions_update_board();

    int menu_number;
    int difficulty = 1; // 1(easy) - 2(normal) - 3(hard)
    cout << "\n(っ◔◡◔)っ Welcome to Strategic Board Game ♗" << endl;
    DisplayMenu();
    cin >> menu_number;

    while (menu_number != 4)
    {
        switch (menu_number)
        {
        case 1:
            cout << "Game is started." << endl;
            Game(difficulty);
            break;
        case 2:
            cout << "Multiplayer game started." << endl;
            MultiplayerGame();
            break;
        case 3:
            ChangeDifficulty(difficulty);
            break;
        case 4:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid input please enter the correct number." << endl;
            break;
        }
        DisplayMenu();
        cin >> menu_number;
    }

    return EXIT_SUCCESS;
}