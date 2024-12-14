#include <iostream>
#include <omp.h>
#include "Board.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    Board board = Board();
    board.print_board();

    UnitTester tester;
    //tester.test_check_game_state();
    tester.test_make_move();
    return EXIT_SUCCESS;
}