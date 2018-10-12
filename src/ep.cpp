/********************************************\
| Edge Perturbation Method v1.0 (2018/10/12) |
|                                            |
|  Copyright (c) 2015-2018 Motomu Matsui     |
|      Distributed under the GNU GPL         |
|                                            |
|      Matsui M and Iwasaki W (2018)         |
|      Systematic Biology, xx:xx-xx.         |
|                                            |
|      http://gs.bs.s.u-tokyo.ac.jp/         |
\********************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

using namespace std;

//ep_functions.cpp
extern double gev(double const&, double const&);

int EP(double* const (&oW), double* (&W), function<double()>& R, int const& size){

  // Edge perturbation
  int N = size*size;
  double* W = new double[N]();
  for(int n = 0; n < N; n++){
    double a = oW[n];
    if(a==0){
      W[n] = 0; // Graph topology is not changed
    }
    else{
      auto b = gev(R(), a);
      W[n] = 
        (b>1)? 1: // b: Similarity scores perturved according to Generalized Extreme Value distribution
        (b<0)? 0: // E[n]: Perturved sequence similarity score
	b; // 0 <= E[n] <= 1
    }
  }

  return 1;
}
