# Sudoku Solver using Integer Programming (Gurobi + C++)

This project implements a Sudoku solver using Integer Linear Programming (ILP) and the Gurobi optimization engine. It formulates the Sudoku puzzle as a 3D binary variable model and finds all valid solutions.

## 🚀 Features
- Solves Sudoku using mathematical optimization
- Finds multiple valid solutions (if any)
- Uses Gurobi's C++ API for constraint modeling

## 📄 Files
- `gurobi_sudoku.cpp`: Main program logic
- `sample_input.txt`: Example 9x9 Sudoku input (one line per row)

## 🔧 How It Works
The solver creates a 3D binary variable `x[i][j][v]` to represent whether cell `(i, j)` holds value `v+1`. Constraints enforce that:
1. Each cell has one value
2. Each number appears once per row, column, and 3×3 box

## ▶️ How to Run

1. **Compile** (you must have Gurobi and its C++ API configured):
```bash
g++ gurobi_sudoku.cpp -o gurobi_solver -I/path/to/gurobi/include -L/path/to/gurobi/lib -lgurobi_c++ -lgurobiXX
