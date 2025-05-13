//
//  main.cpp
//  Sudoku Integer LP
//
//  Created by Ben Granados on 10/6/23.
//

#include <iostream>

/* Copyright 2022, Gurobi Optimization, LLC */
/*
  Sudoku example.

  The Sudoku board is a 9x9 grid, which is further divided into a 3x3 grid
  of 3x3 grids.  Each cell in the grid must take a value from 0 to 9.
  No two grid cells in the same row, column, or 3x3 subgrid may take the
  same value.

  In the MIP formulation, binary variables x[i,j,v] indicate whether
  cell <i,j> takes value 'v'.  The constraints are as follows:
    1. Each cell must take exactly one value (sum_v x[i,j,v] = 1)
    2. Each value is used exactly once per row (sum_i x[i,j,v] = 1)
    3. Each value is used exactly once per column (sum_j x[i,j,v] = 1)
    4. Each value is used exactly once per 3x3 subgrid (sum_grid x[i,j,v] = 1)

  Input datasets for this example can be found in examples/data/sudoku*.
*/

#include "gurobi_c++.h"
#include <sstream>
#include <fstream>
#include <deque>

using std::vector;
using namespace std;

#define sd 3
#define n (sd*sd)

string itos(int i) {stringstream s; s << i; return s.str(); }

int main(int   argc,
     char *argv[])
{
  try {
    GRBEnv env = GRBEnv();
    GRBModel model = GRBModel(env);

    GRBVar vars[n][n][n];
    int i, j, v;

    // Create 3-D array of model variables

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        for (v = 0; v < n; v++) {
          string s = "G_" + itos(i) + "_" + itos(j) + "_" + itos(v);
          vars[i][j][v] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, s);
        }
      }
    }

    // Add constraints

    // Each cell must take one value

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        GRBLinExpr expr = 0;
        for (v = 0; v < n; v++)
          expr += vars[i][j][v];
        string s = "V_" + itos(i) + "_" + itos(j);
        model.addConstr(expr, GRB_EQUAL, 1.0, s);
      }
    }

    // Each value appears once per row

    for (i = 0; i < n; i++) {
      for (v = 0; v < n; v++) {
        GRBLinExpr expr = 0;
        for (j = 0; j < n; j++)
          expr += vars[i][j][v];
        string s = "R_" + itos(i) + "_" + itos(v);
        model.addConstr(expr == 1.0, s);
      }
    }

    // Each value appears once per column

    for (j = 0; j < n; j++) {
      for (v = 0; v < n; v++) {
        GRBLinExpr expr = 0;
        for (i = 0; i < n; i++)
          expr += vars[i][j][v];
        string s = "C_" + itos(j) + "_" + itos(v);
        model.addConstr(expr == 1.0, s);
      }
    }

    // Each value appears once per sub-grid

    for (v = 0; v < n; v++) {
      for (int i0 = 0; i0 < sd; i0++) {
        for (int j0 = 0; j0 < sd; j0++) {
          GRBLinExpr expr = 0;
          for (int i1 = 0; i1 < sd; i1++) {
            for (int j1 = 0; j1 < sd; j1++) {
              expr += vars[i0*sd+i1][j0*sd+j1][v];
            }
          }

          string s = "Sub_" + itos(v) + "_" + itos(i0) + "_" + itos(j0);
          model.addConstr(expr == 1.0, s);
        }
      }
    }

    //read the file through command line argument instead of cin

      ifstream inputFile(argv[1]);
      if( inputFile.is_open()) {
          char file[10];
          for (i = 0; i < n;i++) {
              inputFile >> file;
              for (j = 0; j<n; j++) {
                  int read = (int) file[j] - 48 - 1;
                  if (read >= 0) {
                      vars[i][j][read].set(GRB_DoubleAttr_LB, 1.0);
                  }
              }
          }
      }
      
      else {
          cout << "Could not open file: " << argv[1] << endl;
          return 1;
      }
      inputFile.close();

    // Optimize model
      
    int number_of_solutions = 0;
      
      while(true) {
          model.optimize();
          
          if (model.get(GRB_IntAttr_Status) == GRB_OPTIMAL) {
              number_of_solutions++;
              cout<< endl;
              
              cout << "Solution #" << number_of_solutions<< endl;
              
              for (i = 0; i < n; i++) {
                  for(j = 0; j < n; j++) {
                      for (v = 0; v < n; v++) {
                          if (vars[i][j][v].get(GRB_DoubleAttr_X) > 0.5) {
                              cout << v+1 << " ";
                          }
                      }
                  }
                  cout << endl;
              }
              GRBLinExpr exclude = 0;
              for (i = 0; i < n; i++) {
                  for(j = 0; j < n; j++) {
                      for (v = 0; v < n; v++) {
                          if (vars[i][j][v].get(GRB_DoubleAttr_X) > 0.5) {
                              exclude += vars[i][j][v];
                          }
                      }
                  }
              }
              model.addConstr(exclude <= n*n - 1);
          }
          else {
              break;
          }
      }
      
    cout << endl;
  } catch(GRBException e) {
    cout << "Error code = " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch (...) {
    cout << "Error during optimization" << endl;
  }

  return 0;
}

