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

void EP(double* const (&oW), function<double()>& R, int const& size){

  // Edge perturbation
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      auto a = oW[i*size+j];

      if(a==0){
	cout << a << "\t"; // Graph topology is not changed
      }
      else{
	auto b = gev(R(), a);
	b = 
	  (b>1)? 1: // b: Similarity scores perturved according to Generalized Extreme Value distribution
	  (b<0)? 0: // E[n]: Perturved sequence similarity score
	  b; // 0 <= E[n] <= 1

	cout << b << "\t"; // Graph topology is not changed
      }
    }
    cout << endl;
  }
  cout << endl;
}
