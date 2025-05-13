//
//  main.cpp
//  Card Game
//
//  Created by Ben Granados on 10/17/23.
//

#include <iostream>
#include "cardgame.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int no_of_cards;
    
    std::cout << "Number of cards?";
    std::cin >> no_of_cards;
    
    cout << "Total Number of Cards = " << no_of_cards << endl;
    cout << "Value of the game = " << solve(no_of_cards/2, no_of_cards/2) << endl;
    
    return 0;
}
