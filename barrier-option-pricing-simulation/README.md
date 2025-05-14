# Barrier Option Pricing via Monte Carlo Simulation (C++)

This project prices **European down-and-out barrier options** using Monte Carlo simulation and compares the results with **Black-Scholes analytical prices**. It includes an adjustment based on survival probability for paths that hit the barrier.

## 🧮 Concepts Used
- Monte Carlo Simulation
- Lognormal asset price modeling
- Continuous barrier handling
- Black-Scholes analytical pricing
- Probability-based payoff adjustments
- Gaussian sampling (Box-Muller transform)

## 📄 Files
- `part1.cpp`: Main implementation of the simulation and Black-Scholes comparison

## ▶️ How to Run

### Compile:
```bash
g++ part1.cpp -o barrier_pricer -std=c++11
