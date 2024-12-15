#include <iostream>
#include <iomanip>
#include <sstream>
#include <omp.h>
#include "Board.cpp"

using namespace std;

void DisplayMenu()
{
    cout << "Menu:" << endl;
    cout << "1." << setw(4) << "Play with AI," << endl;
    cout << "2." << setw(4) << "Multiplayer," << endl;
    cout << "3." << setw(4) << "Change difficulty," << endl;
    cout << "4." << setw(4) << "Test game rules," << endl;
    cout << "5." << setw(4) << "Exit the program." << endl;
    return;
}

void Game() {
    Board board = Board();
    board.print_board();
}

void MultiplayerGame() {
    Board board = Board();
    board.print_board();

    bool running = true;
    while (running) {
        running = !board.check_game_state();

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
    }
}


int main(int argc, char* argv[]) {
    //Board board = Board();
    //board.print_board();

    //UnitTester tester;
    //tester.test_check_game_state();
    //tester.test_make_move();
    //tester.test_wall_conditions_update_board();
    //tester.test_middle_conditions_update_board();

    int menu_number;
    DisplayMenu();
    cin >> menu_number;

    while (menu_number != 5)
    {
        switch (menu_number)
        {
        case 1:
            cout << "Game is started." << endl;
            Game();
            break;
        case 2:
            cout << "Multiplayer game started." << endl;
            MultiplayerGame();
            break;
        case 3:
            cout << "Change difficulty:" << endl;
            break;
        case 4:
            cout << "Test game rules:" << endl;
            break;
        case 5:
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