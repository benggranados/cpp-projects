//
//  part1.cpp
//  Assignment10
//
//  Created by Ben Granados on 12/1/23.
//

#include <iostream>
#include <vector>
#include <random>

using namespace std;

int T, n, m;
double r, sigma, S0, K, B;

double simulation_call_price,simulation_put_price, adjustment_call_price, adjustment_put_price, theoretical_call_price, theoretical_put_price;

double max(double a, double b) {
    return (b < a) ? a : b;
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


double option_price_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time) {
    double time_sqrt = sqrt(time);
    
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - sigma * time_sqrt;

    double call_price = S * N(d1) - K * exp(-r * time) * N(d2);
    return call_price;
}


double option_price_put_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time) {
    double time_sqrt = sqrt(time);
    
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - sigma * time_sqrt;

    double put_price = K * exp(-r * time) * N(-d2) - S * N(-d1);
    return put_price;
}

unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator;

double get_uniform() {
std:uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);
    return num;
}

void simulation_price(int T, double r, double sigma, double S0, double K, int n, int m, double B) {
    double time_step = T / static_cast<double>(m);
    double r_step = (r - 0.5 * sigma * sigma) * time_step;
    double vol_step = sigma * sqrt(time_step);

    vector<double> stock(5, S0);
    double total_call_payoff = 0.0, total_put_payoff = 0.0;
    double total_adjusted_call = 0.0, total_adjusted_put = 0.0;
    
    int count = 0;

    for (int i = 0; i < n; ++i) {
        fill(stock.begin() + 1, stock.end(), S0);
        double call_payoff = 0.0, put_payoff = 0.0;

        for (int j = 0; j < m; ++j) {
            double x = get_uniform(), y = get_uniform();
            double a = sqrt(-2.0 * log(x)) * cos(2 * M_PI * y);
            double b = sqrt(-2.0 * log(x)) * sin(2 * M_PI * y);

            for (int k = 1; k <= 4; ++k) {
                double adjustment = k % 2 == 0 ? -vol_step : vol_step;
                adjustment = k > 2 ? adjustment * (k % 2 == 0 ? b : a) : adjustment * a;
                stock[k] = stock[k] * exp(r_step + adjustment);
                stock[k] = stock[k] <= B ? 0 : stock[k];
            }
        }

        for (int k = 1; k <= 4; ++k) {
            if (stock[k] > 0) {
                double difference_call = max(0.0, stock[k] - K);
                double difference_put = max(0.0, K - stock[k]);
                double prob = exp((-2) * log(S0 / B) * log(stock[k] / B) / (sigma * sigma * T));

                call_payoff += difference_call;
                put_payoff += difference_put;
                total_adjusted_call += difference_call * (1 - prob);
                total_adjusted_put += difference_put * (1 - prob);
                count++;
            }
        }

        total_call_payoff += call_payoff / 4;
        total_put_payoff += put_payoff / 4;
    }

    simulation_call_price = total_call_payoff / (n * exp(r * T));
    adjustment_call_price = total_adjusted_call / (count * exp(r * T));
    simulation_put_price = total_put_payoff / (n * exp(r * T));
    adjustment_put_price = total_adjusted_put / (count * exp(r * T));
}

//good
int main(int argc, char* argv[])
{
    sscanf(argv[1], "%d", &T);
    sscanf(argv[2], "%lf", &r);
    sscanf(argv[3], "%lf", &sigma);
    sscanf(argv[4], "%lf", &S0);
    sscanf(argv[5], "%lf", &K);
    sscanf(argv[6], "%d", &n);
    sscanf(argv[7], "%d", &m);
    sscanf(argv[8], "%lf", &B);

    cout << "European Down-and-Out Cotinuous Barrier Options Pricing via Monte Carlo Simulation" << endl;
    cout << "Expiration Time (Years) = " <<T << endl;
    cout << "Risk Free Interest Rate = " << r << endl;
    cout << "Volatility (%age of stock value) = " << sigma * 100 << endl;
    cout << "Initial Stock Price = " << S0 << endl;
    cout << "Strike Price = " << K << endl;
    cout << "Barrier Price = " << B << endl;
    cout << "Number of Trials = " << n << endl;
    cout << "Number of Divisions = " << m << endl;
    cout << "--------------------------------------" << endl;
    
    simulation_price(T, r, sigma, S0, K, n, m, B);
    
    theoretical_call_price = option_price_call_black_scholes(S0, K, r, sigma, T);
    theoretical_put_price = option_price_put_black_scholes(S0, K, r, sigma, T);
    
    cout << "--------------------------------------" << endl;
    cout << "The average Call Price by explicit simulation  = " << simulation_call_price << endl;
    cout << "The call price using the (1-p)-adjustment term = " << adjustment_call_price << endl;
    cout << "Theoretical Call Price                         = " << theoretical_call_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "The average Put Price by explicit simulation  = " << simulation_put_price << endl;
    cout << "The put price using the (1-p)-adjustment term = " << adjustment_put_price << endl;
    cout << "Theoretical Put Price                         = " << theoretical_put_price << endl;
    cout << "--------------------------------------" << endl;
    
    return 0;

}
