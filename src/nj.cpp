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

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <sys/stat.h>

using namespace std;

extern void writeMAT(double*&, ofstream&, int const&);

void NJ(double*& W, string& nj, int const& size, string const& matrix_txt, string& result){

  ofstream ofs(matrix_txt); // Matrix file
  writeMAT(W, ofs, size);

  //NJ method command
  const string R   = "R";
  const string njs = "/user1/scl9/qm/research/2018s/GS/NJs2.R";

  // File I/O
  regex re(R"(_mat\.txt$)"); // Matching to the extention of the input file
  result = regex_replace(matrix_txt, re, "");

  //Commands
  auto cmd = R+" --slave --args "+matrix_txt+" "+result+" < "+njs+" > /dev/null";

  auto info = system(cmd.c_str()); if(info>0){} //NJ method

  auto newick = result+"_njm.nwk";

  ifstream ifs(newick); // NJ tree (newick format)
  string line;
  string strings;

  while(getline(ifs, line)){
    //Split lines
    istringstream stream(line);
    strings += line;
  }

  int N = strings.size();
  stringstream ss;
  int l = 1;

  for(int n=0; n<N; n++){
    auto p = strings[n];
    if(p == 'V'){
    } 
    else if(p == ':'){
      l = 0;
    }
    else if(p == ')'){
      l = 1;
      ss << p;
    }
    else if(p == ','){
      l = 1;	
      ss << p;
    }
    else if(l==1){
      ss << p;
    }
  }

  nj = ss.str();
}
