//
//  part1.cpp
//  part1
//
//  Created by Ben Granados on 11/3/23.
//
  
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std::chrono;

class CoinGame {
private:
    
    double q;
    double p;

    long double binomialCoefficient(int n, int r) {
        if (r == 0 || r == n)
           return 1;
           return binomialCoefficient(n - 1, r - 1) + binomialCoefficient(n - 1, r);
    }

public:
    
    //Constructor
    CoinGame(double probabilityQ, double probabilityP) : q(probabilityQ), p(probabilityP) {}

    long double probabilityAliceWins(int n) {
        long double probAliceWins = 0.0;
        for (int r = 0; r <= n; r++) {
            long double bobChance = binomialCoefficient(n, r) * pow(p, r) * pow(1 - p, n - r);
            for (int s = r + 1; s <= n; s++) {
                long double aliceChance = binomialCoefficient(n, s) * pow(q, s) * pow(1 - q, n - s);
                probAliceWins += aliceChance * bobChance;
            }
        }
        return probAliceWins;
    }

    int findOptimalN() {
        int n = 1;
        long double maxProbability = 0.0;
        int optimalN = n;

        while (true) {
            long double currentProbability = probabilityAliceWins(n);
            if (currentProbability > maxProbability) {
                maxProbability = currentProbability;
                optimalN = n;
            } else {
                // If the probability starts to decrease, we've found our peak
                break;
            }
            ++n;
        }
        
        return optimalN;
    }
};

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Wrong number of inputs" << std::endl;
        return 1;
    }

    double q = std::atof(argv[1]);
    double p = std::atof(argv[2]);

    if (q <= 0.0 || q >= p || p <= 0.0 || p >= 1.0) {
        std::cout << "Probabilities do not satisfy requirements" << std::endl;
        return 1;
    }
    
    auto start = high_resolution_clock::now();
    
    CoinGame game(q, p);
    int optimalN = game.findOptimalN();
    
    std::cout<< "Probability of head up for Alice = " << q << std::endl;
    std::cout<< "Probability of head up for Bob = " << p << std::endl;
    std::cout<< "The optimal number of coin tosses in each game is " << optimalN << std::endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    
    std::cout<< "This program took me " << duration.count() << " seconds" << std::endl;
    
    return 0;
}
