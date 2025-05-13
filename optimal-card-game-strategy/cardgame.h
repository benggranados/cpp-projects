//
//  cardgame.h
//  Card Game
//
//  Created by Ben Granados on 10/17/23.
//

#ifndef cardgame_h
#define cardgame_h

#include <iostream>
#include <vector>


using namespace std;

vector<double> cards(1000, -1.0);
vector<vector<double>> status(1000, cards);

double solve(int redcards, int blackcards) {
    
    double value;
    
    if (redcards == 0) {
        return ((double) blackcards);
    }
    if (blackcards == 0) {
        return 0;
    }
    //Memoization part checks to see if it has already been calculated
    if (status[redcards][blackcards] >= 0.0) {
        value = status[redcards][blackcards];
    } else {
        double redcardsprob = ((double)redcards / (redcards + blackcards)) * solve(redcards - 1, blackcards);
        double blackcardsprob = ((double)blackcards / (redcards + blackcards)) * solve(redcards, blackcards - 1);
        
        value = max((redcardsprob + blackcardsprob), (double)(blackcards - redcards));
        status[redcards][blackcards] = value;
        
    }
    
    return value;
}

#endif /* cardgame_h */
