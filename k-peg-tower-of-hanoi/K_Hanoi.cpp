//
//  Hanoi.cpp
//  K-Peg Tower of Hanoi
//
//  Created by Ben Granados on 8/23/23.
//

#include "K_Hanoi.h"
#include <iostream>

int main (int argc, char * const argv[])
{
    int no_of_disks, no_of_pegs;
    
    // See 'k_hanoi.h' for the Towers class definition
    Towers x;
    
    std::cout << "Number of pegs? ";
    std::cin >> no_of_pegs;
    std::cout << "Number of disks? ";
    std::cin >> no_of_disks;
    
    x.solve(no_of_pegs, no_of_disks);
}
