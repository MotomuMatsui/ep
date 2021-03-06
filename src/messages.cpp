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

using namespace std;

void print_banner(){

  string banner = 
    "--------------------------------------------\n"
    " Edge Perturbation Method v1.0 (2018/10/12) \n"
    "                                            \n"
    "    Copyright (c) 2018 Motomu Matsui        \n"
    "    Systematic Biology, xx:xx-xxx, 2018     \n"
    "                                            \n"
    "    http://gs.bs.s.u-tokyo.ac.jp/           \n"
    "--------------------------------------------\n";

  cerr << banner << endl;
}

void print_usage(char*& program){
  cerr << "Usage: " << program << " [-e INTEGER(>=0)] [-r INTEGER(>0)] input > output" << endl;
  cerr << "-e " << "the number of replicates for EP method. Default: 0" << endl;
  cerr << "-r " << "the random seed number for EP method. Default: random number" << endl;
  cerr << "-h " << "show help messages. Default: Off" << endl;
  cerr << "-v " << "show the version. Default: Off" << endl;
}
