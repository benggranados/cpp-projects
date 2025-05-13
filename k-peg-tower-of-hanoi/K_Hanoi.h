//
//  Hanoi.hpp
//  K-Peg Tower of Hanoi
//
//  Created by Ben Granados on 8/23/23.
//

#ifndef K_Hanoi_hpp
#define K_Hanoi_hpp

#include <stdio.h>
#include <cmath>
#include <deque>
#include <sstream>
#include <iostream>
#include <string>

using std::deque;
using namespace std;

class Towers
{
    // private data member: #steps
    int number_of_steps;
    
    // private data member: #pegs
    int number_of_pegs;
    
    // private data member: #disks on 1st Peg
    int number_of_disks;
    
    // private data member: k-Deques-of-Deques
    // towers[0] is deque for the 1st Peg, towers[1] is the deque
    // for the 2nd Peg,..., towers[k-1] is the deque for the kth Peg
    deque < deque <int> > towers;
    
    // private member function:  returns 'false' if a larger disk
    // is moved on top of a smaller disk during a move
    bool is_everything_legal()
    {
        bool result = true;
            for (int i = 0; i < number_of_pegs; ++i) {
                for (size_t j = 0; j < towers[i].size(); ++j) {
                    for (size_t k = j; k < towers[i].size(); ++k) {
                        if (towers[i][k] < towers[i][j]) {
                            result = false;
                        }
                    }
                }
            }
            return result;
    }
    
    // private member function: initializes the pegs and #disks on Peg 1
    void initialize(int m, int n)
    {
        number_of_pegs = m;
        number_of_disks = n;
        for (int i = 0; i <= number_of_pegs; i++) {
            std::deque<int> X;
            if (i == 0) {
                for (int j = 0; j < number_of_disks; j++) {
                    X.push_back(j + 1);
                }
            }
            towers.push_back(X);
        }
    }
    
    // private member function:  picks the #disks to be moved based on
    // the #free pegs that are available at a given instant
    int pick_the_right_number_to_move(int number_of_disks, long number_of_free_pegs)
    {
        if (1 == number_of_free_pegs)
            return (number_of_disks-1);
        else
            return (number_of_disks/2);
    }
    
    // private member function: primitive/basic move of the top disk
    // from the source peg to the destination peg -- and legality-check
    void move_top_disk(int source, int dest)
    {
        number_of_steps++;
        int x = towers[source].front();
        string y;
        towers[source].pop_front();
        towers[dest].push_front(x);
        if (is_everything_legal() == true) {
            y = " (Legal)";
        } else {
            y = " (Illegal)";
        }
        cout << "Move disk " + to_string(x) + " from peg" + to_string(source + 1) + " to Peg " + to_string(dest + 1) + y << endl;
    }
    
    // private member function: recursive solution to the 3 Peg Tower of Hanoi
    void Move(int number_of_disks, int source_peg_number, int destination_peg_number, deque <int> free_peg_numbers)
    {
        if (free_peg_numbers.size() != 0)
        {
            if (number_of_disks > 1)
            {
                int m = pick_the_right_number_to_move(number_of_disks, free_peg_numbers.size());
                // write the code for this part
                int intermediate_peg_number = free_peg_numbers.back();
                free_peg_numbers.pop_back();
                
                free_peg_numbers.push_back(destination_peg_number);
                
                Move(m, source_peg_number, intermediate_peg_number, free_peg_numbers);
                
                free_peg_numbers.pop_back();
                
                Move(number_of_disks - m, source_peg_number, destination_peg_number, free_peg_numbers);
                
                free_peg_numbers.push_back(source_peg_number);
                
                Move(m, intermediate_peg_number, destination_peg_number, free_peg_numbers);
                
                free_peg_numbers.pop_back();
                free_peg_numbers.push_back(intermediate_peg_number);
            }
            else {
                // number_of_disks == 1
                number_of_steps++;
                move_top_disk(source_peg_number, destination_peg_number);
            }
        }
        else {
            // there are no free pegs
            number_of_steps++;
            move_top_disk(source_peg_number, destination_peg_number);
        }
    }
    
    // private member function: prints the state of Peg m (m = 0, 1, 2)
    void print_peg_state(int m)
    {
        cout << "-----------------------------" << endl;
        cout << "State of Peg " + to_string(m + 1) + " (Top to Bottom): ";
        
        for (int element: towers[m]) {
                std::cout << element << " ";
            }
        
        cout << "Number of Steps = " + to_string(number_of_steps) << endl;
        cout << "-----------------------------" << endl;
    }
    
public:
    // Solves the K Peg Tower of Hanoi
    void solve(int number_of_pegs, int number_of_disks)
    {
        initialize(number_of_pegs, number_of_disks);
        print_peg_state(0);
        
        deque <int> free_peg_numbers;
        // source peg # is 0; destination peg # is no_of_pegs-1;
        // free pegs {1,.., no_of_pegs-2}
        for (int i = 1; i <= number_of_pegs-2; i++)
            free_peg_numbers.push_back(i);
        Move(number_of_disks, 0, number_of_pegs-1, free_peg_numbers);
        print_peg_state(number_of_pegs-1);
    }
};
#endif
