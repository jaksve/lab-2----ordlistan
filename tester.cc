#include "Ordlistan.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
int main(int argc ,char* argv[])
{
  
  ifstream is (argv[1],ifstream::in);
  if(!is)
    {throw invalid_argument{"no such file."};}
  
  stringstream ss;
  ss<<argv[2];
  
  worder word_list{is,ss.str()};
  cout<<endl;
  cout<<endl;
  word_list.out_data(cout);

  is.close();

     
  return 0;
}
