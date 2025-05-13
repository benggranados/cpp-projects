# K-Peg Tower of Hanoi Solver (C++)

This project implements a generalized solution to the classic Tower of Hanoi puzzle using **K pegs**. It extends the traditional 3-peg recursive approach to support any number of pegs and disks.

## 📄 Files
- `K_Hanoi.cpp` – Main driver that prompts for user input and calls the solver
- `K_Hanoi.h` – Header file that defines the recursive logic inside the `Towers` class

## 💡 Concepts Demonstrated
- Recursive problem-solving
- Divide-and-conquer strategy
- Minimal move optimization for K > 3 pegs
- Algorithm design and modular C++

## ▶️ How to Run

### Compile:
```bash
g++ K_Hanoi.cpp -o hanoi
