//
//  main.cpp
//  Repeated Squaring
//
//  Created by Ben Granados on 11/10/23.
//

#include <iostream>
#include <newmat.h>
#include <newmatio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "/Users/main/Software/newmat11/newmatap.h"
#include "/Users/main/Software/newmat11/newmat.h"
#include "/Users/main/Software/newmat11/newmatio.h"

using namespace std;


Matrix repeated_Squaring(Matrix A, int exponent, int no_rows) {
    if (exponent == 0) {
        return IdentityMatrix(no_rows);
    }
    if (exponent == 1) {
        return A;
    } 
    
    if (exponent % 2 == 1) {
        return (A * repeated_Squaring(A * A, (exponent - 1) / 2, no_rows));
    } else {
        return repeated_Squaring(A * A, exponent / 2, no_rows);
    }
}

Matrix bruteForceMultiplication(Matrix A, int exponent) {
    Matrix C = A;
    for (int i = 1; i < exponent; i++) {
        C = A * C;
    }
    return C;
}

Matrix generateRandomMatrix(int no_rows) {
    Matrix A(no_rows, no_rows);
    for (int i = 1; i <= no_rows; i++) {
        for (int j = 1; j <= no_rows; j++) {
            A(i, j) = (std::rand() % 11) - 5; // Random numbers in the range -5 to 5
        }
    }
    return A;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }
    
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);


    // Generate a random matrix
    Matrix A = generateRandomMatrix(n);

    // Repeated Squaring
    clock_t start = clock();
    Matrix result_Repeated = repeated_Squaring(A, k, n);
    clock_t end = clock();
    float timeRepeated = float(end - start) / CLOCKS_PER_SEC;

    // Brute Force Multiplication
    start = clock();
    Matrix resultBruteForce = bruteForceMultiplication(A, k);
    end = clock();
    float timeBruteForce = float(end - start) / CLOCKS_PER_SEC;

    // Output results
    std::cout << "The number of rows/columns in the square matrix is: " << n << std::endl;
    std::cout << "The exponent is: " << k << std::endl;
    
    //This prints the matrix: comment it out if you like
    std::cout << "Repeated Squaring Result:\n" << result_Repeated << std::endl;
    
    std::cout << "Repeated Squaring Result: " << std::endl;
    std::cout << "It took " << timeRepeated << " seconds to complete" << std::endl;
    
    //This also prints the matrix
    std::cout << "Brute Force Multiplication Result:\n" << resultBruteForce << std::endl;
    std::cout << "Direct Multiplication Result: " << std::endl;
    std::cout << "It took " << timeBruteForce << " seconds to complete" << std::endl;
    
    int exponent_max = 300;
    Matrix test = generateRandomMatrix(5);
    vector <double> repeated_time, bruteforce_time;
    
    for (int i = 1; i <= exponent_max; i++) {


        clock_t start = clock();
        Matrix test_repeat = repeated_Squaring(test, i, 5);
        clock_t end = clock();
        
        float test_repeat_time = ((float)end - (float)start) / CLOCKS_PER_SEC;
        
        repeated_time.push_back(test_repeat_time);
    }

    for (int i = 1; i <= exponent_max; i++) {
        
        clock_t start = clock();
        Matrix test_bruteforce = bruteForceMultiplication(test, i);
        clock_t end = clock();
        
        float test_bruteforce_time = ((float)end - (float)start) / CLOCKS_PER_SEC;
        
        bruteforce_time.push_back(test_bruteforce_time);
    }

    // "times.csv" is the file name for values to plot graph
    std::ofstream file("times.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    // Write the header
    file << "Index,Repeated Squaring Time,Brute Force Time\n";

    // Write the data
    for (size_t i = 0; i < repeated_time.size(); ++i) {
        file << (i + 1) << "," << repeated_time[i] << "," << bruteforce_time[i] << "\n";
    }

    file.close();
    std::cout << "Data written to times.csv" << std::endl;

    return 0;
}
