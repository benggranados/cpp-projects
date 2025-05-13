# Optimal Card Game Strategy (C++)

This project solves a two-player recursive card game where players alternate turns selecting from a shared set of cards. Each player seeks to **maximize their score** under optimal play conditions, and the value of the game is computed using dynamic programming.

## 🃏 How It Works
- Game starts with `n` cards (even number)
- Players pick alternately from either end
- Each player plays optimally
- The final result is the **value of the game** under perfect strategy

## 📄 Files
- `cardgame.cpp`: Main execution logic and input handling
- `cardgame.h`: Core recursive logic and memoization structure

## ▶️ How to Run

### Compile:
```bash
g++ cardgame.cpp -o cardgame
