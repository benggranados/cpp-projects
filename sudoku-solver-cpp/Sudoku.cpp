//
//  Sudoku.cpp
//  Sudoku Solver
//
//  Created by Ben Granados on 9/2/23.
//

#include "Sudoku.h"
#include <iostream>

int main (int argc, char * const argv[])
{
    Sudoku x;
    x.read_puzzle(argc, argv);
    x.print_puzzle();
    //x.Solve(0,0);
    x.alternate_Solve(0, 0);
    x.print_puzzle();
    
    return 0;
}
