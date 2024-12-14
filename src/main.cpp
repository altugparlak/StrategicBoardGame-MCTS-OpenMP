#include <iostream>
#include <omp.h>
#include "Board.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    Board board = Board();
    board.print_board();
    
    return EXIT_SUCCESS;
}