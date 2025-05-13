# Matrix Exponentiation Benchmark (C++)

This project compares two methods of matrix exponentiation:
1. Repeated squaring (divide-and-conquer)
2. Brute-force multiplication

It generates random square matrices and measures the performance of both methods across increasing exponents.

## ⚙️ Dependencies
This project uses the **Newmat11** C++ matrix library. Make sure it's installed and properly referenced in your include path.

## 📄 Files
- `main.cpp`: Contains all logic for matrix generation, exponentiation, timing, and CSV export

## 📈 Output
Generates a `times.csv` file with the format:
