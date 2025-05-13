//
//  Sudoku.hpp
//  Sudoku Solver
//
//  Created by Ben Granados on 9/2/23.
//

#include <stdio.h>
#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using namespace std;

class Sudoku
{
    // Private
    int puzzle[9][9];
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row)
    {
        // check validity of "row"
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                if (i != j) {
                    if (puzzle[row][i] == puzzle[row][j]) {
                        if (puzzle[row][i] != 0) {
                            return false;
                        }
                    }
                }
                
            }
            
            
        }
        return true;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col)
    {
        // check validity of "col"
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                if (i != j) {
                    if (puzzle[i][col] == puzzle[j][col]) {
                        if (puzzle[i][col] != 0) {
                            return false;
                        }
                    }
                }
                
            }
            
            
        }
        
        
        
        
        return true;
    }
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // check 3 x 3 block validity
                int startrow = row - row%3;
                int startcol = col - col%3;
                for (int i = startrow; i < startrow + 3; i++) {
                    for (int j = startcol;j < startcol + 3 ; j++) {
                            if (puzzle[i][j] == puzzle[row][col]) {
                                if (i != row){
                                    if (j != col){
                                        if (puzzle[i][j] != 0) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        
                    }
                }
                return true;
        
    }

    public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
        
        ifstream input_file(argv[1]);
        int value_just_read_from_file;
        vector <int> P;
        
        if (argc > 1) {
            if (input_file.is_open()) {
                
                while (input_file >> value_just_read_from_file) {
                    P.push_back(value_just_read_from_file);
                    
                }
                
            }
            
        }
        
        for (int i = 0; i < 9; i++) {
            
            for (int j = 0; j < 9; j++){
                int entry = i * 9 + j;
                puzzle[i][j] = P[entry];
            }
        }
        
        
        
        
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        std::cout << std::endl << "Board Position" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        // use the pseudo code of figure 3 of the description
        
        if (row == 9) {
            return true;
        }

        if (col == 9) {
            return Solve(row + 1, 0);
        }

        if (puzzle[row][col] != 0) {
            return Solve(row, col + 1);
        }


        for (int k = 1; k <= 9; k++) {
            puzzle[row][col] = k;
            if (row_valid(row) && col_valid(col) && block_valid(row, col)) {
                if (Solve(row, col + 1)) {
                    return true;
                }
            }
        
        }
        puzzle[row][col] = 0;
        return false;
        
    }

        

    bool alternate_Solve(int row, int col)
    {
        // This part of the code identifies the row and col number of the
        // first incomplete (i.e., 0) entry in the puzzle. If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col-, and block-valid.
        // Use the pseudo code of figure 3 of the description
        if (row == 9) {
            print_puzzle();
            return false; // Continue searching for more solutions
        }

        if (col == 9) {
            return alternate_Solve(row + 1, 0);
        }

        if (puzzle[row][col] != 0) {
            return alternate_Solve(row, col + 1);
        }

        bool found_at_least_one_solution = false;

        for (int k = 1; k <= 9; k++) {
            puzzle[row][col] = k;
            if (row_valid(row) && col_valid(col) && block_valid(row, col)) {
                
                if (alternate_Solve(row, col + 1)) {
                    // If a solution is found, mark that at least one solution exists
                    found_at_least_one_solution = true;
                }
            }
            puzzle[row][col] = 0;  // Backtrack
        }

        // Return whether at least one solution was found in the current path
        return found_at_least_one_solution;
    }




 };

#endif /* Sudoku_h */
