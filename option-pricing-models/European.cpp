//
//  European.cpp
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
#include <vector>
using namespace std;

double up_factor, uptick_prob, risk_free_rate, strike_price, downtick_prob;
double initial_stock_price, expiration_time, volatility, R;
int no_of_divisions;

vector<vector <double> > call(5010, vector<double>(12000, -1.0));
vector<vector <double> > put(5010, vector<double>(12000, -1.0));

float max(float a, float b) {
    return (b < a )? a:b;
}

double european_call_option(int i, int j) {
    if (i == no_of_divisions) {
        double stock_price_at_j = initial_stock_price * pow(up_factor, static_cast<double>(j));
        return max(0.0, stock_price_at_j - strike_price);
    }
    
    if (call[i][no_of_divisions + j] >= 0) {
        return call[i][no_of_divisions + j];
    }
    
    double option_value = (uptick_prob * european_call_option(i + 1, j + 1) +
                           (1 - uptick_prob - downtick_prob) * european_call_option(i + 1, j) +
                           downtick_prob * european_call_option(i + 1, j - 1)) / R;

    call[i][no_of_divisions + j] = option_value;
    return option_value;
}

double european_put_option(int k, int i) {
    if (k == no_of_divisions) {
        double stock_price_at_i = initial_stock_price * pow(up_factor, static_cast<double>(i));
        return max(0.0, (strike_price - stock_price_at_i));
    }

    if (put[k][no_of_divisions + i] >= 0) {
        return put[k][no_of_divisions + i];
    }

    double option_value = (uptick_prob * european_put_option(k + 1, i + 1) +
                           (1 - uptick_prob - downtick_prob) * european_put_option(k + 1, i) +
                           downtick_prob * european_put_option(k + 1, i - 1)) / R;

    put[k][no_of_divisions + i] = option_value;
    return option_value;
}

double N(const double& z) {
    if (z > 6.0) { return 1.0; };
    if (z < -6.0) { return 0.0; };
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274429;
    double p = 0.2316419;
    double c2 = 0.3989423;
    double a = fabs(z);
    double t = 1.0 / (1.0 + a * p);
    double b = c2 * exp((-z) * (z / 2.0));
    double n = ((((b5 * t + b4) * t + b3) * t + b2) * t + b1) * t;
    n = 1.0 - b * n;
    if (z < 0.0) n = 1.0 - n;
    return n;
};

double option_price_put_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time) {
    double time_sqrt = sqrt(time);
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - sigma * time_sqrt;

    double put_price = K * exp(-r * time) * N(-d2) - S * N(-d1);
    return put_price;
}

double option_price_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time) {
    double time_sqrt = sqrt(time);
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - sigma * time_sqrt;

    double call_price = S * N(d1) - K * exp(-r * time) * N(d2);
    return call_price;
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
    cout << "Recursive Binomial European Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility * 100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "--------------------------------------" << endl;
    double call_price = european_call_option(0, 0);
    cout << "Trinomial Price of an European Call Option = " << call_price << endl;
    cout << "Call Price according to Black-scholes = "<< option_price_call_black_scholes(initial_stock_price, strike_price, risk_free_rate,
        volatility, expiration_time) <<endl;
    double put_price = european_put_option(0, 0);
    cout << "--------------------------------------" << endl;
    cout << "Trinomial Price of an European Put Option = " << put_price << endl;
    cout << "Put Price according to Black-Scholes = " <<
        option_price_put_black_scholes(initial_stock_price, strike_price, risk_free_rate,
            volatility, expiration_time) << endl;
    cout << "--------------------------------------" << endl;

}
