# Option Pricing Models – European & American (C++)

This project implements option pricing models in C++ for both European and American options using recursive trinomial trees. It also compares European option prices with the analytical Black-Scholes formula.

## 🔹 Files
- `European.cpp` – Prices European call and put options using a trinomial tree and compares results with Black-Scholes
- `American.cpp` – Prices American call and put options using a recursive trinomial tree

## 🧠 Key Concepts
- Trinomial tree modeling
- Recursive dynamic programming
- European vs. American option pricing
- Black-Scholes formula (for benchmarking)
- Numerical stability and probability calibration

## ▶️ How to Run

### Compile:
```bash
g++ European.cpp -o european
g++ American.cpp -o american
