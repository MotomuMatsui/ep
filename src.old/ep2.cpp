/******************************************\
| Graph Splitting Method v2.0 (2018/06/01) |
|                                          |
| Copyright (c) 2015-2018 Motomu Matsui    |
|     Distributed under the GNU GPL        |
|                                          |
|     Matsui M and Iwasaki W (2018)        |
|     Systematic Biology, xx:xx-xx.        |
|                                          |
|     http://gs.bs.s.u-tokyo.ac.jp/        |
\******************************************/

#include <fstream>
#include <random>   
#include <cmath> 
#include <functional>
#include <algorithm>
#include <vector>
#include <tuple>
#include <sstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <regex>

using namespace std;

//sc.cpp (spectral clustering)
extern tuple<vector<int>,vector<int>> spectral_clustering(double* const&, vector<int> const&, int const&);

//gs_functions.cpp
extern void sedVECTOR(vector<int>&, vector<int> const&, int const);
extern double simI(double* const&, vector<int> const&, int const);
extern int whichMIN(vector<double> const&);
extern double gev(double const&, double const&);

//format.cpp
extern void countEP(string const&, unordered_map<string, double>&);
extern void writeMAT(double*&, ofstream&, int const&);

void EP2(double* const (&W), unordered_map<string, double>& ep, function<double()>& R, int const& size, string const& matrix_tmp){

  // Edge perturbation
  int N = size*size;
  double* E = new double[N]();
  for(int n = 0; n < N; n++){
    double a = W[n];
    if(a==0){
      E[n] = 0; // Graph topology is not changed
    }
    else{
      auto b = gev(R(), a);
      E[n] = 
	(b>1)? 1: // b: Similarity scores perturved according to Generalized Extreme Value distribution
	(b<0)? 0: // E[n]: Perturved sequence similarity score
	       b; // 0 <= E[n] <= 1
    }
  }

  ofstream ofs(matrix_tmp); // Matrix file
  writeMAT(E, ofs, size);

  //NJ method command
  const string Rcmd = "R";
  const string njs  = "/user1/scl9/qm/research/2018s/GS/NJs2.R";

  // File I/O
  regex re(R"(_mat_tmp\.txt$)"); // Matching to the extention of the input file
  auto result = regex_replace(matrix_tmp, re, "_tmp");

  //Commands
  auto cmd  = Rcmd+" --slave --args "+matrix_tmp+" "+result+" < "+njs+" > /dev/null";
  auto info = system(cmd.c_str()); if(info>0){} //NJ method

  auto newick_nj = result+"_njm.nwk";
  countEP(newick_nj, ep);

  //Free
  delete[] E;
}
