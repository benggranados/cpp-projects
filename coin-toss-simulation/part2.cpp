//
//  part2.cpp
//  part2
//
//  Created by Ben Granados on 11/3/23.
//

#include <iostream>
#include <fstream>
#include <random>
#include <vector>

using namespace std::chrono;

class CoinGameSimulator {
private:
    double q, p;
    int no_of_trials;
    std::string csv_file;
    std::default_random_engine generator;

    bool tossCoin(double probability) {
        std::bernoulli_distribution distribution(probability);
        return distribution(generator);
    }

    long double binomialCoefficient(int n, int r) {
        if (r == 0 || r == n)
           return 1;
           return binomialCoefficient(n - 1, r - 1) + binomialCoefficient(n - 1, r);
    }

    long double theoreticalprobabilityAliceWins(int n) {
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

public:
    CoinGameSimulator(int trials, double q, double p, const std::string& filename)
    : no_of_trials(trials), q(q), p(p), csv_file(filename) {}

    void runSimulation() {
        std::ofstream file(csv_file);

        // Write header to CSV
        file << "n,ExperimentalProbability,TheoreticalProbability\n";

        for (int n = 1; n <= 25; ++n) {
            int aliceWins = 0;

            for (int trial = 0; trial < no_of_trials; ++trial) {
                int aliceHeads = 0, bobHeads = 0;

                for (int toss = 0; toss < n; ++toss) {
                    if (tossCoin(q)) aliceHeads++;
                    if (tossCoin(p)) bobHeads++;
                }
                if (aliceHeads > bobHeads) aliceWins++;
            }

            long double experimentalProbability = static_cast<long double>(aliceWins) / no_of_trials;
            long double theoreticalProbability = theoreticalprobabilityAliceWins(n);
            
            
            file << n << "," << experimentalProbability << "," << theoreticalProbability << std::endl;
        }

        file.close();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Wrong number of inputs" << std::endl;
        return 1;
    }

    double q = std::atof(argv[2]);
    double p = std::atof(argv[3]);
    int trials = std::atof(argv[1]);
    std::string csv_file = argv[4];

    if (q <= 0.0 || q >= 1.0 || p <= 0.0 || p >= 1.0 || q >= p) {
        std::cout << "Probabilities do not satisfy requirements";
        return 1;
    }
    
    auto start = high_resolution_clock::now();
    
    CoinGameSimulator simulator(trials, q, p, csv_file);
    simulator.runSimulation();
    
    std::cout<< "Number of Trials = " << trials << std::endl;
    std::cout<< "Probability of head up for Alice = " << q << std::endl;
    std::cout<< "Probability of head up for Bob = " << p << std::endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    
    std::cout<< "This program took me " << duration.count() << " seconds" << std::endl;

    return 0;
}
