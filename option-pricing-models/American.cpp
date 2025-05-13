//
//  American.cpp
//  Pricing Options
//
//  Created by Ben Granados on 11/17/23.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include<vector>
using namespace std;

double up_factor, uptick_prob, risk_free_rate, strike_price, downtick_prob;
double initial_stock_price, expiration_time, volatility, R;
int no_of_divisions;

vector<vector <double> > call(5010, vector<double>(12000, -1.0));
vector<vector <double> > put(5010, vector<double>(12000, -1.0));


float max(float a, float b) {
    return (b < a )? a:b;
}

double american_call_option(int k, int i, double current_stock_price) {
    if (k == no_of_divisions) {
        return max(0.0, (current_stock_price - strike_price));
    }
    
    if (call[k][no_of_divisions + i] >= 0) {
        return call[k][no_of_divisions + i];
    }
    
    double option_value = max(
        (current_stock_price - strike_price),
        (uptick_prob * american_call_option(k + 1, i + 1, current_stock_price * up_factor) +
         (1 - uptick_prob - downtick_prob) * american_call_option(k + 1, i, current_stock_price) +
         downtick_prob * american_call_option(k + 1, i - 1, current_stock_price / up_factor)) / R
    );

    call[k][no_of_divisions + i] = option_value;
    return option_value;
}

double american_put_option(int k, int i, double current_stock_price) {
    if (k == no_of_divisions) {
        return max(0.0, (strike_price - current_stock_price));
    }
    
    if (put[k][no_of_divisions + i] >= 0) {
        return put[k][no_of_divisions + i];
    }
    
    double option_value = max(
        (strike_price - current_stock_price),
        (uptick_prob * american_put_option(k + 1, i + 1, current_stock_price * up_factor) +
         (1 - uptick_prob - downtick_prob) * american_put_option(k + 1, i, current_stock_price) +
         downtick_prob * american_put_option(k + 1, i - 1, current_stock_price / up_factor)) / R
    );

    put[k][no_of_divisions + i] = option_value;
    return option_value;
}



int main(int argc, char* argv[])
{

    sscanf(argv[1], "%lf", &expiration_time);
    sscanf(argv[2], "%d", &no_of_divisions);
    sscanf(argv[3], "%lf", &risk_free_rate);
    sscanf(argv[4], "%lf", &volatility);
    sscanf(argv[5], "%lf", &initial_stock_price);
    sscanf(argv[6], "%lf", &strike_price);

    up_factor = exp(volatility * sqrt(2 * expiration_time / ((float)no_of_divisions)));
    R = exp(risk_free_rate * expiration_time / ((float)no_of_divisions));
    uptick_prob = pow((sqrt(R) - 1 / sqrt(up_factor)) / (sqrt(up_factor) - 1 / sqrt(up_factor)), 2);
    downtick_prob = pow((sqrt(up_factor) - sqrt(R)) / (sqrt(up_factor) - 1 / sqrt(up_factor)), 2);
    cout << "Recursive Trinomial American Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility * 100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "Notick Probability = " << 1 - uptick_prob - downtick_prob << endl;
    cout << "Downtick Probability = " << downtick_prob << endl;
    cout << "--------------------------------------" << endl;
    double call_price = american_call_option(0, 0, initial_stock_price);
    cout << "Trinomial Price of an American Call Option = " << call_price << endl;
    double put_price = american_put_option(0, 0, initial_stock_price);
    cout << "Trinomial Price of an American Put Option = " << put_price << endl;
    cout << "--------------------------------------" << endl;

}
