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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <regex>
#include <unordered_map>
#include <random>   
#include <functional>

using namespace std;

/// messages.cpp
extern void print_banner();
extern void print_usage(char*&);

// format.cpp
extern void readMAT(ifstream&, double*&, int&);

// ep.cpp
extern void EP(double* const&, function<double()>&, int const&);

int main(int argc, char* argv[]){

  /*/Getopt/*/
  int ep_num = 1; // -e
  int seed   = 0; // -r

  opterr = 0; // default error messages -> OFF
  int opt;
  regex renum(R"(^[\d\.]+$)"); // -e/-r option requires an integer/flout number
  while ((opt = getopt(argc, argv, "shve:r:")) != -1){
    if(opt == 'e'){ // OK! (./gs -e 100 IN.fst)
      if(regex_match(optarg, renum)){
        ep_num = atoi(optarg);
      }
      else{ // NG! (./gs -e hundred IN.fst)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -e requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
    }
    else if(opt == 'r'){ // OK! (./gs -r 12345 IN.fst)
      if(regex_match(optarg, renum)){
        seed = atoi(optarg);
      }
      else{ // NG! (./gs -r one_two_three IN.fst)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -r requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
    }
    else if(opt == 'h'){ // HELP message (./gs -h)
      /*PRINT*/ print_banner();
      /*PRINT*/ print_usage(argv[0]);
      return 0;
    }
    else if(opt == 'v'){ // Version (./gs -v)
      /*PRINT*/ print_banner();
      return 0;
    }
    else if (opt == '?'){
      if(optopt == 'e'){ // NG! (./gs IN.fst -e)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -e requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
      else if(optopt == 'r'){ // NG! (./gs IN.fst -r)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -r requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
      else{ // NG! (./gs -Z)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << argv[0] << ": invalid option\n" <<  endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
    }
  }  
  
  /*/Input file/*/
  string input = "";
  if(optind < argc){ // OK!
    input = argv[optind];
  }
  else{ // NG!
    /*PRINT*/ print_banner();
    /*PRINT*/ cerr << argv[0] << " requires an input file (matrix).\n" << endl;
    /*PRINT*/ print_usage(argv[0]);
    return -1;
  }

  /*/File I/O/*/
  auto original_file = string(input);
  ifstream ifs1(original_file); // Matrix file (original)
  if(ifs1.fail()){
    /*PRINT*/ cerr << "\nCannot access " << original_file << "!" << endl;
    return -1;
  }

  /*/Parsing matrix file/*/
  double* W;     // Distance matrix
  int size;      // Row size of W (W is a synmetry matrix)
  readMAT(ifs1, W, size); 
         // ifs1: INPUT (original matrix file)
         // W:    OUTPUT (matrix)
         // size: # of sequence = row size of sequence similarity matrix

  /*PRINT*/ cout << "[Original]" << endl;
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      cout << W[i*size+j] << "\t";
    }
    cout << endl;
  }
  cout << endl;  
  
  /*/EP method/*/
  if(ep_num>0){
    // Random number generator (Uniform distribution->Mersenne Twister)
    function<double()> R;
    uniform_real_distribution<double> urd(0,1);    // uniform distributed random number

    if(seed>0){
      mt19937 mt(static_cast<unsigned int>(seed)); // mersenne twister
      R = bind(urd, ref(mt));                      // random number generator    
    }
    else{
      random_device rd;                            // random seed
      mt19937 mt(rd());                            // mersenne twister
      R = bind(urd, ref(mt));                      // random number generator        
    }    

    for(int n=1; n<=ep_num; n++){
      /*PRINT*/ cout << "[" << n << "]" << endl;

      EP(W, R, size);
          // W: INPUT (sequence similarity matrix)
          // R: random number generator
    }
  }

  return 0;
}
